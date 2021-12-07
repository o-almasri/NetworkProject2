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
	resultSet->next();
	count = resultSet->getInt(1);
	ReleaseConnection();
	return count > 0;
}

std::string cWebAuthDAO::getSalt(std::string email)
{
	
	CreateConnection();
	//SELECT salt FROM web_auth WHERE email = 1;
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"SELECT salt FROM web_auth WHERE email = ?;");
	stmt->setString(1, email);
	resultSet = stmt->executeQuery();
	resultSet->next();
	if (resultSet->rowsCount() > 0) {
		std::string result = resultSet->getString(1);
		ReleaseConnection();
		return result;
	}
	ReleaseConnection();
	
	//std::cout << "Query get salt Result " << result << std::endl;
	
	return "";

}