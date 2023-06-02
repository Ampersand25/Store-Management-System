#include "DatabaseRepository.h"
#include "RepoException.h"

#include <cstdlib>

using std::to_string;

void DatabaseRepository::addProduct(const Product& product)
{
	if (this->conn) // if (conn)
	{
		const string query{ "INSERT INTO `" + this->table + "` (`name`, `type`, `price`, `producer`) VALUES ('" + product.getName() + "', '" + product.getType() + "', '" + to_string(product.getPrice()) + "', '" + product.getProducer() + "');" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(this->conn, q) };
		if (qstate)
			throw RepoException("[!]Produs deja existent!\n");
	}
}

void DatabaseRepository::deleteProduct(const string& name, const string& producer)
{
	if (this->conn) // if (conn)
	{
		const string query{ "DELETE FROM `" + this->table + "` WHERE `name` = '" + name + "' AND `producer` = '" + producer + "';" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(this->conn, q) };
		if (qstate)
		{
			// ARUNCAM/RIDICAM EXCEPTIE CA SA SEMNALAM FAPTUL CA QUERY-UL (INTEROGAREA) NU S-A PUTUT EXECUTA CU SUCCES
			//string error{ mysql_error(this->conn) };
			//throw new DatabaseException("[!]Delete query failed: " + error + "\n");

			exit(1); // terminam executia aplicatiei cu codul de eroare 1
		}
	}
}

void DatabaseRepository::modifyProduct(const Product& product)
{
	if (this->conn) // if (conn)
	{
		const string query{ "UPDATE `" + this->table + "` SET `type` = '" + product.getType() + "', `price` = '" + to_string(product.getPrice()) + "' WHERE `name` = '" + product.getName() + "' AND `producer` = '" + product.getProducer() + "';" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(this->conn, q) };
		if (qstate)
		{
			// ARUNCAM/RIDICAM EXCEPTIE CA SA SEMNALAM FAPTUL CA QUERY-UL (INTEROGAREA) NU S-A PUTUT EXECUTA CU SUCCES
			//string error{ mysql_error(this->conn) };
			//throw new DatabaseException("[!]Update query failed: " + error + "\n");

			exit(2); // terminam executia aplicatiei cu codul de eroare 2
		}
	}
}

Product DatabaseRepository::searchProduct(const string& name, const string& producer) const
{
	if (!len()) // if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");
	
	if (this->conn) // if (conn)
	{
		const string query{ "SELECT * FROM `" + this->table + "` WHERE `name` = '" + name + "' AND `producer` = '" + producer + "';" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(this->conn, q) };
		if (!qstate)
		{
			MYSQL_RES* res{ mysql_store_result(this->conn) };
			const MYSQL_ROW row{ mysql_fetch_row(res) };
			if (row)
			{
				const string name{ row[1] };
				const string type{ row[2] };
				const double price{ strtod(row[3], nullptr) };
				const string producer{ row[4] };
				const Product product{ name, type, price, producer };

				return product;
			}
		}
		else
		{
			// ARUNCAM/RIDICAM EXCEPTIE CA SA SEMNALAM FAPTUL CA QUERY-UL (INTEROGAREA) NU S-A PUTUT EXECUTA CU SUCCES
			//string error{ mysql_error(this->conn) };
			//throw new DatabaseException("[!]Select (for search) query failed: " + error + "\n");

			exit(3); // terminam executia aplicatiei cu codul de eroare 3
		}
	}

	throw RepoException("[!]Produs inexistent!\n");
}

vector<Product> DatabaseRepository::getAll() const
{
	if (!len()) // if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	vector<Product> products;
	
	if (this->conn) // if (conn)
	{
		const string query{ "SELECT * FROM `" + this->table + "`;" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(this->conn, q) };
		if (!qstate)
		{
			MYSQL_RES* res{ mysql_store_result(this->conn) };
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
			// ARUNCAM/RIDICAM EXCEPTIE CA SA SEMNALAM FAPTUL CA QUERY-UL (INTEROGAREA) NU S-A PUTUT EXECUTA CU SUCCES
			//string error{ mysql_error(this->conn) };
			//throw new DatabaseException("[!]Select (for getAll) query failed: " + error + "\n");

			exit(4); // terminam executia aplicatiei cu codul de eroare 4
		}
	}

	return products;
}

unsigned DatabaseRepository::len() const noexcept
{
	if (this->conn) // if (conn)
	{
		const string query{ "SELECT COUNT(*) FROM `" + this->table + "`;" };
		const char* q{ query.c_str() };
		const auto qstate{ mysql_query(this->conn, q) };
		if (!qstate)
		{
			MYSQL_RES* res{ mysql_store_result(this->conn) };
			const MYSQL_ROW row{ mysql_fetch_row(res) };
			if (row)
			{
				const unsigned number_of_products{ strtoul(row[0], nullptr, 10) };
				return number_of_products;
			}
		}
		else
		{
			// ARUNCAM/RIDICAM EXCEPTIE CA SA SEMNALAM FAPTUL CA QUERY-UL (INTEROGAREA) NU S-A PUTUT EXECUTA CU SUCCES
			//string error{ mysql_error(conn) };
			//throw new DatabaseException("[!]Select (for len) query failed: " + error + "\n");

			exit(5); // terminam executia aplicatiei cu codul de eroare 5
		}
	}
}