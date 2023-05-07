#pragma once

#include "Product.h"

class ProductValidator
{
private:
	/*
	* Functie operand (de tip rezultat) care incearca validarea atributului name (nume) a unui obiect de clasa Product
	* Date de intrare: bad_product - referinta constanta la un obiect de clasa Product (un produs)
	* Preconditii: -
	* Date de iesire: bool (valoare booleana = literalii true (1) si false (0))
	* Postconditii: invalidName = true , daca obiectul bad_product are atributul name (string) un string vid ("") (atribut invalid)
	*               invalidName = false, in caz contrar (entitatea bad_product are campul name (nume) valid)
	*/
	bool invalidName(const Product& bad_product) const noexcept;

	/*
	* Functie operand (de tip rezultat) care incearca validarea atributului type (tip) a unui obiect de clasa Product
	* Date de intrare: bad_product - referinta constanta la un obiect de clasa Product (un produs)
	* Preconditii: -
	* Date de iesire: bool (valoare booleana = literalii true (1) si false (0))
	* Postconditii: invalidType = true , daca obiectul bad_product are atributul type (string) un string vid ("") (atribut invalid)
	*               invalidType = false, in caz contrar (entitatea bad_product are campul type (tip) valid)
	*/
	bool invalidType(const Product& bad_product) const noexcept;

	/*
	* Functie operand (de tip rezultat) care incearca validarea atributului price (pret) a unui obiect de clasa Product
	* Date de intrare: bad_product - referinta constanta la un obiect de clasa Product (un produs)
	* Preconditii: -
	* Date de iesire: bool (valoare booleana = literalii true (1) si false (0))
	* Postconditii: invalidPrice = true , daca obiectul bad_product are atributul price (double) o valoare reala negativa sau apropiata de 0 (atribut invalid)
	*               invalidPrice = false, in caz contrar (entitatea bad_product are campul price (pret) valid)
	*/
	bool invalidPrice(const Product& bad_product) const noexcept;

	/*
	* Functie operand (de tip rezultat) care incearca validarea atributului producer (producator) a unui obiect de clasa Product
	* Date de intrare: bad_product - referinta constanta la un obiect de clasa Product (un produs)
	* Preconditii: -
	* Date de iesire: bool (valoare booleana = literalii true (1) si false (0))
	* Postconditii: invalidProducer = true , daca obiectul bad_product are atributul producer (string) un string vid ("") (atribut invalid)
	*               invalidProducer = false, in caz contrar (entitatea bad_product are campul producer (producator) valid)
	*/
	bool invalidProducer(const Product& bad_product) const noexcept;

public:
	/*
	* Constructorul default
	*/
	ProductValidator() = default;

	/*
	* Constructorul de copiere (impiedicam copierea obiectelor de clasa ProductValidator)
	*/
	ProductValidator(const ProductValidator& ot) = delete;

	/*
	* Procedura care valideaza un obiect de clasa Product (ii verifica corectitudinea atributelor)
	* Date de intrare: bad_product - referinta constanta la un obiect de clasa Product
	* Preconditii: -
	* Date de iesire: -, subrutina nu returneaza/intoarce/furnizeaza nimic prin numele ei (aceasta fiind de tip void, adica procedura)
	* Postconditii: -
	* Exceptii: procedura ridica/arunca exceptie de tipul ProductException cu un mesaj custom de eroare in cazul in care cel putin un atribut/camp al produsului este invalid,
	* in caz contrar (obiectul are toate atributele valide) procedura nu face nimic (nu ridica/arunca exceptie)
	*/
	void validateProduct(const Product& bad_product) const;
};