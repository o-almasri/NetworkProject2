#include "cPacketLoginHandler.h"
#include "login_request.pb.h"
#include "register_request.pb.h"


cPacketLoginHandler::cPacketLoginHandler()
{

}

void cPacketLoginHandler::HandleOnServer(Server& server, Client* client) {

	netutils::PacketLogin packet;
	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);

	//Forward via tcp to the auth server

	//Using Google proto
	//auth::LoginRequest loginRequest;
	//loginRequest.ParseFromString(packet.data);
	//ScreenToAuthServer()
}
