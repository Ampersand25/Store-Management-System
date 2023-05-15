#pragma once

#include <string>

using std::string;

class DBConstants
{
public:
	//const string server{ "localhost" };
	//const string username{ "root" };
	//const string password{ "BacktrackingGOD314#" };
	//const string database{ "sql_virtual_store" };
	//const string table{ "products" };

	static string server;
	static string username;
	static string password;
	static string database;
	static string table;
};

string DBConstants::server = "localhost";
string DBConstants::username = "root";
string DBConstants::password = "BacktrackingGOD314#";
string DBConstants::database = "sql_virtual_store";
string DBConstants::table = "products";