#pragma once
#include <WinSock2.h>
#include "Buffer.h"

#define DEFAULT_BUFLEN 255

//Authentication requester connection information
class cAuthRequester
{
public:
	cAuthRequester();
	long requestId;
	SOCKET socket;
	netutils::Buffer buffer;
};