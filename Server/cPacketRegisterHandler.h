#pragma once
#include "IPacketHandler.h"


class cPacketRegisterHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* client);
};


