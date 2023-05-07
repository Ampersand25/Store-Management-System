#include "Utils.h"

#include <cctype> // #include <ctype.h>
// pentru isdigit si tolower

bool Utils::compareStr(const string& str_1, const string& str_2) const noexcept
{
	if (str_1.size() != str_2.size()) // comparam numarul de caractere din cele doua stringuri STL
		return false; // cele doua stringuri nu corespund (au lungimi diferite)

	// Metoda I

	/*
	const auto& len{ str_1.size() }; // const auto& len{ str_2.size() };
									 // retinem/memoram in variabila len numarul de elemente din cele doua stringuri

	for (unsigned i{ 0 }; i < len; ++i) // ciclam prin cele doua stringuri de dimensiuni egale
		if (tolower(str_1.at(i)) != tolower(str_2.at(i))) // comparam caracterele de pe pozitia/indicele i din ambele stringuri (compararea se face ignore case)
			return false; // cele doua stringuri nu corespund (au cel putin un caracter diferit pe aceeasi pozitie)

	return true; // cele doua stringuri sunt egale (coincid) din punct de vedere case insensitive al caracterelor (nu se fac diferente intre litere mici (minuscule = lowercase) si litere mari (majuscule = uppercase))
	*/

	// Metoda II

	// str_1.begin() - iterator pozitionat pe primul caracter din stringul str_1
	// str_1.end()   - iterator ivalid (nevalid = care nu este valid) pozitionat dupa ultimul caracter din stringul str_1

	auto it_1{ str_1.begin() }; // obtinem in variabila it_1 un iterator pozitionat pe primul caracter din stringul str_1
	auto it_2{ str_2.begin() }; // obtinem in variabila it_2 un iterator pozitionat pe primul caracter din stringul str_2

	while (it_1 != str_1.end()) // while (it_2 != str_2.end())
		// parcurgem ambele stringuri (atat str_1 cat si str_2) cu ajutorul celor 2 iteratori (it_1 si it_2) pana cand iteratorul it_1 (sau it_2) devine invalid (respectiv cat timp acesta este valid, adica este pozitionat pe un caracter din string)
	{
		if (tolower(*it_1) != tolower(*it_2)) // comparam ignore case caracterele din cele doua stringuri (referite de cei doi iteratori)
			return false; // cele doua stringuri nu corespund (au cel putin un caracter diferit pe aceeasi pozitie)

		++it_1; // mutam iteratorul it_1 (il pozitionam pe urmatorul element) in container (adica in stringul str_1)
		++it_2; // mutam iteratorul it_2 (il pozitionam pe urmatorul element) in container (adica in stringul str_2)
	}

	return true; // cele doua stringuri sunt egale (coincid) din punct de vedere case insensitive al caracterelor (nu se fac diferente intre litere mici (minuscule = lowercase) si litere mari (majuscule = uppercase))
}

bool Utils::isDouble(const string& str) const
{
	if (!str.size()) // stringul vid (nu contine caractere)
		return false; // str nu contine reprezentarea text a unui numar real

	if (str.size() == 1 && !isdigit(str.at(0))) // stringul str contine un singur caracter
		// stringul str contine un singur caracter care nu este cifra => stringul str nu contine reprezentarea unui numar real
		return false; // unicul caracter din stringul str trebuie sa fie o cifra pentru ca stringul sa fie un numar real

	if (str.at(0) == '.' || str.at(str.size() - 1) == '.') // str contine caracterul '.' pe prima sau ultima pozitie
		return false; // str nu contine reprezentarea text a unui numar real

	auto found{ false }; // semafor (flag) care sa indice daca s-a gasit un caracter '.' in stringul str
	auto begin{ true };  // semafor (flag) care sa indice daca suntem pozitionati pe primul caracter din stringul str

	for (const auto& chr : str) // iteram prin stringul str de la primul la ultimul caracter (inclusiv)
	{
		// chr - variabila de tip contor in care retinem caracterul curent din stringul str
		if (begin) // ne aflam pe primul element din stringul str
		{
			begin = false; // marcam faptul ca in iteratia urmatoare a for-ului nu o sa mai fim pozitionati pe primul caracter din string

			if (chr == '+' || chr == '-') // primul caracter (caracterul curent) din string este '+' sau '-' (semnul numarului)
				continue; // trecem la urmatoare iteratie/bucla din for (dam skip la ciclul curent)
			// un numar real poate incepe cu un caracter care sa indice semnul acestuia ('+' - numar pozitiv sau '-' - numar negativ), in absenta numarul este pozitiv
		}

		if (chr == '.') // caracterul curent (retinut in variabila chr) este caracterul '.' (dot character)
		{
			// un numar real este format din parte intreaga (inainte de caracterul '.') si parte fractionara (dupa caracterul '.')
			// caracterul '.' se numeste punctul zecimal al numarului real, acesta este un separator intre partea intreaga si cea fractionara a numarului
			// deci un numar real poate contine cel mult un caracter '.' (daca nu contine atunci nu are parte fractionara <=> partea fractionara este 0)
			if (found) // s-a descoperit deja un caracter '.' in string
				return false; // str nu contine reprezentarea text a unui numar real

			found = true; // stringul contine caracterul '.' (cel putin o data)
		}
		else if (!isdigit(chr)) // else if (chr < '0' || chr > '9')
			// stringul str contine un caracter care nu este numeric (adica nu este cifra)
			return false; // str nu contine reprezentarea text a unui numar real
	}

	return true; // str contine reprezentarea text a unui numar real
}

bool Utils::isInteger(const string& str) const
{
	if (!str.size()) // stringul vid (nu contine caractere)
		return false; // str nu contine reprezentarea text a unui numar intreg

	if (str.size() == 1 && !isdigit(str.at(0))) // stringul format dintr-un singur caracter (caracterul trebuie sa fie in acest caz o cifra)
		// cazul in care unicul caracter din stringul str nu este o cifra
		return false; // str nu contine reprezentarea text a unui numar intreg

	auto begin{ true }; // semafor (flag) care sa indice daca suntem pozitionati pe primul caracter din stringul str
	// begin = true  => caracterul curent din stringul str este primul
	//       = false => caracterul curent din stringul str nu este primul (este al doilea, al treilea, ..., sau ultimul)

	for (const auto& chr : str) // iteram prin stringul str de la primul la ultimul caracter (inclusiv)
	{
		// chr - variabila de tip contor in care retinem caracterul curent din stringul str
		if (begin) // ne aflam pe primul caracter din stringul str
		{
			begin = false; // marcam faptul ca in iteratia urmatoare a for-ului nu o sa mai fim pozitionati pe primul caracter din string

			if (chr != '+' && chr != '-' && !isdigit(chr)) // primul caracter din stringul str nu este nici caracterul '+', nici '-', si nici un caracter cifra ('0', '1', ..., '9')
				// primul caracter din string poate sa fie semnul numarului intreg (adica caracterul '+' pentru numere pozitive (>= 0) sau caracterul '-' pentru numere negative (<= 0))
				return false; // str nu contine reprezentarea text a unui numar intreg
		}
		else if (!isdigit(chr)) // caracterul chr din stringul str nu este o cifra si nu este nici primul caracter din string
			// (primul caracter poate sa fie '+' sau '-', adica semnul/signatura numarului)
			return false; // str nu contine reprezentarea text a unui numar intreg
	}

	return true; // str contine reprezentarea text a unui numar intreg
}