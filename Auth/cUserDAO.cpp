#include "cUserDAO.h"

cUserDAO::cUserDAO() {}
cUserDAO:: ~cUserDAO() {}

// check if the email is already registered
bool cUserDAO::Exists(std::string email)
{
	int count = 0;
	CreateConnection();
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"SELECT count(*) FROM user WHERE email = ?;");
	stmt->setString(1, email);
	resultSet = stmt->executeQuery();
	count = resultSet->getInt(1);
	ReleaseConnection();
	return count>0;
}
//Save a new user
sUser cUserDAO::Save(sUser user)
{
	CreateConnection();
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"INSERT INTO user(`name`, email, age, last_login_date, creation_date) VALUES (?, ?, ?, now(), now());");
	stmt->setString(1, user.name);
	stmt->setString(2, user.email);
	stmt->setInt(3, user.age);
	int result = stmt->executeUpdate();
	ReleaseConnection();
	
	//retrieve to check what ID was generated
	sUser savedUser = FindByEmail(user.email);
	
	return savedUser;
}
//Update the the last login information with the current datetime
void cUserDAO::UpdateLastLogin(std::string email)
{
	CreateConnection();
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"UPDATE user SET last_login = now() WHERE email = ?;");
	stmt->setString(1, email);
	int result = stmt->executeUpdate();
	ReleaseConnection();
}

sUser cUserDAO::FindByEmail(std::string email)
{
	CreateConnection();
	sUser user;
	sql::PreparedStatement* stmt = connection->prepareStatement(
		"SELECT count(*) FROM user WHERE email = ?;");
	stmt->setString(1, email);
	resultSet = stmt->executeQuery();
	user.id = resultSet->getInt(1);
	user.name = resultSet->getString(2);
	user.email = resultSet->getString(3);
	user.age = resultSet->getInt(4);
	ReleaseConnection();
	return user;
}