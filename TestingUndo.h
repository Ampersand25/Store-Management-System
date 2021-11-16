#pragma once

#include "Undo.h"

class TestingUndo
{
private:
	// metode private (nu pot fi apelate din exteriorul clasei, ci doar din interiorul acesteia)

	/*
	* Functie de test care compara doua numere reale in dubla precizie (double-uri) a si b
	* Metoda foloseste functia build-in assert pentru comparare
	*/
	void cmpDouble(const double& a, const double& b) const noexcept;

	/*
	* Functie de test care compara (folosind instructiunea assert din fisierul antet/header assert.h (cassert))
	* doua obiecte de clasa Product (parametrii de intrare vor fi referinte constante la aceste obiecte)
	* Se compara camp cu camp (atribut cu atribut) cele doua obiecte
	*/
	void testFunction(const Product& product_1, const Product& product_2) const noexcept;

	/*
	* Metoda privata pentru testarea clasei UndoAdauga din fisierul antet (header) Undo.h
	*/
	void runTestsUndoAdauga() const;

	/*
	* Metoda privata pentru testarea clasei UndoSterge din fisierul antet (header) Undo.h
	*/
	void runTestsUndoSterge() const;

	/*
	* Metoda privata pentru testarea clasei UndoModifica din fisierul antet (header) Undo.h
	*/
	void runTestsUndoModifica() const;

public:
	// metode publice (pot fi apelate atat din interiorul cat si din exteriorul clasei)

	/*
	* Constructorul default al unui obiect de clasa TestingUndo
	*/
	TestingUndo() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingUndo)
	*/
	TestingUndo(const TestingUndo& ot) = delete;

	/*
	* Metoda care ruleaza teste pentru clasele derivate din clasa ActiuneUndo
	*/
	void runTestsUndo() const;
};