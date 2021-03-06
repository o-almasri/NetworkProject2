//ss
#pragma once

#include "Buffer.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <sstream>

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

	void set_State(int x); // to allow to hop between states

	void set_name(std::string name);

	void set_LastMsg(std::string msg);

	std::string get_LastMsg();

	netutils::Buffer buffer;

	std::stringstream chatLog;

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
	std::string LastMsg;


	PCSTR serverIp;
	PCSTR serverPort;
	SOCKET serverSocket;
	void CleanChar();
	void AddMessage(char& key);
	int GenerateRequestId();
	void ReceiveMessage(DWORD& bytesReceived, FD_SET& readSet, int& total);
	void ResetScreen();
};