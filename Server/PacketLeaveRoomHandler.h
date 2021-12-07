#pragma once
#include "IPacketHandler.h"

class PacketLeaveRoomHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* sender);
};


