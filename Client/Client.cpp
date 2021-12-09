//ss
#include "Client.h"
#include "Packets.h"
#include "PacketManager.h"
#include "login_request.pb.h"
#include "register_request.pb.h"


#include <stdio.h>
#include <conio.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512 // Default buffer length of our buffer in characters

const char ESCAPE = 27;
const char BACKSPACE = 8;
const char ENTER = 13;
const char KEY_1 = 49;
const char KEY_2 = 50;

auth::LoginRequest loginReq;
auth::RegisterRequest registerReq;


Client::Client(PCSTR serverIp, PCSTR port)
	: buffer(DEFAULT_BUFLEN)
{
	this->serverIp = serverIp;
	this->serverPort = port;
	this->serverSocket = INVALID_SOCKET;
	this->running = false;
	this->LastMsg = "";
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

	int total;
	int result;

	DWORD flags;
	DWORD bytesReceived;

	FD_SET readSet;

	this->running = true;
	bool roomChange = false;
	state = states::BEGIN;
	std::cout << "Welcome, Press Space to start..." << std::endl;
	while (this->running)
	{

		if (_kbhit())
		{
			char key = _getch();
			statemachine(key);
		}

		ReceiveMessage(bytesReceived, readSet, total);

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

void Client::CleanChar()
{
	if (!message.empty())
	{
		message.pop_back();
		std::string msg(message.begin(), message.end());
		std::cout << "\r" << msg;
	}
}

void Client::AddMessage(char& key)
{
	
	message.push_back(key);
	std::string msg(message.begin(), message.end());
	std::cout << "\r" << msg;
}

int Client::GenerateRequestId()
{
	//Get current timestamp as ID
	unsigned int uiTime = static_cast<unsigned int>(time(NULL));
	return uiTime;
}

void Client::ReceiveMessage(DWORD& bytesReceived, FD_SET& readSet, int& total)
{
	FD_ZERO(&readSet); // Wipe out our read set
	FD_SET(this->serverSocket, &readSet); // Add connection socket to the read set (AKA: Keep listening for connections)

	timeval timeoutValue = { 0 };

	// Find the sockets that need updating
	total = select(0, &readSet, NULL, NULL, &timeoutValue);
	if (total == SOCKET_ERROR) {
		printf("select() has failed! %d\n", WSAGetLastError());
		this->running = false;
		return;
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
				return;
			}

		}
		else if (bytesReceived == 0)
		{
			printf("Disconnected from server!\n");
			this->running = false;
			return;
		}

		int packetHeader = buffer.ReadInt();
		PacketManager::GetInstance()->HandlePacket(*this, this->serverSocket, packetHeader);
		this->buffer.Clear();
	}
}

void Client::ResetScreen()
{
	message.clear();
	system("CLS");
}

void Client::set_State(int x) {

	if (x > 10 || x < 0)
	{
		state = 0;
		printf("Client.set_State(int x) Error : Trying to hop into unRegistered State %d",x );
		printf("State is Force set to 0 ");
	}
	else {
		state = x;
		
		statemachine(x);
		CleanChar();
	}
	
}

void Client::set_name(std::string newName)
{
	name = newName;
}

//add a state variable to the client
void Client::statemachine(char key) {
	system("CLS");
	std::cout << LastMsg << std::endl;
	switch (state) {
	case BEGIN: // user can login or register 
	{
		std::cout << "Press 1 To Login  || Press 2 to Register" << std::endl;
		if (key == KEY_1 || key == KEY_2)
		{
			if (message.size() == 1) CleanChar();
			AddMessage(key);
		}
		else if(key == ENTER)
		{
			if (message.at(0) == KEY_1)
			{
				//Start Login
				state = states::LOGIN_INPUT_EMAIL;
				ResetScreen();
				std::cout << "Input your email" << std::endl;
			}
			else
			{
				//Start register
				state = states::REGISTER_INPUT_USERNAME;
				ResetScreen();
				std::cout << "Input your Name" << std::endl;
			}
		}
		else if (key == ESCAPE)
		{
			running = false;
		}
		break;
	}
	//user choose to login 
	case LOGIN_INPUT_EMAIL: // input username to login 
	{	
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			std::string msg(message.begin(), message.end());
			loginReq.set_email(msg);
			
			state = states::LOGIN_INPUT_PASSWORD;
			ResetScreen();
			std::cout << "Input your Password" << std::endl;
		}
		else AddMessage(key);
		break;
	}		
	case LOGIN_INPUT_PASSWORD: // input pass to login 
	{
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			//send msg to server with username and password
			netutils::PacketLogin packet;
			buffer.WriteInt(packet.header.packetType);
			std::string msg(message.begin(), message.end());
			loginReq.set_password(msg);
			loginReq.set_requestid(GenerateRequestId());
			std::string tempData;
			loginReq.SerializeToString(&tempData);
			buffer.WriteInt(tempData.length());
			buffer.WriteString(tempData);
			this->buffer.data;
			SendToServer(this->buffer.data, this->buffer.Length());

			state = LOGIN_WAITING_RESPONSE;
			ResetScreen();
			std::cout << "attempting to login .." << std::endl;
		}
		else AddMessage(key);
		break;

	}		
	case LOGIN_WAITING_RESPONSE: // user cant do anything until the server complete the proccessing 
	{
		if (key == ESCAPE)
		{
			state = states::BEGIN;
			std::cout << "Exiting Option..." << std::endl;
		}
		break;
	}	
		//user choose to Register
	case REGISTER_INPUT_USERNAME: // input username to Register
	{
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			std::string msg(message.begin(), message.end());
			registerReq.set_name(msg);
			message.clear();

			ResetScreen();
			state = states::REGISTER_INPUT_EMAIL;
			std::cout << "Input your EMAIL" << std::endl;
			
		}
		else AddMessage(key);
		break;
	}
	case REGISTER_INPUT_EMAIL:
	{
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			std::string msg(message.begin(), message.end());
			registerReq.set_email(msg);
			message.clear();

			state = states::REGISTER_INPUT_PASSWORD;
			ResetScreen();
			std::cout << "Input New password to Register" << std::endl;
		}
		else AddMessage(key);
		break;
	}
	case REGISTER_INPUT_PASSWORD: // input pass to Register 
	{
	
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			std::string msg(message.begin(), message.end());
			registerReq.set_password(msg);

			state = states::REGISTER_INPUT_AGE;
			ResetScreen();
			std::cout << "Input your Age" << std::endl;
		}
		else AddMessage(key);
		break;
	}
	
	case REGISTER_INPUT_AGE:
	{
		
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			netutils::PacketRegister packet;
			buffer.WriteInt(packet.header.packetType);
			std::string msg(message.begin(), message.end());
			registerReq.set_age(stoi(msg));
			INT32 REQ = GenerateRequestId();
			registerReq.set_requestid(REQ);
			std::string tempData;
			registerReq.SerializeToString(&tempData);
			buffer.WriteInt(tempData.length());
			buffer.WriteString(tempData);
			SendToServer(this->buffer.data, this->buffer.Length());
			state = states::REGISTER_WAITING_RESPONSE;
			ResetScreen();
			std::cout << "Registering... Waiting for Server Response" << std::endl;
		}
		else AddMessage(key);
		break;
	}
	case REGISTER_WAITING_RESPONSE: // user cant do anything until the server complete the proccessing 
	{
		if (key == ESCAPE)
		{
			state = states::BEGIN;
			std::cout << "Exiting Option..." << std::endl;
		}
		break;
	}	//user is logged in
	case ROOM_SELECTION: // input chat room to enter
	{
		//ResetScreen();
		std::cout << "Enter Room Name:" << std::endl;
		if (key == BACKSPACE) CleanChar();
		else if (key == ESCAPE) state = states::BEGIN;
		else if (key == ENTER)
		{
			//send join room request to server
			netutils::PacketJoinRoom packetJoinRoom;
			std::string RoomName(message.begin(), message.end());
			this->currentRoom = RoomName;
			packetJoinRoom.roomNameLength = this->currentRoom.size();
			packetJoinRoom.roomName = this->currentRoom;
			
			packetJoinRoom.nameLength = name.size();
			packetJoinRoom.name = name;

			/*packetJoinRoom.nameLength = this->name.size();
			packetJoinRoom.name = this->name;*/
			this->buffer.Clear();
			this->buffer.WriteInt(packetJoinRoom.header.packetType);
			this->buffer.WriteInt(packetJoinRoom.roomNameLength);
			this->buffer.WriteString(packetJoinRoom.roomName);
			this->buffer.WriteInt(packetJoinRoom.nameLength);
			this->buffer.WriteString(packetJoinRoom.name);

			//std::cout << " Room Name : "<< packetJoinRoom.roomName << std::endl;
			this->SendToServer(this->buffer.data, this->buffer.Length());
			ResetScreen();
			state = states::CHATTING;
		}
		else AddMessage(key);
		break;
	}	
	case CHATTING: // you are in a chatting room just chat
	{
		std::cout << "Enter A Message :" << std::endl;
		//ResetScreen();
		if (key == BACKSPACE) CleanChar();
		else if (key == ENTER)
		{
			//send chat request to server
			std::string msg(message.begin(), message.end());
			netutils::PacketSendMessage packet;
			packet.messageLength = msg.size();
			packet.message = msg;
			//std::cout << "msg to be sent " << msg << std::endl;

			
			buffer.WriteInt(packet.header.packetType);
			buffer.WriteInt(packet.messageLength);
			buffer.WriteString(packet.message);

			this->SendToServer(this->buffer.data, this->buffer.Length());
			this->buffer.Clear();
			message.clear();

			//ResetScreen();
			
			break;
		}
		else if (key == ESCAPE)
		{
			//go back to room joining state
			netutils::PacketLeaveRoom packet;
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

			this->SendToServer(this->buffer.data, this->buffer.Length());
			ResetScreen();
			state = states::ROOM_SELECTION;
		}
		else AddMessage(key);
		break;
	}	

	}//switch 


}

void Client::set_LastMsg(std::string msg)
{
	LastMsg = msg;
}

std::string Client::get_LastMsg()
{
	return LastMsg;
}
