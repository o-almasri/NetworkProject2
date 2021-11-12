#pragma once
#include <string>
#include "cBaseDAO.h"

//DTO for web auth
struct sWebAuth
{
	long id;
	std::string email;
	std::string hashedPassword;
	std::string salt;
	long userId;
};
//Data access Object to manipulate web_auth table
class cWebAuthDAO : public cBaseDAO
{
public:
	cWebAuthDAO();
	~cWebAuthDAO();
	//save web auth generated from registration with the created userId
	void Save(sWebAuth webAuth);
	//Check if the email and passord are existing in db, therefore valid
	bool Exists(std::string email, std::string hashedPassword);
	
};