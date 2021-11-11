#include "PacketManager.h"
#include "PacketSendMessageHandler.h"
#include "cRegisterPacketHandler.h"
#include "cLoginPacketHandler.h"
#include "cAuthRequester.h"

#include <iostream>

PacketManager* PacketManager::instance = NULL;

PacketManager* PacketManager::GetInstance()
{
	if (PacketManager::instance == NULL)
	{
		PacketManager::instance = new PacketManager();
		instance->handlerMap.insert(std::make_pair(0, new PacketSendMessageHandler()));
		instance->handlerMap.insert(std::make_pair(4, new cRegisterPacketHandler()));
		instance->handlerMap.insert(std::make_pair(5, new cLoginPacketHandler()));
	}

	return instance;
}

void PacketManager::HandlePacket(Server& server, cAuthRequester* requester, unsigned int packetType)
{
	std::map<unsigned int, IPacketHandler*>::iterator it = this->handlerMap.find(packetType);
	if (it != this->handlerMap.end())
	{
		it->second->HandleOnServer(server, requester);
	}
	else
	{
		std::cout << "Packet handler for type " << packetType << " was not found!" << std::endl;
	}
}

void PacketManager::CleanUp()
{
	std::map<unsigned int, IPacketHandler*>::iterator it;
	for (it = this->handlerMap.begin(); it != this->handlerMap.end(); it++)
	{
		delete it->second;
	}

	this->handlerMap.clear();
}