#include "FileRepository.h"
#include "RepoException.h"
#include "ProductValidator.h"
#include "ProductException.h"

#include <iostream>  // pentru std::cerr si std::endl
#include <fstream>   // pentru std::ifstream si std::ofstream
#include <sstream>   // pentru std::istringstream
#include <vector>    // pentru std::vector
#include <exception> // pentru std::exception

using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::vector;
using std::exception;
using std::cerr;
using std::endl;

void FileRepoProducts::loadFromFile()
{
	const string path{ ".\\Fisiere text - repo\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + this->filename + extension }; // const string full_filename{ path + filename + extension };

	ifstream in;
	in.open(full_filename);

	if (!in.is_open())
	{
		ofstream out(full_filename);
		out.close();

		in.open(full_filename);
	}

	unsigned idx{ 1 };

	while (!in.eof())
	{
		string line;
		getline(in, line);

		if (!line.compare(""))
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

		try {
			const Product product{ record.at(0), record.at(1), stod(record.at(2)), record.at(3) };
			const ProductValidator valid;

			try {
				valid.validateProduct(product);
				RepoProducts::addProduct(product);
			}
			catch (const ProductException& pe) {
				cerr << "\nProdusul #" << idx << " nu a putut fi importat din fisier!\n" << pe.getMessage();
				// exit(1);
			}
		}
		catch (const exception& ex) {
			cerr << "\nProdusul #" << idx << " nu a putut fi importat din fisier!\n[!]" << ex.what() << endl;
			// exit(2);
		}

		++idx;
	}

	in.close();
}

void FileRepoProducts::writeToFile()
{
	const string path{ ".\\Fisiere text - repo\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + this->filename + extension }; // const string full_filename{ path + filename + extension };

	ofstream out;
	out.open(full_filename);

	try {
		const auto products{ RepoProducts::getAll() };
		for (const auto& product : products)
		{
			out << product.getName()     << '|'
				<< product.getType()     << '|'
				<< product.getPrice()    << '|'
				<< product.getProducer() << endl;
		}
	}
	catch (const RepoException&) {

	}

	out.close();
}

void FileRepoProducts::addProduct(const Product& product)
{
	RepoProducts::addProduct(product); // apelam metoda addProduct mostenita din clasa de baza RepoProducts
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileRepoProducts::deleteProduct(const string& name, const string& producer)
{
	RepoProducts::deleteProduct(name, producer); // apelam metoda deleteProduct mostenita din clasa de baza RepoProducts
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileRepoProducts::modifyProduct(const Product& product)
{
	RepoProducts::modifyProduct(product); // apelam metoda modifyProduct mostenita din clasa de baza RepoProducts
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}