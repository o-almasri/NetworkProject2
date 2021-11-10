#pragma once
#include <vector>
#include "sRegisterRequest.h"
#include "sRegisterResponse.h"
#include "sLoginRequest.h"
#include "sLoginResponse.h"
#include "sAuthRequester.h"

//Authetication Service
class cAuthService
{
private:
	std::vector<sAuthRequester*> requests;
public:
	cAuthService();
	virtual ~cAuthService();
	//Register a new user
	sRegisterResponse Register(sRegisterRequest request);
	//authenticate the user with login (email) and password
	sLoginResponse Login(sLoginRequest request);
	//Return the list of all authentication requests received
	std::vector<sAuthRequester*> GetRequests();
	//Disconnect a requester from the server
	void Disconnect(sAuthRequester* requester);
};