#include "cPacketLoginHandler.h"
#include "login_request.pb.h"


void cPacketLoginHandler::HandleOnServer(Server& server, Client* client) {

	netutils::PacketLogin packet;
	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);
	//Forward via tcp to the auth server

	//Using Google proto
	auth::LoginRequest loginRequest;
	loginRequest.ParseFromString(packet.data);

	/*
	add this request to the awaiting respons map 
	send login request to the server with the request id
	*/



	if (server.SendToAuthServer(client->buffer.data, client->buffer.Length())) 
	{
		//if send succss add to response map to track respons form auth
		server.AddRequest(loginRequest.requestid(), client);

	}
}
