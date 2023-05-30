#pragma once

#include "AbstractRepo.h"

class DatabaseRepository : public AbstractRepo
{
private:
	const string server;
	const string username;
	const string password;
	const string database;
	const string table;
	const int port;

public:
	// metode/functii publice

	/*
	* Constructorul (de instantiere a) unui obiect de clasa DatabaseRepository
	* Cream un constructor custom care primeste 5 parametrii de intrare (parametrii formali/simbolici) ci anume: server, username, password, database
	*/
	DatabaseRepository(const string& server, const string& username, const string& password, const string& database, const string& table, const int& port) : server{ server }, username{ username }, password{ password }, database{ database }, table{ table }, port{ port } {
		
	}

	/*
	* Destructorul virtual al unui obiect de clasa DatabaseRepository (il setam ca fiind default)
	*/
	virtual ~DatabaseRepository() = default;

	/*
	* Constructorul de copiere a unui obiect de clasa DatabaseRepository (il setam ca fiind delete)
	* Astfel nu se vor putea copia obiecte de clasa DatabaseRepository
	*/
	DatabaseRepository(const DatabaseRepository& ot) = delete;

	/*
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie virtuala care incearca sa adauge un obiect product de clasa Product in repo (magazin)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs deja existent!\n" daca produsul product exista deja in lista din repo (exista un produs cu acelasi nume si producator)
	*/
	void addProduct(const Product& product) override; // virtual void addProduct(const Product& product) override;

	/*
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie virtuala care incearca stearga un obiect de clasa Product cu numele name si producatorul producer din lista de produse (entitati de clasa Product) din repo (magazin)
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul product nu se afla in magazin (nu exista obiect de clasa Product (entitati/inregistrari) nu numele name si producatorul producer in lista din repo)
	*/
	void deleteProduct(const string& name, const string& producer) override; // virtual void deleteProduct(const string& name, const string& producer) override;

	/*
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie virtuala care incearca actualizarea/modificarea atributele price si type a unui obiect product de clasa Product din repo (magazin)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul care se doreste a fi actualizat nu se afla in repo (magazin), adica nu exista nicio inregistrare cu numele produsului product si producatorul produsului product
	*/
	void modifyProduct(const Product& product) override; // virtual void modifyProduct(const Product& product) override;

	/*
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care cauta un produs in lista de produse din repo dupa nume si producator
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): obiect de clasa Product (copie a obiectului gasit in lista din repozitoriu)
	* Postconditii: searchProduct() = copie a obiectului (produsului) cu numele name si producatorul producer gasit (in cazul in care acesta exista in repo)
	*                                 -, daca produsul cautat nu se afla in repo (ridica exceptie)
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul cautat nu se afla in repo (magazin), adica nu exista nicio inregistrare cu numele name si producatorul producer
	*/
	Product searchProduct(const string& name, const string& producer) const override;

	/*
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care returneaza o copie a listei de obiecte din repo
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): un vector de obiecte de clasa Product
	* Postconditii: getAll() = o copie a listei de obiecte (produse) din repo (magazin)
	*                          -, daca nu exista produse in repo (ridica exceptie)
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*/
	vector<Product> getAll() const override;

	/*
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care returneaza numarul de obiecte de clasa Product (numarul de produse) din lista din repository (magazin)
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): intreg fara semn (unsigned)
	* Postconditii: len() = numarul de entitati/inregistrari din repo
	*/
	unsigned len() const noexcept override;
};