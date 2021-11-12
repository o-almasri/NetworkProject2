#include "cBaseDAO.h"
#include <string>


const std::string SCHEMA = "authenticationservice";
const std::string HOST = "127.0.0.1";
const std::string USER = "root";
const std::string PWD = "1234";

void cBaseDAO::Connect(const std::string& hostname, const std::string& username, const std::string& password)
{
	//If it is already Oppened return
	if (!this->connection->isClosed())
	{
		return;
	}
	//If it is still connecting return 
	if (connecting)
		return;
	connecting = true;
	try
	{
		//Attempt to create the connection
		driver = mysql::get_driver_instance();
		connection = driver->connect(hostname, username, password);
		connection->setSchema(SCHEMA);
	}
	catch (SQLException e)
	{
		printf("Failed to connect to database with error: %s\n", e.what());
		connecting = false;
		return;
	}
	//Update the connection state
	connected = true;
	connecting = false;
}

void cBaseDAO::CreateConnection()
{
	this->Connect(HOST, USER, PWD);
}

void cBaseDAO::ReleaseConnection()
{
	if (!this->connection->isClosed())
	{
		this->connection->close();
	}
}