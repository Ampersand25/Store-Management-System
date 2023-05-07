#pragma once

#include "Product.h"
#include "ProductValidator.h"
#include "Service.h"

class TestingService
{
private:
	// atribute private

	ProductValidator& valid; // atribut de tip referinta la un obiect valid de clasa ProductValidator

	// metode private (pot fi apelate doar din interiorul clasei)

	/*
	* Metoda care testeaza functia cmpStrings din fisierul antet/header Business.h
	*/
	void runTestsServiceCmpStrings() const;

	/*
	* Metoda care testeaza functia verifyIfDouble din fisierul antet/header Business.h
	*/
	void runTestsServiceVerifyIfDouble() const;

	/*
	* Metoda care testeaza functia verifyIfInteger din fisierul antet/header Business.h
	*/
	void runTestsServiceVerifyIfInteger() const;

	/*
	* Metoda care testeaza functia add din fisierul antet/header Business.h
	*/
	void runTestsServiceAdd() const;

	/*
	* Metoda care testeaza functia del din fisierul antet/header Business.h
	*/
	void runTestsServiceDel() const;

	/*
	* Metoda care testeaza functia modify din fisierul antet/header Business.h
	*/
	void runTestsServiceModify() const;

	/*
	* Metoda care testeaza functia search din fisierul antet/header Business.h
	*/
	void runTestsServiceSearch() const;

	/*
	* Metoda care testeaza functia getAll din fisierul antet/header Business.h
	*/
	void runTestsServiceGetAll() const;

	/*
	* Metoda care testeaza functia countType din fisierul antet/header Business.h
	*/
	void runTestsCountType() const;

	/*
	* Metoda care testeaza functia undo din fisierul antet/header Business.h
	*/
	void runTestsUndo() const;

	/*
	* Functie de test care verifica daca un produs p are atributul name identic cu name, atributul type identic cu type, atributul price identic cu price si atributul producer identic cu producer
	*/
	void testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept;
	
	/*
	* Metoda care testeaza functia filterProducts (de filtrare a produselor dupa un criteriu) din fisierul header/antet Business.h
	*/
	void runTestsServiceFilterProducts() const;

	/*
	* Metoda care testeaza functia sortProducts din fisierul antet/header Business.h
	*/
	void runTestsServiceSortProducts() const;

	/*
	* Metoda care testeaza functia adaugareCos din fisierul antet/header Business.h
	*/
	void runTestsAdaugareCos() const;

	/*
	* Functie de test care compara doua numere reale in dubla precizie (double-uri) a si b
	* Metoda foloseste functia build-in assert pentru comparare
	*/
	void cmpDouble(const double& a, const double& b) const noexcept;

	/*
	* Metoda care testeaza functia totalCos din fisierul antet/header Business.h
	*/
	void runTestsTotalCos() const;

	/*
	* Metoda care testeaza functia cantitateCos din fisierul antet/header Business.h
	*/
	void runTestsCantitateCos() const;

	/*
	* Metoda care testeaza functia golireCos din fisierul antet/header Business.h
	*/
	void runTestsGolireCos() const;

	/*
	* Metoda care testeaza functia generareCos din fisierul antet/header Business.h
	*/
	void runTestsGenerareCos() const;

	/*
	* Metoda care testeaza functia exportCos din fisierul antet/header Business.h
	*/
	void runTestsExportCos() const;

	/*
	* Functie privata auxiliara de test care face urmatoarele verificari pentru functia runTestsGetCosCumparaturi:
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista a produse (obiecte de clasa Product) cu numele (atributul name) "chipsuri" si producatorul (atributul producer) "Lays"
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista b produse (obiecte de clasa Product) cu numele (atributul name) "ton in ulei" si producatorul (atributul producer) "Tonno Rio Mare"
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista c produse (obiecte de clasa Product) cu numele (atributul name) "boia" si producatorul (atributul producer) "Delikat"
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista d produse (obiecte de clasa Product) cu numele (atributul name) "pasta de dinti" si producatorul (atributul producer) "Colgate"
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista e produse (obiecte de clasa Product) cu numele (atributul name) "iaurt" si producatorul (atributul producer) "Milka UK"
	*/
	void cmpCantityCos(const Service& srv, const int& a, const int& b, const int& c, const int& d, const int& e) const;

	/*
	* Metoda care testeaza functia getCosCumparaturi din fisierul antet/header Business.h
	*/
	void runTestsGetCosCumparaturi() const;

public:
	// metode publice (pot fi apelate din exteriorul clasei)

	/*
	* Stergem constructorul default al unui obiect de clasa TestingService
	*/
	TestingService() = delete;

	/*
	* Constructor custom al unui obiect de clasa TestingService care primeste o referinta la un obiect valid de clasa ProductValidator
	* Contructorul va popula atributul privat valid al obiectului instantiat cu obiectul primit
	*/
	TestingService(ProductValidator& valid) noexcept : valid{ valid }  {

	}

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingService)
	*/
	TestingService(const TestingService& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru layerul/stratul de business (services = servicii)
	*/
	void runTestsService() const;
};