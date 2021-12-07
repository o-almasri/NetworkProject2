#pragma once
#include "IPacketHandler.h"

class PacketSendMessageHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* sender);
};

