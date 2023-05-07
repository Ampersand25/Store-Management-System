#pragma once

#include <string> // pentru std::string

using std::string;

class Utils
{
public:
	/*
	* Constructorul default (implicit/prestabilit) a unui obiect de clasa Utils
	* Constructorul instantiaza un obiect de clasa Utils
	*/
	Utils() = default;

	/*
	* Stergem operatorul de assignment (asignare/atribuire) folosind calificativul delete
	*/
	void operator=(const Utils& ot) = delete;

	/*
	* Subprogram care compara case insensitive (nu se face deosebirea/distingerea dintre litere mici (minuscule) si litere mari (majuscule)) doua stringuri
	* Date de intrare: str_1 - referinta constanta la un string
	*                  str_2 - referinta constanta la un string
	* Preconditii: -
	* Date de iesire: bool (true sau false)
	* Postconditii: compareStr = true , daca cele doua stringuri (str_1 si str_2 date ca si parametrii) corespund
	*                          = false, daca cele doua stringuri nu coincid (au lungimi diferite sau cel putin un caracter diferit pe aceeasi pozitie)
	*/
	bool compareStr(const string& str_1, const string& str_2) const noexcept;

	/*
	* Subprogram care verifica daca un string dat ca si argument contine reprezentarea unui numar real in dubla precizie (double)
	* Date de intrare: str - referinta constanta la un string
	* Preconditii: -
	* Date de iesire: bool (true sau false)
	* Postconditii: isDouble = true , daca stringul str reprezinta un double (numar real)
	*                        = false, in caz contrar
	*/
	bool isDouble(const string& str) const;

	/*
	* Subprogram care verifica daca un string dat ca si argument contine reprezentarea unui numar intreg
	* Date de intrare: str - referinta constanta la un string
	* Preconditii: -
	* Date de iesire: bool (true sau false)
	* Postconditii: isInteger = true , daca stringul str reprezinta un intreg (cu semn = signed)
	*                         = false, in caz contrar
	*/
	bool isInteger(const string& str) const;
};

