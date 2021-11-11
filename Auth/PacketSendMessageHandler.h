#pragma once 

#include "IPacketHandler.h"
#include "cAuthRequester.h"

class PacketSendMessageHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, cAuthRequester* requester);

private:
	friend class PacketManager;
	PacketSendMessageHandler();
};

