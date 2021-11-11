#include "cLoginPacketHandler.h"


cLoginPacketHandler::cLoginPacketHandler()
{

}

void cLoginPacketHandler::HandleOnServer(Server& server, cAuthRequester* requester) {

	netutils::PacketLogin packet;
	packet.dataLength = requester->buffer.ReadInt();
	packet.data = requester->buffer.ReadString(packet.dataLength);

	server.Login(requester, packet);
}
