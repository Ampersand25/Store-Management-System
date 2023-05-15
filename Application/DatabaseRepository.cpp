#include "DatabaseRepository.h"
#include "RepoException.h"
#include "DatabaseException.h"

#include <mysql.h>
#include <cstdlib>

using std::to_string;

void DatabaseRepository::addProduct(const Product& product)
{
	MYSQL* conn{ mysql_init(0) };
	conn = mysql_real_connect(conn, this->server.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), 3306, NULL, 0);

	if (conn)
	{
		const string query{ "INSERT INTO " + this->table + " (name, type, price, producer) VALUES ('" + product.getName() + "', '" + product.getType() + "', '" + to_string(product.getPrice()) + "', '" + product.getProducer() + "');" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(conn, q) };
		if (qstate)
			throw RepoException("[!]Produs deja existent!\n");
	}
	else
		//throw new DatabaseException("[!]Connection to database failed (in addProduct method)!\n");
		exit(1);
}

void DatabaseRepository::deleteProduct(const string& name, const string& producer)
{
	MYSQL* conn{ mysql_init(0) };
	conn = mysql_real_connect(conn, this->server.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), 3306, NULL, 0);

	if (conn)
	{
		const string query{ "DELETE FROM " + this->table + " WHERE name = '" + name + "' AND producer = '" + producer + "';" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(conn, q) };
		if (qstate)
		{
			//string error{ mysql_error(conn) };
			//throw new DatabaseException("[!]Delete query failed: " + error + "\n");
			exit(2);
		}
	}
	else
		//throw new DatabaseException("[!]Connection to database failed (in deleteProduct method)!\n");
		exit(3);
}

void DatabaseRepository::modifyProduct(const Product& product)
{
	MYSQL* conn{ mysql_init(0) };
	conn = mysql_real_connect(conn, this->server.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), 3306, NULL, 0);

	if (conn)
	{
		const string query{ "UPDATE " + this->table + " SET type = '" + product.getType() + "', price = '" + to_string(product.getPrice()) + "' WHERE name = '" + product.getName() + "' AND producer = '" + product.getProducer() + "';" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(conn, q) };
		if (qstate)
		{
			//string error{ mysql_error(conn) };
			//throw new DatabaseException("[!]Update query failed: " + error + "\n");
			exit(4);
		}
	}
	else
		//throw new DatabaseException("[!]Connection to database failed (in modifyProduct method)!\n");
		exit(5);
}

const Product& DatabaseRepository::searchProduct(const string& name, const string& producer) const
{
	if (!len()) // if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	MYSQL* conn{ mysql_init(0) };
	conn = mysql_real_connect(conn, this->server.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), 3306, NULL, 0);

	if (conn)
	{
		const string query{ "SELECT * FROM " + this->table + " WHERE name = '" + name + "' AND producer = '" + producer + "';" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(conn, q) };
		if (!qstate)
		{
			MYSQL_RES* res{ mysql_store_result(conn) };
			const MYSQL_ROW row{ mysql_fetch_row(res) };
			if (row)
			{
				const string name{ row[1] };
				const string type{ row[2] };
				const double price{ strtod(row[3], nullptr) };
				const string producer{ row[4] };
				const Product* product = new Product{ name, type, price, producer }; // memory leak

				return *product;
			}
		}
		else
		{
			//string error{ mysql_error(conn) };
			//throw new DatabaseException("[!]Select (for search) query failed: " + error + "\n");
			exit(6);
		}
	}
	else
		//throw new DatabaseException("[!]Connection to database failed (in searchProduct method)!\n");
		exit(7);

	throw RepoException("[!]Produs inexistent!\n");
}

vector<Product> DatabaseRepository::getAll() const
{
	if (!len()) // if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	vector<Product> products;
	
	MYSQL* conn{ mysql_init(0) };
	conn = mysql_real_connect(conn, this->server.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), 3306, NULL, 0);

	if (conn)
	{
		const string query{ "SELECT * FROM " + this->table + ";" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(conn, q) };
		if (!qstate)
		{
			MYSQL_RES* res{ mysql_store_result(conn) };
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res))
			{
				const string name{ row[1] };
				const string type{ row[2] };
				const double price{ strtod(row[3], nullptr) };
				const string producer{ row[4] };
				const Product product{ name, type, price, producer };

				products.push_back(product);
			}
		}
		else
		{
			//string error{ mysql_error(conn) };
			//throw new DatabaseException("[!]Select (for getAll) query failed: " + error + "\n");
			exit(8);
		}
	}
	else
		//throw new DatabaseException("[!]Connection to database failed (in getAll method)!\n");
		exit(9);

	return products;
}

unsigned DatabaseRepository::len() const noexcept
{
	MYSQL* conn{ mysql_init(0) };
	conn = mysql_real_connect(conn, this->server.c_str(), this->username.c_str(), this->password.c_str(), this->database.c_str(), 3306, NULL, 0);

	if (conn)
	{
		const string query{ "SELECT COUNT(*) FROM " + this->table + ";" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(conn, q) };
		if (!qstate)
		{
			MYSQL_RES* res{ mysql_store_result(conn) };
			const MYSQL_ROW row{ mysql_fetch_row(res) };
			if (row)
			{
				const unsigned number_of_products{ strtoul(row[0], nullptr, 10) };
				return number_of_products;
			}
		}
		else
		{
			//string error{ mysql_error(conn) };
			//throw new DatabaseException("[!]Select (for len) query failed: " + error + "\n");
			exit(10);
		}
	}
	else
		//throw new DatabaseException("[!]Connection to database failed (in len method)!\n");
		exit(11);
}