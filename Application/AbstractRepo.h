#pragma once

#include "Product.h"

#include <string> // pentru std::string
#include <vector> // pentru std::vector

using std::string; // sir de caractere dinamic din STL (Standard Template Library)
using std::vector; // vector dinamic din STL (Standard Template Library)

class AbstractRepo // clasa de baza pur abstracta (are doar metode pur virtuale)
{
public:
	// metode (functii) publice (pot fi apelate din exteriorul clasei)

	// Operatiile pe un repository (repozitoriu) sunt de tipul CRUD:
	// C - create (addProduct)
	// R - read   (searchProduct, getAll, len)
	// U - update (modifyProduct)
	// D - delete (deleteProduct)

	/*
	* Constructorul default (implicit) al unui obiect de clasa AbstractRepo
	* Setam constructorul ca fiind implicit folosind calificativul default
	*/
	AbstractRepo() = default;

	/*
	* Metoda pur virtuala care incearca sa adauge un produs (obiect de clasa Product) product in repository (repozitoriu)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs deja existent!\n" daca produsul product exista deja in lista din repo (exista un produs cu acelasi nume si producator)
	*/
	virtual void addProduct(const Product& product) = 0;

	/*
	* Metoda pur virtuala care incearca sa elimine (stearga) produsul (obiect de clasa Product) cu numele name si producatorul producer din repository (repozitoriu)
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul product nu se afla in magazin (nu exista obiect de clasa Product (entitati/inregistrari) nu numele name si producatorul producer in lista din repo)
	*/
	virtual void deleteProduct(const string& name, const string& producer) = 0;

	/*
	* Metoda pur virtuala care incearca sa modifice un produs (obiect de clasa Product) product in repository (repozitoriu)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul care se doreste a fi actualizat nu se afla in repo (magazin), adica nu exista nicio inregistrare cu numele produsului product si producatorul produsului product
	*/
	virtual void modifyProduct(const Product& product) = 0;

	/*
	* Metoda pur virtuala care cauta un produs (obiect de clasa Product) in repository (repozitoriu) dupa numele name si producatorul producer
	* Calificativul const: starea obiectului nu se modifica in interiorul metodei
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): obiect de clasa Product
	* Postconditii: searchProduct() = copie a obiectului (produsului) cu numele name si producatorul producer gasit (se returneaza/intoarce produsul propriu zis ci nu referinta (constanta) la acesta)
	*                                 -, daca produsul cautat nu se afla in repo (ridica exceptie)
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul cautat nu se afla in repo (magazin), adica nu exista nicio inregistrare cu numele name si producatorul producer
	*/
	virtual Product searchProduct(const string& name, const string& producer) const = 0;

	/*
	* Metoda pur virtuala care returneaza o lista care contine toate produsele (obiectele de clasa Product) din repository (repozitoriu)
	* Calificativul const: starea obiectului nu se modifica in interiorul metodei
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): un vector de obiecte de clasa Product (copie a listei de inregistrari din repo)
	* Postconditii: getAll() = o lista de obiecte (produse) din repo (magazin)
	*                          -, daca nu exista produse in repo (ridica exceptie)
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*/
	virtual vector<Product> getAll() const = 0;

	/*
	* Metoda pur virtuala care returneaza numarul de produse (obiecte de clasa Product) din repository (repozitoriu)
	* Calificativul const: starea obiectului nu se modifica in interiorul metodei
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): intreg fara semn (unsigned)
	* Postconditii: len() = numarul de entitati/inregistrari din repo
	*/
	virtual unsigned len() const = 0;

	/*
	* Destructorul unui obiect de clasa AbstractRepo
	* Destructorul este unul virtual pe care il setam ca fiind implicit folosind calificativul default
	*/
	virtual ~AbstractRepo() = default;
};