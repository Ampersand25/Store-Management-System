#pragma once

#include "Product.h"
#include "Repository.h"

#include <string> // pentru std::string

using std::string;

class ActiuneRedo // clasa de baza
{
public:
	// metode publice ale unui obiect de clasa ActiuneRedo si a tuturor obiectelor derivate din clasa aceasta

	/*
	* Constructorul default (implicit/prestabilit) al unui obiect de clasa ActiuneRedo
	*/
	ActiuneRedo() = default;

	/*
	* Metoda pur virtuala care face redo la ultima operatie de undo (undo adaugare, undo modificare sau undo stergere)
	* Cu alte cuvinte, metoda reface ultima operatie de undo
	* Aceasta metoda va fi definita (implementata) in clasele derivate din clasa de baza ActiuneRedo
	* Metoda este doar declarata in clasa de baza (este responsabilitatea fiecarei clase derivate din aceasta sa o suprascrie)
	*/
	virtual void doRedo() = 0;

	/*
	* Metoda pur virtuala care afiseaza un mesaj custom pentru fiecare clasa derivata care sa indice utilizatorului tipul de redo care a avut loc
	* Marcam metoda ca fiind constanta folosind calificativul const (aceasta metoda nu va altera starea obiectului pe care se va apela)
	* Aceasta metoda va fi definita (implementata) in clasele derivate din clasa de baza ActiuneRedo
	* Metoda este doar declarata in clasa de baza (este responsabilitatea fiecarei clase derivate din aceasta sa o suprascrie)
	*/
	virtual string typeRedo() const = 0;

	/*
	* Metoda pur virtuala de tip operand/rezultat care returneaza/intoarce obiectul de clasa Product pe care s-a facut ultima operatie de undo
	* Aceasta metoda va fi definita (implementata) in clasele derivate din clasa de baza ActiuneRedo
	* Metoda este doar declarata in clasa de baza (este responsabilitatea fiecarei clase derivate din aceasta sa o suprascrie)
	*/
	virtual Product getProduct() const = 0;

	/*
	* Destructorul default al unui obiect de clasa ActiuneRedo
	* Acesta este un destructor virtual (metoda virtuala)
	*/
	virtual ~ActiuneRedo() = default;
};

class RedoAdauga : public ActiuneRedo // clasa derivata din clasa de baza ActiuneRedo
{
private:
	// atribute private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)

	AbstractRepo& repo; // referinta la un obiect de clasa AbstractRepo
	Product product;    // copie a unui obiect de clasa Product (obiectul adaugat in repo)

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem folosind calificativul delete constructorul default (implicit) al unui obiect de clasa RedoAdauga
	* Astfel, vom impiedica instantierea de obiecte de clasa RedoAdauga fara a specifica valorile atributelor private repo si product
	*/
	RedoAdauga() = delete;

	/*
	* Constructor custom al unui obiect de clasa RedoAdauga care instantiaza un obiect de clasa RedoAdauga
	* Constructorul primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta constanta la un obiect product de clasa Product
	* Acesta populeaza atributule (campurile) private repo si product cu valorile primite
	*/
	RedoAdauga(AbstractRepo& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	/*
	* Metoda pur virtuala doRedo mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Procedura (functia procedurala) care la apelul polimorfic, face redo la ultima operatie de undo adauga/adaugare
	*/
	void doRedo() override;

	/*
	* Metoda constanta pur virtuala typeRedo mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce stringul (sir de caractere din STL = Standard Template Library) "[+]Redo opeatie undo adaugare realizat cu succes!\n"
	*/
	string typeRedo() const override;

	/*
	* Metoda constanta pur virtuala getProduct mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce produsul (instanta a clasei Product) pe care s-a facut undo
	*/
	Product getProduct() const override {
		return product; // return this->product;
	}
};

class RedoModifica : public ActiuneRedo // clasa derivata din clasa de baza ActiuneRedo
{
private:
	// atribute private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)

	AbstractRepo& repo; // referinta la un obiect de clasa AbstractRepo
	Product product;    // copie a unui obiect de clasa Product (obiectul modificat in repo)

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem folosind calificativul delete constructorul default (implicit) al unui obiect de clasa RedoModifica
	* Astfel, vom impiedica instantierea de obiecte de clasa RedoModifica fara a specifica valorile atributelor private repo si product
	*/
	RedoModifica() = delete;

	/*
	* Constructor custom al unui obiect de clasa RedoModifica care instantiaza un obiect de clasa RedoModifica
	* Constructorul primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta constanta la un obiect product de clasa Product
	* Acesta populeaza atributule (campurile) private repo si product cu valorile primite
	*/
	RedoModifica(AbstractRepo& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	/*
	* Metoda pur virtuala doRedo mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Procedura (functia procedurala) care la apelul polimorfic, face redo la ultima operatie de undo modifica/modificare
	*/
	void doRedo() override;

	/*
	* Metoda constanta pur virtuala typeRedo mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce stringul (sir de caractere din STL = Standard Template Library) "[+]Redo opeatie undo modificare realizat cu succes!\n"
	*/
	string typeRedo() const override;

	/*
	* Metoda constanta pur virtuala getProduct mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce produsul (instanta a clasei Product) pe care s-a facut undo
	*/
	Product getProduct() const override {
		return product; // return this->product;
	}
};

class RedoSterge : public ActiuneRedo // clasa derivata din clasa de baza ActiuneRedo
{
private:
	// atribute private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)

	AbstractRepo& repo; // referinta la un obiect de clasa AbstractRepo
	Product product;    // copie a unui obiect de clasa Product (obiectul sters din repo)

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem folosind calificativul delete constructorul default (implicit) al unui obiect de clasa RedoSterge
	* Astfel, vom impiedica instantierea de obiecte de clasa RedoSterge fara a specifica valorile atributelor private repo si product
	*/
	RedoSterge() = delete;

	/*
	* Constructor custom al unui obiect de clasa RedoSterge care instantiaza un obiect de clasa RedoSterge
	* Constructorul primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta constanta la un obiect product de clasa Product
	* Acesta populeaza atributule (campurile) private repo si product cu valorile primite
	*/
	RedoSterge(AbstractRepo& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	/*
	* Metoda pur virtuala doRedo mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Procedura (functia procedurala) care la apelul polimorfic, face redo la ultima operatie de undo sterge/stergere
	*/
	void doRedo() override;

	/*
	* Metoda constanta pur virtuala typeRedo mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce stringul (sir de caractere din STL = Standard Template Library) "[+]Redo opeatie undo stergere realizat cu succes!\n"
	*/
	string typeRedo() const override;

	/*
	* Metoda constanta pur virtuala getProduct mostenita din clasa de baza ActiuneRedo si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce produsul (instanta a clasei Product) pe care s-a facut undo
	*/
	Product getProduct() const override {
		return product; // return this->product;
	}
};