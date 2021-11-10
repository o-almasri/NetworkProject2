#include "cWebAuthDAO.h"

cWebAuthDAO::cWebAuthDAO() {}
cWebAuthDAO::~cWebAuthDAO() {}
//save web auth generated from registration with the created userId
sWebAuth cWebAuthDAO::Save(sWebAuth auth)
{
	sql::Connection* conn = CreateConnection();
	sWebAuth webAuth;
	//TODO INSERT INTO web_auth() VALUES (????)
	//INSERT = sql::Statement::execute()
	ReleaseConnection(conn);
	return webAuth;
}
//Check if the email and passord are existing in db, therefore valid
bool cWebAuthDAO::Exists(std::string email, std::string hashedPassword)
{
	sql::Connection* conn = CreateConnection();
	//TODO SELECT count(*) FROM web_auth WHERE email = ? AND hashed_password = ?
	// SELECT = sql::Statement::executeQuery()
	ReleaseConnection(conn);
	return false;
}