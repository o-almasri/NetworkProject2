#pragma once
#include "IPacketHandler.h"


class PacketJoinRoomHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* sender);
};


