#pragma once

#include "Product.h"
#include "Repository.h"
#include "Observer.h"

#include <map>    // pentru std::map
#include <string> // pentru std::string

using std::map;    // dictionar sortat (ordonat) din STL (Standard Template Library)
using std::string; // sir de caractere din STL (Standard Template Library)

#define TKey Product                 // cheia din dictionarul ordonat/sortat (map): obiect de clasa Product
#define TValue unsigned              // valoarea asociata unei chei din dictionar : intreg fara semn (unsigned) <=> numar natural
#define dictionary map<TKey, TValue> // dictionar ordonat/sortat care mapeaza chei de tipul TKey (Product) la valori de tipul TValue (unsigned)

// in map vom retine pentru fiecare produs (cheia dictionarului = obiect de clasa Product) de cate ori acesta apare in cosul de cumparaturi (valoarea asociata cheii)

class CosCumparaturi : public Observable
{
private:
	// atribute/campuri private (nu pot fi accesate din exteriorul clasei)

	dictionary cos;     // cos         - map (TAD Dictionar ordonat/sortat implementat cu Red-Black Tree) din STL care mapeaza chei (obiecte de clasa Product) la valori intregi fara semn (unsigned)
	AbstractRepo& repo; // repo        - referinta la un obiect de clasa AbstractRepo
	double total_price; // total_price - variabila de tip double (numar real reprezentat in virgula mobila/flotanta cu dubla precizie)

	// metodele private (nu pot fi apelate din exteriorul clasei)

	/*
	* Functie de tip operand care verifica daca cosul de cumparaturi este sau nu gol
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (valoare logica de adevar, adica literalii true (1) si false (0))
	* Postconditii: cosGol = true , daca exista cel putin un produs (obiect de clasa Product) in cosul de cumparaturi (atributul privat cos al clasei CosCumparaturi)
	*                        false, in caz contrar (nu exista produse in cos, deci cosul este gol)
	* Exceptii: -
	*/
	bool cosGol() const noexcept;

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Constructorul default al unui obiect de clasa CosCumparaturi
	* Prin calificativul delete nu permitem creare de obiecte de clasa CosCumparaturi fara a specifica atributele repo (vezi constructorul custom)
	*/
	CosCumparaturi() = delete;

	/*
	* Constructor custom al unui obiect de clasa CosCumparaturi care primeste o referinta la un obiect repo de clasa AbstractRepo
	* Contructorul va popula atributul privat repo cu referinta la obiectul primit si atributul privat total_price cu valoarea 0
	* Pe atributul privat cos (de tipul vector) se va apela constructorul default si acesta va fi un vector vid (fara elemente)
	*/
	CosCumparaturi(AbstractRepo& repo) noexcept : repo{ repo }, total_price{ 0 } {

	}

	/*
	* Procedura (functie procedurala) care elimina toate produsele din cosul de cumparaturi
	* Declaram metoda (functia) ca fiind virtuala (folosind calificativul virtual) pentru a putea sa o suprascriem in clasa derivata FileCosCumparaturi (clasa derivata din clasa de baza CosCumparaturi) folosind calificativul override (astfel facem apel polimorfic (dynamic/polymorphic dispatch) la runtime (in timpul executiei programului))
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire: -
	* Postconditii: atributul privat total_price (care stocheaza pretul curent al produselor din cos) se va reseta (va deveni 0)
	*               cosul de cumparaturi va deveni gol (atributul privat cos va fi un vector vid (fara elemente))
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Nu exista produse in cosul de cumparaturi!\n", in cazul in care nu exista produse in cos (cosul este gol)
	*/
	virtual void golesteCos();

	/*
	* Procedura (subprogram procedural) care incearca adaugarea in cosul de cumparaturi a unui produs din magazin cu numele name si producatorul producer
	* Declaram metoda (functia) ca fiind virtuala (folosind calificativul virtual) pentru a putea sa o suprascriem in clasa derivata FileCosCumparaturi (clasa derivata din clasa de baza CosCumparaturi) folosind calificativul override (astfel facem apel polimorfic (dynamic/polymorphic dispatch) la runtime (in timpul executiei programului))
	* Date de intrare: name     - referinta constanta (nu se poate modifica) la un string din STL
	*                  producer - referinta constanta (nu se poate modifica) la un string din STL
	* Preconditii: name     <> "" (string nevid)
	*              producer <> "" (string nevid)
	* Date de iesire: -
	* Postconditii: atributul privat total_price va fi incrementat cu pretul produsului adaugat, daca adaugarea va avea loc (sau nu se va modifica/altera in cazul in care adaugarea nu se realizeaza)
	*               se adauga produsul cu numele name si producatorul producer din magazin daca acesta exista in stoc sau se ridica/arunca exceptie in caz contrar
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]RepoException cu mesajul "[!]Nu exista produse in magazin!\n", in cazul in care nu exista produse in magazin (entitati in repo)
	* [!]CosException cu mesajul "[!]Produsul cautat nu se afla in stoc!\n", in cazul in care nu exista niciun produs (obiect de clasa Product) cu numele name si producatorul producer in magazin
	*/
	virtual void adaugaInCos(const string& name, const string& producer);

	/*
	* Procedura (subprogram procedural) care incearca adaugarea in cosul de cumparaturi a number_of_products produse (obiecte de clasa Product) random (in mod arbitrar/aleator) din magazin (produse care exista in stoc)
	* Declaram metoda (functia) ca fiind virtuala (folosind calificativul virtual) pentru a putea sa o suprascriem in clasa derivata FileCosCumparaturi (clasa derivata din clasa de baza CosCumparaturi) folosind calificativul override (astfel facem apel polimorfic (dynamic/polymorphic dispatch) la runtime (in timpul executiei programului))
	* Date de intrare: number_of_products - intreg (int = integer) fara semn (unsigned, adica intreg pozitiv), adica variabila care retine un numar natural (>= 0)
	* Preconditii: -
	* Date de iesire: -
	* Postconditii: atributul privat total_price va fi incrementat cu pretul fiecarui produs din cele number_of_products generate din stocul magazinului
	*               se adauga number_of_products produse in cosul de cumparaturi
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Produsul cautat nu se afla in stoc!\n", in cazul in care nu exista niciun produs (obiect de clasa Product) cu numele name si producatorul producer in magazin
	*/
	virtual void genereazaCos(unsigned number_of_products);

	/*
	* Procedura (functie procedurala) care da export la produsele din lista de cumparaturi intr-un fisier CSV (Comma-separated values) cu numele filename si extensia .csv
	* Date de intrare: filename - referinta constanta la un string din STL
	* Preconditii: filename <> "" (stringul filename trebuie sa fie nevid)
	* Date de iesire: -
	* Postconditii: se creeaza fisierul cu numele filename si extensia .csv (fisierul este deschis la creare) in modul scriere (fisier de iesire) si se scriu toate produsele in el pe cate o linie
	*               atributele produselor (name, type, price si producer) vor fi separate prin caracterul ','
	* Exceptii: -
	*/
	void exportCosFisierCSV(const string& filename) const;

	/*
	* Procedura (functie procedurala) care da export la produsele din lista de cumparaturi intr-un fisier HTML (Hyper Text Markup Language) cu numele filename si extensia .html
	* Date de intrare: filename - referinta constanta la un string din STL
	* Preconditii: filename <> "" (stringul filename trebuie sa fie nevid)
	* Date de iesire: -
	* Postconditii: se creeaza fisierul cu numele filename si extensia .html (fisierul este deschis la creare) in modul scriere (fisier de iesire) si se scriu toate produsele in el pe cate o linie
	* Exceptii: -
	*/
	void exportCosFisierHTMLOld(const string& filename) const;

	/*
	* Procedura (functie procedurala) care da export la produsele din lista de cumparaturi intr-un fisier HTML (Hyper Text Markup Language) cu numele filename si extensia .html
	* Date de intrare: filename - referinta constanta la un string din STL
	* Preconditii: filename <> "" (stringul filename trebuie sa fie nevid)
	* Date de iesire: -
	* Postconditii: se creeaza fisierul cu numele filename si extensia .html (fisierul este deschis la creare) in modul scriere (fisier de iesire) si se scriu toate produsele in el pe cate o linie
	* Exceptii: -
	*/
	void exportCosFisierHTML(const string& filename) const;

	/*
	* Functie de tip operand (rezultat) care returneaza pretul total al produselor din cos
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta constanta la o variabila de tip double (numar real in dubla precizie)
	* Postconditii: rezultatul intors/returnat de functie reprezinta suma preturilor (atributelor price) ale produselor (obiecte de clasa Product) din cosul de cumparaturi
	* Exceptii: -
	*/
	const double& getTotal() const noexcept;

	/*
	* Functie de tip operand (rezultat) care returneaza numarul total de produse din cosul de cumparaturi
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): intreg fara semn (unsigned), adica un numar natural (>= 0)
	* Postconditii: rezultatul intors/returnat de functie reprezinta marimea cosului de cumparaturi (adica numarul de produse din cos)
	* Exceptii: -
	*/
	unsigned nrProduseCos() const noexcept;

	/*
	* Functie de tip operand (rezultat) care returneaza o un vector din STL care va contine lista de produse (obiecte de clasa Product) din cosul de cumparaturi
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): vector din STL (Standard Template Library) cu obiecte de clasa Product
	* Postconditii: vectorul intors/returnat/furnizat de subprogram/subrutina contine toate produsele din lista de cumparaturi
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Nu exista produse in cosul de cumparaturi!\n", in cazul in care lista care contine produsele din cosul de cumparaturi este goala/vida
	*/
	vector<Product> getCos() const;

	/*
	* Procedura (subrutina procedurala) care incearca sa modifice/actualizeze toate produsele cu acelasi nume si producator ca si produsul product din cosul de cumparaturi
	* Declaram metoda (functia) ca fiind virtuala (folosind calificativul virtual) pentru a putea sa o suprascriem in clasa derivata FileCosCumparaturi (clasa derivata din clasa de baza CosCumparaturi) folosind calificativul override (astfel facem apel polimorfic (dynamic/polymorphic dispatch) la runtime (in timpul executiei programului))
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire: -
	* Postconditii: toate produsele cu acelasi nume si producator din cosul de cumparaturi ca si product vor fi actualizate (vor avea acelasi tip si pret ca si produsul product in urma apelului metodei)
	* Exceptii: -
	*/
	virtual void modificaProduseCos(const TKey& product);

	/*
	* Procedura (subrutina procedurala) care incearca sa stearga/elimine toate produsele (obiectele de clasa Product) din cosul de cumparaturi care au numele name si producatorul producer
	* Declaram metoda (functia) ca fiind virtuala (folosind calificativul virtual) pentru a putea sa o suprascriem in clasa derivata FileCosCumparaturi (clasa derivata din clasa de baza CosCumparaturi) folosind calificativul override (astfel facem apel polimorfic (dynamic/polymorphic dispatch) la runtime (in timpul executiei programului))
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: name     <> "" (unde "" - stringul vid si <> - operatorul de diferit)
	*              producer <> "" (unde "" - stringul vid si <> - operatorul de diferit)
	* Date de iesire: -
	* Postconditii: apelul metodei publice stergeProduseCos va elimina din cosul de cumparaturi toate produsele cu numele name si producatorul producer
	* Exceptii: -
	*/
	virtual void stergeProduseCos(const string& name, const string& producer) noexcept;

	/*
	* Procedura (subrutina procedurala) care incearca sa stearga/elimine un singur produs (obiect de clasa Product) din cosul de cumparaturi care are numele name si producatorul producer
	* Declaram metoda (functia) ca fiind virtuala (folosind calificativul virtual) pentru a putea sa o suprascriem in clasa derivata FileCosCumparaturi (clasa derivata din clasa de baza CosCumparaturi) folosind calificativul override (astfel facem apel polimorfic (dynamic/polymorphic dispatch) la runtime (in timpul executiei programului))
	* Date de intrare: name     - referinta constanta la un string (sir de caractere din STL = Standard Template Library)
	*                  producer - referinta constanta la un string (sir de caractere din STL = Standard Template Library)
	* Preconditii: name     <> "" (unde "" - stringul vid (empty string (are lungimea egala cu 0)) si <> (echivalent cu !=) - operatorul de diferit)
	*              producer <> "" (unde "" - stringul vid (empty string (are lungimea egala cu 0)) si <> (echivalent cu !=) - operatorul de diferit)
	* Date de iesire: -
	* Postconditii: apelul metodei publice eliminaProdusCos va elimina din cosul de cumparaturi primul produs gasit (daca exista) cu numele name si producatorul producer (in cazul in care nu exista niciun produs cu numele name si producatorul producer atunci cosul de cumparaturi ramane nemodificat)
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul: "[!]Nu exista produse in cosul de cumparaturi!\n", in cazul in care lista care contine produsele din cosul de cumparaturi este goala/vida
	*                             "[!]Produsul cautat nu exista in cosul de cumparaturi!\n", in cazul in care nu exista niciun produs cu numele name si producatorul producer in lista de cumparaturi
	*/
	virtual void eliminaProdusCos(const string& name, const string& producer);

	/*
	* Destructorul unui obiect de clasa CosCumparaturi
	* Il setam ca fiind default folosind calificativul cu acelasi nume
	* Metoda va fi virtuala pentru a evita fenomenul de slicing in cazul polimorfismului
	*/
	virtual ~CosCumparaturi() = default;
};