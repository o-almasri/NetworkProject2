#pragma once
#include <string>

struct sRegisterRequest
{
	long requestId;
	std::string name;
	std::string email;
	std::string password;
	int age;
};