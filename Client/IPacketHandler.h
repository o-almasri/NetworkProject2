#pragma once
#include "Buffer.h"
#include "Client.h"

class IPacketHandler
{
public:
	virtual void HandleOnClient(Client& client, const SOCKET& serverSocket) = 0;
};


