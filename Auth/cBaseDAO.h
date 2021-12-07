#pragma once
#include <mysql/jdbc.h>
#include <string>
using namespace sql;

//Base DAO implementation
class cBaseDAO
{
protected:
	//MySql Driver reference
	mysql::MySQL_Driver* driver;
	//Connection reference
	Connection* connection;
	//Result set reference
	ResultSet* resultSet;
	//Flag to indicate if it is connected to the DB
	bool connected;
	//Flag to indicate if is in process of connection
	bool connecting;
	//Actual impl to Connect to the specified database 
	void Connect(const std::string& hostname, const std::string& username, const std::string& password);
public:
	//Return the current connection reference
	void CreateConnection();
	//Release and close the current connection
	void ReleaseConnection();
};