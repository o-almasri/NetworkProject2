#include "cPacketLoginResponseHandler.h"
#include "login_response.pb.h"
#include "register_response.pb.h"

void cPacketLoginResponseHandler::HandleOnServer(Server& server, Client* client) {

	netutils::PacketLogin packet;
	
	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);

	auth::LoginResponse_eAuthResultType RES;
	INT32 ID, REQ;


	auth::LoginResponse LR;
	LR.ParseFromString(packet.data);
	
	ID = LR.userid();
	REQ = LR.requestid();
	RES = LR.result();
	
	//std::cout << "Lid :" << ID << std::endl;
	//std::cout << "Lresult :" << RES << std::endl;
	//std::cout << "LREQ ID :" << REQ << std::endl;

	//BUG:: when you read a value from response it gets removed / doesn't get serialized again unless you reset it  


	LR.set_requestid(REQ);
	LR.set_result(RES);
	LR.set_userid(ID);

	Client* Actual_Client = server.Getclient(REQ);
	//Client* Actual_Client = server.responseMap[REQ];
	// no need to read the Data just send them directly to the client and he will handle it there 
	netutils::Buffer buffer(packet.GetSize());
	buffer.WriteInt(packet.header.packetType);
	buffer.WriteInt(packet.data.length());
	buffer.WriteString(packet.data);
	server.SendToClient(Actual_Client, buffer.data, buffer.Length());


	//SendToClient(client, packet.data, packet.dataLength);
	//Forward via tcp to the auth server

	//Using Google proto
	//auth::LoginRequest loginRequest;
	//loginRequest.ParseFromString(packet.data);
	//ScreenToAuthServer()
}
