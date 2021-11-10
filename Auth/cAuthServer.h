#pragma once
#define DEFAULT_PORT "5151"
#include <WinSock2.h>

//Authenticator server configuration and base cycle
class cAuthServer
{
private:
	WSADATA wsaData;

	SOCKET listenSocket = INVALID_SOCKET;

	struct addrinfo* addrResult = NULL;
	struct addrinfo hints;

	// Initialize Winsock
	void CreateSocket();
	//Setup the TCP listening socket
	void Bind();
	//Throw Fatal Exception
	void HandleError(const char* message, const int result);
public:
	DWORD NonBlock = 1;
	cAuthServer();
	virtual ~cAuthServer();
	void Start();
	//Prepare socket for listening
	SOCKET StartListening();
	//Shutdown  the server
	void Shutdown(SOCKET& acceptSocket);
	//Send buffer response to the socket
	void SendResponse(SOCKET& socket, WSABUF& dataBuf);
};