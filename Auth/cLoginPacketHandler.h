#pragma once
#include "IPacketHandler.h"
#include "Server.h"
#include "cAuthRequester.h"


class cLoginPacketHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, cAuthRequester* requester);

private:
	friend class PacketManager;
	cLoginPacketHandler();
};


