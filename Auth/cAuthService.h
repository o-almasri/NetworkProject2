#pragma once
#include "register_request.pb.h"
#include "register_response.pb.h"
#include "login_request.pb.h"
#include "login_response.pb.h"

using namespace auth;

//Authetication Service
class cAuthService
{	
public:
	cAuthService();
	virtual ~cAuthService();
	//Register a new user
	RegisterResponse Register(RegisterRequest request);
	//authenticate the user with login (email) and password
	LoginResponse Login(LoginRequest request);
	
};