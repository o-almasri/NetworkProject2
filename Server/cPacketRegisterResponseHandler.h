#pragma once
#include "PacketHandler.h"
#include "Server.h"
#include "Client.h"


class cPacketRegisterResponseHandler : public IPackethandler
{
public:
	virtual void HandleOnServer(Server& server, Client* client);

private:
	friend class PacketManager;
	cPacketRegisterResponseHandler();
};
