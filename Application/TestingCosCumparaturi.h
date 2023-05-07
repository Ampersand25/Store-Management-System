#pragma once

#include "CosCumparaturi.h"
#include "Repository.h"

class TestingCosCumparaturi
{
private:
	// atribute/campuri private

	CosCumparaturi& cos_cumparaturi;
	RepoProducts& repo;

	// metode/functii private

	/*
	* Functie de test care compara doua numere reale in dubla precizie (double-uri) a si b
	* Metoda foloseste functia build-in assert pentru comparare
	*/
	void cmpDouble(const double& a, const double& b) const noexcept;

	/*
	* Functie privata care testeaza constructorul custom al unui obiect de clasa CosCumparaturi
	*/
	void runTestsConstructor() const noexcept;

	/*
	* Functie privata care testeaza metoda publica adaugaInCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsAdaugaInCos() const;

	/*
	* Functie privata care testeaza metoda publica golesteCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsGolesteCos() const;

	/*
	* Functie privata care testeaza metoda publica genereazaCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsGenereazaCos() const;

	/*
	* Functie privata care testeaza metoda publica exportCosFisierHTML a unui obiect de clasa CosCumparaturi
	*/
	void runTestsExportCosFisierHTML() const;

	/*
	* Functie privata care testeaza metoda publica exportCosFisierCSV a unui obiect de clasa CosCumparaturi
	*/
	void runTestsExportCosFisierCSV() const;

	/*
	* Functie privata care testeaza metodele publice exportCosFisierCSV si exportCosFisierHTML a unui obiect de clasa CosCumparaturi
	*/
	void runTestsExportCosFisier() const;

	/*
	* Functie privata care testeaza metoda publica getTotal a unui obiect de clasa CosCumparaturi
	*/
	void runTestsGetTotal() const;

	/*
	* Functie privata care testeaza metoda publica nrProduseCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsNrProduseCos() const;

	/*
	* Functie privata auxiliara de test care face urmatoarele verificari pentru functia runTestsGetCos:
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista x produse (obiecte de clasa Product) cu numele (atributul name) "pasta de dinti" si producatorul (atributul producer) "Colgate"
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista y produse (obiecte de clasa Product) cu numele (atributul name) "vegeta" si producatorul (atributul producer) "Vegeta"
	* - daca in cosul de cumparaturi cos (obiect de clasa CosCumparaturi) exista z produse (obiecte de clasa Product) cu numele (atributul name) "chipsuri" si producatorul (atributul producer) "Lays"
	*/
	void cmpCantity(const CosCumparaturi& cos, const int& x, const int& y, const int& z) const;

	/*
	* Functie privata care testeaza metoda publica getCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsGetCos() const;

	/*
	* Functie privata care testeaza metoda publica stergeProduseCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsStergeProduseCos() const;

	/*
	* Functie privata care testeaza metoda publica modificaProduseCos a unui obiect de clasa CosCumparaturi
	*/
	void runTestsModificaProduseCos() const;

public:
	// metode/functii publice

	/*
	* Stergem constructorul default al unui obiect de clasa TestingCosCumparaturi folosind calificativul delete
	* Astfel, nu se vor putea instantia obiecte de clasa TestingCosCumparaturi fara a se specifica o referinta la un obiect de clasa CosCumparaturi
	*/
	TestingCosCumparaturi() = delete;

	TestingCosCumparaturi(CosCumparaturi& cos_cumparaturi, RepoProducts& repo) noexcept : cos_cumparaturi{ cos_cumparaturi }, repo{ repo } {

	}

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingCosCumparaturi)
	*/
	TestingCosCumparaturi(const TestingCosCumparaturi& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru modului CosCumparaturi
	*/
	void runTestsCosCumparaturi() const;
};