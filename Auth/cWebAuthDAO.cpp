#include "cWebAuthDAO.h"

cWebAuthDAO::cWebAuthDAO() {}
cWebAuthDAO::~cWebAuthDAO() {}
//save web auth generated from registration with the created userId
void cWebAuthDAO::Save(sWebAuth webAuth)
{
	CreateConnection();
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"INSERT INTO web_auth(email, salt, hashed_password, user_id) VALUES (?, ?, ?, ?);");
	stmt->setString(1, webAuth.email);
	stmt->setString(2, webAuth.salt);
	stmt->setString(3, webAuth.hashedPassword);
	stmt->setInt(4, webAuth.userId);
	int result = stmt->executeUpdate();
	ReleaseConnection();
}
//Check if the email and passord are existing in db, therefore valid
bool cWebAuthDAO::Exists(std::string email, std::string hashedPassword)
{
	int count = 0;
	CreateConnection();
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"SELECT count(*) FROM web_auth WHERE email = ? and hashed_password = ?;");
	stmt->setString(1, email);
	stmt->setString(2, hashedPassword);
	resultSet = stmt->executeQuery();
	count = resultSet->getInt(1);
	ReleaseConnection();
	return count > 0;
}