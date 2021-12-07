#include "PacketRegisterResponseHandler.h"
#include "register_response.pb.h"
#include <iostream>
#include <string>

void PacketRegisterResponseHandler::HandleOnClient(Client& client, const SOCKET& serverSocket)
{


	
	//netutils::PacketRegisterResponse packet;
	int dataLength = client.buffer.ReadInt();
	std::string data = client.buffer.ReadString(dataLength);


	auth::RegisterResponse RSP;
	RSP.ParseFromString(data);
	client.set_name(RSP.name());
	//std::cout << "id :" << RSP.userid() << std::endl;
	//std::cout << "result :" << RSP.result() << std::endl;
	//std::cout << "ID :" << RSP.requestid() << std::endl;
	/*
	if Registration succeed then no need to login -> go to room selection 
	else if fail go back to default state
	*/

	int newState = 0;
	switch (RSP.result()) 
	{
		case 0:
			printf("registered successfully");
			newState = 9;
			break;
		case 1:
			printf("ACCOUNT_ALREADY_EXISTS");
			break;
		case 2:
			printf(" INVALID_PASSWORD ");
			break;
		case 3:
			printf(" INTERNAL_SERVER_ERROR ");
			break;
		default:
			printf(" unknown Error");
			break;

	}

	client.set_State(newState); // Default


	//client.set_State();




}