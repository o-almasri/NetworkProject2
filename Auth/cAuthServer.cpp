#include "cAuthServer.h"
#include "sAuthRequester.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

void cAuthServer::CreateSocket()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		HandleError("WSAStartup failed with error: %d\n", iResult);
	}
	printf("WSAStartup() was successful!\n");

	// Define our connection address info 
	ZeroMemory(&hints, sizeof(this->hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &addrResult);
	if (iResult != 0)
	{
		WSACleanup();
		HandleError("getaddrinfo() failed with error %d\n", iResult);
	}

	printf("getaddrinfo() is good!\n");

	// Create a SOCKET for connecting to the server
	listenSocket = socket(
		addrResult->ai_family,
		addrResult->ai_socktype,
		addrResult->ai_protocol
	);
	if (listenSocket == INVALID_SOCKET)
	{
		freeaddrinfo(addrResult);
		WSACleanup();
		HandleError("socket() failed with error %d\n", WSAGetLastError());
	}
	printf("socket() is created!\n");
}

void cAuthServer::Bind()
{
	int iResult = bind(
		listenSocket,
		this->addrResult->ai_addr,
		(int)this->addrResult->ai_addrlen
	);

	if (iResult == SOCKET_ERROR)
	{
		freeaddrinfo(this->addrResult);
		closesocket(this->listenSocket);
		WSACleanup();
		HandleError("bind failed with error: %d\n", WSAGetLastError());
	}
	printf("bind() is good!\n");

}

void cAuthServer::HandleError(const char* message, int iResult)
{
	printf(message, iResult);
	throw FatalExit;
}

SOCKET cAuthServer::StartListening()
{

	freeaddrinfo(addrResult);

	int iResult = listen(listenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(listenSocket);
		WSACleanup();
		HandleError("listen() failed with error %d\n", WSAGetLastError());
	}

	printf("listen() was successful!\n");


	// Change the socket mode on the listening socket from blocking to
	// non-blocking so the application will not block waiting for requests

	iResult = ioctlsocket(listenSocket, FIONBIO, &NonBlock);
	if (iResult == SOCKET_ERROR)
	{
		closesocket(listenSocket);
		WSACleanup();
		HandleError("ioctlsocket() failed with error %d\n", WSAGetLastError());
	}
	printf("ioctlsocket() was successful!\n");
	return  listenSocket;
}

cAuthServer::cAuthServer()
{

}

cAuthServer::~cAuthServer()
{
}

void cAuthServer::Start()
{
	CreateSocket();
	Bind();
}

void cAuthServer::Shutdown(SOCKET& acceptSocket)
{
	// close socket
	int iResult = shutdown(acceptSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		closesocket(acceptSocket);
		WSACleanup();
		HandleError("shutdown failed with error: %d\n", WSAGetLastError());
	}

	// cleanup
	closesocket(acceptSocket);
	WSACleanup();
}

void cAuthServer::SendResponse(SOCKET& socket, WSABUF& dataBuf)
{
	DWORD Flags = 0;
	DWORD SentBytes;
	int iResult = WSASend(
		socket,
		&(dataBuf),
		1,
		&SentBytes,
		Flags,
		NULL,
		NULL
	);

	if (SentBytes == SOCKET_ERROR)
	{
		printf("send error %d\n", WSAGetLastError());
	}
	else if (SentBytes == 0)
	{
		printf("Send result is 0\n");
	}
	else
	{
		printf("Successfully sent %d bytes!\n", SentBytes);
	}
}