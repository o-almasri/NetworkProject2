#pragma once
#include <string>
#include "cBaseDAO.h"

//DTO or user
struct sUser
{
	long id;
	std::string name;
	std::string email;
	int age;
	std::string lastLoginDate;
	std::string creationDate;
	
};

//Data Access Object to manipulare user table
class cUserDAO: public cBaseDAO
{
public:
	cUserDAO();
	virtual ~cUserDAO();

	// check if the email is already registered
	bool Exists(std::string email);
	//Save a new user
	sUser Save(sUser user);
	//Update the the last login information with the current datetime
	void UpdateLastLogin(std::string email);
	//Return the sUser by email
	sUser FindByEmail(std::string email);
	
};