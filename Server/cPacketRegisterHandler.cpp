#include "cPacketRegisterHandler.h"
#include "register_request.pb.h"
void cPacketRegisterHandler::HandleOnServer(Server& server, Client* client) {

	netutils::PacketRegister packet;
	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);

	//netutils::PacketRegisterAuth authPacket;
	//authPacket.socketLength = client->socket;
	//authPacket.socket = client->socket;
	//authPacket.dataLength = client->buffer.ReadInt();
	//authPacket.data = client->buffer.ReadString(packet.dataLength);

	auth::RegisterRequest Reg;
	Reg.ParseFromString(packet.data);

	if (server.SendToAuthServer(client->buffer.data, client->buffer.Length()))
	{
		//if send succss add to response map to track respons form auth
		server.AddRequest(Reg.requestid(), client);

	}

}
