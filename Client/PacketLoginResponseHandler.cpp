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
		client.set_LastMsg("Login successfully");
		newState = 9;
		break;
	case 1:
		//we know its invalid password only but we dont want client to know
		client.set_LastMsg("INVALID EMAIL OR PASSWORD");
		break;
	case 2:
		client.set_LastMsg(" EMAIL_NOT_FOUND ");
		break;
	case 3:
		client.set_LastMsg(" INTERNAL_SERVER_ERROR ");
		break;
	default:
		client.set_LastMsg(" unknown Error ");
		break;

	}

	client.set_State(newState); // Default

}