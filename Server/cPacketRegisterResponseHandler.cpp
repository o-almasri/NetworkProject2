#include "cPacketRegisterResponseHandler.h"
#include "login_response.pb.h"
#include "register_response.pb.h"


void cPacketRegisterResponseHandler::HandleOnServer(Server& server, Client* client) {
	//the client in the header is the Auth server 
	netutils::PacketRegisterResponse packet;

	packet.dataLength = client->buffer.ReadInt();
	packet.data = client->buffer.ReadString(packet.dataLength);

	//userId, result

	auth::RegisterResponse_eRegisterResultType RES;
	INT32 ID, REQ;

	auth::RegisterResponse RSP;
	RSP.ParseFromString(packet.data);

	ID = RSP.userid();
	RES = RSP.result();
	REQ = RSP.requestid();


	//std::cout << "id :" << ID << std::endl;
	//std::cout << "result :" << RES << std::endl;
	//std::cout << "REQ ID :" << REQ << std::endl;

	
	//BUG:: when you read a value from response it gets removed / doesn't get serialized again unless you reset it  

	RSP.set_requestid(REQ);
	RSP.set_result(RES);
	RSP.set_userid(ID);

	//find which client this request belong to 

	
	//RSP.SerializeToString(&packet.data);

	
	server.responseMap;
	Client* Actual_Client = server.Getclient(REQ);
	//Client* Actual_Client = server.responseMap[REQ];
	// no need to read the Data just send them directly to the client and he will handle it there 
	netutils::Buffer buffer(packet.GetSize());
			buffer.WriteInt(packet.header.packetType);
			buffer.WriteInt(packet.data.length());
			buffer.WriteString(packet.data);
			server.SendToClient(Actual_Client, buffer.data, buffer.Length());


	//server.SendToClient(Actual_Client, packet.data, packet.dataLength);
	




	//SendToClient(client, packet.data, packet.dataLength);
	//Forward via tcp to the auth server

	//Using Google proto
	//auth::LoginRequest loginRequest;
	//loginRequest.ParseFromString(packet.data);
	//ScreenToAuthServer()
}
