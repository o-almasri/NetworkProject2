#include "cPacketRegisterHandler.h"
#include "Client.h"

cPacketRegisterHandler::cPacketRegisterHandler()
{

}

void cPacketRegisterHandler::HandleOnServer(Server& server, Client* client) {

	netutils::PacketRegister packet;
	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);

	/*netutils::PacketRegisterAuth authPacket;
	authPacket.socketLength = client->socket;
	authPacket.socket = client->socket;
	authPacket.dataLength = client->buffer.ReadInt();
	authPacket.data = client->buffer.ReadString(packet.dataLength);*/

	//SendToAuthServer(authPacket);

	//server.Register(requester, packet);
}
