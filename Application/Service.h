#pragma once

#include "AbstractRepo.h"
#include "ProductValidator.h"
#include "CosCumparaturi.h"
#include "Undo.h"
#include "Observer.h"

#include <map>     // pentru std::map
#include <vector>  // pentru std::vector
#include <memory>  // pentru std::unique_ptrs
#include <utility> // pentru std::pair si make_pair

using std::map;
using std::pair;
using std::vector;
using std::unique_ptr;

class Service : public Observable {
private:
	// atribute (campuri) si metode (functii) private

	AbstractRepo& repo;                        // atribut de tip referinta la un obiect repo de clasa AbstractRepo
	ProductValidator& valid;                   // atribut de tip referinta la un obiect valid de clasa ProductValidator
	CosCumparaturi cosCumparaturi;             // atribut de tip obiect de clasa cosCumparaturi
	CosCumparaturi& cos;                       // atribut de tip referinta la un obiect cos de clasa cosCumparaturi
	vector<unique_ptr<ActiuneUndo>> undo_list; // atribut de tip vector din STL (Standard Template Library) cu elemente avand tipul pointer la obiecte de clasa ActiuneUndo

	/*
	* Functie booleana care verifica daca un produs (obiect de clasa Product) p respecta filtrul de pret price in raport cu semnul (simbolul) de inegalitate sign
	* Date de intrare: p     - referinta constanta la un obiect de clasa Product
	*                  price - referinta constanta la un string (sir de caractere din STL = Standard Template Library)
	*                  sign  - referinta constanta la un string (sir de caractere din STL = Standard Template Library)
	* Preconditii: sign = "<" sau sign = "=" sau sign = ">"
	* Date de iesire (rezultate): valoare booleana (true (1) sau false (0)), adica valoare logica de adevar
	* Postconditii: validPriceFilter = false, daca produsul p nu va fi filtrat (nu satisface filtrul impus)
	*                                  true , daca produsul p va fi filtrat (satisface filtrul impus)
	* Exceptii: metoda privata poate arunca urmatoarele exceptii:
	* [!]ServiceException cu mesajul "[!]Simbol de inegalitate invalid!\n" daca nu sunt respectate preconditiile (sign <> "<", sign <> "=" si sign <> ">")
	*/
	// bool validPriceFilter(const Product& p, const string& price, const string& sign) const;

	/*
	* Functie booleana care verifica daca un produs (obiect de clasa Product) p respecta filtrul de nume name (are atributul name egal cu parametrul name care reprezinta filtrul)
	* Date de intrare: p    - referinta constanta la un obiect de clasa Product
	*                  name - referinta constanta la un string (sir de caractere din STL = Standard Template Library)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true (1) sau false (0)), adica valoare logica de adevar
	* Postconditii: validNameFilter = false, daca produsul p nu va fi filtrat (nu satisface filtrul impus)
	*                                 true , daca produsul p va fi filtrat (satisface filtrul impus)
	* Exceptii: -
	*/
	// bool validNameFilter(const Product& p, const string& name) const;

	/*
	* Functie booleana care verifica daca un produs (obiect de clasa Product) p respecta filtrul de producator producer (are atributul producer egal cu parametrul producer care reprezinta filtrul)
	* Date de intrare: p        - referinta constanta la un obiect de clasa Product
	*                  producer - referinta constanta la un string (sir de caractere din STL = Standard Template Library)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true (1) sau false (0)), adica valoare logica de adevar
	* Postconditii: validProducerFilter = false, daca produsul p nu va fi filtrat (nu satisface filtrul impus)
	*                                     true , daca produsul p va fi filtrat (satisface filtrul impus)
	* Exceptii: -
	*/
	// bool validProducerFilter(const Product& p, const string& producer) const;

	/*
	* Metoda care sorteaza in-place crescator o lista products de obiecte de clasa Product dupa un criteriu crt
	* Date de intrare: products - referinta la o lista (vector) de obiecte de clasa Product
	*                  crt      - referinta constanta la un string (criteriul de sortare)
	* Preconditii: crt trebuie sa fie stringul "1", "2" sau "3"
	* Date de iesire: -
	*                 arunca exceptie daca criteriul crt nu este valid
	* Postconditii: lista products va fi sortate/ordonata crescator dupa criteriu nume (crt = "1"), pret (crt = "2") sau nume + tip (crt = "3")
	* Exceptii: metoda ridica exceptie de tipul ServiceException cu mesajul de eroare/exceptie "[!]Criteriu de sortare invalid!\n" daca nu se respecta preconditiile (crt <> "1" si crt <> "2" si crt <> "3", adica criteriu de sortare este invalid)
	*/
	// void sortProductsAscending(vector<Product>& products, const string& crt) const;
	
	/*
	* Metoda care sorteaza in-place descrescator o lista products de obiecte de clasa Product dupa un criteriu crt
	* Date de intrare: products - referinta la o lista (vector) de obiecte de clasa Product
	*                  crt      - referinta constanta la un string (criteriul de sortare)
	* Preconditii: crt trebuie sa fie stringul "1", "2" sau "3"
	* Date de iesire: -
	*                 arunca exceptie daca criteriul crt nu este valid
	* Postconditii: lista products va fi sortate/ordonata descrescator dupa criteriu nume (crt = "1"), pret (crt = "2") sau nume + tip (crt = "3")
	* Exceptii: metoda ridica exceptie de tipul ServiceException cu mesajul de eroare/exceptie "[!]Criteriu de sortare invalid!\n" daca nu se respecta preconditiile (crt <> "1" si crt <> "2" si crt <> "3", adica criteriu de sortare este invalid)
	*/
	// void sortProductsDescending(vector<Product>& products, const string& crt) const;
	
	/*
	* Metoda privata care sorteaza/ordoneaza in-place o lista de obiecte de clasa Product dupa atributul/campul name (nume) in ordine crescatoare sau descrescatoare
	* Date de intrare: products - referinta la o lista (vector din STL) de obiecte de clasa Product
	*				   reversed - variabila de tip bool (tip de data logic), care poate lua doar valorile true (1) si false (0)
	* Preconditii: reversed = true  => sortare crescatoare
	*              reversed = false => sortare descrescatoare
	* Date de iesire (rezultate): -
	* Postconditii: in urma apelului, lista products va contine produse sortate crescator (reversed = 0) sau descrescator (reversed = 1) dupa numele (atributul privat name) produselor
	* Exceptii aruncate/ridicate: -
	*/
	void sortCrtName(vector<Product>& products, bool reversed) const;
	
	/*
	* Metoda privata care sorteaza/ordoneaza in-place o lista de obiecte de clasa Product dupa atributul/campul price (pret) in ordine crescatoare sau descrescatoare
	* Date de intrare: products - referinta la o lista (vector din STL) de obiecte de clasa Product
	*				   reversed - variabila de tip bool (tip de data logic), care poate lua doar valorile true (1) si false (0)
	* Preconditii: reversed = true  => sortare crescatoare
	*              reversed = false => sortare descrescatoare
	* Date de iesire (rezultate): -
	* Postconditii: in urma apelului, lista products va contine produse sortate crescator (reversed = 0) sau descrescator (reversed = 1) dupa pretul (atributul privat price) produselor
	* Exceptii aruncate/ridicate: -
	*/
	void sortCrtPrice(vector<Product>& products, bool reversed) const;

	/*
	* Metoda privata care sorteaza/ordoneaza in-place o lista de obiecte de clasa Product dupa atributele/campurile name (nume) si type (tip) in ordine crescatoare sau descrescatoare
	* Date de intrare: products - referinta la o lista (vector din STL) de obiecte de clasa Product
	*				   reversed - variabila de tip bool (tip de data logic), care poate lua doar valorile true (1) si false (0)
	* Preconditii: reversed = true  => sortare crescatoare
	*              reversed = false => sortare descrescatoare
	* Date de iesire (rezultate):
	* Postconditii: in urma apelului, lista products va contine produse sortate crescator (reversed = 0) sau descrescator (reversed = 1) dupa numele (atributul privat name) produselor si dupa tipul acestora (atributul privat type)
	* Daca doua produse au acelasi atribtut name (nume), atunci ele vor fi sortate/ordonate dupa atributul type (tip)
	* Exceptii aruncate/ridicate: -
	*/
	void sortCrtNamePlusType(vector<Product>& products, bool reversed) const;

	/*
	* Procedura care filtreaza o lista de produse (obiecte de clasa Product) dupa criteriul pret (in functie de atributul price) si in raport cu o relatie sign (simbol/semn de egalitate sau inegalitate)
	* Date de intrare: products      - referinta constanta la o lista de obiecte de clasa Product (lista care se filtreaza)
	*                  filtered_list - referinta constanta la o lista de obiecte de clasa Product (lista in care are loc filtrarea)
	*                  price         - referinta constanta la un string
	*                  sign          - referinta constanta la un string
	* Preconditii: stringul price trebuie sa contina reprezentarea unui numar real
	*              sign = "<" sau sign = "=" sau sign = ">"
	* Date de iesire (rezultate): -
	* Postconditii: lista filtered_list va contine toate produsele (obiectele de clasa Product) din products care satisfac filtrul impus: au atributul price (pret) mai mare strict (sign = ">"), mai mic strict (sign = "<") sau egal (sign = "=") decat parametrul price convertit la double
	* Exceptii: metoda privata poate arunca urmatoarele exceptii:
	* [!]ServiceException daca nu sunt respectate preconditiile (price nu e un numar real sau sign <> "<" si sign <> "=" si sign <> ">")
	*/
	void filterAfterPrice(const vector<Product>& products, vector<Product>& filtered_list, const string& price, const string& sign) const;

	/*
	* Procedura care filtreaza o lista de produse (obiecte de clasa Product) dupa criteriul nume (in functie de atributul name)
	* Date de intrare: products      - referinta constanta la o lista de obiecte de clasa Product (lista care se filtreaza)
	*                  filtered_list - referinta constanta la o lista de obiecte de clasa Product (lista in care are loc filtrarea)
	*                  name          - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: lista filtered_list va contine toate produsele (obiectele de clasa Product) din products care satisfac filtrul impus: au atributul name (nume) asemenea cu parametrul name
	* Exceptii: - (subrutina nu arunca/ridica exceptii)
	*/
	void filterAfterName(const vector<Product>& products, vector<Product>& filtered_list, const string& name) const;

	/*
	* Procedura care filtreaza o lista de produse (obiecte de clasa Product) dupa criteriul producator (in functie de atributul producer)
	* Date de intrare: products      - referinta constanta la o lista de obiecte de clasa Product (lista care se filtreaza)
	*                  filtered_list - referinta constanta la o lista de obiecte de clasa Product (lista in care are loc filtrarea)
	*                  producer      - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: lista filtered_list va contine toate produsele (obiectele de clasa Product) din products care satisfac filtrul impus: au atributul producer (producator) asemenea cu parametrul producer
	* Exceptii: - (subrutina nu arunca/ridica exceptii)
	*/
	void filterAfterProducer(const vector<Product>& products, vector<Product>& filtered_list, const string& producer) const;

public:
	// metode (functii) publice

	/*
	* Constructorul default al unui obiect de clasa Service
	* Prin calificativul delete nu permitem creare de obiecte de clasa Service fara a specifica atributele repo si valid
	*/
	Service() = delete;

	/*
	* Constructor custom al unui obiect de clasa Service care primeste o referinta la un obiect repo de clasa AbstractRepo si o referinta la un obiect valid de clasa ProductValidator
	* Contructorul va popula atributele private repo si valid ale obiectului instantiat cu obiectele primite
	*/
	Service(AbstractRepo& repo, ProductValidator& valid) noexcept : repo{ repo }, valid{ valid }, cosCumparaturi{ repo }, cos{ cosCumparaturi }  {
		
	}

	/*
	* Constructor custom al unui obiect de clasa Service care primeste o referinta la un obiect repo de clasa AbstractRepo, o referinta la un obiect valid de clasa ProductValidator si o referinta la un obiect cos de clasa CosCumparaturi
	* Contructorul va popula atributele private repo, valid si cos ale obiectului instantiat cu obiectele primite
	*/
	Service(AbstractRepo& repo, ProductValidator& valid, CosCumparaturi& cos) noexcept : repo{ repo }, valid{ valid }, cosCumparaturi{ repo }, cos{ cos }  {

	}

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa Service)
	*/
	Service(const Service& ot) = delete;

	/*
	* Metoda care compara doua stringuri str_1 si str_2 fara a tine cont de diferenta dintre litere mici si mari
	* Date de intrare: str_1 - adresa constanta la un string
	*                  str_2 - adresa constanta la un string
	* Preconditii: -
	* Date de iesire: bool (true sau false)
	* Postconditii: cmpStrings = true  (1), daca cele doua stringuri coincid (sunt identice)
	*                          = false (0), in caz contrar (cele doua stringuri str_1 si str_2 difera)
	*/
	bool cmpStrings(const string& str_1, const string& str_2) const noexcept;

	/*
	* Metoda care verifica daca un string contine reprezentarea unui numar real
	* Date de intrare: str - adresa constanta la un string
	* Preconditii: -
	* Date de iesire: -, daca stringul str este un numar real
	*                 arunca/ridica exceptie daca str nu contine reprezentarea text/scrisa a unui double (numar real in dubla precizie)
	* Postconditii: -
	* Exceptii: metoda arunca exceptie de tipul ServiceException cu mesajul "[!]Pretul introdus nu este un numar real!\n" daca stringul dat ca parametru nu contine reprezentarea unui double
	*/
	void verifyIfDouble(const string& str) const;

	/*
	* Metoda care verifica daca un string contine reprezentarea unui numar intreg cu semn (signed)
	* Date de intrare: str - adresa constanta la un string
	* Preconditii: -
	* Date de iesire: -, daca stringul str este un numar intreg
	*                 arunca/ridica exceptie daca str nu contine reprezentarea text/scrisa a unui intreg
	* Postconditii: -
	* Exceptii: metoda arunca exceptie de tipul ServiceException cu mesajul "[!]Informatia introdusa nu este un numar intreg!\n" daca stringul dat ca parametru nu contine reprezentarea unui intreg
	*/
	void verifyIfInteger(const string& str) const;

	/*
	* Metoda care incearca sa adauge un obiect de clasa Product cu atributele name, type, price si producer
	* Date de intrare: name     - referinta constanta la un string
	*                  type     - referinta constanta la un string
	*                  price    - referinta constanta la un double
	*                  producer - referinta constanta la un string
	* Preconditii: name     <> "" (name trebuie sa fie un string nevid)
	*			   type     <> "" (type trebuie sa fie un string nevid)
	*              price     > 0
	*              producer <> "" (producer trebuie sa fie un string nevid)
	* Date de iesire: -, daca adaugarea s-a realizat cu succes
	*                 arunca exceptie in caz contrar
	* Postconditii: -
	* Exceptii: metoda poate arunca urmatoarele exceptii:
	* [!]RepoException daca produsul se afla deja in magazin (in repo)
	* [!]ProductException (daca unul din atributele produsului nu este valid, adica nu sunt respectate preconditiile (conditiile impuse asupra datelor/parametrilor de intrare))
	*/
	void add(const string& name, const string& type, const double& price, const string& producer);

	/*
	* Metoda care incearca sa stearga/elimine un obiect de clasa Product cu numele name si producatorul producer din magazin
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: name     <> "" (name trebuie sa fie o referinta constanta la un string nevid)
	*              producer <> "" (producer trebuie sa fie o referinta constanta la un string nevid)
	* Date de iesire: -, daca stergerea s-a realizat cu succes
	*                 arunca exceptie in caz contrar
	* Postconditii: -
	* Exceptii: metoda poate arunca urmatoarele exceptii:
	* [!]RepoException daca nu exista obiecte de clasa Product in lista din repo sau produsul nu se afla in magazin (in repo)
	* [!]ServiceException (daca nu sunt respectate preconditiile <=> name sau producer sunt referinte constante la stringuri vide)
	*/
	void del(const string& name, const string& producer);

	/*
	* Metoda care incearca sa modifice/actualizeze atributele type si price ale unui obiect de clasa Product care are numele name si producatorul producer
	* Date de intrare: name     - referinta constanta la un string
	*                  type     - referinta constanta la un string
	*                  price    - referinta constanta la un double
	*                  producer - referinta constanta la un string
	* Preconditii: name     <> "" (name trebuie sa fie un string nevid)
	*			   type     <> "" (type trebuie sa fie un string nevid)
	*              price     > 0
	*              producer <> "" (producer trebuie sa fie un string nevid)
	* Date de iesire: -, daca modificarea s-a realizat cu succes
	*                 arunca exceptie in caz contrar
	* Postconditii: -
	* Exceptii: metoda poate arunca urmatoarele exceptii:
	* [!]RepoException daca nu exista obiecte de clasa Product in lista din repo sau produsul nu se afla in magazin (in repo)
	* [!]ProductException (daca unul din atributele produsului nu este valid, adica nu sunt respectate preconditiile (conditiile impuse asupra datelor/parametrilor de intrare))
	*/
	void modify(const string& name, const string& type, const double& price, const string& producer);

	/*
	* Metoda care cauta un obiect de clasa Product cu numele name si producatorul producer in lista de obiecte de clasa Product din repository (magazin)
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: name     <> "" (name trebuie sa fie o referinta constanta la un string nevid)
	*              producer <> "" (producer trebuie sa fie o referinta constanta la un string nevid)
	* Date de iesire: referinta constanta la un obiect de clasa Product, daca acesta exista in stocul din magazin
	*                 arunca exceptie in caz contrar
	* Postconditii: search = obiectul cautat cu numele name si producatorul producer
	* Exceptii: metoda poate arunca urmatoarele exceptii:
	* [!]RepoException daca nu exista obiecte de clasa Product in lista din repo sau produsul nu se afla in magazin (in repo)
	* [!]ServiceException (daca nu sunt respectate preconditiile <=> name sau producer sunt referinte constante la stringuri vide)
	*/
	const Product& search(const string& name, const string& producer) const;

	/*
	* Metoda care returneaza toate produsele din magazin
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire: copie la o lista (vector) de obiecte de clasa Product
	* Postconditii: getAll = lista de produse din repo (magazin)
	* Exceptii: metoda poate arunca urmatoarele exceptii:
	* [!]RepoException daca nu exista obiecte de clasa Product in lista din repo
	*/
	vector<Product> getAll() const;

#undef TKey
#undef TValue
#undef dictionary

#define TKey string
#define TValue pair<string, unsigned>
#define dictionary map<TKey, TValue>

	/*
	* Functie de tip operand (rezultat) care returneaza un dictionary (map = dictionar ordonat) care contine toate tipurile de produse (obiecte de clasa Product) din magazin (repo) si de cate ori apare fiecare
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): map din STL care va avea ca si cheie (key) un sir de caractere din STL (TKey = string), iar ca si valoare o pereche (TValue = pair) care contine un string (first) si un intreg fara semn (second)
	* Postconditii: dictionarul returnat/intors de functie contine ca si chei toate tipurile de produse din magazin ordonate/sortate crescator dupa tip (cheie) si pentru fiecare tip de produs retine ca si valoare tipul produsului si cate produse cu tipul respectiv exista in stoc
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]RepoException cu mesajul "[!]Nu exista produse in magazin!\n", daca stocul din magazin este gol (nu exista entitati (obiecte de clasa Product) in repo)
	*/
	dictionary countType() const;

	/*
	* Procedura care face undo la operatiile de adaugare, modificare si stergere pentru repository
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): un string (structura de date din STL)
	* Postconditii: - dupa apelul functiei se va reface ultima adunare (se va sterge ultimul produs adaugat in magazin), daca ultima operatie efectuata a fost o adunare
	*                                                        stergere (se va re-adauga ultimul produs sters din magazin), daca ultima operatie efectuata a fost o stergere
	*                                                        modificare (se va modifica ultimul produs modificat din magazin, acesta va reveni la configuratia de dinainte de modificare), daca ultima operatie efectuata a fost o modificare
	*				- stringul intors/returnat de functie este: "[+]Undo stergere realizat cu succes!\n"  , daca s-a facut undo la stergere (ultima operatie pe repo a fost una de stergere)
	*                                                           "[+]Undo adaugare realizat cu succes!\n"  , daca s-a facut undo la adaugare (ultima operatie pe repo a fost una de adaugare)
	*															"[+]Undo modificare realizat cu succes!\n", daca s-a facut undo la modificare (ultima operatie pe repo a fost una de modificare)
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]ServiceException cu mesajul "[!]Nu se mai poate realiza operatia de undo\n", daca nu se mai poate face undo la lista de produse din repository
	*/
	string undo();

	/*
	* Functie care filtreaza produsele din magazin dupa un anumit criteriu (pret, nume, producator), filtru (valoarea pretului, numelui sau producatorului) si un semn (<, = sau >) in cazul in care criteriul de filtrare este pretul
	* Date de intrare: crt    - referinta constanta la un string (crt    = criteriul de filtrare)
	*                  filter - referinta constanta la un string (filter = filtrul)
	*                  sign   - referinta constanta la un string (semnul dupa care sa se faca filtrarea ca pret)
	* Preconditii: crt  apartine {"1", "2", "3"}
	*              sign apartine {"<", "=", ">"}, doar daca crt = "1"
	* Date de iesire: un vector de obiecte de clasa Product
	* Postconditii: filterProducts = lista (vector) de produse care respecta filtrul ales
	* Exceptii:
	* [!]ServiceException daca nu sunt respectate preconditiile (crt <> "1", crt <> "2" si crt <> "3" sau daca crt = "1" atunci sign <> "<", sign <> "=" si sign <> ">")
	*/
	vector<Product> filterProducts(const string& crt, const string& filter, const string& sign) const;

	/*
	* Metoda care sorteaza out-of-place (not-in-place) crescator sau descrescator lista de produse din magazin
	* Date de intrare: crt - referinta constanta la un string (criteriul de sortare)
	*                  ord - referinta constanta la un string (ordinea de sortare)
	* Preconditii: crt trebuie sa fie stringul "1", "2" sau "3"
	*              ord trebuie sa fie stringul "c" ("C") sau "d" ("D")
	* Date de iesire: vector (lista) de obiecte de clasa Product
	*                 arunca exceptie daca criteriul crt nu este valid sau ordinea ord nu este valida
	* Postconditii: sortProducts = o copie a listei de produse din repo sortate dupa nume (crt = "1"), pret (crt = "2"), nume + tip (crt = "3") in ordine crescatoare (ord = "c" sau ord = "C") sau descrescatoare (ord = "d" sau ord = "D")
	* Exceptii:
	* [!]ServiceException daca nu sunt respectate preconditiile
	*/
	vector<Product> sortProducts(const string& crt, const string& ord) const;

	/*
	* Functie de tip operand (rezultat) care returneaza o referinta la atributul privat cos al unui obiect de clasa Service
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): CosCumparaturi& - referinta la un obiect de clasa CosCumparaturi
	* Postconditii: metoda publica intoarce prin numele ei o referinta la atributul privat cos al obiectului pe care se apeleaza
	* Exceptii: metoda nu arunca/ridica exceptii
	*/
	CosCumparaturi& getCosSrv() const noexcept;

	/*
	* Procedura care goleste toate produsele din cosul de cumparaturi
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Nu exista produse in cosul de cumparaturi!\n" daca cosul de cumparaturi este gol
	*/
	void golireCos();

	/*
	* Procedura care incearca sa adauge un produs cu numele name si producatorul producer in cosul de cumparaturi al utilizatorului (userului)
	* Date de intrare: name     - referinta constanta la un string (dinamic) din STL
	*                  producer - referinta constanta la un string (dinamic) din STL
	* Preconditii: name     <> "" (stringul name trebuie sa fie nevid)     <=> name.length     <> 0
	*              producer <> "" (stringul producer trebuie sa fie nevid) <=> producer.length <> 0
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Produsul cautat nu se afla in stoc!\n"
	* [!]ServiceException (nu sunt respectate preconditiile privind datele de intrare)
	* cu unul din mesajele: "[!]Nume invalid!\n", daca doar numele name este invalid (stringul name este vid)
	*                       "[!]Producator invalid!\n", daca doar producatorul producer este invalid (stringul producer este vid)
	*                       "[!]Nume invalid!\n[!]Producator invalid!\n", daca atat numele name cat si producatorul producer sunt atribute invalide (stringuri vide)
	*/
	void adaugareCos(const string& name, const string& producer);

	/*
	* Procedura care incearca sa adauge num produse random din stocul magazinului in cosul de cumparaturi
	* Date de intrare: num - referinta constanta la un string (sir de caractere alocat dinamic din STL = Standard Template Library)
	* Preconditii: stringul num trebuie sa contina reprezentarea scrisa/text a unui numar intreg fara semn (unsigned = numar natural)
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]ServiceException cu mesajul "[!]Numarul introdus nu este o valoare pozitiva!\n", daca num contine reprezentarea unui numar care nu este pozitiv (numar intreg negativ)
	* [!]ServiceException cu mesajul "[!]Informatia introdusa nu este un numar intreg!\n", daca num nu contine reprezentarea unui numar intreg (integer) cu (signed) sau fara semn (unsigned)
	*/
	void generareCos(const string& num);

	/*
	* Procedura care incearca sa scrie lista de produse din cosul de cumparaturi intr-un fisier CSV (filetype = "csv") sau HTML (filetype = "html") cu numele filename (filename nu trebuie sa contina extensia .csv sau .html, aceasta va fi adaugata automat in functie de natura fisierului)
	* Date de intrare: filename - referinta constanta la un string (sir de caractere din STL)
	*                  filetype - referinta constanta la un string (sir de caractere din STL)
	* Preconditii: filename trebuie sa fie un string nevid (adica sa contina cel putin un caracter)
	*              filetype trebuie sa fie stringul "html" sau "csv" (case insensitive)
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii (nu sunt respectate preconditiile):
	* [!]ServiceException cu mesajul "[!]Numele fisierului nu poate fi vid!\n", daca stringul filename este vid
	* [!]ServiceException cu mesajul "[!]Tip fisier export invalid!\n", daca filetype nu este un tip de fisier valabil
	*/
	void exportCos(const string& filename, const string& filetype);

	/*
	* Functie de tip operand (rezultat) care returneaza pretul total al produselor din cos
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta constanta la o variabila de tip double (numar real in dubla precizie)
	* Postconditii: rezultatul intors/returnat de functie reprezinta suma preturilor (atributelor price) ale produselor (obiecte de clasa Product) din cosul de cumparaturi
	* Exceptii: -
	*/
	const double& totalCos() noexcept;

	/*
	* Functie de tip operand (rezultat) care returneaza numarul total de produse din cos
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): intreg fara semn (unsigned)
	* Postconditii: rezultatul intors/returnat de functie reprezinta numarul de produse din cosul de cumparaturi
	* Exceptii: -
	*/
	unsigned cantitateCos() noexcept;

	/*
	* Functie de tip operand (rezultat) care returneaza o copie la lista de produse (obiecte de clasa Product) din cosul de cumparaturi
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): vector din STL (Standard Template Library) cu obiecte de clasa Product
	* Postconditii: vectorul intors/returnat/furnizat de subprogram/subrutina contine toate produsele din lista de cumparaturi
	* Exceptii: metoda poate arunca/ridica urmatoarele exceptii:
	* [!]CosException cu mesajul "[!]Nu exista produse in cosul de cumparaturi!\n", in cazul in care lista care contine produsele din cosul de cumparaturi este goala/vida
	*/
	vector<Product> getCosCumparaturi() const;
};

