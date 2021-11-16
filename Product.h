#pragma once

#include <string> // pentru std::string

using std::string;

class Product
{
private:
	// atribute/campuri private (nu pot fi accesate din exteriorul clasei, doar din interiorul acesteia)

	// un produs (obiect de clasa Product) este unic identificabil dupa nume (name) si producator (producer)
	// nu pot exista doua produse (entitati) cu acelasi nume (name) si producator (producer)

	string name;     // numele produsului: string (sir de caractere)
	string type;     // tipul produsului: string (sir de caractere)
	double price;    // pretul produsului: numar real in virgula flotanta/mobila cu dubla precizie
	string producer; // producatorul produsului: string (sir de caractere)

public:
	// metode/functii publice (pot fi accesate din exteriorul clasei)

	/*
	* Constructorul default (implicit) al unui obiect de clasa Product
	* Il stergem folosind calificativul delete (vom impiedica astfel instantierea de produse (obiecte de clasa Product) fara specificarea valorilor atributelor (campurilor) private) in constructor
	*/
	Product() = delete;

	/*
	* Constructor custom care primeste 4 valori (name, type, price si producer) si instantiaza un obiect de clasa Product
	* care sa aiba ca si atribute/campuri private copii ale valorile primite
	*/
	Product(string name, string type, double price, string producer) : name{ name }, type{ type }, price{ price }, producer{ producer } {

	}

	/*
	* Constructorul de copiere pentru obiectele de clasa Product
	* Se copiaza atribut cu atribut in obiectul curent campurile obiectului dat ca parametru/argument
	*/
	Product(const Product& ot) : name{ ot.name }, type{ ot.type }, price{ ot.price }, producer{ ot.producer } {
		// std::cout << "[!]Copiere produs!\n";
	}

	/*
	* Metoda getter pentru a obtine atributul privat name al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un string
	* Postconditii: metoda intoarce referinta constanta la campul/atributul name al obiectului pentru care se apeleaza
	*/
	const string& getName() const noexcept;

	/*
	* Metoda getter pentru a obtine atributul privat type al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un string
	* Postconditii: metoda intoarce referinta constanta la campul/atributul type al obiectului pentru care se apeleaza
	*/
	const string& getType() const noexcept;

	/*
	* Metoda getter pentru a obtine atributul privat price al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un double (numar real in dubla precizie)
	* Postconditii: metoda intoarce referinta constanta la campul/atributul price al obiectului pentru care se apeleaza
	*/
	const double& getPrice() const noexcept;

	/*
	* Metoda getter pentru a obtine atributul privat producer al unui obiect de clasa Product
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta (adresa) constanta la un string
	* Postconditii: metoda intoarce referinta constanta la campul/atributul producer al obiectului pentru care se apeleaza
	*/
	const string& getProducer() const noexcept;

	/*
	* Metoda de tip setter pentru a actualiza/modifica campul/atributul privat type al unui obiect de clasa Product cu un tip nou dat ca si parametru
	* Date de intrare: referinta constanta la un string (new_type)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	*/
	void setType(const string& new_type);

	/*
	* Metoda de tip setter pentru a actualiza/modifica campul/atributul privat price al unui obiect de clasa Product cu un pret nou dat ca si parametru
	* Date de intrare: referinta constanta la o variabila reala de tip double (new_price)
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	*/
	void setPrice(const double& new_price) noexcept;

	/*
	* Metoda care compara doua obiecte de clasa Product
	* Date de intrare: referinta constanta la un obiect de clasa Product (ot)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true sau false)
	* Postconditii: cmpProducts = true  (1) - daca cele doua obiecte de clasa Product au acelasi atribut name (nume) si acelasi atribut producer (producator)
	*                           = false (0) - in caz contrar
	*/
	bool cmpProducts(const Product& ot) const noexcept;

	/*
	* Metoda care returneaza forma scrisa (text) a unui obiect de clasa Product (un string care contine valorile atributelor/campurilor private)
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): string (sir de caractere)
	* Postconditii: metoda intoarce un string care contine valorile efective ale campurilor/atributelor obiectului de clasa Product pe care se apeleaza
	*/
	string strProduct() const;

	/*
	* Metoda care suprascrie operatorul < pe clasa Product (astfel se vor putea compara cu simbolul matematic de inegalitate stricta < doua obiecte de clasa Product)
	* Date de intrare: referinta constanta la un obiect de clasa Product (ot)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true sau false), adica valoare logica de adevar (truth value)
	* Postconditii: metoda intoare (returneaza): true  (1) - daca primul obiect de clasa Product (lvalue = left value) este mai mic decat cel de al doilea obiect de clasa Product (rvalue = right value)
	*                                            false (0) - in caz contrar
	* Fie a, b: Product (obiecte de clasa Product)
	* a - lvalue (left value)
	* b - rvalue (right value)
	* a < b = true  => a.name = b.name and a.producer < b.producer
	*                  a.name < b.name
	* a < b = false => a.name  = b.name and a.producer >= b.producer
	*                  a.name >= b.name
	*/
	bool operator<(const Product& ot) const noexcept;

	/*
	* Metoda care suprascrie operatorul == pe clasa Product (astfel se vor putea compara cu simbolul matematic de egalitate == doua obiecte de clasa Product)
	* Date de intrare: referinta constanta la un obiect de clasa Product (ot)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true sau false), adica valoare logica de adevar (truth value)
	* Postconditii: metoda intoare (returneaza): true  (1) - daca cele doua obiecte coincid (sunt identice din punct de vedere semantic), adica au aceleasi atribute/campuri private name si producer
	*                                            false (0) - in caz contrar (cele doua obiecte sunt diferite/distince, adica nu coincid)
	* Fie a, b: Product (obiecte de clasa Product)
	* a - lvalue (left value)
	* b - rvalue (right value)
	* a == b = true  => a.name  = b.name and a.producer  = b.producer
	* a == b = false => a.name <> b.name or  a.producer <> b.producer
	*/
	bool operator==(const Product& ot) const noexcept;

	/*
	* Metoda care suprascrie operatorul != pe clasa Product (astfel se vor putea compara cu simbolul matematic de inegalitate != doua obiecte de clasa Product)
	* Date de intrare: referinta constanta la un obiect de clasa Product (ot)
	* Preconditii: -
	* Date de iesire (rezultate): valoare booleana (true sau false), adica valoare logica de adevar (truth value)
	* Postconditii: metoda intoare (returneaza): true  (1) - daca cele doua obiecte sunt diferite (unul din campurile/atributele private name sau producer difera)
	*                                            false (0) - in caz contrar, adica cele doua obiecte sunt identice (au aceleasi campuri name si producer)
	* Fie a, b: Product (obiecte de clasa Product)
	* a - lvalue (left value)
	* b - rvalue (right value)
	* a != b = true  => a.name <> b.name  or a.producer <> b.producer
	* a != b = false => a.name  = b.name and a.producer  = b.producer
	*/
	bool operator!=(const Product& ot) const noexcept;

	/*
	* Operatorul de assignment definit pe clasa Product
	* Acest operator este de tip const Product& (referinta constanta la un obiect de clasa Product), ci nu de tip void
	* pentru a permite expresii (asignari/atribuiri) inlantuite, adica a = b = c (unde a, b, c: Product)
	* Date de intrare: referinta constanta la un obiect de clasa Product (ot)
	* Preconditii: -
	* Date de iesire (rezultate): referinta constanta la un obiect de clasa Product
	* Postconditii: se copiaza atributele (campurile) private ale obiectului rvalue (right value = operandul drept) in obiectul lvalue (left value = operandul stang)
	* a, b, c: Product (obiecte de clasa Product cu atributele private name, type, price si producer)
	* a = b = c => b.name     = c.name    , a.name     = b.name
	*              b.type     = c.type    , a.type     = b.type
	*              b.price    = c.price   , a.price    = b.price
	*              b.producer = c.producer, a.producer = b.producer
	*/
	const Product& operator=(const Product& ot);
};