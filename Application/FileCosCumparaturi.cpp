#include "FileCosCumparaturi.h"
#include "CosException.h"

#include <iostream>  // pentru std::cerr
#include <fstream>   // pentru std::ifstream si std::ofstream
#include <sstream>   // pentru std::istringstream
#include <exception> // pentru std::exception
#include <vector>    // pentru std::vector

using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::cerr;
using std::exception;
using std::vector;

void FileCosCumparaturi::loadFromFile()
{
	const string path{ ".\\Fisiere text - cos de cumparaturi\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + this->filename + extension };

	ifstream in;
	in.open(full_filename);

	if (!in.is_open())
	{
		ofstream out(full_filename);
		out.close();

		in.open(full_filename);
	}

	while (!in.eof())
	{
		string line;
		getline(in, line);

		if (!line.length())
			break;

		istringstream ss(line);
		vector<string> record;

		while (ss)
		{
			string str;

			if (!getline(ss, str, '|'))
				break;

			record.push_back(str);
		}

		const auto name_product{ record.at(0) };
		const auto producer_product{ record.at(1) };

		if (!name_product.length() && !producer_product.length())
			throw CosException("[!]Nume produs invalid!\nProducator produs invalid!\n");
		else if (!name_product.length())
			throw CosException("[!]Nume produs invalid!\n");
		else if (!producer_product.length())
			throw CosException("[!]Producator produs invalid!\n");
		else
			CosCumparaturi::adaugaInCos(name_product, producer_product);
	}

	in.close();
}

void FileCosCumparaturi::writeToFile()
{
	const string path{ ".\\Fisiere text - cos de cumparaturi\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + this->filename + extension };

	ofstream out;
	out.open(full_filename);

	try {
		const auto shopping_cart{ CosCumparaturi::getCos() };
		for (const auto& product_shopping_cart : shopping_cart)
			out << product_shopping_cart.getName() << '|'
				<< product_shopping_cart.getProducer() << '\n';
	}
	catch (const CosException&) {
		;
	}

	out.close();
}

void FileCosCumparaturi::adaugaInCos(const string& name, const string& producer)
{
	CosCumparaturi::adaugaInCos(name, producer);
	this->writeToFile(); // writeToFile();
}

void FileCosCumparaturi::genereazaCos(unsigned number_of_products)
{
	CosCumparaturi::genereazaCos(number_of_products);
	this->writeToFile(); // writeToFile();
}

void FileCosCumparaturi::golesteCos()
{
	CosCumparaturi::golesteCos();
	this->writeToFile(); // writeToFile();
}

void FileCosCumparaturi::modificaProduseCos(const TKey& product)
{
	CosCumparaturi::modificaProduseCos(product);
	this->writeToFile(); // writeToFile();
}

void FileCosCumparaturi::stergeProduseCos(const string& name, const string& producer) noexcept
{
	CosCumparaturi::stergeProduseCos(name, producer);
	this->writeToFile(); // writeToFile();
}

void FileCosCumparaturi::eliminaProdusCos(const string& name, const string& producer)
{
	CosCumparaturi::eliminaProdusCos(name, producer);
	this->writeToFile(); // writeToFile();
}