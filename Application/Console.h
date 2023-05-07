#pragma once

#include "Service.h"

class UI
{
private:
	Service& srv; // referinta la un obiect de clsa Service

	/*
	* Procedura care afiseaza/tipareste meniul aplicatiei (lista de comenzi disponibile)
	*/
	void showMenu() const;

	/*
	* Procedura care incearca adaugarea unui produs in magazin
	*/
	void addUI() const;

	/*
	* Procedura care incearca stergerea unui produs din magazin
	*/
	void delUI() const;

	/*
	* Procedura care incearca modificarea unui produs din magazin
	*/
	void modifyUI() const;

	/*
	* Procedura care cauta un produs in magazin
	*/
	void searchUI() const;

	/*
	* Procedura care primeste o referinta constanta la o lista (vector) de produse (obiecte de clasa Product)
	* si afiseaza/tipareste pe ecran (in consola/terminal) fiecare produs din lista primita
	*/
	void typeProducts(const vector<Product>& products) const;

	/*
	* Procedura care afiseaza toate produsele existente in magazin
	*/
	void printAllUI() const;

	/*
	* Procedura care afiseaza pentru fiecare tip de produs din magazin de cate ori apare
	* Subrutina va tipari in consola/terminal (adica pe ecran) tipurile de produse din magazin ordonate/sortate crescator si cate produse cu tipul respectiv exista in stoc
	*/
	void countTypeUI() const;

	/*
	* Procedura care face undo la ultima operatie (adauga, modifica sau sterge)
	*/
	void undoUI() const;

	/*
	* Procedura care afiseaza pe ecran criteriile existente de filtrare a produselor din magazin
	*/
	void showFilterCriterions() const;

	/*
	* Functie de tip operand (rezultat) care citeste criteriul pentru functionalitatea de filtrare ca si string si il returneaza/intoarce prin numele ei
	*/
	string readFilterCrt() const;

	/*
	* Functie de tip operand (rezultat) care citeste filtrul pentru functionalitatea de filtrare ca si string si il returneaza/intoarce prin numele ei
	* Functia primeste ca si argument (parametru de intrare) criteriul dupa care se va face/realiza filtrarea
	*/
	string readFilter(const string& crt) const;

	/*
	* Functie de tip operand (rezultat) care citeste semnul (de egalitate sau inegalitate) dupa care sa se faca filtrarea pentru criteriul pret
	*/
	string readFilterSign() const;

	/*
	* Procedura care filtreaza produsele din magazin dupa un anumit criteriu
	*/
	void filterUI() const;

	/*
	* Procedura care afiseaza criteriile de sortare disponibile
	*/
	void showSortingCriterions() const;

	/*
	* Functie de tip operand (rezultat) care citeste criteriul pentru functionalitatea de sortare ca si string si il returneaza/intoarce prin numele ei
	*/
	string readSortingCrt() const;

	/*
	* Procedura care afiseaza ordinea in care se poate efectua/realiza sortarea pentru toate criteriile (general valabil)
	*/
	void showSortingOrders() const;

	/*
	* Functie de tip operand (rezultat) care citeste ordinea de sortare pentru functionalitatea de sortare/ordonare ca si string si o returneaza/intoarce prin numele ei
	*/
	string readSortingOrd() const;

	/*
	* Procedura care sorteaza/ordoneaza produsele existente in magazin dupa un anumit criteriu si o ordine data (crescator sau descrescator)
	*/
	void sortUI() const;

	/*
	* Procedura care afiseaza/tipareste meniul cosului de cumparaturi (lista de actiuni disponibile)
	*/
	void afiseazaMeniuCosCumparaturi() const;

	/*
	* Procedura care goleste toate produsele din cosul de cumparaturi
	*/
	void golireCosUI() const;

	/*
	* Procedura care adauga un produs in cosul de cumparaturi
	*/
	void adaugareCosUI() const;

	/*
	* Procedura care genereaza un cos de cumparaturi total aleator
	* (introduce n produse din stoc in cos, unde n este citit de la tastatura)
	*/
	void generareCosUI() const;

	/*
	* Procedura care afiseaza toate produsele din cosul de cumparaturi
	*/
	void tiparireCos() const;

	/*
	* Procedura care afiseaza toate produsele din cosul de cumparaturi intr-un fisier CSV
	*/
	void exportCosUI() const;

	/*
	* Procedura care gestioneaza cosul de cumparaturi din aplicatie
	*/
	void cosCumparaturiUI() const;

	/*
	* Procedura care curata terminalul/consola aplicatiei (sterge continutul de pe ecran)
	*/
	void clearUI() const noexcept;

	/*
	* Procedura care incearca adaugarea unui produs (obiect de clasa Product) cu numele name, tipul type, preturl price si producatorul producer
	* Valoarea (continutul) variabilei cont se va incrementa daca adaugarea s-a reazlizat cu succes (adica nu exista un produs cu numele name si producatorul producer in stocul magazinului)
	* Variabila cont este transmisa prin referinta (este o resursa volatila care se poate modifica/altera in corpul subprogramului/subrutinei)
	*/
	void addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const;

	/*
	* Procedura care adauaga 10 obiecte de clasa Product (10 inregistrari) in lista din repo (adica in magazin)
	*/
	void debugUI() const;

public:
	/*
	* Constructorul default de instantiere (care nu primeste niciun argument/parametru)
	* Impiedicam folosirea constructorului default prin "stergerea" lui folosind calificativul delete
	*/
	UI() = delete;

	/*
	* Definim un constructor al clasei care primeste un obiect de clasa Service (referinta la acest obiect)
	* Constructorul va instantia obiectul curent de clasa UI, populand atributul privat srv al acestuia cu obiectul primit ca argument
	*/
	UI(Service& srv) noexcept :srv{ srv } {

	}

	/*
	* Constructorul default de copiere
	* Impiedicam copierea obiectelor de clasa UI prin intermediul calificativului delete
	*/
	UI(const UI& ot) = delete;

	/*
	* Procedura care ruleaza aplicatia
	*/
	void runApp() const;
};