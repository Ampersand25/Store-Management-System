#include "Product.h"

#include <iostream> // pentru std::to_string

using std::to_string; // functie de conversie de la un tip de data la string (sir de caractere din STL)

// Metode de tip getter (acceseaza anumite atribute/campuri private ale unui obiect)

// Getter pentru a accesa din exteriorul clasei campul (atributul) privat name al unui obiect de clasa Product
const string& Product::getName() const noexcept
{
	return name; // return this->name;
}

// Getter pentru a accesa din exteriorul clasei campul (atributul) privat type al unui obiect de clasa Product
const string& Product::getType() const noexcept
{
	return type; // return this->type;
}

// Getter pentru a accesa din exteriorul clasei campul (atributul) privat price al unui obiect de clasa Product
const double& Product::getPrice() const noexcept
{
	return price; // return this->price;
}

// Getter pentru a accesa din exteriorul clasei campul (atributul) privat producer al unui obiect de clasa Product
const string& Product::getProducer() const noexcept
{
	return producer; // return this->producer;
}

// Metode de tip setter (seteaza anumite atribute/campuri private ale unui obiect)

// Setter pentru a modifica/actualiza atributul privat type al unui obiect de clasa Product
// type <- new_type
void Product::setType(const string& new_type)
{
	type = new_type; // this->type = new_type;
}

// Setter pentru a modifica/actualiza atributul privat price al unui obiect de clasa Product
// price <- new_price
void Product::setPrice(const double& new_price) noexcept
{
	price = new_price; // this->price = new_price;
}

// Metoda de comparare a doua entitati (obiecte de clasa Product)
bool Product::cmpProducts(const Product& ot) const noexcept
{
	return name == ot.name && producer == ot.producer; // return name == ot.getName() && producer == ot.getProducer();
	// return this->name == ot.getName() && this->producer == ot.getProducer();
	// return this->name == ot.name && this->producer == ot.producer;
}

// Metoda de a obtine forma text/scrisa a unei entitati (obiect de clasa Product)
string Product::strProduct() const
{
	return "Nume: " + name + "\nTip: " + type + "\nPret: " + to_string(price) + "\nProducator: " + producer + '\n'; // return "Nume: " + this->name + "\nTip: " + this->type + "\nPret: " + to_string(this->price) + "\nProducator: " + this->producer + '\n';
}

// Operatorul < compara doua obiecte de clasa Product si returneaza true daca primul (lvalue = left value, operandul stang)
// este mai mic strict decat al doilea (rvalue = right value, operandul drept) pe baza unui anumit criteriu de comparare
// se vor compara identificatorii unici (adica perechea de atribute private <name, producer>)
bool Product::operator<(const Product& ot) const noexcept
{
	if (name == ot.name) // if (this->name == ot.name)
		return producer < ot.producer; // return this->producer < ot.producer;

	return name < ot.name; // return this->name < ot.name;
}

// Operatorul == compara doua obiecte de clasa Product si returneaza true daca primul (lvalue = left value, operandul stang)
// este egal cu al doilea (rvalue = right value, operandul drept) pe baza unui anumit criteriu de comparare
// se vor compara identificatorii unici (adica perechea de atribute private <name, producer>)
bool Product::operator==(const Product& ot) const noexcept
{
	if (name == ot.name && producer == ot.producer) // if (name == ot.getName() && producer == ot.getProducer())
		return true;

	return false;

	// return this->name == ot.name && this->producer == ot.producer;
}

// Operatorul != compara doua obiecte de clasa Product si returneaza true daca primul (lvalue = left value, operandul stang)
// este diferit fata de al doilea (rvalue = right value, operandul drept) pe baza unui anumit criteriu de comparare
// se vor compara identificatorii unici (adica perechea de atribute private <name, producer>)
bool Product::operator!=(const Product& ot) const noexcept
{
	if (name != ot.name || producer != ot.producer) // if (name != ot.getName() || producer != ot.getProducer())
		return true;

	return false;

	// return this->name != ot.name || this->producer != ot.producer;
}

// Assignment operator pe clasa Product
// Astfel putem folosi operatorul = (de asignare/atribuire) pentru a copia continutul unui obiect de clasa Product in altul
// Metoda privata returneaza/intoarce referinta constanta la obiectul care se modifca (destinatia)
// dest, src: Product (dest - destination (destinatia), src - source (sursa))
// dest reprezinta lvalue (left value)
// src reprezinta rvalue (right value)
// dest = src => metoda intoarce dest (obiectul dest va avea aceleasi atribute (campuri) name, type, price si producer ca si obiectul src)
const Product& Product::operator=(const Product& ot)
{
	/*
	name = ot.name;         // this->name     = ot.name;
	type = ot.type;         // this->type     = ot.type;
	price = ot.price;       // this->price    = ot.price;
	producer = ot.producer; // this->producer = ot.producer;
	*/

	name = ot.name;         // this->name = ot.getName();
	setType(ot.type);       // this->setType(ot.getType());
	setPrice(ot.price);     // this->setPrice(ot.getPrice());
	producer = ot.producer; // this->producer = ot.getProducer();

	return *this;
}