#pragma once
#include "IPacketHandler.h"


class cPacketLoginResponseHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* client);
};
