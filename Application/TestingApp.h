#pragma once

class TestingApp
{
public:
	/*
	* Constructorul default al unui obiect de clasa TestingApp
	*/
	TestingApp() = default;

	/*
	* Constructorul de copiere (folosind calificativul delete impiedicam copiere de obiecte de clasa TestingApp)
	*/
	TestingApp(const TestingApp& ot) = delete;

	/*
	* Procedura (subrutina procedurala) care ruleaza teste pentru validarea fiecarui layer/strat din aplicatie (sunt testate toate functiile care nu tin de UI = interfata cu utilizatorul, adica care nu contin citiri sau/si afisari)
	*/
	void runTestsApp() const;
};