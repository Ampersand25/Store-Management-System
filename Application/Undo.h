#pragma once

#include "Product.h"
#include "Repository.h"

#include <string> // pentru std::string

using std::string;

class ActiuneUndo // clasa de baza
{
public:
	// metode publice ale unui obiect de clasa ActiuneUndo si a tuturor obiectelor derivate din clasa aceasta

	/*
	* Constructorul default (implicit/prestabilit) al unui obiect de clasa ActiuneUndo
	*/
	ActiuneUndo() = default;

	/*
	* Metoda pur virtuala care face undo la ultima operatie de adaugare/stergere/modificare din repo
	* Aceasta metoda va fi definita (implementata) in clasele derivate din clasa de baza ActiuneUndo
	* Metoda este doar declarata in clasa de baza (este responsabilitatea fiecarei clase derivate din aceasta sa o suprascrie)
	*/
	virtual void doUndo() = 0;

	/*
	* Metoda pur virtuala care afiseaza un mesaj custom pentru fiecare clasa derivata care sa indice utilizatorului tipul de undo care a avut loc
	* Aceasta metoda va fi definita (implementata) in clasele derivate din clasa de baza ActiuneUndo
	* Metoda este doar declarata in clasa de baza (este responsabilitatea fiecarei clase derivate din aceasta sa o suprascrie)
	*/
	virtual string typeUndo() = 0;

	/*
	* Destructorul default al unui obiect de clasa ActiuneUndo
	* Acesta este un destructor virtual (metoda virtuala)
	*/
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo // clasa derivata din clasa de baza ActiuneUndo
{
private:
	// atribute private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)

	AbstractRepo& repo; // referinta la un obiect de clasa AbstractRepo
	Product product;    // copie a unui obiect de clasa Product (obiectul adaugat in repo)

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem folosind calificativul delete constructorul default (implicit) al unui obiect de clasa UndoAdauga
	* Astfel, vom impiedica instantierea de obiecte de clasa UndoAdauga fara a specifica valorile atributelor private repo si product
	*/
	UndoAdauga() = delete;

	/*
	* Constructor custom al unui obiect de clasa UndoAdauga care instantiaza un obiect de clasa UndoAdauga
	* Constructorul primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta constanta la un obiect product de clasa Product
	* Acesta populeaza atributule (campurile) private repo si product cu valorile primite
	*/
	UndoAdauga(AbstractRepo& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	/*
	* Metoda pur virtuala doUndo mostenita din clasa de baza si suprascrisa (folosind calificativul override)
	* Procedura (functia procedurala) face la apelul polimorfic undo la ultima operatie de adaugare in repo
	*/
	void doUndo() override;

	/*
	* Metoda pur virtuala typeUndo mostenita din clasa de baza si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce stringul (sir de caractere din STL) "[+]Undo adaugare realizat cu succes!\n"
	*/
	string typeUndo() override;
};

class UndoModifica : public ActiuneUndo // clasa derivata din clasa de baza ActiuneUndo
{
private:
	// atribute private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)

	AbstractRepo& repo; // referinta la un obiect de clasa AbstractRepo
	Product product;    // copie a unui obiect de clasa Product (obiectul modificat in repo)

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem folosind calificativul delete constructorul default (implicit) al unui obiect de clasa UndoModifica
	* Astfel, vom impiedica instantierea de obiecte de clasa UndoModifica fara a specifica valorile atributelor private repo si product
	*/
	UndoModifica() = delete;

	/*
	* Constructor custom al unui obiect de clasa UndoModifica care instantiaza un obiect de clasa UndoModifica
	* Constructorul primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta constanta la un obiect product de clasa Product
	* Acesta populeaza atributule (campurile) private repo si product cu valorile primite
	*/
	UndoModifica(AbstractRepo& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	/*
	* Metoda pur virtuala doUndo mostenita din clasa de baza si suprascrisa (folosind calificativul override)
	* Procedura (functia procedurala) face la apelul polimorfic undo la ultima operatie de modificare in repo
	*/
	void doUndo() override;

	/*
	* Metoda pur virtuala typeUndo mostenita din clasa de baza si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce stringul (sir de caractere din STL) "[+]Undo modificare realizat cu succes!\n"
	*/
	string typeUndo() override;
};

class UndoSterge : public ActiuneUndo // clasa derivata din clasa de baza ActiuneUndo
{
private:
	// atribute private (nu pot fi accesate din exteriorul clasei, ci doar din interiorul acesteia)

	AbstractRepo& repo; // referinta la un obiect de clasa AbstractRepo
	Product product;    // copie a unui obiect de clasa Product (obiectul sters din repo)

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem folosind calificativul delete constructorul default (implicit) al unui obiect de clasa UndoSterge
	* Astfel, vom impiedica instantierea de obiecte de clasa UndoSterge fara a specifica valorile atributelor private repo si product
	*/
	UndoSterge() = delete;

	/*
	* Constructor custom al unui obiect de clasa UndoSterge care instantiaza un obiect de clasa UndoSterge
	* Constructorul primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta constanta la un obiect product de clasa Product
	* Acesta populeaza atributule (campurile) private repo si product cu valorile primite
	*/
	UndoSterge(AbstractRepo& repo, const Product& product) : repo{ repo }, product{ product } {

	}

	/*
	* Metoda pur virtuala doUndo mostenita din clasa de baza si suprascrisa (folosind calificativul override)
	* Procedura (functia procedurala) face la apelul polimorfic undo la ultima operatie de stergere din repo
	*/
	void doUndo() override;

	/*
	* Metoda pur virtuala typeUndo mostenita din clasa de baza si suprascrisa (folosind calificativul override)
	* Functie publica care la apelul polimorfic (dynamic dispatch) returneaza/intoarce stringul (sir de caractere din STL) "[+]Undo stergere realizat cu succes!\n"
	*/
	string typeUndo() override;
};