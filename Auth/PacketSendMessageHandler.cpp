#include "PacketSendMessageHandler.h"
#include "cAuthRequester.h"
#include "Packets.h"

PacketSendMessageHandler::PacketSendMessageHandler()
{

}

void PacketSendMessageHandler::HandleOnServer(Server& server, cAuthRequester* requester)
{
	int messageLength = requester->buffer.ReadInt();
	std::string message = requester->buffer.ReadString(messageLength);

	netutils::PacketReceiveMessage receivePacket;
	/*receivePacket.nameLength = requester->name.size();
	receivePacket.senderName = requester->name;*/
	receivePacket.messageLength = messageLength;
	receivePacket.message = message;

	netutils::Buffer buffer(receivePacket.GetSize());
	buffer.WriteInt(receivePacket.header.packetType);
	buffer.WriteInt(receivePacket.nameLength);
	buffer.WriteString(receivePacket.senderName);
	buffer.WriteInt(receivePacket.messageLength);
	buffer.WriteString(receivePacket.message);
	server.SendToClient(requester, buffer.data, buffer.Length());
	
}


