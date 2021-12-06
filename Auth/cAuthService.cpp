#include "cAuthService.h"
#include "cUserDAO.h"
#include "cWebAuthDAO.h"
#include "HashGenerator.h"

cUserDAO* userDAO;
cWebAuthDAO* webauthDAO;

//Generate the hash and salt
void GenerateHashedPassword(sUser& user, sWebAuth& webAuth, const std::string& plainPassword)
{
	std::string salt = "";
	char alphaSalt[27] = { 'a','b','c','d','e',
						   'f','g','h','i','j',
						   'k','l','m','n','o',
						   'p','q','r','s','t',
						   'u','v','w','x','y',
						   'z','!' };

	for (int i = 0; i < 8; i++)
	{
		int a = (std::rand() % 27);
		salt += alphaSalt[a];
	}
	webAuth.salt = salt;
	std::string password = plainPassword + salt;
	SHA256 sha;
	sha.update(password);
	uint8_t* digest = sha.digest();
	std::cout << SHA256::toString(digest) << std::endl;
	webAuth.hashedPassword = SHA256::toString(digest);
}


cAuthService::cAuthService()
{
	userDAO = new cUserDAO();
	webauthDAO = new cWebAuthDAO();
}
cAuthService:: ~cAuthService(){}

RegisterResponse cAuthService::Register(RegisterRequest request)
{
	
	RegisterResponse response;
	//check if already exists if not save it
	if (userDAO->Exists(request.email()))
	{
		sUser user = userDAO->FindByEmail(request.email());
		response.set_result(RegisterResponse_eRegisterResultType_ACCOUNT_ALREADY_EXISTS);
		response.set_userid(user.id);
	}
	else
	{
		//Save the user
		sUser user;
		user.name = request.name();
		user.email = request.email();
		user.age = request.age();
		user = userDAO->Save(user);
		//Save the webAuth
		sWebAuth webAuth;
		webAuth.email = request.name();
		webAuth.userId = user.id;
		//generate the hashed password and salt
		GenerateHashedPassword(user, webAuth, request.password());
		webauthDAO->Save(webAuth);
		response.set_result(RegisterResponse_eRegisterResultType_SUCCESS);
		response.set_userid(user.id);
	}

	return response;
}
LoginResponse cAuthService::Login(LoginRequest request)
{
	LoginResponse response;
	//try to match email and password
	if (webauthDAO->Exists(request.email(), request.password()))
	{
		
		response.set_requestid(request.requestid());
		response.set_result(LoginResponse_eAuthResultType_SUCCESS);
		//finds the user ID
		sUser user = userDAO->FindByEmail(request.email());
		response.set_userid(user.id);
		//Updates the last successful login datetime
		userDAO->UpdateLastLogin(user.email);
	}
	else
	{
		//Case email + password didnt match, return error
		response.set_requestid(request.requestid());
		if (userDAO->Exists(request.email()))
		{
			response.set_result(LoginResponse_eAuthResultType_INVALID_PASSWORD);
		}
		else
		{
			response.set_result(LoginResponse_eAuthResultType_EMAIL_NOT_FOUND);
		}
		
	}
	return response;
}
