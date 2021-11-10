#include "cUserDAO.h"

cUserDAO::cUserDAO() {}
cUserDAO:: ~cUserDAO() {}

// check if the email is already registered
bool cUserDAO::Exists(std::string email)
{
	sql::Connection* conn = CreateConnection();
	//TODO SELECT count(*) FROM user WHERE email = ?
	// SELECT = sql::Statement::executeQuery()
	ReleaseConnection(conn);
	return false;
}
//Save a new user
sUser cUserDAO::Save(sUser user)
{
	sql::Connection* conn = CreateConnection();
	//TODO INSERT INTO user() VALUES (????)
	//INSERT = sql::Statement::execute()
	// 
	//retrieve to check what ID was generated
	sUser savedUser = FindByEmail(user.email);
	ReleaseConnection(conn);
	return savedUser;
}
//Update the the last login information with the current datetime
void cUserDAO::UpdateLastLogin(std::string email)
{
	sql::Connection* conn = CreateConnection();
	//TODO UPDATE user SET last_login = now() WHERE email = ?
	// UPDATE = and sql::Statement::executeUpdate()
	ReleaseConnection(conn);
}

sUser cUserDAO::FindByEmail(std::string email)
{
	sql::Connection* conn = CreateConnection();
	sUser user;
	// TODO SELECT * FROM user WHERE email = ?
	// SELECT = sql::Statement::executeQuery()
	ReleaseConnection(conn);
	return user;
}