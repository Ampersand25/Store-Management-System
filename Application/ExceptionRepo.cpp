#include "ExceptionRepo.h"
#include "RepoException.h"

#include <exception> // pentru std::exception
#include <random>    // pentru std::random_device, std::mt19937 si std::uniform_int_distribution
#include <iostream>  // pentru std::cout

using std::exception;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::cout;

// un element dintr-un map (dictionar ordonat) este de fapt un pair (o pereche) <cheie, valoare> (<key, value>)
// atributul cheie al unui element din map se acceseaza astfel  : elem.first
// atributul valoare al unui element din map se acceseaza astfel: elem.second
#define key first    // key va reprezenta atributul cheii unui element din dictionar
#define value second // value va reprezenta atributul valorii unui element din dictionar (valoarea asociata cheii elementului respectiv)

void ExceptionRepo::checkProbability() const
{
	mt19937 mt{ random_device{}() };
	uniform_int_distribution<> dist(0, 99);

	const double random_double{ dist(mt) / 100.0 };

	cout << "Valoarea reala din intervalul [0, 1) generata arbitrar/aleator este: " << random_double << "\n\n";

	if (probability > random_double) // if (this->probability > random_double)
		throw exception("[!]Exception!\n"); // aruncam un obiect de clasa exception cu mesajul de eroare "[!]Exception!\n" (const char*)
}

bool ExceptionRepo::isEmpty() const noexcept
{
	for (const auto& elem : elems)
		if (elem.value) // if (elem.value == true)
			return false;

	return true;
}

void ExceptionRepo::addProduct(const TKey& product)
{
	checkProbability(); // this->checkProbability();

	for (const auto& elem : elems)
	{
		const auto& prod{ elem.key };

		if (prod == product) // if (prod.cmpProducts(product))
		{
			if (elem.value) // if (elem.value == true)
				throw RepoException("[!]Produs deja existent!\n");
			else {
				/*
				elems[product] = true;

				return;
				*/

				break;
			}
		}
	}

	elems[product] = true;
}

void ExceptionRepo::deleteProduct(const string& name, const string& producer)
{
	checkProbability(); // this->checkProbability();

	if (isEmpty()) // if (this->isEmpty())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	for (const auto& elem : elems)
	{
		const auto& product{ elem.key };

		if (product.getName() == name && product.getProducer() == producer)
		{
			elems[product] = false;

			return;
		}
	}

	throw RepoException("[!]Produs inexistent!\n");
}

void ExceptionRepo::modifyProduct(const TKey& product)
{
	checkProbability(); // this->checkProbability();

	if (isEmpty()) // if (this->isEmpty())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	/*
	for (const auto& elem : elems)
	{
		const auto& prod{ elem.key };

		if (product == prod) // if (product.cmpProducts(prod))
		{
			elems[prod] = false;
			elems[product] = true;

			return;
		}
	}

	throw RepoException("[!]Produs inexistent!\n");
	*/

	auto iter{ elems.begin() };

	while (iter != elems.end())
	{
		const auto& elem{ *iter };
		const auto& prod{ elem.key };

		if (prod == product) // if (prod.cmpProducts(product))
		{
			elems.erase(iter);
			elems[product] = true;

			return;
		}

		++iter;
	}

	throw RepoException("[!]Produs inexistent!\n");
}

TKey ExceptionRepo::searchProduct(const string& name, const string& producer) const
{
	checkProbability(); // this->checkProbability();

	if (isEmpty()) // if (this->isEmpty())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	for (const auto& elem : elems)
	{
		const auto& product{ elem.key };

		if (product.getName() == name && product.getProducer() == producer)
		{
			if (elem.value) // if (elem.value == true)
				return product;

			break; // throw RepoException("[!]Produs inexistent!\n");
		}
	}

	throw RepoException("[!]Produs inexistent!\n");
}

vector<TKey> ExceptionRepo::getAll() const
{
	checkProbability(); // this->checkProbability();

	if (isEmpty()) // if (this->isEmpty())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	vector<TKey> prods{}; // vector<TKey> prods;

#define pb push_back

	for (const auto& elem : elems)
		if (elem.value) // if (elem.value == true)
			prods.pb(elem.key);

#undef pb

	return prods;
}

unsigned ExceptionRepo::len() const
{
	checkProbability(); // this->checkProbability();

	unsigned cont{ 0 };

	for (const auto& elem : elems)
		if (elem.value) // if (elem.value == true)
			++cont;

	return cont;
}