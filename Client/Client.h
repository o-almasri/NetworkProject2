//ss
#pragma once

#include "Buffer.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#include "login_request.pb.h"
#include "register_request.pb.h"

class Client
{
public:
	Client(PCSTR serverIp, PCSTR port);
	~Client();

	bool Initialize();

	void Start();

	bool SendToServer(char* data, int dataLength);

	void statemachine(char key);

	netutils::Buffer buffer;

private:
	void ShutDown();
	//to keep track of the state that the user is on
	enum states {
		BEGIN,
		LOGIN_INPUT_EMAIL,
		LOGIN_INPUT_PASSWORD,
		LOGIN_WAITING_RESPONSE,
		REGISTER_INPUT_USERNAME,
		REGISTER_INPUT_PASSWORD,
		REGISTER_INPUT_EMAIL,
		REGISTER_INPUT_AGE,
		REGISTER_WAITING_RESPONSE,
		ROOM_SELECTION,
		CHATTING
	};
	int state; // used to determine what to display for the client
	std::vector<char> message; // used to hold the msg



	bool running;

	std::string currentRoom;
	std::string name;

	PCSTR serverIp;
	PCSTR serverPort;
	SOCKET serverSocket;


};