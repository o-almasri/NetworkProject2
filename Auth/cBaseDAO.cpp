#include "cBaseDAO.h"
#include <string>

const std::string HOST = "";
const std::string USER = "root";
const std::string PWD = "1234";

void cBaseDAO::Connect(const std::string& hostname, const std::string& username, const std::string& password)
{
	
}

Connection* cBaseDAO::CreateConnection()
{
	this->Connect(HOST, USER, PWD);
	return this->connection;
}

void cBaseDAO::ReleaseConnection(Connection* connection)
{

}