#include "Server.h"
#include "Packets.h"
#include "PacketManager.h"
#include "login_request.pb.h"
#include "register_request.pb.h"
#include "cAuthService.h"

#include <iostream>


cAuthService* authService;

Server::Server(PCSTR port)
{
    this->port = port;
    this->connectionSocket = INVALID_SOCKET; // This socket is used to listen for incoming connections
    this->acceptSocket = INVALID_SOCKET;
}

Server::~Server()
{
    for (cAuthRequester* requester : requesters)
    {
        delete requester;
    }

    requesters.clear();
}

bool Server::Initialize()
{
    printf("Initializing server...\n");

    int result;
    struct addrinfo* info = NULL;
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints)); // Fills the hints block of memory with 0's
    hints.ai_family = AF_INET;  // Specify address fmaily
    hints.ai_socktype = SOCK_STREAM; // Assign socket type
    hints.ai_protocol = IPPROTO_TCP; // Use TCP for protocol
    hints.ai_flags = AI_PASSIVE;

    // Resolve port & address
    result = getaddrinfo(NULL, this->port, &hints, &info);
    if (result != 0)
    {
        printf("getaddrinfo failed with error: %d\n", result);
        WSACleanup();
        return false;
    }

    this->connectionSocket = socket(info->ai_family, info->ai_socktype, info->ai_protocol); // Assign our socket with our address info properties
    if (this->connectionSocket == INVALID_SOCKET)
    { // We failed...
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(info);
        WSACleanup();
        return false;
    }

    // Attempt to bind our connection socket
    result = bind(this->connectionSocket, info->ai_addr, (int)info->ai_addrlen);
    if (result == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(info);
        closesocket(this->connectionSocket);
        WSACleanup();
        return false;
    }

    freeaddrinfo(info); // Socket was bound, we don't need this anymore.

    // Listen for activing on our connection socket
    result = listen(this->connectionSocket, SOMAXCONN); // Puts the connection socket in a state where it is listening for an incoming connection
    if (result == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(this->connectionSocket);
        WSACleanup();
        return false;
    }

    // Force our connection socket to be non-blocking
    DWORD nonBlock = 1;
    result = ioctlsocket(this->connectionSocket, FIONBIO, &nonBlock);
    if (result == SOCKET_ERROR)
    {
        printf("Failed to make connection socket non-blocking! %d\n", WSAGetLastError());
        closesocket(this->connectionSocket);
        WSACleanup();
        return false;
    }

    //Start authService
    authService = new cAuthService();

    return true;
}

void Server::Start()
{
    int result;
    int total;
  
    DWORD flags;
    DWORD bytesReceived;
    DWORD nonBlock = 1;

    FD_SET readSet;

    printf("Server started!\n");
    while (true)
    {
        timeval timeoutValue = { 0 };
        timeoutValue.tv_sec = 2; // 2 second timeout value

        FD_ZERO(&readSet); // Wipe out our read set
        FD_SET(connectionSocket, &readSet); // Add connection socket to the read set (AKA: Keep listening for connections)

        // Add all client sockets to the read set
        for (cAuthRequester* requester : requesters)
        {
            FD_SET(requester->socket, &readSet);
        }

        // Find the sockets that need updating
        total = select(0, &readSet, NULL, NULL, &timeoutValue);
        if (total == SOCKET_ERROR) {
            printf("select() has failed! %d\n", WSAGetLastError());
            return;
        }

        // Handle incoming connections
        if (FD_ISSET(connectionSocket, &readSet))
        {
            total--;
            this->acceptSocket = accept(connectionSocket, NULL, NULL); // Permits the incoming connection
            if (acceptSocket == INVALID_SOCKET)
            {
                printf("Failed to accept socket! %d\n", WSAGetLastError());
                break;
            }

            // Make the newly accept socket non-blocking
            result = ioctlsocket(this->acceptSocket, FIONBIO, &nonBlock);
            if (result == SOCKET_ERROR)
            {
                printf("Failed to make accepted socket non-blocking! %d\n", WSAGetLastError());
            }
            else
            {
                cAuthRequester* requester = new cAuthRequester();
                requester->socket = this->acceptSocket;
                this->requesters.push_back(requester);
                printf("New client has connected on socket %d.\n", (int)this->acceptSocket);
            }
        }

        for (int i = this->requesters.size() - 1; i >= 0; i--)
        {
            cAuthRequester* requester = requesters[i];

            // Check if we are in the read set (AKA: Check if socket sent some new data)
            if (FD_ISSET(requester->socket, &readSet))
            {
                total--;
                DWORD flags = 0;
                bytesReceived = recv(requester->socket, requester->buffer.data, requester->buffer.Length(), flags); // Recieve the data (THIS IS BLOCKING, which is we we only call it when the socket has new data)
                if (bytesReceived == SOCKET_ERROR)
                {
                    printf("recv() has failed!\n");
                    printf("Client disconnected!\n");
                    this->requesters[i] = requesters[this->requesters.size() - 1];
                    this->requesters.pop_back();
                    continue;
                }
                else if (bytesReceived == 0) // Client left
                {
                    // remove client from vector array 
                    printf("Client disconnected!\n");
                    this->requesters[i] = requesters[this->requesters.size() - 1];
                    this->requesters.pop_back();
                    continue;
                }

                int packetHeader = requester->buffer.ReadInt();
                PacketManager::GetInstance()->HandlePacket(*this, requester, packetHeader);
                requester->buffer.Clear();
            }
        }
    }

    ShutDown();
}

void Server::ShutDown()
{
    printf("Server shutting down...\n");
    closesocket(this->acceptSocket);
    closesocket(this->connectionSocket);
    for (cAuthRequester* requester : requesters)
    {
        closesocket(requester->socket);
    }
}


void Server::SendToClient(cAuthRequester* requester, char* dataToSend, int dataLength)
{
    int result;
    result = send(requester->socket, dataToSend, dataLength, 0);
    if (result == SOCKET_ERROR)
    {
        printf("send() has failed!");
    }
}


//std::map<std::string, std::vector<Client*> > rooms;
void Server::Register(cAuthRequester* requester, netutils::PacketRegister& packet)
{
    //Using Google proto
    auth::RegisterRequest registerRequest;
    registerRequest.ParseFromString(packet.data);

    //Calls the service to register the client
    RegisterResponse response = authService->Register(registerRequest);

    //Prepare response
    netutils::PacketRegisterResponse responsePacket;

    std::string output = {};
    response.SerializeToString(&output);

    responsePacket.dataLength = output.length();
    responsePacket.data = output;

    netutils::Buffer buffer(responsePacket.GetSize());

    buffer.WriteInt(packet.header.packetType);
    buffer.WriteInt(packet.dataLength);
    buffer.WriteString(packet.data);
    //Send to the client the register response
    SendToClient(requester, buffer.data, buffer.Length());
}

void Server::Login(cAuthRequester* requester, netutils::PacketLogin& packet)
{
    //Using Google proto
    auth::LoginRequest loginRequest;
    loginRequest.ParseFromString(packet.data);

    //Calls the service to authenticate the client
    LoginResponse response = authService->Login(loginRequest);

    //Prepare authentication response
    netutils::PacketLoginResponse responsePacket;

    std::string output = {};
    response.SerializeToString(&output);

    responsePacket.dataLength = output.length();
    responsePacket.data = output;

    netutils::Buffer buffer(responsePacket.GetSize());

    buffer.WriteInt(packet.header.packetType);
    buffer.WriteInt(packet.dataLength);
    buffer.WriteString(packet.data);
    //Send to the client the authentication response
    SendToClient(requester, buffer.data, buffer.Length());
}
