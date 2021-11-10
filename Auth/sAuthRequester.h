#pragma once
#include <WinSock2.h>
#include <string>

#define DEFAULT_BUFLEN 255

//Authentication requester connection information
struct sAuthRequester
{
	long requestId;
	SOCKET socket;
	WSABUF dataBuf;

	sAuthRequester()
	{
		socket = NULL;
		requestId = 0;
		char buffer[DEFAULT_BUFLEN];
		dataBuf.buf = buffer;
		dataBuf.len = DEFAULT_BUFLEN;
	}
};