#pragma once

#include "Repository.h"
//#include "Product.h"

//#include <string> // pentru std::string

//using std::string;

class FileRepoProducts : public RepoProducts // clasa derivata din clasa de baza RepoProducts (clasa care la randul ei este derivata din clasa de baza AbstractRepo)
{
private:
	// atribute private

	string filename; // sir de caractere din STL (string) care contine numele fisierului text in care se va face salvarea (datele vor persista in acel fisier)

	// metode (functii) private

	/*
	* Metoda care citeste continutul fisierului text cu numele filename si salveaza in repository produsele (obiectele de clasa Product) din acest fisier
	* Procedura (functia procedurala) incarca datele din fisier in memorie => face import
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: - (metoda nu arunca exceptii)
	* Metoda face exit cu codul de retur 1 (exit status/code) daca datele din fisier nu sunt valide (pretul nu este corect definit)
	*/
	void loadFromFile();

	/*
	* Metoda care scrie (afiseaza/tipareste) in fisierul cu numele filename, lista de produse (obiecte de clasa Product) din repozitoriu
	* Astfel se salveaza datele in fisier
	* Procedura (functia procedurala) incarca datele din memorie in fisier => face export
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: -
	* Exceptii: - (metoda nu arunca exceptii)
	*/
	void writeToFile();

public:
	/*
	* Constructorul unui obiect de clasa FileRepoProducts
	*/
	FileRepoProducts(const string& filename) : RepoProducts(), filename{ filename } {
		// incarcam datele (obiecte de clasa Product) din fisier in memorie
		// se realizeaza astfel operatia de import
		this->loadFromFile(); // loadFromFile();
	}

	/*
	* Metoda publica mostenita din clasa de baza RepoProducts (va fi suprascrisa) care incearca sa adauge un obiect product de clasa Product in repo (magazin)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: procedura (functia procedurala) salveaza (scrie) in fisier lista de produse din stocul magazinului dupa adaugarea produsului product (daca acesta nu se afla deja in magazin <=> nu exista un produs (obiect de clasa Product) cu acelasi nume si producator)
	*               se actualizeaza fisierul text cu numele filename
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs deja existent!\n" daca produsul product exista deja in lista din repo (exista un produs cu acelasi nume si producator)
	*/
	void addProduct(const Product& product) override;

	/*
	* Metoda publica mostenita din clasa de baza RepoProducts (va fi suprascrisa) care incearca stearga un obiect de clasa Product cu numele name si producatorul producer din lista de produse (entitati de clasa Product) din repo (magazin)
	* Date de intrare: name     - referinta constanta la un string
	*                  producer - referinta constanta la un string
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: procedura (functia procedurala) salveaza (scrie) in fisier lista de produse din stocul magazinului dupa stergerea produsului cu numele name si producatorul producer (in cazul in care exista un produs in magazin cu aceste atribute)
	*               se actualizeaza fisierul text cu numele filename
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul product nu se afla in magazin (nu exista obiect de clasa Product (entitati/inregistrari) nu numele name si producatorul producer in lista din repo)
	*/
	void deleteProduct(const string& name, const string& producer) override;

	/*
	* Metoda publica mostenita din clasa de baza RepoProducts (va fi suprascrisa) care incearca actualizarea/modificarea atributele price si type a unui obiect product de clasa Product din repo (magazin)
	* Date de intrare: product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire (rezultate): -
	* Postconditii: procedura (functia procedurala) salveaza (scrie) in fisier lista de produse din stocul magazinului dupa modificarea produsului product (daca exista un produs in magazin cu acelasi nume si producator ca si parametrul de intrare product)
	*               se actualizeaza fisierul text cu numele filename
	* Exceptii: metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Nu exista produse in magazin!\n" daca lista de obiecte este vida/goala (nu exista inregistrari in repo)
	*           metoda arunca/ridica exceptie de tipul RepoException cu mesajul de eroare/exceptie "[!]Produs inexistent!\n" daca produsul care se doreste a fi actualizat nu se afla in repo (magazin), adica nu exista nicio inregistrare cu numele produsului product si producatorul produsului product
	*/
	void modifyProduct(const Product& product) override;
};