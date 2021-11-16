#pragma once

#include "Product.h"

class TestingExceptionRepo
{
private:
	// metode/functii private

	/*
	* Functie de test care compara doua obiecte de clasa Product
	* Metoda primeste referinte constanta la cele doua obiecte si verifica sa aiba aceleasi campuri/atribute private
	*/
	void testFunction(const Product& p, const Product& ot) const noexcept;

	/*
	* Metoda privata care testeaza metoda publica len din clasa ExceptionRepo
	* len este o metoda pur virtuala in clasa de baza AbstractRepo din care mosteneste ExceptionRepo
	* Aceasta metoda este suprascrisa in clasa derivata ExceptionRepo
	*/
	void runTestsRepoLen() const;

	/*
	* Metoda privata care testeaza metoda publica getAll din clasa ExceptionRepo
	* getAll este o metoda pur virtuala in clasa de baza AbstractRepo din care mosteneste ExceptionRepo
	* Aceasta metoda este suprascrisa in clasa derivata ExceptionRepo
	*/
	void runTestsRepoGetAll() const;

	/*
	* Metoda privata care testeaza metoda publica addProduct din clasa ExceptionRepo
	* addProduct este o metoda pur virtuala in clasa de baza AbstractRepo din care mosteneste ExceptionRepo
	* Aceasta metoda este suprascrisa in clasa derivata ExceptionRepo
	*/
	void runTestsRepoAddProduct() const;

	/*
	* Metoda privata care testeaza metoda publica deleteProduct din clasa ExceptionRepo
	* deleteProduct este o metoda pur virtuala in clasa de baza AbstractRepo din care mosteneste ExceptionRepo
	* Aceasta metoda este suprascrisa in clasa derivata ExceptionRepo
	*/
	void runTestsRepoDeleteProduct() const;

	/*
	* Metoda privata care testeaza metoda publica modifyProduct din clasa ExceptionRepo
	* modifyProduct este o metoda pur virtuala in clasa de baza AbstractRepo din care mosteneste ExceptionRepo
	* Aceasta metoda este suprascrisa in clasa derivata ExceptionRepo
	*/
	void runTestsRepoModifyProduct() const;

	/*
	* Metoda privata care testeaza metoda publica searchProduct din clasa ExceptionRepo
	* searchProduct este o metoda pur virtuala in clasa de baza AbstractRepo din care mosteneste ExceptionRepo
	* Aceasta metoda este suprascrisa in clasa derivata ExceptionRepo
	*/
	void runTestsRepoSearchProduct() const;

public:
	// metode/functii publice

	/*
	* Constructorul default al unui obiect de clasa TestingExceptionRepo
	*/
	TestingExceptionRepo() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingExceptionRepo)
	*/
	TestingExceptionRepo(const TestingExceptionRepo& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru clasa ExceptionRepo definita in layerul/stractul infrastructure (infrastrcutura) de persistenta a datelor
	*/
	void runTestsExceptionRepo() const;
};

