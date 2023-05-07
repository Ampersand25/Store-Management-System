#pragma once

#include <string> // pentru std::string

using std::string; // sir de caractere din STL (Standard Template Library)

class Exception // clasa de baza pentru clasele de exceptii ServiceException, CosException, ProductException si RepoException (clase derivate din aceasta clasa)
{
private:
	// atribute (campuri) private (pot fi accesate doar din interiorul clasei)

	const string msg; // mesajul de eroare/exceptie al unui obiect de clasa Exception (sau al unui obiect dintr-o clasa derivata din aceasta)

public:
	// metode (functii) publice (pot fi apelate si din exteriorul clasei)

	/*
	* Constructorul default al unui obiect de clasa Exception
	* Folosind calificativul delete nu vom putea apela constructorul default pe un obiect de clasa Exception
	*/
	Exception() = delete;

	/*
	* Constructor al unui obiect de clasa Exception care primeste o referinta constanta la un string msg
	* si instantiaza un obiect de clasa Exception care sa aiba ca si camp/atribut privat msg o copie a valorii stringului msg
	*/
	Exception(const string& msg) : msg{ msg } {

	}

	/*
	* Constructorul de copiere (il setam ca si constructor default = implicit)
	*/
	Exception(const Exception& ot) = default;

	/*
	* Metoda de tipul getter care returneaza/intoarce atributul privat msg (string din STL) al unui obiect de clasa Exception sau de clasa derivata din clasa de baza Exception
	* Date de intrare: -
	* Preconditii: -
	* Date de iesire (rezultate): referinta constanta la un string (sir de caractere din STL)
	* Postconditii: getMessage() = referinta constanta la atributul/campul privat msg (string) al unui obiect de clasa Exception
	*/
	const string& getMessage() const noexcept;
};