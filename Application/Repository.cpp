#include "Repository.h"
#include "RepoException.h"

#include <algorithm> // pentru std::find_if

using std::find_if;

void RepoProducts::addProduct(const Product& product)
{
	// Varianta I
	/*
	for (const auto& p : products)
		if (p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
			throw RepoException("[!]Produs deja existent!\n");

	products.push_back(product);
	*/

	// Varianta II (cu functia build-in std::find_if din algorithm (STL = Standard Template Library))
	const auto& p{ find_if(products.begin(),
						   products.end(),
						   [&product](const Product& p) noexcept {return p.cmpProducts(product); }) };

	if (p != products.end())
		throw RepoException("[!]Produs deja existent!\n");

	products.push_back(product);
}

void RepoProducts::deleteProduct(const string& name, const string& producer)
{
	if (!len()) // if (!products.size())
		// if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	// Varianta I
	/*
	auto found{ false };
	auto pos{ 0 };

	for (const auto& p : products)
	{
		if (p.getName() == name && p.getProducer() == producer)
		{
			products.erase(products.begin() + pos);
			found = true;

			break;
		}

		++pos;
	}

	if(!found)
		throw RepoException("[!]Produs inexistent!\n");
	*/

	// Varianta II (cu iterator)
	/*
	auto it{ products.begin() };
	auto found{ false };

	while (it != products.end())
	{
		const auto& p{ *it };

		if (p.getName() == name && p.getProducer() == producer)
		{
			products.erase(it);
			found = true;

			break;
		}

		++it;
	}

	if (!found)
		throw RepoException("[!]Produs inexistent!\n");
	*/

	// Varianta III (cu functia build-in std::find_if din algorithm (STL = Standard Template Library))
	const auto& p{ find_if(products.begin(),
						   products.end(),
						   [&name, &producer](const Product& product) noexcept {return product.getName() == name && product.getProducer() == producer; }) };

	if (p == products.end())
		throw RepoException("[!]Produs inexistent!\n");

	products.erase(p);
}

void RepoProducts::modifyProduct(const Product& product)
{
	if (!len()) // if (!products.size())
		// if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	// Varianta I
	/*
	for (auto& p : products)
		if(p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
		{
			p.setType(product.getType());
			p.setPrice(product.getPrice());

			return;
		}

	throw RepoException("[!]Produs inexistent!\n");
	*/

	// Varianta II (cu iterator)
	/*
	auto it{ products.begin() };

	while (it != products.end())
	{
		auto& p{ *it };

		if (p.cmpProducts(product)) // if (p.getName() == product.getName() && p.getProducer() == product.getProducer())
		{
			p.setType(product.getType());
			p.setPrice(product.getPrice());

			return;
		}

		++it;
	}

	throw RepoException("[!]Produs inexistent!\n");
	*/

	// Varianta III (cu functia build-in std::find_if din algorithm (STL = Standard Template Library))
	const auto& p{ find_if(products.begin(),
						   products.end(),
						   [&product](const Product& p) noexcept {return p.cmpProducts(product); }) };

	if (p == products.end())
		throw RepoException("[!]Produs inexistent!\n");

	auto& prod = *p;
	prod.setType(product.getType());
	prod.setPrice(product.getPrice());
}

const Product& RepoProducts::searchProduct(const string& name, const string& producer) const
{
	if (!len()) // if (!products.size())
		// if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	// Varianta I
	/*
	for (const auto& p : products)
		if (p.getName() == name && p.getProducer() == producer)
			return p;

	throw RepoException("[!]Produs inexistent!\n");
	*/

	// Varianta II (cu functia build-in std::find_if din algorithm (STL = Standard Template Library))
	const auto& p{ find_if(products.begin(),
						   products.end(),
						   [&name, &producer](const Product& product) noexcept {return product.getName() == name && product.getProducer() == producer; }) };

	if (p == products.end())
		throw RepoException("[!]Produs inexistent!\n");

	return *p;
}

vector<Product> RepoProducts::getAll() const
{
	if (!len()) // if (!products.size())
		// if (!this->len())
		throw RepoException("[!]Nu exista produse in magazin!\n");

	return products; // return this->products;
}

unsigned RepoProducts::len() const noexcept
{
	return (unsigned)products.size(); // return (unsigned)this->products.size();
}