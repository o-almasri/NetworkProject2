//ss
#include "Client.h"
#include "Packets.h"
#include "PacketManager.h"



#include <stdio.h>
#include <conio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512 // Default buffer length of our buffer in characters


auth::LoginRequest loginReq;
auth::RegisterRequest registerReq;


Client::Client(PCSTR serverIp, PCSTR port)
	: buffer(DEFAULT_BUFLEN)
{
	this->serverIp = serverIp;
	this->serverPort = port;
	this->serverSocket = INVALID_SOCKET;
	this->running = false;
}

Client::~Client()
{

}

bool Client::Initialize()
{
	std::cout << "Initializing client..." << std::endl;
	struct addrinfo* infoResult = NULL; // Holds the address information of our server
	struct addrinfo* ptr = NULL;
	struct addrinfo hints;

	int result;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve server
	result = getaddrinfo(this->serverIp, this->serverPort, &hints, &infoResult);
	if (result != 0)
	{
		printf("getaddrinfo failed with error: %d\n", result);
		WSACleanup();
		return 1;
	}

	// Try to connect to an address
	for (ptr = infoResult; ptr != NULL; ptr = ptr->ai_next)
	{
		// Create a SOCKET for connecting to server
		this->serverSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (this->serverSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		result = connect(this->serverSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (result == SOCKET_ERROR)
		{
			closesocket(this->serverSocket);
			this->serverSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(infoResult); // Done connecting, free from memory

	if (this->serverSocket == INVALID_SOCKET)
	{
		printf("Failed to connect to server!\n");
		WSACleanup();
		return 1;
	}

	// Force our connection socket to be non-blocking
	DWORD nonBlock = 1;
	result = ioctlsocket(this->serverSocket, FIONBIO, &nonBlock);
	if (result == SOCKET_ERROR)
	{
		printf("Failed to make connection socket non-blocking! %d\n", WSAGetLastError());
		closesocket(this->serverSocket);
		WSACleanup();
		return false;
	}

	printf("Connection successful!\n");
	return true;
}

void Client::Start()
{

	/*this->SendToServer(this->buffer.data, this->buffer.Length());
	this->buffer.Clear();*/

	/*registerReq.set_email("fafasfaf");
		loginReq.set_email("fafasfaf");
		loginReq.set_password("fafasfaf");*/



	int total;
	int result;

	DWORD flags;
	DWORD bytesReceived;

	FD_SET readSet;

	this->running = true;
	bool roomChange = false;
	while (this->running)
	{



		if (_kbhit())
		{
			char key = _getch();

		}

		FD_ZERO(&readSet); // Wipe out our read set
		FD_SET(this->serverSocket, &readSet); // Add connection socket to the read set (AKA: Keep listening for connections)

		timeval timeoutValue = { 0 };

		// Find the sockets that need updating
		total = select(0, &readSet, NULL, NULL, &timeoutValue);
		if (total == SOCKET_ERROR) {
			printf("select() has failed! %d\n", WSAGetLastError());
			this->running = false;
			break;
		}

		// Handle incoming connections
		if (FD_ISSET(this->serverSocket, &readSet))
		{
			total--;
			DWORD flags = 0;

			bytesReceived = recv(this->serverSocket, this->buffer.data, this->buffer.Length(), flags); // Recieve the data (THIS IS BLOCKING, which is we we only call it when the socket has new data)
			if (bytesReceived == SOCKET_ERROR)
			{
				printf("recv() has failed!");

				if (WSAGetLastError() == 10054)
				{
					printf("Disconnected from server!\n");
					this->running = false;
					break;
				}

			}
			else if (bytesReceived == 0)
			{
				printf("Disconnected from server!\n");
				this->running = false;
				break;
			}

			int packetHeader = buffer.ReadInt();
			PacketManager::GetInstance()->HandlePacket(*this, this->serverSocket, packetHeader);
			this->buffer.Clear();
		}
	}

	this->ShutDown();
}

void Client::ShutDown()
{
	std::cout << "Client shutting down..." << std::endl;

	int result;
	// Shut down the connection 
	result = shutdown(this->serverSocket, SD_SEND);
	if (result == SOCKET_ERROR)
	{
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(this->serverSocket);
		return;
	}

	// Cleanup
	closesocket(this->serverSocket);
}

bool Client::SendToServer(char* data, int dataLength)
{
	int result;
	result = send(this->serverSocket, data, dataLength, 0);
	if (result == SOCKET_ERROR)
	{
		printf("Failed to send message: %d\n", WSAGetLastError());
		closesocket(this->serverSocket);
		return false;
	}

	return true;
}



//add a state variable to the client
void Client::statemachine(char key) {
	system("CLS");
	switch (state) {
	case BEGIN: // user can login or register 
		std::cout << "Press 1 To Login  || Press 2 to Register" << std::endl;
		if (key == 49)
		{
			// 1 = user wants to login 
			state = 1;
		}
		else if (key == 50) //TODO: change key code to be num 2 here
		{
			//user wants to register
			state = 4;
		}
		else if (key == 27) // escape key
		{
			//shutDown
			running = false;
		}
		break;

		//user choose to login 
	case LOGIN_INPUT_EMAIL: // input username to login 
		std::cout << "Input your email" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 27) // escape key
		{
			//send user back to state 0
			state = 0;
		}
		else if (key == 13) // enter
		{

			// send user to enter password
			std::string msg(message.begin(), message.end());
			loginReq.set_email(msg);
			message.clear();

			state = 2;
		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;
	case LOGIN_INPUT_PASSWORD: // input pass to login 
		std::cout << "Input your Password" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 27) // escape key
		{
			//send user back to state 1 to enter the username again
			state = 1;
		}
		else if (key == 13) // enter
		{
			//send msg to server with username and password

			netutils::PacketLogin packet;
			buffer.WriteInt(packet.header.packetType); // write packet header inside the buffer

			std::string msg(message.begin(), message.end());
			loginReq.set_password(msg);
			loginReq.set_requestid(5);
			//TODO: serialize the msg to a buffer then send it to the server
			std::string tempData;
			loginReq.SerializeToString(&tempData);
			buffer.WriteString(tempData);
			SendToServer(this->buffer.data, this->buffer.Length());
			message.clear();
			state = 3;


		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}


		break;
	case LOGIN_WAITING_RESPONSE: // user cant do anything until the server complete the proccessing 
		std::cout << "attempting to login .." << std::endl;
		break;


		//user choose to Register
	case REGISTER_INPUT_USERNAME: // input username to Register
		std::cout << "Input your Name" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 27) // escape key
		{
			//send user back to state 0
			state = 0;
		}
		else if (key == 13) // enter
		{
			// send user to enter password
			//TODO : save the username 
			// send user to enter password
			std::string msg(message.begin(), message.end());
			registerReq.set_name(msg);
			message.clear();


			state = 5;
		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;
	case REGISTER_INPUT_PASSWORD: // input pass to Register 
		std::cout << "Input New password to Register" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 27) // escape key
		{
			//send user back to state 1 to enter the username again
			state = 1;
		}
		else if (key == 13) // enter
		{
			//send msg to server with username and password
			std::string msg(message.begin(), message.end());
			registerReq.set_password(msg);
			message.clear();

			state = 6;
		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;

	case REGISTER_INPUT_EMAIL: // input pass to Register 
		std::cout << "Input your EMAIl" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 27) // escape key
		{
			//send user back to state 1 to enter the username again
			state = 1;
		}
		else if (key == 13) // enter
		{
			std::string msg(message.begin(), message.end());
			registerReq.set_email(msg);
			message.clear();

			state = 7;
		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;

	case REGISTER_INPUT_AGE: // input pass to Register 
		std::cout << "Input your Age" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 27) // escape key
		{
			//send user back to state 1 to enter the username again
			state = 1;
		}
		else if (key == 13) // enter
		{
			netutils::PacketRegister packet;
			buffer.WriteInt(packet.header.packetType); // write packet header inside the buffer
			//send msg to server with username and password
			std::string msg(message.begin(), message.end());
			registerReq.set_age(stoi(msg));
			message.clear();
			registerReq.set_requestid(4);
			std::string tempData;
			registerReq.SerializeToString(&tempData);
			buffer.WriteString(tempData);
			SendToServer(this->buffer.data, this->buffer.Length());
			message.clear();


			state = 8;
		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;

	case REGISTER_WAITING_RESPONSE: // user cant do anything until the server complete the proccessing 
		std::cout << "Waiting for Server Response" << std::endl;
		break;


		//user is logged in
	case ROOM_SELECTION: // input chat room to enter
		std::cout << "Enter Room Name:" << std::endl;
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 13) //enter
		{
			//send join room request to server


			//netutils::PacketJoinRoom packetJoinRoom;
			//packetJoinRoom.roomNameLength = this->currentRoom.size();
			//packetJoinRoom.roomName = this->currentRoom;
			//packetJoinRoom.nameLength = this->name.size();
			//packetJoinRoom.name = this->name;

			//this->buffer.WriteInt(packetJoinRoom.header.packetType);
			//this->buffer.WriteInt(packetJoinRoom.roomNameLength);
			//this->buffer.WriteString(packetJoinRoom.roomName);
			//this->buffer.WriteInt(packetJoinRoom.nameLength);
			//this->buffer.WriteString(packetJoinRoom.name);

			//this->SendToServer(this->buffer.data, this->buffer.Length());
		}
		else if (key == 27) // escape key
		{
			//esc = logout here 
			state = 0;

		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;
	case CHATTING: // you are in a chatting room just chat
		if (key == 8 && !message.empty()) // Backspace
		{
			message.pop_back();
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}
		else if (key == 13) //enter
		{
			//send chat request to server
			std::string msg(message.begin(), message.end());
			netutils::PacketSendMessage packet;
			packet.messageLength = msg.size();
			packet.message = msg;

			netutils::Buffer buffer(packet.GetSize());
			buffer.WriteInt(packet.header.packetType);
			buffer.WriteInt(packet.messageLength);
			buffer.WriteString(packet.message);


		}
		else if (key == 27) // escape key
		{
			//esc = go back to room joining state
			state = 9;
			//TODO: send leave room packet to server

	/*		netutils::PacketLeaveRoom packet;
			packet.roomNameLength = this->currentRoom.size();
			packet.roomName = this->currentRoom;
			packet.namelength = this->name.size();
			packet.name = this->name;

			netutils::Buffer buffer(packet.GetSize());
			buffer.WriteInt(packet.header.packetType);
			buffer.WriteInt(packet.roomNameLength);
			buffer.WriteString(packet.roomName);
			buffer.WriteInt(packet.namelength);
			buffer.WriteString(packet.name);

			this->SendToServer(this->buffer.data, this->buffer.Length());*/
		}
		else
		{
			message.push_back(key);
			std::string msg(message.begin(), message.end());
			std::cout << "\r" << msg;
		}

		break;

	}//switch 


}