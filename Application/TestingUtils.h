#pragma once

#include "Utils.h"

class TestingUtils
{
private:
	// atribute private

	Utils& utils; // atribut de tip referinta la un obiect utils de clasa Utils
	
	// metode private (nu pot fi apelate din exteriorul clasei, ci doar din interiorul acesteia)

	/*
	* Metoda privata pentru testarea functiei compareStr din fisierul antet (header) Utils.h
	*/
	void runTestsUtilsCompareStr() const;

	/*
	* Metoda privata pentru testarea functiei isDouble din fisierul antet (header) Utils.h
	*/
	void runTestsUtilsIsDouble() const;

	/*
	* Metoda privata pentru testarea functiei isInteger din fisierul antet (header) Utils.h
	*/
	void runTestsUtilsIsInteger() const;

public:
	// metode publice (pot fi apelate atat din interiorul cat si din exteriorul clasei)

	/*
	* Stergem constructorul default al unui obiect de clasa TestingUtils
	*/
	TestingUtils() = delete;

	/*
	* Constructor custom al unui obiect de clasa TestingUtils care primeste o referinta la un obiect utils de clasa Utils
	* Contructorul va popula atributul privat utils al obiectului instantiat cu obiectul primit
	*/
	TestingUtils(Utils& utils) noexcept : utils { utils } {

	}

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingUtils)
	*/
	TestingUtils(const TestingUtils& ot) = delete;

	/*
	* Metoda care ruleaza teste pentru functiile de pe stratul/layerul Utils (functii utilitare)
	*/
	void runTestsUtils() const;
};