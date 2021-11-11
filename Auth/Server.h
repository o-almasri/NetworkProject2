#pragma once

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

#include "cAuthRequester.h"
#include "Packets.h"

class Server
{
public:
	Server(PCSTR port);
	~Server();

	bool Initialize();

	void Start();

	void SendToClient(cAuthRequester* client, char* dataToSend, int dataLength);

	void Register(cAuthRequester* requester, netutils::PacketRegister& packet);

	void Login(cAuthRequester* requester, netutils::PacketLogin& packet);

private:
	void ShutDown();

	PCSTR port;
	SOCKET connectionSocket; // This socket is used to listen for incoming connections
	SOCKET acceptSocket; // Will hold a new connection

	std::vector<cAuthRequester*> requesters; // Holds our connected clients
};