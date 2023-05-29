#include "Service.h"
#include "ServiceException.h"
#include "Utils.h"

#include <algorithm> // pentru std::sort, std::copy_if si std::back_inserter
#include <exception> // pentru std::exception
#include <string>    // pentru stoi (string to integer build-in function)
#include <iostream>  // pentru back_inserter

using std::sort;          // functie build-in de sortare (ordonare) a unei structuri de date
using std::copy_if;       // functie de copiere dintr-o structura de date in alta (folosita la filtrare)
using std::back_inserter; // functie care face push_back la copy_if in structura de date in care se face copierea/filtarea si da ensure capacity (daca nu mai exista spatiu in zona de memorie unde se face copierea, atunci se face resize/redimensionare astfel incat sa acomodeze toate elementele ce trebuie copiate)
using std::make_unique;   // functie care creeaza un smart pointer
using std::exception;     // clasa de exceptie din STL

bool Service::cmpStrings(const string& str_1, const string& str_2) const noexcept
{
	const Utils utils;
	return utils.compareStr(str_1, str_2); // comparam case insensitive cele doua stringuri (str_1 si str_2)
}

void Service::verifyIfDouble(const string& str) const
{
	const Utils utils;

	if (!utils.isDouble(str)) // verificam daca str contine reprezentarea unui numar real
		throw ServiceException("[!]Pretul introdus nu este un numar real!\n"); // aruncam/ridicam exceptie de clasa ServiceException
}

void Service::verifyIfInteger(const string& str) const
{
	const Utils utils;

	if (!utils.isInteger(str)) // verificam daca str contine reprezentarea unui numar intreg
		throw ServiceException("[!]Informatia introdusa nu este un numar intreg!\n"); // aruncam/ridicam exceptie de clasa ServiceException
}

void Service::add(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer }; // cream produsul cu numele name, tipul type, pretul price si producatorul producer

	valid.validateProduct(product); // validam obiectul de clasa Product (produsul) creat (instantiat) anterior/precedent
	repo.addProduct(product); // incercam sa adaugam in repo produsul product

	undo_list.push_back(make_unique<UndoAdauga>(repo, product)); // adaugam in lista (vectorul) undo_list un smart pointer la un obiect de clasa UndoAdauga care va retine un obiect de clasa Repository si elementeul (obiect de clasa Product) adaugat in repo

	this->notify(); // notify();
}

void Service::del(const string& name, const string& producer)
{
	// validam numele name si producatorul producer
	string err{ "" }; // lista de erori (string)

	if (!name.size())     // if (name == "")
		err += "[!]Nume invalid!\n";       // name invalid
	if (!producer.size()) // if (producer == "")
		err += "[!]Producator invalid!\n"; // producer invalid

	if (err.size()) // lista de erori contine cel putin o eroare (name si/sau producer sunt stringuri vide, deci invalide)
		throw ServiceException(err); // aruncam exceptie de clasa ServiceException cu mesajul de eroare/exceptie err

	// salvam in variabila deleted_product o copie a produsului (obiect de clasa Product) de dinainte de stergere
	auto deleted_product{ this->search(name, producer) }; // const auto& deleted_product{ repo.searchProduct(name, producer) };
	repo.deleteProduct(name, producer); // incercam sa stergem produsul cu numele name si producatorul producer din magazin (repo)

	// pe linia asta se ajunge daca exista un produs (obiect de clasa Product) cu numele name si producatorul producer
	// cu alte cuvinte, metoda publica deleteProduct a obiectului repo nu a aruncat exceptie (deci stergerea s-a realizat cu succes)
	cos.stergeProduseCos(name, producer); // stergem/eliminam toate produsele din cosul de cumparaturi cu numele name si producatorul producer

	undo_list.push_back(make_unique<UndoSterge>(repo, deleted_product)); // adaugam in lista (vectorul) undo_list un smart pointer la un obiect de clasa UndoSterge care va retine un obiect de clasa Repository si elementeul (obiect de clasa Product) sters din repo

	this->notify(); // notify();
}

void Service::modify(const string& name, const string& type, const double& price, const string& producer)
{
	Product product{ name, type, price, producer }; // cream produsul cu numele name, tipul type, pretul price si producatorul producer

	valid.validateProduct(product); // validam obiectul de clasa Product (produsul) creat (instantiat) anterior/precedent
	// salvam in variabila modified_product o copie a produsului (obiect de clasa Product) de dinainte de modificare
	auto modified_product{ this->search(name, producer) }; // const auto& modified_product{ repo.searchProduct(name, producer) };
	repo.modifyProduct(product); // incercam sa modificam un produs care are numele name si producatorul producer din repo (daca acesta exista) cu noul produs product

	// pe linia asta se ajunge daca exista un produs (obiect de clasa Product) product in magazin (repository)
	// cu alte cuvinte, metoda publica modifyProduct a obiectului repo nu a aruncat exceptie (deci modificarea s-a realizat cu succes)
	cos.modificaProduseCos(product); // modificam toate produsele din cosul de cumparaturi care au acelasi nume si producator cu produsul product (adica numele name si producatorul producer)

	undo_list.push_back(make_unique<UndoModifica>(repo, modified_product)); // adaugam in lista (vectorul) undo_list un smart pointer la un obiect de clasa UndoModifica care va retine un obiect de clasa Repository si elementeul (obiect de clasa Product) modificat din repo

	this->notify(); // notify();
}

const Product& Service::search(const string& name, const string& producer) const
{
	// validam numele name si producatorul producer
	if (!name.size() * !producer.size()) // if (name == "" && producer == "")
		throw ServiceException("[!]Nume invalid!\n[!]Producator invalid!\n");
	if (!name.size())                    // if (name == "")
		throw ServiceException("[!]Nume invalid!\n");
	if (!producer.size())                // if (producer == "")
		throw ServiceException("[!]Producator invalid!\n");

	return repo.searchProduct(name, producer); // cautam un produs cu numele name si producatorul producer in lista de produse din repository
}

vector<Product> Service::getAll() const
{
	return repo.getAll(); // returnam o referinta constanta la lista de obiecte de clasa Product din repo
}

unsigned Service::numberOfProducts() const
{
	return repo.len(); // returnam numarul de elemente care se afla stocate in repository apeland metoda len() pe obiectul repo care este incapsulat in cadrul clasei
}

dictionary Service::countType() const
{
	dictionary types_map;

	const auto& products{ getAll() };

	for (const auto& prod : products)
		if (types_map.find(prod.getType()) == types_map.end())
			types_map[prod.getType()] = make_pair(prod.getType(), 1); // types_map[prod.getType()] = { prod.getType(), 1 };
		else
			++types_map[prod.getType()].second;

	return types_map;
}

string Service::undo()
{
	if (!undo_list.size()) // if (undo_list.empty())
		// lista de undo este vida/goala (nu se mai poate face operatia de undo)
		throw ServiceException("[!]Nu se mai poate realiza operatia de undo!\n"); // ridicam/aruncam exceptie de clasa ServiceException

	const auto& undo_class_ptr{ undo_list.back() }; // retinem in constanta undo_class_ptr ultimul element (smart pointer) din vectorul undo_list
	
	const auto product{ undo_class_ptr->getProduct() }; // salvam in constanta product ultimul produs modificat de operatia de undo (obiect de clasa Product pe care vom face redo)
	const auto mesaj_undo{ undo_class_ptr->typeUndo() }; // apelam metoda publica typeUndo pe obiectul referit de smart pointerul undo_class_ptr si retinem stringul intors de metoda in constanta mesaj_undo
	const auto what_undo{ undo_class_ptr->whatUndo() }; // stocam in constanta what_redo tipul operatiei redo care se va executa

	if (what_undo == UNDO_TYPE::ADD_TYPE_UNDO) // s-a realizat operatia de undo pentru adaugarea unui produs (s-a sters produsul)
		redo_list.push_back(make_unique<RedoAdauga>(repo, product)); // adaugam in lista (vectorul) redo_list un smart pointer la un obiect de clasa RedoAdauga care va retine un obiect de clasa Repository si obiectul de clasa Product pe care s-a facut undo adaugare
	else if (what_undo == UNDO_TYPE::REMOVE_TYPE_UNDO) // s-a realizat operatia de undo pentru stergerea unui produs (s-a adaugat produsul)
		redo_list.push_back(make_unique<RedoSterge>(repo, product)); // adaugam in lista (vectorul) redo_list un smart pointer la un obiect de clasa RedoSterge care va retine un obiect de clasa Repository si obiectul de clasa Product pe care s-a facut undo stergere
	else //else if (what_undo == UNDO_TYPE::UPDATE_TYPE_UNDO)
		 // s-a realizat operatia de undo pentru modificarea unui produs (s-a modificat produsul)
		redo_list.push_back(make_unique<RedoModifica>(repo, this->search(product.getName(), product.getProducer()))); // adaugam in lista (vectorul) redo_list un smart pointer la un obiect de clasa RedoModifica care va retine un obiect de clasa Repository si obiectul de clasa Product de dinainte de undo modificare

	undo_class_ptr->doUndo(); // apel polimorfic la metoda virtuala doUndo a unui obiect de clasa UndoAdauga, UndoSterge sau UndoModifica (obiecte derivate din clasa de baza ActiuneUndo)
	undo_list.pop_back(); // eliminam/stergem ultimul element (pointer la un obiect de clasa ActiuneUndo) din vectorul undo_list

	this->notify(); // notify();

	return mesaj_undo; // returnam stringul care sa contina mesajul cu operatia la care s-a facut undo (adaugare/modificare/stergere)
}

string Service::redo()
{
	if (!redo_list.size()) // if (redo_list.empty())
		// lista de redo este vida/goala (nu se mai poate face operatia de redo)
		throw ServiceException("[!]Nu se mai poate realiza operatia de redo!\n"); // ridicam/aruncam exceptie de clasa ServiceException

	const auto& redo_class_ptr{ redo_list.back() }; // retinem in constanta redo_class_ptr ultimul element (smart pointer) din vectorul redo_list

	const auto product{ redo_class_ptr->getProduct() }; // salvam in constanta product ultimul produs modificat de operatia de redo (obiect de clasa Product pe care vom face undo)
	const auto mesaj_redo{ redo_class_ptr->typeRedo() }; // apelam metoda publica typeRedo pe obiectul referit de smart pointerul redo_class_ptr si retinem stringul intors de metoda in contanta mesaj_redo
	const auto what_redo{ redo_class_ptr->whatRedo() }; // stocam in constanta what_redo tipul operatiei redo care se va executa

	if (what_redo == REDO_TYPE::ADD_TYPE_REDO) // s-a realizat operatia de redo pentru undo adaugare (s-a re-adaugat un produs)
		undo_list.push_back(make_unique<UndoAdauga>(repo, product)); // adaugam in lista (vectorul) undo_list un smart pointer la un obiect de clasa UndoAdauga care va retine un obiect de clasa Repository si obiectul de clasa Product pe care s-a facut redo adauga
	else if (what_redo == REDO_TYPE::REMOVE_TYPE_REDO) // s-a realizat operatia de redo pentru undo stergere (s-a sters un produs)
		undo_list.push_back(make_unique<UndoSterge>(repo, product)); // adaugam in lista (vectorul) undo_list un smart pointer la un obiect de clasa UndoSterge care va retine un obiect de clasa Repository si obiectul de clasa Product pe care s-a facut redo sterge
	else //else if (what_redo == REDO_TYPE::UPDATE_TYPE_REDO)
		 // s-a realizat operatia de redo pentru undo modificare (s-a modificat un produsul)
		undo_list.push_back(make_unique<UndoModifica>(repo, this->search(product.getName(), product.getProducer()))); // adaugam in lista (vectorul) undo_list un smart pointer la un obiect de clasa UndoModifica care va retine un obiect de clasa Repository si obiectul de clasa Product de dinainte de redo modificare

	redo_class_ptr->doRedo(); // apel polimorfic la metoda virtuala doRedo a unui obiect de clasa RedoAdauga, RedoSterge sau RedoModifica (obiecte derivate din clasa de baza ActiuneRedo)
	redo_list.pop_back(); // eliminam/stergem ultimul element (pointer la un obiect de clasa ActiuneRedo) din vectorul redo_list

	this->notify(); // notify();

	return mesaj_redo; // returnam stringul care sa contina mesajul cu operatia la care s-a facut redo (undo adaugare/modificare/stergere)
}

/*
bool Service::validPriceFilter(const Product& p, const string& price, const string& sign) const
{
	verifyIfDouble(price);

	if (sign == "<")      // se filtreaza produsele cu pret mai mic
		return p.getPrice() < stod(price, nullptr);
	else if (sign == "=") // se filtreaza produsele cu pret egal
		return fabs(p.getPrice() - stod(price, nullptr)) < 1e-12;
	else if (sign == ">") // se filtreaza produsele cu pret mai mare
		return p.getPrice() > stod(price, nullptr);
	else                  // simbol/semn de inegalitate invalid
		throw ServiceException("[!]Simbol de inegalitate invalid!\n");
}

bool Service::validNameFilter(const Product& p, const string& name) const
{
	if (cmpStrings(p.getName(), name))
		return true; // p satisface filtrul de nume
	return false; // p nu satisface filtrul de nume
}

bool Service::validProducerFilter(const Product& p, const string& producer) const
{
	if (cmpStrings(p.getProducer(), producer))
		return true; // p satisface filtrul de producator
	return false; // p nu satisface filtrul de producator
}
*/

void Service::filterAfterPrice(const vector<Product>& products, vector<Product>& filtered_list, const string& price, const string& sign) const
{
	verifyIfDouble(price);

	const auto& price_double{ stod(price, nullptr) };

	if (sign != "<" && sign != "=" && sign != ">") // simbol/semn de inegalitate invalid
		throw ServiceException("[!]Simbol de inegalitate invalid!\n");

	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&price_double, &sign](const Product& p) {
			if (sign == "<")
				return p.getPrice() < price_double;
			else if (sign == ">")
				return p.getPrice() > price_double;
			return fabs(p.getPrice() - price_double) < 1e-12;
		});
}

void Service::filterAfterName(const vector<Product>& products, vector<Product>& filtered_list, const string& name) const
{
	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&](const Product& p) noexcept {
			return cmpStrings(p.getName(), name);
		});
}

void Service::filterAfterProducer(const vector<Product>& products, vector<Product>& filtered_list, const string& producer) const
{
	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&](const Product& p) noexcept {
			return cmpStrings(p.getProducer(), producer);
		});
}

void Service::filterAfterType(const vector<Product>& products, vector<Product>& filtered_list, const string& type) const
{
	copy_if(products.begin(),
		products.end(),
		back_inserter(filtered_list),
		[&](const Product& p) noexcept {
			return cmpStrings(p.getType(), type);
		});
}

vector<Product> Service::filterProducts(const string& crt, const string& filter, const string& sign) const
{
	/*
	const auto& products{ repo.getAll() };
	vector<Product> filtered_list;

#define pb push_back

	for (const auto& p : products)
	{
		auto isValid{ false }; // semafor care sa indice/semnaleze daca produsul p va fi sau nu filtrat (satisface criteriul de filtrare)

		if (crt == "1")      // criteriul de filtrare: pret (fieldul price)
			isValid = validPriceFilter(p, filter, sign);
		else if (crt == "2") // criteriu de filtrare: nume (fieldul name)
			isValid = validNameFilter(p, filter);
		else if (crt == "3") // criteriu de filtrare: producator (fieldul producer)
			isValid = validProducerFilter(p, filter);
		else                 // criteriu de filtrare invalid
			throw ServiceException("[!]Criteriu de filtrare invalid!\n");

		if (isValid) // obiectul p de clasa Product respecta filtrul impus
			filtered_list.pb(p); // filtram produsul p
	}

#undef pb

	return filtered_list;
	*/

	const auto& products{ repo.getAll() };
	vector<Product> filtered_list;

	if (crt == "1")      // criteriul de filtrare: pret (fieldul price)
		filterAfterPrice(products, filtered_list, filter, sign);
	else if (crt == "2") // criteriu de filtrare: nume (fieldul name)
		filterAfterName(products, filtered_list, filter);
	else if (crt == "3") // criteriu de filtrare: producator (fieldul producer)
		filterAfterProducer(products, filtered_list, filter);
	else if (crt == "4") // criteriu de filtrare: tip (fieldul type)
		filterAfterType(products, filtered_list, filter);
	else                 // criteriu de filtrare invalid
		throw ServiceException("[!]Criteriu de filtrare invalid!\n");

	return filtered_list;
}

/*
void Service::sortProductsAscending(vector<Product>& products, const string& crt) const
{
	if (crt == "1") // criteriu sortare: nume
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getName() < p2.getName(); });
	else if (crt == "2") // criteriu sortare: pret
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getPrice() < p2.getPrice(); });
	else if (crt == "3") // criteriu sortare: nume + tip
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {if (p1.getName() == p2.getName()) { return p1.getType() < p2.getType(); } return p1.getName() < p2.getName(); });
	else // criteriu de sortare invalid
		throw ServiceException("[!]Criteriu de sortare invalid!\n");
}

void Service::sortProductsDescending(vector<Product>& products, const string& crt) const
{
	if (crt == "1") // criteriu sortare: nume
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getName() > p2.getName(); });
	else if (crt == "2") // criteriu sortare: pret
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {return p1.getPrice() > p2.getPrice(); });
	else if (crt == "3") // criteriu sortare: nume + tip
		sort(products.begin(),
			products.end(),
			[](const Product& p1, const Product& p2) noexcept {if (p1.getName() == p2.getName()) { return p1.getType() > p2.getType(); } return p1.getName() > p2.getName(); });
	else // criteriu de sortare invalid
		throw ServiceException("[!]Criteriu de sortare invalid!\n");
}
*/

void Service::sortCrtName(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
				return p1.getName() < p2.getName();
			return p1.getName() > p2.getName();
		});
}

void Service::sortCrtPrice(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
				return p1.getPrice() < p2.getPrice();
			return p1.getPrice() > p2.getPrice();
		});
}

void Service::sortCrtNamePlusType(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
			{
				if (p1.getName() == p2.getName())
					return p1.getType() < p2.getType();
				return p1.getName() < p2.getName();
			}
			else {
				if (p1.getName() == p2.getName())
					return p1.getType() > p2.getType();
				return p1.getName() > p2.getName();
			}
		});
}

void Service::sortCrtType(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
				return p1.getType() < p2.getType();
			return p1.getType() > p2.getType();
		});
}

void Service::sortCrtProducer(vector<Product>& products, bool reversed) const
{
	sort(products.begin(),
		products.end(),
		[reversed](const Product& p1, const Product& p2) noexcept {
			if (!reversed)
				return p1.getProducer() < p2.getProducer();
			return p1.getProducer() > p2.getProducer();
		});
}

vector<Product> Service::sortProducts(const string& crt, const string& ord) const
{
	/*
	auto products = repo.getAll();

	if (ord == "c" || ord == "C")      // ordinea de sortare: crescator
		sortProductsAscending(products, crt);
	else if (ord == "d" || ord == "D") // ordinea de sortare: descrescator
		sortProductsDescending(products, crt);
	else                               // ordine de sortare invalida
		throw ServiceException("[!]Ordine de sortare invalida!\n");

	return products;
	*/

	if (ord != "c" && ord != "C" && ord != "d" && ord != "D") // ordine de sortare invalida
		throw ServiceException("[!]Ordine de sortare invalida!\n");

	auto products{ repo.getAll() };

#define ternary(a, b, c) \
	((a) ? (b) : (c))
	const auto reversed{ ternary(ord == "d" || ord == "D", true, false) }; // const auto reversed{ (ord == "c" || ord == "C") ? (false) : (true) };
#undef ternary

	// reversed = 0 => sortare in ordine crescatoare
	//            1 => sortare in ordine descrescatoare

	if (crt == "1")      // criteriu sortare: nume
		sortCrtName(products, reversed);
	else if (crt == "2") // criteriu sortare: pret
		sortCrtPrice(products, reversed);
	else if (crt == "3") // criteriu sortare: nume + tip
		sortCrtNamePlusType(products, reversed);
	else if (crt == "4") // criteriu sortare: tip
		sortCrtType(products, reversed);
	else if (crt == "5") // criteriu sortare: producator
		sortCrtProducer(products, reversed);
	else                 // criteriu de sortare invalid
		throw ServiceException("[!]Criteriu de sortare invalid!\n");

	return products;
}

CosCumparaturi& Service::getCosSrv() const noexcept
{
	return cos;
}

void Service::golireCos()
{
	cos.golesteCos();
}

void Service::adaugareCos(const string& name, const string& producer)
{
	// validam numele name si producatorul producer
	string err{ "" }; // lista de erori (string)

	if (!name.size())     // if (name == "")
		err += "[!]Nume invalid!\n";       // name invalid
	if (!producer.size()) // if (producer == "")
		err += "[!]Producator invalid!\n"; // producer invalid

	if (err.size()) // lista de erori contine cel putin o eroare (name si/sau producer sunt stringuri vide, deci invalide)
		throw ServiceException(err); // aruncam exceptie de clasa ServiceException cu mesajul de eroare/exceptie err

	cos.adaugaInCos(name, producer);
}

void Service::generareCos(const string& num)
{
	/*
	try {
		const int number_of_products{ stoi(num) };

		if (number_of_products < 0)
			throw ServiceException("[!]Numarul introdus nu este o valoare pozitiva!\n");

		cos.genereazaCos(number_of_products);
	}
	catch (const exception&) {
		throw ServiceException("[!]Informatia introdusa nu este un numar intreg!\n");
	}
	*/

	this->verifyIfInteger(num); // verifyIfInteger(num);

	const int number_of_products{ stoi(num) };

	if (number_of_products < 0)
		throw ServiceException("[!]Numarul introdus nu este o valoare pozitiva!\n");

	cos.genereazaCos(number_of_products);
}

void Service::exportCos(const string& filename, const string& filetype)
{
	if (!filename.size()) // if (filename == "")
		throw ServiceException("[!]Numele fisierului nu poate fi vid!\n");

	if (cmpStrings(filetype, "html"))     // exportul cosului de cumparaturi se face intr-un fisier html
		cos.exportCosFisierHTML(filename);
	else if (cmpStrings(filetype, "csv")) // exportul cosului de cumparaturi se face intr-un fisier csv
		cos.exportCosFisierCSV(filename);
	else                                  // tipul fisierului este invalid (nu este html sau csv)
		throw ServiceException("[!]Tip fisier export invalid!\n");
}

const double& Service::totalCos() noexcept
{
	return cos.getTotal();
}

unsigned Service::cantitateCos() noexcept
{
	return cos.nrProduseCos();
}

vector<Product> Service::getCosCumparaturi() const
{
	return cos.getCos();
}