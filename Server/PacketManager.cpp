#include "PacketManager.h"
#include "PacketSendMessageHandler.h"
#include "PacketLeaveRoomHandler.h"
#include "PacketJoinRoomHandler.h"
#include "cPacketRegisterHandler.h"
#include "cPacketLoginHandler.h"

#include <iostream>

PacketManager* PacketManager::instance = NULL;

PacketManager* PacketManager::GetInstance()
{
	if (PacketManager::instance == NULL)
	{
		PacketManager::instance = new PacketManager();
		instance->handlerMap.insert(std::make_pair(0, new PacketSendMessageHandler()));
		instance->handlerMap.insert(std::make_pair(2, new PacketJoinRoomHandler()));
		instance->handlerMap.insert(std::make_pair(3, new PacketLeaveRoomHandler()));
		/*instance->handlerMap.insert(std::make_pair(4, new cPacketRegisterHandler()));
		instance->handlerMap.insert(std::make_pair(5, new cPacketLoginHandler()));*/
	}

	return instance;
}

void PacketManager::HandlePacket(Server& server, Client* client, unsigned int packetType)
{
	std::map<unsigned int, IPackethandler*>::iterator it = this->handlerMap.find(packetType);
	if (it != this->handlerMap.end())
	{
		it->second->HandleOnServer(server, client);
	}
	else
	{
		std::cout << "Packet handler for type " << packetType << " was not found!" << std::endl;
	}
}

void PacketManager::CleanUp()
{
	std::map<unsigned int, IPackethandler*>::iterator it;
	for (it = this->handlerMap.begin(); it != this->handlerMap.end(); it++)
	{
		delete it->second;
	}

	this->handlerMap.clear();
}