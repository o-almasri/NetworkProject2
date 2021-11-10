#pragma once
#include <mysql/jdbc.h>
#include <string>
using namespace sql;

class cBaseDAO
{
protected:
	mysql::MySQL_Driver* driver;
	Connection* connection;
	ResultSet* resultSet;
	bool connected;
	bool connecting;
	void Connect(const std::string& hostname, const std::string& username, const std::string& password);
public:
	Connection* CreateConnection();
	void ReleaseConnection(Connection* connection);
};