#pragma once

class TestingDomain
{
private:
	// metode/functii private

	/*
	* Metoda care testeaza constructorul de copiere (copy constructorul) al unei entitati din domain (domeniu)
	*/
	void runTestsDomainCopyConstructor() const;

	/*
	* Metoda care testeaza functiile de tip getter din domain (domeniu)
	*/
	void runTestsDomainGetters() const;
	
	/*
	* Metoda care testeaza functiile de tip setter din domain (domeniu)
	*/
	void runTestsDomainSetters() const;
	
	/*
	* Metoda care testeaza functia cmpProducts din domain (domeniu) care compara doua obiecte de clasa Product
	*/
	void runTestsDomainCmpProducts() const;
	
	/*
	* Metoda care testeaza functia strProduct din domain (domeniu)
	*/
	void runTestsDomainStrProduct() const;

	/*
	* Metoda care testeaza operatorul de inegalitate stricta < definit pe clasa Product din domain (domeniu)
	* Se vor compara doua obiecte de clasa Product folosind operatorul < (simbol matematic de inegalitate stricta)
	*/
	void runTestsLessOperator() const;

	/*
	* Metoda care testeaza operatorul de egalitate == definit pe clasa Product din domain (domeniu)
	* Se vor compara doua obiecte de clasa Product folosind operatorul == (simbol matematic de egalitate)
	*/
	void runTestsEqualOperator() const;

	/*
	* Metoda care testeaza operatorul de inegalitate != definit pe clasa Product din domain (domeniu)
	* Se vor compara doua obiecte de clasa Product folosind operatorul != (simbol matematic de inegalitate)
	*/
	void runTestsNotEqualOperator() const;

	/*
	* Metoda care testeaza operatorul de assignment definit pe clasa Product din domain (domeniu)
	* Acesta permite atribuiri (asignari) multiple (inlantuite) de obiecte de clasa Product
	*/
	void runTestsAssignmentOperator() const;

public:
	// metode/functii publice

	/*
	* Constructorul default al unui obiect de clasa TestingDomain
	*/
	TestingDomain() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingDomain)
	*/
	TestingDomain(const TestingDomain& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru layerul/stratul de domain = domeniu (entitatile (entities) aplicatiei)
	*/
	void runTestsDomain() const;
};