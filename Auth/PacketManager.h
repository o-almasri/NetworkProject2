#pragma once

#include "IPacketHandler.h"
#include "cAuthRequester.h"

#include <map>

class PacketManager
{
public:
	static PacketManager* GetInstance();

	void HandlePacket(Server& server, cAuthRequester* requester, unsigned int packetType);

	void CleanUp();
private:
	static PacketManager* instance;
	std::map<unsigned int, IPacketHandler*> handlerMap;
};