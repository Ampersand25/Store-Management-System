#pragma once

#include "AbstractRepo.h"

#include <map> // pentru std::map

using std::map; // TAD (Tip Abstract de Date) dictionar ordonat (sortat) din STL (Standard Template Library)
                // acesta mapeaza o cheie la o anumita valoare (valoare de dispersie = hash value)

typedef Product TKey;           // tipul de data al unei chei din dictionar
typedef bool TValue;            // tipul valorii asociate unei chei din dictionar
typedef map<TKey, TValue> dict; // un dictionar ordonat/sortat in care cheile (obiecte de clasa Product) au asociate valori booleene (false sau true)
								// d: dict => m.first : TKey (Product)
                                //            m.second: TValue (bool)

// daca un produs din magazin are asociata ca si cheie - false inseamna ca acesta nu este disponibil momentan in stoc
//                                                     - true  inseamna ca acesta se afla in stocul magazinului si poate fi cumparat/achizitionat

class ExceptionRepo : public AbstractRepo // clasa ExceptionRepo este derivata din clasa de baza AbstractRepo (clasa pur abstracta <=> contine doar metode pur virtuale)
{
private:
	// atribute (campuri) si metode private

	double probability; // numar real in virgula flotanta (mobila) cu dubla precizie (double precision)

	dict elems; // lista in care vom retine produsele (obiecte de clasa Product) din magazin (repo)

	/*
	* Metoda privata care arunca exceptie (obiect de clasa std::exception) cu o probabilitate egala cu atributul privat/campul probability
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda poate arunca exceptie de clasa std::exception cu mesajul de eroare "[!]Exception!\n"
	*/
	void checkProbability() const;

	/*
	* Metoda privata care verifica daca containerul de date contine sau nu elemente (adica daca avem produse (obiecte de clasa Product) in magazin (repo))
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana de adevar (valoare logica), adica literalii false (0) sau true (orice valoare nenula, adica diferita de false (0))
	* Postcondii: isEmpty = true , nu exista produse in repozitoriu (repository)                   => repo-ul este gol
	*                     = false, exista cel putin un produs (obiect de clasa Product) in magazin => repo-ul nu este gol
	*/
	bool isEmpty() const noexcept;

public:
	// metode publice

	/*
	* Constructorul default (implicit) al unui obiect de clasa ExceptionRepo
	* Il stergem folosind calificativul delete
	* Astfel, la instantierea obiectelor de clasa ExceptionRepo va trebui sa apelam un constructor custom existen (care sa primeasca parametrii)
	*/
	ExceptionRepo() = delete;
	
	/*
	* Constructor custom a unui obiect de clasa ExceptionRepo
	* Acesta primeste o referinta constanta la un double (numar real in dubla precizie) si instantiaza campul/atributul privat probability al obiectului creat cu aceasta valoare
	*/
	ExceptionRepo(const double& probability) noexcept : probability { probability } {
		
	}

	/*
	ExceptionRepo(const double& probability) noexcept : AbstractRepo(), probability { probability } {

	}
	*/

	/*
	ExceptionRepo(const double& probability) noexcept : AbstractRepo{}, probability { probability } {
		
	}
	*/
	
	/*
	* Evitam copierea de obiecte de clasa ExceptionRepo folosind calificativul delete pe constructorul de copiere
	*/
	ExceptionRepo(const ExceptionRepo& ot) = delete;
	
	/*
	* Evitam copierea de obiecte de clasa ExceptionRepo folosind calificativul delete pe operatorul de assignment (operator de asignare/atribuire)
	*/
	const ExceptionRepo& operator=(const ExceptionRepo& ot) = delete; // void operator=(const ExceptionRepo& ot) = delete;

	// Operatii CRUD pe repo (metode mostenite din clasa de baza AbstractRepo)
	// Aceste metode vor fi suprascrise in cadrul clasei derivate ExceptionRepo

	/*
	* Operatie de tip C (Create), care modifica repo-ul adaugand o inregistrare in acesta (creste numarul de entiati/date salvate in repository/repozitoriu)
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care incearca sa adauge o variabila de tipul TKey (obiect de clasa Product)
	* Date de intrare: product - referinta constanta la o variabila avand tipul de data TKey
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari vizibile in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs deja existent!\n" daca produsul product exista deja in lista din repo (exista un produs cu acelasi nume si producator disponibil in stocul din magazin <=> are valoarea asociata true in map/dictionar)
	*           metoda arunca/ridica exceptie de tipul std::exception cu mesajul "[!]Exception!\n" cu o probabilitate egala cu campul/atributul privat probability
	*/
	void addProduct(const TKey& product) override;
	
	/*
	* Operatie de tip D (Delete), care modifica repo-ul stergand o inregistrare din acesta (scade/descreste numarul de entiati/date salvate in repository/repozitoriu)
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care incearca stearga un obiect de clasa Product cu numele name si producatorul producer din lista de produse (entitati de clasa Product) din repo (magazin)
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari vizibile in repo, adica produse disponibile in stocul din magazin)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul product nu se afla in stocul din magazin (nu exista obiect de clasa Product (entitati/inregistrari) vizibil (cu valoarea true asociata in map/dictionar) nu numele name si producatorul producer in lista din repo)
	*           metoda arunca/ridica exceptie de tipul std::exception cu mesajul "[!]Exception!\n" cu o probabilitate egala cu campul/atributul privat probability
	*/
	void deleteProduct(const string& name, const string& producer) override;

	/*
	* Operatie de tip U (Update), care nu modifica starea repo-ului (dar nu altereaza numarul de inregistrari/obiecte/entitati din acesta, ci doar actualizeaza una existenta)
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care incearca actualizarea/modificarea atributele price si type a unui element de tip TKey (obiect de clasa Product = produs) din repo (magazin)
	* Date de intrare: product - referinta constanta la o variabila de tip TKey (adica la un obiect de clasa Product, TKey - tipul de data al unei chei din map = dictionar)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari vizibile in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul care se doreste a fi actualizat nu se afla in repo (magazin) sau se afla dar este marcat ca fiind invizibil (are valoarea false <=> nu este disponibil in stocul magazinului), adica nu exista nicio inregistrare vizibila (disponibila in magazin) cu numele produsului product si producatorul produsului product
	*           metoda arunca/ridica exceptie de tipul std::exception cu mesajul "[!]Exception!\n" cu o probabilitate egala cu campul/atributul privat probability
	*/
	void modifyProduct(const TKey& product) override;

	/*
	* Operatie de tip R (Read), care nu modifica starea repo-ului
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care cauta un produs in lista de produse din repo dupa nume si producator
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): referinta constanta la un element avand tipul de data TKey (cheie din dictionar, adica obiect de clasa Product)
	* Postconditii: searchProduct() = referinta la obiectul (produsul) cu numele name si producatorul producer gasit (daca acesta se afla in stoc <=> este disponibil)
	*                                 -, daca produsul cautat nu se afla in repo (ridica exceptie) sau se afla dar stocul a fost epuizat (nu poate fi achizitionat)
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari vizibile in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul cautat nu se afla in repo (magazin), adica nu exista nicio inregistrare cu numele name si producatorul producer sau exista una dar este marcata ca fiind invizibila/stearsa (adica nu se afla in stoc)
	*           metoda arunca/ridica exceptie de tipul std::exception cu mesajul "[!]Exception!\n" cu o probabilitate egala cu campul/atributul privat probability
	*/
	const TKey& searchProduct(const string& name, const string& producer) const override;

	/*
	* Operatie de tip R (Read), care nu modifica starea repo-ului
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care returneaza un vector din STL (Standard Template Library) care va contine toate produsele disponibile in magazin (toate cheile din map care au ca si valoare booleana true)
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): un vector de elemente de tipul TKey (tipul de data al unei chei din map/dictionar)
	* Postconditii: getAll() = un vector care contine fiecare inregistrare din repository (repozitoriu) care are ca si valoare asociata in map (dictionar) valoarea logica de adevar true
	*                          -, daca nu exista produse in repo (ridica exceptie) sau toate produsele din repo nu mai sunt disponibile in stocul magazinului (au fost epuizate)
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo sau toate inregistrarile au ca si valoare in map false)
	*           metoda arunca/ridica exceptie de tipul std::exception cu mesajul "[!]Exception!\n" cu o probabilitate egala cu campul/atributul privat probability
	*/
	vector<TKey> getAll() const override;
	
	/*
	* Operatie de tip R (Read), care nu modifica starea repo-ului
	* Metoda mostenita din clasa de baza AbstractRepo (aceasta va fi suprascrisa in clasa derivata)
	* Functie care returneaza numarul de obiecte de clasa Product (numarul de produse) din lista din repository (magazin) care sunt disponibile in stoc (nu au fost epuizate)
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): intreg fara semn (unsigned)
	* Postconditii: len() = numarul de entitati/inregistrari din repo (chei din map/dictionar) care sunt vizibile (au ca si valoare asociata true, ci nu false)
	* Exceptii: metoda arunca/ridica exceptie de tipul std::exception cu mesajul "[!]Exception!\n" cu o probabilitate egala cu campul/atributul privat probability
	*/
	unsigned len() const override;
};