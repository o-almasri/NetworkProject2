#pragma once
#include "IPacketHandler.h"
#include "Server.h"
#include "Client.h"


class cPacketRegisterHandler : public IPackethandler
{
public:
	virtual void HandleOnServer(Server& server, Client* client);

private:
	friend class PacketManager;
	cPacketRegisterHandler();
};


