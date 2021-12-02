#pragma once
#include "IPacketHandler.h"


class cPacketLoginHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* client);
};


