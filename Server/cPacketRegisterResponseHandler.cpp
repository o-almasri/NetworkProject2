#include "cPacketRegisterResponseHandler.h"
#include "login_response.pb.h"
#include "register_response.pb.h"


cPacketRegisterResponseHandler::cPacketRegisterResponseHandler()
{

}

void cPacketRegisterResponseHandler::HandleOnServer(Server& server, Client* client) {

	netutils::PacketLogin packet;

	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);




	//SendToClient(client, packet.data, packet.dataLength);
	//Forward via tcp to the auth server

	//Using Google proto
	//auth::LoginRequest loginRequest;
	//loginRequest.ParseFromString(packet.data);
	//ScreenToAuthServer()
}
