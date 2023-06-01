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
	const string path{ ".\\Fisiere text - cos de cumparaturi\\" };  // calea pe disk catre fisierul text in care sunt stocate produsele din cosul de cumparaturi
	const string extension{ ".txt" };                                // extensia fisierului (.txt este extensia folosita pentru fisierele text)
	const string full_filename{ path + this->filename + extension }; // numele complet al fisierului text format din cale + nume fisier + extensie

	ifstream in;            // obiect de clasa input file stream
	in.open(full_filename); // deschidem fisierul text in modul citire

	if (!in.is_open()) // fisierul text nu a fost deschis ceea ce inseamna ca el nu exista (cel mai probabil)
	{
		ofstream out(full_filename); // deschidem fisierul text in modul scriere (fisierul va fi creat daca nu exista)
		out.close();                 // inchidem fisierul text deschis in modul scriere

		in.open(full_filename); // redeschidem fisierul text in modul citire
	}

	while (!in.eof()) // eof - end of file (citim date din fisier pana cand nu mai putem citi (s-a ajuns cu citirea la finalul/sfarsitul fisierului text))
	{
		string line;
		getline(in, line); // citim linia curenta din fisier si o stocam in variabila line (sir de caractere din STL = Standard Template Library)

		if (!line.length()) // linia citita este vida (este ultima linie din fisierul text)
			break;          // iesim in mod fortat si imediat din loop (ciclu)

		istringstream ss(line);
		vector<string> record;

		while (ss)
		{
			// extragem din linia curenta numele si producatorul produsului din cosul de cumparaturi
			string str;

			if (!getline(ss, str, '|')) // spargem linia curenta dupa caracterul '|' (separator)
				break;                 // iesim in mod fortat si imediat din loop (ciclu)

			record.push_back(str); // adaugam sirul de caractere din variabila str pe ultima pozitie in vectorul record
		}
		
		// record[0] = numele produsului din cosul de cumparaturi
		// record[1] = producatorul produsului din cosul de cumparaturi
		const auto name_product{ record.at(0) }; // extragem numele produsului si il memoram in variabila name_product
		const auto producer_product{ record.at(1) }; // extragem producatorul produsului si il memoram in variabila producer_product

		if (!name_product.length() && !producer_product.length())                        // atat numele cat si producatorul sunt invalizi
			throw CosException("[!]Nume produs invalid!\nProducator produs invalid!\n"); // aruncam/ridicam exceptie (obiect de clasa CosException care mosteneste din std::exception)
		else if (!name_product.length())                     // doar numele este invalid (sirul de caractere (stringul) vid)
			throw CosException("[!]Nume produs invalid!\n"); // aruncam/ridicam exceptie (obiect de clasa CosException care mosteneste din std::exception)
		else if (!producer_product.length())                       // doar producatorul este invalid (sirul de caractere (stringul) vid)
			throw CosException("[!]Producator produs invalid!\n"); // aruncam/ridicam exceptie (obiect de clasa CosException care mosteneste din std::exception)
		else                                                             // daca se intra pe aceasta ramura inseamna ca atat numele cat si producatorul sunt doua siruri de caractere (stringuri) valide (nevide)
			CosCumparaturi::adaugaInCos(name_product, producer_product); // apelam metoda adaugaInCos din clasa de baza CosCumparaturi cu argumentele name_product si producer_product
	}

	in.close(); // inchidem fisierul text deschis in modul citire apeland metoda publica close pe obiectul in
}

void FileCosCumparaturi::writeToFile()
{
	const string path{ ".\\Fisiere text - cos de cumparaturi\\" };  // calea pe disk catre fisierul text in care sunt stocate produsele din cosul de cumparaturi
	const string extension{ ".txt" };                                // extensia fisierului (.txt este extensia folosita pentru fisierele text)
	const string full_filename{ path + this->filename + extension }; // numele complet al fisierului text format din cale + nume fisier + extensie

	ofstream out;            // obiect de clasa output file stream
	out.open(full_filename); // deschidem fisierul text in modul scriere (adaugare de continut)
	// daca fisierul nu exista atunci acesta va fi creat la deschidere
	// daca fisierul exista atunci acesta va fi suprascris

	try {
		const auto shopping_cart{ CosCumparaturi::getCos() }; // stocam in variabila shopping_cart lista (vector din STL = Standard Template Library) cu produsele (obiecte de clasa Product) din cosul de cumparaturi (shopping cart)
		for (const auto& product_shopping_cart : shopping_cart) // iteram prin vectorul dinamic shopping_cart folosind variabila de ciclare/iterare product_shopping_cart (aceasta va lua, pe rand, toate elementele din lista shopping_cart)
			// scriem in fisier folosind obiectul out si operatorul de inserare
			// prima oara scriem numele produsului din cosul de cumparaturi, urmat de caracterul special '|' care va fi folosit ca si separator dintre nume si producator, urmat de producatorul produsului din cosul de cumparaturi, urmat in final de linie noua (rand nou)
			// '\n' = new line (echivalent cu std::endl (end of line))
			out << product_shopping_cart.getName() << '|'
				<< product_shopping_cart.getProducer() << '\n';
	}
	catch (const CosException&) { // prindem exceptia CosException aruncata/ridicata in blocul try (tratam cazul in care nu exista produse in cosul de cumparaturi)
		; // instructiunea vida (nu are niciun efect asupra executiei)
	}

	out.close(); // inchidem fisierul text deschis in modul scriere apeland metoda publica close pe obiectul out
}

void FileCosCumparaturi::adaugaInCos(const string& name, const string& producer)
{
	CosCumparaturi::adaugaInCos(name, producer); // apelam metoda adaugaInCos mostenita din clasa de baza CosCumparaturi
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileCosCumparaturi::genereazaCos(unsigned number_of_products)
{
	CosCumparaturi::genereazaCos(number_of_products); // apelam metoda genereazaCos mostenita din clasa de baza CosCumparaturi
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileCosCumparaturi::golesteCos()
{
	CosCumparaturi::golesteCos(); // apelam metoda golesteCos mostenita din clasa de baza CosCumparaturi
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileCosCumparaturi::modificaProduseCos(const TKey& product)
{
	CosCumparaturi::modificaProduseCos(product); // apelam metoda modificaProduseCos mostenita din clasa de baza CosCumparaturi
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileCosCumparaturi::stergeProduseCos(const string& name, const string& producer) noexcept
{
	CosCumparaturi::stergeProduseCos(name, producer); // apelam metoda stergeProduseCos mostenita din clasa de baza CosCumparaturi
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}

void FileCosCumparaturi::eliminaProdusCos(const string& name, const string& producer)
{
	CosCumparaturi::eliminaProdusCos(name, producer); // apelam metoda eliminaProdusCos mostenita din clasa de baza CosCumparaturi
	this->writeToFile(); // writeToFile();
	// scriem in fisier (actualizam continutul fisierului text)
}