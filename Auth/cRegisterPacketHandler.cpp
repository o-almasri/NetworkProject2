#include "cRegisterPacketHandler.h"


cRegisterPacketHandler::cRegisterPacketHandler()
{

}

void cRegisterPacketHandler::HandleOnServer(Server& server, cAuthRequester* requester) {

	netutils::PacketRegister packet;
	packet.dataLength = requester->buffer.ReadInt();
	packet.data = requester->buffer.ReadString(packet.dataLength);

	server.Register(requester, packet);
}
