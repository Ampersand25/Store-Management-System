#include "Console.h"
#include "ServiceException.h"
#include "RepoException.h"
#include "ProductException.h"
#include "CosException.h"

#include <iostream>  // pentru std::cin, std::cout, std::cerr si std::endl
#include <exception> // pentru std::exception

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

void UI::showMenu() const
{
	cout << "Meniul aplicatiei:\n";
	cout << "adaugare    - adauga un produs in magazin\n";
	cout << "stergere    - sterge un produs din magazin care are un nume si un producator dati\n";
	cout << "modificare  - modifica un produs din magazin\n";
	cout << "cautare     - cauta un produs in magazin dupa un nume si un producator introdusi\n";
	cout << "afisare     - tipareste in consola toate produsele disponibile in magazin\n";
	cout << "info tipuri - afiseaza toate tipurile de produse din magazin si cate produse de tipul respectiv exista in stoc!\n";
	cout << "undo        - face undo la ultima operatie de adaugare, modificare sau stergere\n";
	cout << "filtrare    - filtrare produse dupa: pret, nume, producator\n";
	cout << "sortare     - sortare produse dupa: nume, pret, nume + tip\n";
	cout << "cumparaturi - crearea si gestionarea cosului de cumparaturi\n";
	cout << "clear       - curata ecranul (se sterge continutul terminalului)\n";
	cout << "exit        - inchide aplicatia\n";
}

void UI::addUI() const
{
	string name, type, price_str, producer;

	cout << "Nume: ";
	getline(cin, name);

	cout << "Tip: ";
	getline(cin, type);

	cout << "Pret: ";
	getline(cin, price_str);

	try {
		srv.verifyIfDouble(price_str);
	}
	catch (const ServiceException& se) {
		cerr << endl << se.getMessage() << endl;
		return;
	}

	const auto& price{ stod(price_str, nullptr) };

	cout << "Producator: ";
	getline(cin, producer);

	cout << endl;

	try {
		srv.add(name, type, price, producer);
		cout << "[*]Adaugarea s-a realizat cu succes!\n\n";
	}
	catch (const ProductException& pe) {
		cerr << pe.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::delUI() const
{
	string name, producer;

	cout << "Nume: ";
	getline(cin, name);

	cout << "Producator: ";
	getline(cin, producer);

	cout << endl;

	try {
		srv.del(name, producer);
		cout << "[*]Stergerea s-a realizat cu succes!\n\n";
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::modifyUI() const
{
	string name, type, price_str, producer;

	cout << "Nume: ";
	getline(cin, name);

	cout << "Tip: ";
	getline(cin, type);

	cout << "Pret: ";
	getline(cin, price_str);

	try {
		srv.verifyIfDouble(price_str);
	}
	catch (const ServiceException& se) {
		cerr << endl << se.getMessage() << endl;
		return;
	}

	const auto& price{ stod(price_str, nullptr) };

	cout << "Producator: ";
	getline(cin, producer);

	cout << endl;

	try {
		srv.modify(name, type, price, producer);
		cout << "[*]Modificarea s-a realizat cu succes!\n\n";
	}
	catch (const ProductException& pe) {
		cerr << pe.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::searchUI() const
{
	string name, producer;

	cout << "Nume: ";
	getline(cin, name);

	cout << "Producator: ";
	getline(cin, producer);

	cout << '\n';

	try {
		const auto& p{ srv.search(name, producer) };
		cout << "Produsul cu numele " << name << " si producatorul " << producer << " este:\n" << p.strProduct() << endl;
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage() << endl;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::typeProducts(const vector<Product>& products) const
{
	auto cont{ 0 };

	for (const auto& p : products)
		cout << "\nProdusul #" << ++cont << ":\n" << p.strProduct();

	cout << endl;
}

void UI::printAllUI() const
{
	try {
		const auto& products{ srv.getAll() };

		cout << "Produsele din magazin sunt:\n";
		typeProducts(products);
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
	}
}

void UI::countTypeUI() const
{
	try {
		const auto& types_map{ srv.countType() };

#define type first
#define freq second

		for (const auto elem : types_map) // parcurgem toate perechile <cheie, valoare> din dictionarul ordonat
		{
			const auto key{ elem.first };    // cheia elementului elem
			const auto value{ elem.second }; // valoarea elementului elem

			// key (cheia): TKey = string
			// value (valoarea cheii): TPair = pair<string, unsigned>
			// value.type (value.first): string (sir de caractere din STL = Standard Template Library)
			// value.freq (value.second): unsigned (intreg fara semn)

			cout << "Exista " << value.freq << " produse cu tipul \"" << key << "\" in magazin!\n";
		}

#undef type
#undef freq
	}
	catch (const RepoException& re) {
		cerr << re.getMessage();
	}

	cout << endl;
}

void UI::undoUI() const
{
	cout << "Sunteti sigur ca doriti sa faceti undo la ultima operatie efectuata? [Y/N]: ";
	string ans;
	getline(cin, ans);

	while (ans != "y" && ans != "Y" && ans != "n" && ans != "N")
	{
		cerr << "[X]Optiune invalida!\n";
		cout << "\nReintroduceti optiunea aleasa [Y/N]: ";
		getline(cin, ans);
	}

	cout << endl;

	if (ans == "n" || ans == "N")
		return;

	try {
		auto msg_undo{ srv.undo() };
		cout << msg_undo << endl;
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage() << endl;
	}
}

void UI::showFilterCriterions() const
{
	cout << "Criterii de filtrare:\n";
	cout << "1 - dupa pret\n";
	cout << "2 - dupa nume\n";
	cout << "3 - dupa producator\n";
}

string UI::readFilterCrt() const
{
	showFilterCriterions();

	cout << "\nIntroduceti criteriu de filtrare dorit [1|2|3]: ";
	string crt;
	getline(cin, crt);

	while (crt != "1" && crt != "2" && crt != "3")
	{
		cerr << "[X]Criteriu de filtrare invalid!\n";

		cout << "\nReintroduceti criteriu dorit [1|2|3]: ";
		getline(cin, crt);
	}

	return crt;
}

string UI::readFilter(const string& crt) const
{
	if (crt == "1")
		cout << "\nAlegeti pretul dupa care sa se faca filtrarea: ";
	else if (crt == "2")
		cout << "\nAlegeti numele dupa care sa se faca filtrarea: ";
	else
		cout << "\nAlegeti producatorul dupa care sa se faca filtrarea: ";

	string filter;
	getline(cin, filter);

	return filter;
}

string UI::readFilterSign() const
{
	cout << "\nAlegeti cum sa fie pretul produselor filtrate in raport cu pretul introdus [<|=|>]: ";
	string sign;
	getline(cin, sign);

	while (sign != "<" && sign != "=" && sign != ">")
	{
		cerr << "[X]Semnul de inegalitate intre preturi este invalid!\n";

		cout << "\nReintroduceti semnul de inegalitate dorit [<|=|>]: ";
		getline(cin, sign);
	}

	return sign;
}

void UI::filterUI() const
{
	const auto crt{ readFilterCrt() };
	const auto filter{ readFilter(crt) };

	string sign{ "-" };

	if (crt == "1")
		sign = readFilterSign();
	try {
		const auto& products = srv.filterProducts(crt, filter, sign);

		if (!products.size())
			cout << "\nNu exista produse in magazin cu ";
		else
			cout << "\nProdusele din magazin cu ";

		if (crt == "1")
		{
			cout << "pretul ";

			if (sign == "<")
				cout << "mai mic (strict) decat ";
			else if (sign == "=")
				cout << "egal cu ";
			else
				cout << "mai mare (strict) decat ";
		}
		else if (crt == "2")
			cout << "numele ";
		else
			cout << "producatorul ";

		cout << filter;

		if (products.size())
		{
			cout << " sunt:\n";
			typeProducts(products);
		}
		else
			cout << "\n\n";
	}
	catch (const RepoException& re) {
		cerr << endl << re.getMessage() << endl;
	}
	catch (const ServiceException& se) {
		cerr << endl << se.getMessage() << endl;
	}
}

void UI::showSortingCriterions() const
{
	cout << "Criterii de sortare:\n";
	cout << "1 - dupa nume\n";
	cout << "2 - dupa pret\n";
	cout << "3 - dupa nume + tip\n";
}

string UI::readSortingCrt() const
{
	showSortingCriterions();

	cout << "\nIntroduceti criteriu de sortare dorit [1|2|3]: ";
	string crt;
	getline(cin, crt);

	while (crt != "1" && crt != "2" && crt != "3")
	{
		cerr << "[X]Criteriu de sortare invalid!\n";

		cout << "\nReintroduceti criteriu dorit [1|2|3]: ";
		getline(cin, crt);
	}

	return crt;
}

void UI::showSortingOrders() const
{
	cout << "\nOrdinea de sortare poate fi:\n";
	cout << "c - crescator\n";
	cout << "d - descrescator\n";
}

string UI::readSortingOrd() const
{
	showSortingOrders();

	cout << "\nIntroduceti ordinea de sortare dorita [c|d]: ";
	string ord;
	getline(cin, ord);

	while (ord != "c" && ord != "C" && ord != "d" && ord != "D")
	{
		cerr << "[X]Ordine de sortare invalida!\n";

		cout << "\nReintroduceti ordinea dorita [c|d]: ";
		getline(cin, ord);
	}

	return ord;
}

void UI::sortUI() const
{
	const auto crt{ readSortingCrt() }; // criteriul de sortare
	const auto ord{ readSortingOrd() }; // ordinea de sortare

	try {
		const auto& products{ srv.sortProducts(crt, ord) };

		cout << "\nProdusele din magazin ordonate ";

		if (ord == "d" || ord == "D")
			cout << "des";

		cout << "crescator dupa ";

		if (crt == "1")
			cout << "nume";
		else if (crt == "2")
			cout << "pret";
		else
			cout << "nume + tip";

		cout << " sunt:\n";

		typeProducts(products);
	}
	catch (const RepoException& re) {
		cerr << endl << re.getMessage() << endl;
	}
}

void UI::afiseazaMeniuCosCumparaturi() const
{
	cout << "Meniu cos de cumparaturi:\n";
	cout << "golire   - sterge toate produsele din cosul de cumparaturi\n";
	cout << "adaugare - adauga in cosul de cumparaturi un produs dupa nume si producator\n";
	cout << "generare - cosul de cumparaturi se populeaza aleator cu produse\n";
	cout << "tiparire - afiseaza pe ecran produsele din cosul de cumparaturi\n";
	cout << "export   - se salveaza intr-un fisier CSV (Comma-separated values) cosul de cumparaturi\n";
	cout << "clear    - curata ecranul (se sterge continutul terminalului)\n";
	cout << "back     - revenire la meniul principal al aplicatiei\n";
}

void UI::golireCosUI() const
{
	cout << "Sunteti sigur ca doriti sa goliti cosul de cumparaturi? [Y/N]: ";
	string ans;
	getline(cin, ans);

	while (ans != "y" && ans != "Y" && ans != "n" && ans != "N")
	{
		cerr << "[X]Optiune invalida!\n";
		cout << "\nReintroduceti optiunea aleasa [Y/N]: ";
		getline(cin, ans);
	}

	cout << endl;

	if (ans == "n" || ans == "N")
		return;

	try {
		srv.golireCos();
		cout << "[*]Golirea cosului de cumparaturi s-a realizat cu succes!\n";
	}
	catch (const CosException& ce) {
		cerr << ce.getMessage();
	}
}

void UI::adaugareCosUI() const
{
	cout << "Introduceti informatiile despre produsul pe care vreti sa il adaugati in cos\n";

	cout << "Dati numele produsului pe care doriti sa il adaugati in cos: ";
	string name;
	getline(cin, name);

	cout << "Dati producatorul produsului pe care doriti sa il adaugati in cos: ";
	string producer;
	getline(cin, producer);

	cout << endl;

	try {
		srv.adaugareCos(name, producer);
		cout << "[*]Adaugarea produsului in cos s-a realizat cu succes!\n";
	}
	catch (const CosException& ce) {
		cerr << ce.getMessage();
	}
	catch (const RepoException& re) {
		cerr << re.getMessage();
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage();
	}
}

void UI::generareCosUI() const
{
	cout << "Dati numarul de produse care doriti sa fie adaugate in mod aleator in cos: ";
	string num;
	getline(cin, num);

	cout << endl;

	try {
		srv.generareCos(num);
		cout << "[*]Generarea cosului de cumparaturi s-a realizat cu succes!\n";
	}
	catch (const RepoException& re) {
		cerr << re.getMessage();
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage();
	}
}

void UI::tiparireCos() const
{
	try {
		const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

		auto cont{ 0 };

		cout << "Cele " << srv.cantitateCos() << " produse din cosul de cumparaturi sunt:\n\n";

		/*
		for (const auto& prod : lista_cumparaturi)
			cout << ++cont          << ": " <<
					prod.getName()  << " | " <<
					prod.getType()  << " | " <<
					prod.getPrice() << " | " <<
					prod.getProducer() << endl;
		*/

		for (const auto& prod : lista_cumparaturi)
		{
			cout.width(5);
			cout << ++cont << " | ";

			cout.width(20);
			cout << prod.getName() << " | ";

			cout.width(20);
			cout << prod.getType() << " | ";

			cout.width(20);
			cout << prod.getPrice() << " | ";

			cout.width(20);
			cout << prod.getProducer() << " |\n";
		}

		cout << endl;
	}
	catch (const CosException& ce) {
		cerr << ce.getMessage();
	}
}

void UI::exportCosUI() const
{
	cout << "Dati numele fisierului in care sa se faca exportul cosului de cumparaturi: ";
	string filename;
	getline(cin, filename);

	cout << "Dati tipul fisierului in care sa se faca exportul cosului de cumparaturi [html|csv]: ";
	string filetype;
	getline(cin, filetype);

	cout << endl;

	try {
		srv.exportCos(filename, filetype);
		cout << "[*]Exportul in fisier s-a realizat cu succes!\n";
	}
	catch (const CosException& ce) {
		cerr << ce.getMessage();
	}
	catch (const ServiceException& se) {
		cerr << se.getMessage();
	}
}

void UI::cosCumparaturiUI() const
{
	cout << endl;

	const vector<string> commands{ "golire", "adaugare", "generare",
								   "tiparire", "export", "clear",
								   "back" };
	string cmd;

	while (true)
	{
		afiseazaMeniuCosCumparaturi();

		bool actiuneCos{ false };

		cout << "\n>>>";
		getline(cin, cmd);

		if (srv.cmpStrings(cmd, commands.at(0)))
		{
			golireCosUI();
			actiuneCos = true;
		}
		else if (srv.cmpStrings(cmd, commands.at(1)))
		{
			adaugareCosUI();
			actiuneCos = true;
		}
		else if (srv.cmpStrings(cmd, commands.at(2)))
		{
			generareCosUI();
			actiuneCos = true;
		}
		else if (srv.cmpStrings(cmd, commands.at(3)))
		{
			tiparireCos();
			actiuneCos = true;
		}
		else if (srv.cmpStrings(cmd, commands.at(4)))
		{
			exportCosUI();
			actiuneCos = true;
		}
		else if (srv.cmpStrings(cmd, commands.at(5)))
			clearUI();
		else if (srv.cmpStrings(cmd, commands.at(6)))
		{
			cout << endl;
			return;
		}
		else
			cerr << "[X]Actiune inexistenta!\n\n";

		if (actiuneCos)
			cout << "[$]Pret total: " << srv.totalCos() << "\n\n";
	}
}

void UI::clearUI() const noexcept
{
	system("CLS");
}

void UI::addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const
{
	try {
		srv.add(name, type, price, producer);
		++cont;
	}
	catch (const RepoException& re) {
		cerr << re.getMessage();
	}
}

void UI::debugUI() const
{
	/*
	try{
		srv.add("iaurt"         , "produse lactate", 4.63   , "Danone");
		srv.add("chipsuri"      , "snacksuri"      , 9.6    , "Lays");
		srv.add("ton in ulei"   , "conserve"       , 13.9841, "Tonno Rio Mare");
		srv.add("boia"          , "condimente"     , 0.999  , "Delikat");
		srv.add("pasta de dinti", "igiena"         , 7.12   , "Colgate");
		srv.add("iaurt"         , "produse lactate", 5.013  , "Milka UK");
		srv.add("sare"          , "condimente"     , 11     , "Maggi");
		srv.add("parmezan"      , "condimente"     , 8.301  , "Delikat");
		srv.add("chipsuri"      , "snacksuri"      , 1.53   , "Chio");
		srv.add("chipsuri"      , "snacksuri"      , 9.1    , "Pringles");
	}
	catch (const RepoException& re) {
		cerr << re.getMessage() << endl;
		return;
	}

	cout << "Cele 10 produse au fost adaugate cu succes in stoc!\n\n";
	*/

	unsigned cont{ 0 };

	addDebug("iaurt", "produse lactate", 4.63, "Danone", cont);
	addDebug("chipsuri", "snacksuri", 9.6, "Lays", cont);
	addDebug("rozmarin", "condimente", 1.68, "Kamis", cont);
	addDebug("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare", cont);
	addDebug("boia", "condimente", 0.999, "Delikat", cont);
	addDebug("maioneza", "sosuri", 5.891, "Hellmann's", cont);
	addDebug("suc", "bauturi racoritoare", 6.9, "Pepsi", cont);
	addDebug("pasta de dinti", "igiena", 7.12, "Colgate", cont);
	addDebug("tigari", "cancerigene", 8.4018, "Marlboro", cont);
	addDebug("iaurt", "produse lactate", 5.013, "Milka UK", cont);
	addDebug("sare", "condimente", 11, "Maggi", cont);
	addDebug("suc", "bauturi racoritoare", 15.5, "Coca-Cola", cont);
	addDebug("tigari", "cancerigene", 5.83, "Kent", cont);
	addDebug("tigari", "cancerigene", 17.25, "Camel", cont);
	addDebug("parmezan", "condimente", 8.301, "Delikat", cont);
	addDebug("chipsuri", "snacksuri", 1.53, "Chio", cont);
	addDebug("chipsuri", "snacksuri", 9.1, "Pringles", cont);
	addDebug("coriandru", "condimente", 0.0471, "Knorr", cont);
	addDebug("tigari", "cancerigene", 21, "Pall Mall", cont);
	addDebug("ketchup", "sosuri", 4.2810, "Heinz", cont);

	if (!cont)
		cout << "[X]Nu au fost adaugate produse noi in stoc!\n\n";
	else
		cout << "[*]Au fost adaugate " << cont << " produse noi in stoc!\n\n";
}

void UI::runApp() const
{
	clearUI();

	auto run{ true };
	const vector<string> commands{ "adaugare", "stergere", "modificare",
								   "cautare", "afisare", "info tipuri",
								   "undo", "filtrare", "sortare",
								   "cumparaturi", "clear", "exit",
								   "debug" };
	string cmd;

	while (run)
	{
		showMenu();

		cout << "\n>>>";
		getline(cin, cmd);

		try {
			if (srv.cmpStrings(cmd, commands.at(0)))
				addUI();
			else if (srv.cmpStrings(cmd, commands.at(1)))
				delUI();
			else if (srv.cmpStrings(cmd, commands.at(2)))
				modifyUI();
			else if (srv.cmpStrings(cmd, commands.at(3)))
				searchUI();
			else if (srv.cmpStrings(cmd, commands.at(4)))
				printAllUI();
			else if (srv.cmpStrings(cmd, commands.at(5)))
				countTypeUI();
			else if (srv.cmpStrings(cmd, commands.at(6)))
				undoUI();
			else if (srv.cmpStrings(cmd, commands.at(7)))
				filterUI();
			else if (srv.cmpStrings(cmd, commands.at(8)))
				sortUI();
			else if (srv.cmpStrings(cmd, commands.at(9)))
				cosCumparaturiUI();
			else if (srv.cmpStrings(cmd, commands.at(10)))
				clearUI();
			else if (srv.cmpStrings(cmd, commands.at(11)))
				run = false;
			else if (srv.cmpStrings(cmd, commands.at(12)))
				debugUI();
			else
				cerr << "[X]Comanda invalida!\n\n";
		}
		catch (const exception& ex) {
			cerr << ex.what() << endl;
		}
	}
}