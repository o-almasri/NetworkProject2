#pragma once

#include "Buffer.h"
#include "Server.h"
#include "cAuthRequester.h"

class IPacketHandler
{
public:
	virtual void HandleOnServer(Server& server, cAuthRequester* requester) = 0;
};

