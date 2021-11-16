#pragma once

#include <vector>
#include <algorithm>

using std::vector;
using std::remove;

/*
* Clasa Observer - clasa pur abstracta (contine doar functii pur virtuale)
* O clasa abstracta este o clasa care are cel putin o metode/functie pur virtuala
* Nu se vor putea instantia obiecte de clasa Observer (doar obiecte dintr-o clasa derivata)
*/
class Observer {
public:
	/*
	* Constructorul unui obiect de clasa Observer
	* Il setam ca fiind default (implicit/prestabilit)
	*/
	Observer() = default;

	/*
	* Metoda update (metoda pur virtuala)
	* Aceasta metoda este declarata in clasa de baza (Observer) si va trebui sa fie definita in fiecare din clasele derivate
	* In clasa de baza doar stabilim signatura (antetul) acestei functii/metode
	* Metoda defineste un slot pentru un semnal primit de la un obiect de tip Observable
	*/
	virtual void update() = 0;

	/*
	* Destructorul unui obiect de clasa Observer
	* Il setam ca fiind virtual si default (implicit)
	*/
	virtual ~Observer() = default;
};

class Observable {
private:
	vector<Observer*> observers; // vector din STL de pointeri la obiecte de clasa Observer
	                             // folosim pointeri pentru a putea face un apel polimorfic (dynamic dispatch) pentru fiecare astfel de obiect dintr-o clasa derivata din clasa Observer (clasa de baza)

protected:
	/*
	* Metoda notify o facem protejata (folosind calificativul protected)
	* Astfel ea va putea fi apelata in mod direct in fiecare clasa derivata din clasa Observable
	* Dar nu va putea fi apelata din exterior (adica dintr-o clasa care nu este derivata din clasa de baza Observable)
	* Metoda trimite un semnal (signal) tuturor observerilor (obiectelor care o observa) pentru a semnala aparitia unei schimbari a starii (adica un eveniment la care observerii vor trebui sa reactioneze prin apelul metodei update)
	*/
	void notify() {
		// folosim auto ci nu auto& la ranged for deoarece in cazul pointerilor nu exista diferente (nu se face copie)
		for (auto obs : observers) // parcurgem lista de observeri
			obs->update(); // pentru fiecare observer (obiect dintr-o clasa derivata din clasa pur abstracta Observer)
		                   // apelam metoda publica update (se va face dynamic/late binding, adica legare intarziata, apelul fiind unul polimorfic, care se relizeaza in functie de tipul actual al obiectului de la runtime) 
	}

public:
	/*
	* Constructorul default (implicit) al unui obiect de clasa Observable
	* Am folosit calificativul default
	*/
	Observable() = default;

	/*
	* Metoda publica care ataseaza un observer (obiect dintr-o clasa derivata din clasa pur virtuala Observer (clasa de baza)) la un obiect de clasa Observable (sau derivat din clasa Observable)
	* Functia adauga observerul obs in lista de observeri (observers) pe ultima pozitie
	*/
	void attachObserver(Observer* obs) {
		observers.push_back(obs); // atasam observerul obs la obiectul nostru de clasa Observable
	}
	
	/*
	* Metoda publica care detaseaza un observer (obiect dintr-o clasa derivata din clasa pur virtuala Observer (clasa de baza)) de la un obiect de clasa Observable (sau derivat din clasa Observable)
	* Observerul trebuie sa fi fost atasat anterior (prin apelul metodei publice attachObserver, complementara cu metoda/functia curenta) pentru a avea loc detasarea
	* Functia sterge observerul obs din lista de observeri (observers)
	*/
	void detachObserver(Observer* obs) {
		// observers.begin() - iterator pozitionat pe primul element din vectorul (container de date implementat folosind un vector dinamic) observers
		// observers.end()   - iterator pozitionat dupa ultimul element din vectorul (container de date implementat folosind un vector dinamic) observers
		// perechea (observers.begin(), observers.end()) ne ajuta sa definim orice secventa din vectorul/containerul observers (inclusiv secventa vida)
		// observers.begin() refera elementul observers[0]
		// observers.end()   refera elementul observers[observers.size()] (observers.size() = numarul de elemente din container)
		
		auto iter{ observers.begin() }; // obtinem un iterator pozitionat pe primul element din vectorul observers
		
		while (iter != observers.end()) // ciclam/iteram atata timp cat iteratorul este unul valid (pozitionat pe un element din container)
		{
			if (*iter == obs) // elementul curent din vectorul observers este obiectul obs cautat
			{
				observers.erase(iter); // detasam observerul obs de la obiectul nostru de clasa Observable

				return; // iesim in mod fortat din functie/metoda
			}
			
			++iter; // pozitionam iteratorul pe urmatorul element din container
		}

		// observers.erase(remove(begin(observers), end(observers), obs), observers.end());
	}

	/*
	* Destructorul unui obiect de clasa Observable
	* Il setam ca fiind virtual si default (implicit)
	*/
	virtual ~Observable() = default;
};