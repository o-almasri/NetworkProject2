#pragma once
#include "IPacketHandler.h"

class cPacketRegisterResponseHandler : public IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, Client* client);
};
