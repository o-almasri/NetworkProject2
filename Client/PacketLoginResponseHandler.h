#pragma once
#include "IPacketHandler.h"

class PacketLoginResponseHandler : public IPacketHandler
{
public:
	virtual void HandleOnClient(Client& client, const SOCKET& serverSocket);
};
