#include "cAuthService.h"
#include "cUserDAO.h"
#include "cWebAuthDAO.h"

cUserDAO* userDAO;
cWebAuthDAO* webauthDAO;

//Generate the hash and salt
void GenerateHashedPassword(sUser& user, sWebAuth& webAuth, const std::string& plainPassword)
{
	//TODO generate salt
	webAuth.salt = "TODO";
	//TODO 
	webAuth.hashedPassword = "TODO";
}


cAuthService::cAuthService()
{
	userDAO = new cUserDAO();
	webauthDAO = new cWebAuthDAO();
}
cAuthService:: ~cAuthService()
{
	for (size_t i = 0; i < requests.size(); i++)
	{
		delete requests.at(i);
	}
	requests.clear();
}

sRegisterResponse cAuthService::Register(sRegisterRequest request)
{
	sRegisterResponse response;
	//check if already exists if not save it
	if (userDAO->Exists(request.email))
	{
		sUser user = userDAO->FindByEmail(request.email);
		response.result = eRegisterResultType::ACCOUNT_ALREADY_EXISTS;
		response.userId = user.id;
	}
	else
	{
		//Save the user
		sUser user;
		user.name = request.name;
		user.email = request.email;
		user.age = request.age;
		user = userDAO->Save(user);
		//Save the webAuth
		sWebAuth webAuth;
		webAuth.email = request.name;
		webAuth.userId = user.id;
		//generate the hashed password and salt
		GenerateHashedPassword(user, webAuth, request.password);
		webauthDAO->Save(webAuth);
		response.result = eRegisterResultType::SUCCESS;
		response.userId = user.id;
	}

	return response;
}
sLoginResponse cAuthService::Login(sLoginRequest request)
{
	sLoginResponse response;
	//try to match email and password
	if (webauthDAO->Exists(request.email, request.password))
	{
		response.requestId = request.requestId;
		response.result = eAuthResultType::SUCCESS;
		//finds the user ID
		sUser user = userDAO->FindByEmail(request.email);
		response.userId = user.id;
		//Updates the last successful login datetime
		userDAO->UpdateLastLogin(user.email);
	}
	else
	{
		//Case email + password didnt match, return error
		response.requestId = request.requestId;
		if (userDAO->Exists(request.email))
		{
			response.result = eAuthResultType::INVALID_PASSWORD;
		}
		else
		{
			response.result = eAuthResultType::EMAIL_NOT_FOUND;
		}
		
	}
	return response;
}
std::vector<sAuthRequester*> cAuthService::GetRequests()
{
	return this->requests;
}

void cAuthService::Disconnect(sAuthRequester* requester)
{
	//Close socket
	closesocket(requester->socket);
	printf("Closing socket %d\n", (int)requester->socket);

	//Remove from vector
	for (size_t i = 0; i < this->requests.size(); i++)
	{
		sAuthRequester* r = this->requests.at(i);
		if (r->requestId == r->requestId)
		{
			this->requests.erase(this->requests.begin() + i);
		}
	}
}