#pragma once

#include "ProductValidator.h"

class TestingValidation
{
private:
	// atribute private (nu pot fi apelate din exteriorul clasei, ci doar din interiorul acesteia)

	ProductValidator& valid; // atribut de tip referinta la un obiect valid de clasa ProductValidator

public:
	/*
	* Stergem constructorul default al unui obiect de clasa TestingValidation
	*/
	TestingValidation() = delete;

	/*
	* Constructor custom al unui obiect de clasa TestingValidation care primeste o referinta la un obiect valid de clasa ProductValidator
	* Contructorul va popula atributul privat valid al obiectului instantiat cu obiectul primit
	*/
	TestingValidation(ProductValidator& valid) noexcept : valid{ valid } {

	}

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingValidation)
	*/
	TestingValidation(const TestingValidation& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru validarea de produse (layerul de validation = validare a datelor)
	*/
	void runTestsProductValidator() const;
};

