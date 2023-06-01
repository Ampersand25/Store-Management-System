#pragma once

#include "CosCumparaturi.h"

#define TKey Product // definim TKey ca fiind Product (clasa)

class FileCosCumparaturi : public CosCumparaturi // clasa FileCosCumparaturi (clasa derivata) mosteneste public din clasa CosCumparaturi (clasa de baza)
{
private:
	// atribute private

	string filename; // numele fisierului in care o sa salvam produsele (obiecte de clasa Product) din cosul de cumparaturi

	// metode (functii) private

	/*
	* Metoda care citeste continutul fisierului text cu numele filename si salveaza in cosul de cumparaturi produsele (obiectele de clasa Product) din acest fisier
	* Procedura (functia procedurala) incarca datele din fisier text in memorie => face import
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: in memoria RAM (Random Access Memory) vor fi incarcate toate produsele (obiecte de clasa Product) din fisierul text cu numele filename
	* Exceptii: - (metoda nu arunca exceptii)
	* Metoda face exit cu codul de retur 1 (exit status/code) daca datele din fisier nu sunt valide (pretul nu este corect definit)
	*/
	void loadFromFile(); // metoda/functie privata care incarca produsele din fisier text in memoria RAM

	/*
	* Metoda care scrie (afiseaza/tipareste) in fisierul cu numele filename, lista de produse (obiecte de clasa Product) din cosul de cumparaturi
	* Astfel se salveaza datele in fisier (persistenta datelor)
	* Procedura (functia procedurala) incarca datele din memorie in fisier => face export
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: fisierul cu numele filename va contine toate produsele (obiecte de clasa Product) existente in cosul de cumparaturi dupa apelul acestei metode
	* Exceptii: - (metoda nu arunca exceptii)
	*/
	void writeToFile(); // metoda/functie privata care incarca produsele din memoria RAM in fisier text

public:
	/*
	* Destructorul default (implicit/prestabilit) al unui obiect de clasa FileCosCumparaturi
	* Marcam acest constructor ca fiind interzis (sters) folosind calificativul delete
	* Astfel, nu vor putea fi instantiate obiecte de clasa FileCosCumparaturi folosind acest constructor (fara a furniza parametrii de intrare pentru constructor)
	*/
	FileCosCumparaturi() = delete;


	/*
	* Constructorul custom al unui obiect de clasa FileCosCumparaturi
	* Acest constructor primeste doi parametrii de intrare (parametrii formali/simbolici), ci anume: repo si filename
	* repo     - referinta la un obiect de clasa AbstractRepo
	* filename - referinta constanta la un string (sir de caractere din STL (Standard Template Library)) reprezentand numele fisierului in care vor fi salvate produsele (obiecte de clasa Product) din cosul de cumparaturi
	* CosCumparaturi(repo) - apeleaza constructorul din clasa de baza CosCumparaturi cu argumentul repo (constructor custom)
	*/
	FileCosCumparaturi(AbstractRepo& repo, const string& filename) : CosCumparaturi(repo), filename{ filename } {
		// incarcam datele (obiecte de clasa Product) din fisier in memorie
		// se realizeaza astfel operatia de import
		this->loadFromFile(); // loadFromFile();
	}

	/*
	* Procedura (functie procedurala) care elimina toate produsele din cosul de cumparaturi
	* Folosind calificativul override marcam ca aceasta metoda este mostenita din clasa de baza (este declarata ca fiind o metoda virtuala in clasa de baza CosCumparaturi) si suprascrisa in clasa derivata (clasa FileCosCumparaturi)
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire: -
	* Postconditii: atributul privat total_price (care stocheaza pretul curent al produselor din cos) se va reseta (va deveni 0)
	*               cosul de cumparaturi va deveni gol (atributul privat cos va fi un vector vid (fara elemente))
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Nu exista produse in cosul de cumparaturi!\n", in cazul in care nu exista produse in cos (cosul este gol)
	*/
	void golesteCos() override;

	/*
	* Procedura (subprogram procedural) care incearca adaugarea in cosul de cumparaturi a unui produs din magazin cu numele name si producatorul producer
	* Folosind calificativul override marcam ca aceasta metoda este mostenita din clasa de baza (este declarata ca fiind o metoda virtuala in clasa de baza CosCumparaturi) si suprascrisa in clasa derivata (clasa FileCosCumparaturi)
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
	void adaugaInCos(const string& name, const string& producer) override;

	/*
	* Procedura (subprogram procedural) care incearca adaugarea in cosul de cumparaturi a number_of_products produse (obiecte de clasa Product) random (in mod arbitrar/aleator) din magazin (produse care exista in stoc)
	* Folosind calificativul override marcam ca aceasta metoda este mostenita din clasa de baza (este declarata ca fiind o metoda virtuala in clasa de baza CosCumparaturi) si suprascrisa in clasa derivata (clasa FileCosCumparaturi)
	* Date de intrare: number_of_products - intreg (int = integer) fara semn (unsigned, adica intreg pozitiv), adica variabila care retine un numar natural (>= 0)
	* Preconditii: -
	* Date de iesire: -
	* Postconditii: atributul privat total_price va fi incrementat cu pretul fiecarui produs din cele number_of_products generate din stocul magazinului
	*               se adauga number_of_products produse in cosul de cumparaturi
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Produsul cautat nu se afla in stoc!\n", in cazul in care nu exista niciun produs (obiect de clasa Product) cu numele name si producatorul producer in magazin
	*/
	void genereazaCos(unsigned number_of_products) override;

	/*
	* Procedura (subrutina procedurala) care incearca sa modifice/actualizeze toate produsele cu acelasi nume si producator ca si produsul product din cosul de cumparaturi
	* Folosind calificativul override marcam ca aceasta metoda este mostenita din clasa de baza (este declarata ca fiind o metoda virtuala in clasa de baza CosCumparaturi) si suprascrisa in clasa derivata (clasa FileCosCumparaturi)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire: -
	* Postconditii: toate produsele cu acelasi nume si producator din cosul de cumparaturi ca si product vor fi actualizate (vor avea acelasi tip si pret ca si produsul product in urma apelului metodei)
	* Exceptii: -
	*/
	void modificaProduseCos(const TKey& product) override;

	/*
	* Procedura (subrutina procedurala) care incearca sa stearga/elimine toate produsele (obiectele de clasa Product) din cosul de cumparaturi care au numele name si producatorul producer
	* Folosind calificativul override marcam ca aceasta metoda este mostenita din clasa de baza (este declarata ca fiind o metoda virtuala in clasa de baza CosCumparaturi) si suprascrisa in clasa derivata (clasa FileCosCumparaturi)
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: name     <> "" (unde "" - stringul vid si <> - operatorul de diferit)
	*              producer <> "" (unde "" - stringul vid si <> - operatorul de diferit)
	* Date de iesire: -
	* Postconditii: apelul metodei publice stergeProduseCos va elimina din cosul de cumparaturi toate produsele cu numele name si producatorul producer
	* Exceptii: -
	*/
	void stergeProduseCos(const string& name, const string& producer) noexcept override;

	/*
	* Procedura (subrutina procedurala) care incearca sa stearga/elimine un singur produs (obiect de clasa Product) din cosul de cumparaturi care are numele name si producatorul producer
	* Folosind calificativul override marcam ca aceasta metoda este mostenita din clasa de baza (este declarata ca fiind o metoda virtuala in clasa de baza CosCumparaturi) si suprascrisa in clasa derivata (clasa FileCosCumparaturi)
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
	void eliminaProdusCos(const string& name, const string& producer) override;

	/*
	* Destructorul unui obiect de clasa FileCosCumparaturi
	* Marcam acest destructor ca fiind unul default (implicit/prestabilit) folosind calificativul default
	*/
	~FileCosCumparaturi() = default;
};