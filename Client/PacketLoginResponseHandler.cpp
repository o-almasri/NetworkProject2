#include "PacketLoginResponseHandler.h"
#include "login_response.pb.h"
#include <iostream>
#include <string>


void PacketLoginResponseHandler::HandleOnClient(Client& client, const SOCKET& serverSocket)
{

	//netutils::PacketRegisterResponse packet;
	int dataLength = client.buffer.ReadInt();
	std::string data = client.buffer.ReadString(dataLength);

	auth::LoginResponse LR;
	LR.ParseFromString(data);
	client.set_name(LR.name());
	std::cout << LR.name() << std::endl;
	int newState = 0;
	switch (LR.result())
	{
	case 0:
		printf("Login successfully");
		newState = 9;
		break;
	case 1:
		printf("INVALID EMAIL OR PASSWORD");
		//actually its invalid password but i dont want the client to know which one 
		break;
	case 2:
		printf(" EMAIL_NOT_FOUND ");
		break;
	case 3:
		printf(" INTERNAL_SERVER_ERROR ");
		break;
	default:
		printf(" unknown Error");
		break;

	}

	client.set_State(newState); // Default

}