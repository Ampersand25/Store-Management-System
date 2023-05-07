#pragma once

#include "Product.h"

class TestingFileRepo
{
private:
	// metode/functii private

	/*
	* Functie de test care verifica daca un produs (obiect de clasa Product) p are:
	* atributul/campul privat name (nume produs) identic cu parametrul/argumentul name
	* atributul/campul privat type (tip produs) identic cu parametrul/argumentul type
	* atributul/campul privat price (pret produs) identic cu parametrul/argumentul price
	* atributul/campul privat producer (producator produs) identic cu parametrul/argumentul producer
	*/
	void testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept;

	/*
	* Metoda care testeaza functia loadFromFile din repository-ul cu fisiere
	*/
	void runTestsLoadFromFile() const;

	/*
	* Metoda care testeaza functia writeToFile din repository-ul cu fisiere
	*/
	void runTestsWriteToFile() const;

	/*
	* Metoda care testeaza functia addProduct din repository-ul cu fisiere
	*/
	void runTestsFileRepoAddProduct() const;

	/*
	* Metoda care testeaza functia deleteProduct din repository-ul cu fisiere
	*/
	void runTestsFileRepoDeleteProduct() const;

	/*
	* Metoda care testeaza functia modifyProduct din repository-ul cu fisiere
	*/
	void runTestsFileRepoModifyProduct() const;

public:
	// metode/functii publice

	/*
	* Constructorul default al unui obiect de clasa TestingFileRepo
	*/
	TestingFileRepo() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingFileRepo)
	*/
	TestingFileRepo(const TestingFileRepo& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru layerul/stratul de infrastructure = infrastructura (persistena a datelor, adica file repository = repozitoriu cu fisiere text)
	*/
	void runTestsFileRepo() const;
};