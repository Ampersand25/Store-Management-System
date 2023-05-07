// 1 Magazin.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "TestingApp.h"       // TestingApp       - clasa in care are loc testarea aplicatiei
#include "AbstractRepo.h"     // AbstractRepo     - clasa pur abstracta
#include "Repository.h"       // RepoProducts     - clasa abstracta derivata din clasa de baza AbstractRepo
#include "FileRepository.h"   // FileRepoProducts - clasa derivata din clasa de baza Repository
#include "ExceptionRepo.h"    // ExceptionRepo    - clasa derivata din clasa de baza AbstractRepo
#include "ProductValidator.h" // ProductValidator - clasa de tip validator (valideaza entitatile din aplicatie)
#include "Service.h"          // Service          - clasa din stratul de business (controllerul aplicatiei)
#include "Console.h"          // UI               - clasa care asigura interactiunea cu userul utilizatorul

// Pentru detectarea de memory leaks (scurgeri de memorie)
#define _CRTDBG_MAP_ALLOC
#include <cstdio> // #include <stdio.h>
#include <crtdbg.h>

#include <iostream>  // pentru std::cin, std::cout, std::cerr si std::endl
#include <string>    // pentru std::string si std::stod
#include <memory>    // pentru std::unique_ptr si std::make_unique
#include <exception> // pentru std::exception

using std::cin;         // console in/input (functie care citeste de la intrarea standard (stdin = standard in/input))
using std::cout;        // console out/output (functie care scrie la iesirea standard (stdout = standard out/output))
using std::cerr;        // console error (functie care scrie la iesirea standard de erori (stderr = standard error))
using std::endl;        // end of line (acelasi efect ca si caracterul '\n')
using std::string;      // sir de caractere din STL
using std::stod;        // string to double (conversie de la std::string la double)
using std::unique_ptr;  // smart pointer
using std::make_unique; // functie care returneaza un smart pointer
using std::exception;   // exceptie din STL (clasa de exceptii)

/*
* Procedura care ruleaza testele pentru fiecare layer/strat din aplicatie (cu exceptia UI-ului)
*/
void testApplication(void)
{
    const TestingApp testing_app; // instantiem un obiect de clasa TestingApp
    testing_app.runTestsApp(); // rulam toate testele (pentru fiecare layer/strat din aplicatie)
}

/*
* Procedura (functie procedurala) care afiseaza optiunile de persistenta a datelor in cadrul aplicatiei
*/
void meniuSalvareFisiere(void)
{
    cout << "Alegeti cum sa se faca salvarea datelor in cadrul aplicatie:\n";
    cout << "1 - salvare in memorie\n";
    cout << "2 - salvare in fisier text\n";
    cout << "3 - salvare in repository de exceptii (tot in memorie)\n";
}

/*
* Functie operand (de tip rezultat) care citeste de la tastatura (intrarea standard) modul in care se vor salva datele in cadrul aplicatiei
* Subprogramul intoarce un string care contine modul de salvare a datelor (stringul "1" pentru salvare in memorie, stringul "2" pentru salvare in fisier text sau stringul "3" pentru salvarea in repozitoriul (repository) de exceptii)
*/
string readOptionDataPersistence(void)
{
    string ans; // string in care vom citi raspunsul dat de utilizator (user)
    getline(cin, ans); // citim stringul ans de la tastatura (intrarea standard) cu functia getline (care citeste si spatiile, pana la newline = end of line)

    while (ans != "1" && ans != "2" && ans != "3") // stringul ans nu este valid (raspunsul utilizatorului este invalid)
    {
        cout << "[X]Optiune inexistenta!\n";
        cout << "\n>>>";

        getline(cin, ans); // re-citim in stringul ans cum sa se faca salvarea datelor in aplicatie
    }

    // ans este stringul "1", "2" sau "3"

    return ans; // returnam/intoarcem prin numele functiei stringul care reprezinta modul in care se vor salva datele in fisier
    // ans = "1" - salvarea datelor in memorie
    // ans = "2" - salvarea datelor in fisier
    // ans = "3" - salvarea datelor in memorie folosind un repository de exceptii
}

/*
* Functie operand (de tip rezultat) care citeste de la tastatura (intrarea standard) numele fisierului in care vor fi salvate datele din cadrul aplicatiei
* Subprogramul intoarce un string nevid (<> "") care va fi numele fisierului in care se va face import si export in cadrul aplicatiei
*/
string readFilename(void)
{
    cout << "Introduceti numele fisierului text in care sa se faca salvarea datelor: ";

    string filename; // string in care memoram/retinem numele fisierului in care se vor salva datele
    getline(cin, filename); // citim stringul filename de la tastatura (intrarea standard) cu functia getline (care citeste si spatiile, pana la newline = end of line)

    while (filename.empty()) // while (!filename.size())
        // while (filename == "")
    {
        // stringul citit de la tastatura (filename) este vid/gol
        // acesta nu poate reprezenta numele unui fisier text

        cout << "[X]Numele fisierului nu poate sa fie vid!\n";
        cout << "\nReintroduceti numele fisierului text in care se va face salvarea datelor: ";

        getline(cin, filename); // re-citim numele fisierului in care se vor salva datele
    }

    // stringul filename contine cel putin un element (caracter) <=> nu este gol

    return filename; // returnam/intoarcem prin numele functiei un string (sir de caractere din STL) care reprezinta numele fisierului text in care se vor salva datele din aplicatie
    // filename <> "" (stringul filename nu este stringul vid)
}

/*
* Procedura care asambleaza si ruleaza (executa) aplicatia
*/
void runApplication(const unique_ptr<AbstractRepo>& repo)
{
    ProductValidator valid; // instantiem un obiect de clasa ProductValidator
    Service srv{ *repo, valid }; // instantiem un obiect de clasa Service caruia ii parsam ca si atribute private obiectele repo (de clasa RepoProducts) si valid (de clasa ProductValidator) instantiate anterior/precedent
    const UI ui{ srv }; // instantiem un obiect de clasa UI caruia ii parsam ca si atribut privat obiectul srv (de clasa Service) instantiat anterior
    ui.runApp(); // pornim aplicatia
}

/*
* Functie operand (de tip rezultat) care citeste de la tastatura o probabilitate pentru repository-ul de exceptii
* Subrutina/subprogramul intoarce valoarea reala citita sub forma text (ca si string)
* sau ridica exceptie de clasa std::exception daca stringul introdus de catre utilizator la intrarea standard nu contine reprezentarea unui double (numar real in dubla precizie)
* sau daca valoarea reala citita nu este subunitara sau echiunitara (cuprinsa in intervalul [0, 1])
*/
double readProbability(void)
{
    cout << "Dati probabilitatea (valoare reala intre 0 si 1) cu care repo-ul sa arunce exceptie: ";

    string str_probability{ "" };  // probabilitatea cu care repository-ul sa arunce/ridice exceptie in oricare din metodele sale
    // string str_probability;
    getline(cin, str_probability); // citim stringul str_probability de la tastatura (intrarea standard) cu functia getline (care citeste si spatiile, pana la newline = end of line)

    double probability; // probabilitatea repository-ului de exceptii
    // probability - numar real in dubla precizie (pe 64 de biti) din intervalul [0, 1]

    try {
        probability = stod(str_probability); // apelam functia build-in std::stod (string to double) din libraria string
    }
    catch (const exception&) {
        // stod a aruncat/ridicat exceptie de clasa exception
        throw exception("[!]Probabilitatea introdusa nu este un numar real!\n"); // aruncam un obiect de clasa exception cu mesajul de eroare/exceptie "[!]Probabilitatea introdusa nu este un numar real!\n"
    }

    if (probability < 0 || probability > 1) // probabilitatea citita trebuie sa fie din intervalul [0, 1]
        throw exception("[!]Probabilitatea introdusa nu este un numar real cuprins in intervalul [0, 1]!\n"); // aruncam un obiect de clasa exception cu mesajul de eroare/exceptie "[!]Probabilitatea introdusa nu este un numar real cuprins in intervalul [0, 1]!\n"

    return probability; // intoarcem prin numele functiei probabilitatea citita cu succes de la tastatura
}

/*
* Procedura (functie procedurala) care instantiaza repository-ul in care se vor memora datele din aplicatie
* Repo-ul poate sa fie unu simplu (salvare in memorie) sau cu fisiere (salvare in fisier text)
* Subrutina asambleaza repository-ul (obiect de clasa RepoProducts sau derivat din aceasta clasa) si dupa face un apel polimorfic la procedura runApplication care va instantia si celelalte obiecte din aplicatie dupa care o va executa (rula)
*/
void setUpRepository(void)
{
    meniuSalvareFisiere(); // afisam meniul cu optiunile de salvare a datelor

    cout << "\n>>>";

    const string ans{ readOptionDataPersistence() }; // string in care retinem modul de salvare a datelor in aplicatie
    // ans = "1" - salvare in memorie
    // ans = "2" - salvare in fisier text
    // ans = "3" - salvare in repo de exceptii

    unique_ptr<AbstractRepo> repo{}; // unique_ptr<AbstractRepo> repo;
    // smart pointer care retine un obiect de clasa AbstractRepo (sau obiecte de clasa derivata din aceasta)

    if (ans == "1")
    {
        // salvarea datelor in memorie

        repo = make_unique<RepoProducts>(); // instantiem un obiect de clasa RepoProducts
    }
    else if (ans == "2")
    {
        // salvarea datelor in fisier text (cu extensia .txt)

        const string filename{ readFilename() }; // numele fisierului text in care vom salva datele

        cout << "Fisierul text in care se vor salva datele din repository este: \"" << filename << ".txt\"\n";               // afisam pe ecran numele fisierului text in care se vor salva datele din repo (persistenta datelor se va face in acest fisier ci nu in memoria RAM)
        cout << "Acesta va fi creat in folderul \"Fisiere text - repo\" din directorul curent (acelasi cu proiectul)\n"; // tiparim in consola/terminal locatia fisierului text pe disk

        repo = make_unique<FileRepoProducts>(filename); // instantiem un obiect de clasa FileRepoProducts caruia ii atribuim ca si camp privat stringul filename (numele fisierului text in care va avea loc persistenta datelor din aplicatie)
    }
    else {
        // salvarea datelor in repository (repozitoriu) care arunca exceptie cu o anumita probabilitate citita de la tastatura

        double probability{}; // probabilitatea cu care repo-ul sa ridice exceptie (numar real din intervalul [0, 1])
        auto valid_probability{ false }; // semafor (flag) care sa indice daca probabilitatea citita este sau nu valida
        // valid_probability = false - probabilitatea citita in functia readProbability nu este o valoare reala intre 0 si 1
        // valid_probability = true  - in caz contrar

        while (!valid_probability) // cat timp probabilitatea nu este valida (un numar real din intervalul [0, 1]), reapelam functia readProbability pentru a citi o probabilitate noua
        {
            try {
                probability = readProbability(); // incarcam in variabila probability rezultatul intors de functia readProbability
                valid_probability = true; // probabilitatea citita este valida (un numar real pozitiv intre 0 si 1)
            }
            catch (const exception& ex) { // functia readProbability a aruncat/ridicat exceptie de clasa exception
                // ramura pe care se intra daca probabilitatea citita in functia readProbability nu este valida (nu este o valoare reala sau nu apartine intervalului [0, 1])
                // ex        - referinta constanta la un obiect de clasa std::exception
                // ex.what() - mesajul de eroare (const char*) al obiectului ex de clasa std::exception
                cerr << ex.what() << endl; // afisam la iesirea standard de erori (stderr = standard error) mesajul de eroare al obiectului de clasa std::exception aruncata de functia readProbability
            }
        }

        cout << "Probabilitatea citita este: " << probability << endl; // afisam/tiparim probabilitatea introdusa de utilizator pentru repository-ul de exceptii

        repo = make_unique<ExceptionRepo>(probability); // instantiem un obiect de clasa ExceptionRepo caruia ii atribuim ca si camp privat valoarea reala probability
    }

    cout << endl; // simulam trecerea la rand nou (linie noua)
    // endl = end of line (caracterul '\n')

    system("pause"); // oprim consola (terminaul) pana la primirea de input de la user (utilizator)

    runApplication(repo); // apel polimorfic (dynamic dispatch) la procedura runApplication care va rula aplicatia

    /*
    try {
        runApplication(repo); // apealam procedura runApplication care va rula aplicatia
    }
    catch (const exception& ex) {
        // functia runApplication poate arunca/ridica exceptie de clasa std::exception daca se apeleaza cu un repository de exceptii (obiect de clasa ExceptionRepo)
        cerr << ex.what(); // afisam/tiparim la iesirea standard de erori (stderr = standard error) mesajul asociat obiectului de clasa std::exception aruncat de functie
    }
    */
}

/*
* Procedura (functie procedurala) care testeaza aplicatia de memory leaks (scurgeri de informatie)
*/
void testMemoryLeaks(void) noexcept
{
    _CrtDumpMemoryLeaks(); // apelam _CrtDumpMemoryLeaks care detecteaza scurgerile de memorie rezultate in urma ne-eliberarii memoriei de pe heap (alocata dinamic) cu free sau delete
}

int oldMain(void)
{
    // Testarea aplicatiei
    testApplication();

    // Asamblarea si rularea aplicatie
    setUpRepository();

    // Testam aplicatia de memory leaks (scurgeri/leak-uri de memorie)
    testMemoryLeaks();

    // Terminarea aplicatiei
    return 0; // codul de return al aplicatiei (exit status) care indica o terminare normala (0 - fara erori)
}