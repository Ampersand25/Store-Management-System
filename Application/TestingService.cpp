#include "TestingService.h"
//#include "Service.h"
#include "ServiceException.h"
#include "Repository.h"
#include "RepoException.h"
#include "ProductException.h"
#include "CosException.h"

#include <cmath>     // #include <math.h>
					 // for fabs (float absolute value)
#include <cassert>   // #include <assert.h>
					 // for assert
#include <algorithm> // for std::count_if

using std::count_if;

void TestingService::runTestsServiceCmpStrings() const
{
	RepoProducts repo;
	const Service srv{ repo, valid };

	assert(srv.cmpStrings(" ", "") == false);
	assert(srv.cmpStrings("afs", "32jio") == false);
	assert(srv.cmpStrings("9823sf", "fdg") == false);
	assert(srv.cmpStrings("1874", "1875") == false);
	assert(srv.cmpStrings("abcdefgh", "abcdhfgh") == false);
	assert(srv.cmpStrings("1fas43o./afs", "2fas43o./afs") == false);

	assert(srv.cmpStrings("", "") == true);
	assert(srv.cmpStrings("-a./b123c34", "-a./b123c34") == true);
	assert(srv.cmpStrings("A5b-.343c", "a5B-.343c") == true);
	assert(srv.cmpStrings(".a.?2351B--C", ".A.?2351b--c") == true);
	assert(srv.cmpStrings("aBc329de12F3", "aBC329dE12f3") == true);
	assert(srv.cmpStrings("459ab4398C0d./23f", "459aB4398c0d./23F") == true);
}

void TestingService::runTestsServiceVerifyIfDouble() const
{
	RepoProducts repo;
	const Service srv{ repo, valid };

	try {
		srv.verifyIfDouble("32.341.");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Pretul introdus nu este un numar real!\n");
	}

	try {
		srv.verifyIfDouble(".541");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Pretul introdus nu este un numar real!\n");
	}

	try {
		srv.verifyIfDouble("65.");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Pretul introdus nu este un numar real!\n");
	}

	try {
		srv.verifyIfDouble("0.234");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("23");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("0");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("+443");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("+65.135");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("+0.34");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("-5");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("-435.123");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfDouble("-0.3");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceVerifyIfInteger() const
{
	RepoProducts repo;
	const Service srv{ repo, valid };

	// Cazuri de exceptie

	try {
		srv.verifyIfInteger("");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("+");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("++");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("+-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("-+");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("--");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("abc");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("123abc4567");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("ab12345");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("10.25");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("5+");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.verifyIfInteger("25-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	// Cazuri in care nu se arunca exceptie

	try {
		srv.verifyIfInteger("+7");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfInteger("-3");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfInteger("+5781");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfInteger("-370");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfInteger("0");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfInteger("+0");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.verifyIfInteger("-0");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceAdd() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.add("a", "b", 4.725, "c");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.add("a", "deg", 13.05, "c");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.add("", "x", 0, "y");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException& pe) {
		assert(pe.getMessage() == "[!]Nume invalid!\n[!]Pret invalid!\n");
	}
}

void TestingService::runTestsServiceDel() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.del("a", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("a", "");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(true);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 0.1, "c");

	try {
		srv.del("a", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("a", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n[!]Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.del("a", "c");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceModify() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.modify("a", "b", 3.573, "c");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 6.1, "c");

	try {
		srv.modify("a", "x", 9, "d");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.modify("", "", -5.21, "d");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException& ex) {
		assert(ex.getMessage() == "[!]Nume invalid!\n[!]Tip invalid!\n[!]Pret invalid!\n");
	}

	try {
		srv.modify("a", "x", 21.4501, "c");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceSearch() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.search("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n[!]Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "c");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 0.56, "c");

	try {
		srv.search("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n[!]Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Producator invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		const auto& p = srv.search("a", "c");

		assert(p.getName() == "a");
		assert(p.getType() == "b");
		assert(fabs(p.getPrice() - 0.56) < 1e-12);
		assert(p.getProducer() == "c");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	try {
		srv.search("a", "b");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsServiceGetAll() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.getAll();
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("a", "b", 3.74, "c");

	try {
		const auto& produse = srv.getAll();

		assert(produse.at(0).getName() == "a");
		assert(produse.at(0).getType() == "b");
		assert(fabs(produse.at(0).getPrice() - 3.74) < 1e-12);
		assert(produse.at(0).getProducer() == "c");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("x", "y", 15.1, "z");

	try {
		const auto& produse = srv.getAll();

		assert(produse.at(0).getName() == "a");
		assert(produse.at(0).getType() == "b");
		assert(fabs(produse.at(0).getPrice() - 3.74) < 1e-12);
		assert(produse.at(0).getProducer() == "c");

		assert(produse.at(1).getName() == "x");
		assert(produse.at(1).getType() == "y");
		assert(fabs(produse.at(1).getPrice() - 15.1) < 1e-12);
		assert(produse.at(1).getProducer() == "z");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}

	srv.add("abc", "xyzklm", 15.1, "1pr23qst456u7v");

	try {
		const auto& produse = srv.getAll();

		assert(produse.at(0).getName() == "a");
		assert(produse.at(0).getType() == "b");
		assert(fabs(produse.at(0).getPrice() - 3.74) < 1e-12);
		assert(produse.at(0).getProducer() == "c");

		assert(produse.at(1).getName() == "x");
		assert(produse.at(1).getType() == "y");
		assert(fabs(produse.at(1).getPrice() - 15.1) < 1e-12);
		assert(produse.at(1).getProducer() == "z");

		assert(produse.at(2).getName() == "abc");
		assert(produse.at(2).getType() == "xyzklm");
		assert(fabs(produse.at(2).getPrice() - 15.1) < 1e-12);
		assert(produse.at(2).getProducer() == "1pr23qst456u7v");
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ProductException&) {
		assert(false);
	}
}

void TestingService::runTestsCountType() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.countType();
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	srv.add("a", "b", 5.74, "c");

	try {
		auto m{ srv.countType() };

		assert(m.size() == 1);

		assert(m.find("b") != m.end());
		assert(m["b"].first == "b");
		assert(m["b"].second == 1);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.add("x", "b", 7.213, "z");

	try {
		auto m{ srv.countType() };

		assert(m.size() == 1);

		assert(m.find("b") != m.end());
		assert(m["b"].first == "b");
		assert(m["b"].second == 2);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.add("d", "e", 3, "f");

	try {
		auto m{ srv.countType() };

		assert(m.size() == 2);

		assert(m.find("b") != m.end());
		assert(m["b"].first == "b");
		assert(m["b"].second == 2);

		assert(m.find("e") != m.end());
		assert(m["e"].first == "e");
		assert(m["e"].second == 1);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.add("u", "v", 9.45, "w");

	try {
		auto m{ srv.countType() };

		assert(m.size() == 3);

		assert(m.find("b") != m.end());
		assert(m["b"].first == "b");
		assert(m["b"].second == 2);

		assert(m.find("e") != m.end());
		assert(m["e"].first == "e");
		assert(m["e"].second == 1);

		assert(m.find("e") != m.end());
		assert(m["v"].first == "v");
		assert(m["v"].second == 1);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.add("r", "b", 85.5337, "t");

	try {
		auto m{ srv.countType() };

		assert(m.size() == 3);

		assert(m.find("b") != m.end());
		assert(m["b"].first == "b");
		assert(m["b"].second == 3);

		assert(m.find("e") != m.end());
		assert(m["e"].first == "e");
		assert(m["e"].second == 1);

		assert(m.find("e") != m.end());
		assert(m["v"].first == "v");
		assert(m["v"].second == 1);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.add("m", "e", 13.1, "o");

	try {
		auto m{ srv.countType() };

		assert(m.size() == 3);

		assert(m.find("b") != m.end());
		assert(m["b"].first == "b");
		assert(m["b"].second == 3);

		assert(m.find("e") != m.end());
		assert(m["e"].first == "e");
		assert(m["e"].second == 2);

		assert(m.find("e") != m.end());
		assert(m["v"].first == "v");
		assert(m["v"].second == 1);
	}
	catch (const RepoException&) {
		assert(false);
	}
}

void TestingService::runTestsUndo() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.undo();
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nu se mai poate realiza operatia de undo!\n");
	}

	srv.add("a", "b", 6.37, "c");
	assert(srv.getAll().size() == 1);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");

	srv.add("d", "e", 13.206, "f");
	assert(srv.getAll().size() == 2);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");

	srv.add("g", "h", 4.1, "i");
	assert(srv.getAll().size() == 3);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "h", 4.1, "i");

	srv.add("j", "k", 9, "l");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(3), "j", "k", 9, "l");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	assert(srv.getAll().size() == 3);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "h", 4.1, "i");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	assert(srv.getAll().size() == 2);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	assert(srv.getAll().size() == 1);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	try {
		assert(srv.getAll().size() == 0);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		srv.undo();
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nu se mai poate realiza operatia de undo!\n");
	}

	srv.add("a", "b", 6.37, "c");
	srv.add("d", "e", 13.206, "f");
	srv.add("g", "h", 4.1, "i");
	srv.add("j", "k", 9, "l");

	srv.modify("g", "x", 24.45, "i");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "k", 9, "l");

	srv.modify("a", "y", 11.6, "c");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "y", 11.6, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "k", 9, "l");

	srv.modify("j", "z", 0.571, "l");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "y", 11.6, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "z", 0.571, "l");

	srv.modify("d", "w", 4.57014, "f");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "y", 11.6, "c");
	testFunction(srv.getAll().at(1), "d", "w", 4.57014, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "z", 0.571, "l");

	assert(srv.undo() == "[+]Undo modificare realizat cu succes!\n");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "y", 11.6, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "z", 0.571, "l");

	assert(srv.undo() == "[+]Undo modificare realizat cu succes!\n");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "y", 11.6, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "k", 9, "l");

	assert(srv.undo() == "[+]Undo modificare realizat cu succes!\n");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "x", 24.45, "i");
	testFunction(srv.getAll().at(3), "j", "k", 9, "l");

	assert(srv.undo() == "[+]Undo modificare realizat cu succes!\n");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");
	testFunction(srv.getAll().at(2), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(3), "j", "k", 9, "l");

	srv.del("d", "f");
	assert(srv.getAll().size() == 3);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(2), "j", "k", 9, "l");

	srv.del("a", "c");
	assert(srv.getAll().size() == 2);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(1), "j", "k", 9, "l");

	srv.del("j", "l");
	assert(srv.getAll().size() == 1);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");

	srv.del("g", "i");
	try {
		assert(srv.getAll().size() == 0);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	assert(srv.undo() == "[+]Undo stergere realizat cu succes!\n");
	assert(srv.getAll().size() == 1);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");

	assert(srv.undo() == "[+]Undo stergere realizat cu succes!\n");
	assert(srv.getAll().size() == 2);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(1), "j", "k", 9, "l");

	assert(srv.undo() == "[+]Undo stergere realizat cu succes!\n");
	assert(srv.getAll().size() == 3);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(1), "j", "k", 9, "l");
	testFunction(srv.getAll().at(2), "a", "b", 6.37, "c");

	assert(srv.undo() == "[+]Undo stergere realizat cu succes!\n");
	assert(srv.getAll().size() == 4);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(1), "j", "k", 9, "l");
	testFunction(srv.getAll().at(2), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(3), "d", "e", 13.206, "f");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	assert(srv.getAll().size() == 3);
	testFunction(srv.getAll().at(0), "g", "h", 4.1, "i");
	testFunction(srv.getAll().at(1), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(2), "d", "e", 13.206, "f");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	assert(srv.getAll().size() == 2);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");
	testFunction(srv.getAll().at(1), "d", "e", 13.206, "f");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	assert(srv.getAll().size() == 1);
	testFunction(srv.getAll().at(0), "a", "b", 6.37, "c");

	assert(srv.undo() == "[+]Undo adaugare realizat cu succes!\n");
	try {
		assert(srv.getAll().size() == 0);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		srv.undo();
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nu se mai poate realiza operatia de undo!\n");
	}
}

void TestingService::testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept
{
	assert(p.getName() == name);
	assert(p.getType() == type);
	assert(fabs(p.getPrice() - price) < 1e-12);
	assert(p.getProducer() == producer);
}

void TestingService::runTestsServiceFilterProducts() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	vector<Product> products;

	try {
		products = srv.filterProducts("1", "4.25", "<");
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snacksuri", 9.6, "Lays");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snacks", 9.1, "Pringles");

	products = srv.filterProducts("1", "8.5", "<");
	assert(products.size() == 3);
	testFunction(products.at(0), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(1), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(2), "parmezan", "condimente", 8.301, "Delikat");

	products = srv.filterProducts("1", "8.301", "=");
	assert(products.size() == 1);
	testFunction(products.at(0), "parmezan", "condimente", 8.301, "Delikat");

	products = srv.filterProducts("1", "9.4", ">");
	assert(products.size() == 2);
	testFunction(products.at(0), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(1), "sare", "condimente", 11, "Maggi");

	try {
		products = srv.filterProducts("1", "2.57", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Simbol de inegalitate invalid!\n");
	}

	try {
		products = srv.filterProducts("1", "12.013", ".");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Simbol de inegalitate invalid!\n");
	}

	try {
		products = srv.filterProducts("4", "69", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de filtrare invalid!\n");
	}

	try {
		products = srv.filterProducts("0", "abc", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de filtrare invalid!\n");
	}

	try {
		products = srv.filterProducts("abc", "...", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de filtrare invalid!\n");
	}

	try {
		products = srv.filterProducts("", "2.55", "-");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de filtrare invalid!\n");
	}

	products = srv.filterProducts("1", "0.1", "<");
	assert(products.size() == 0);

	products = srv.filterProducts("1", "9.69", "=");
	assert(products.size() == 0);

	products = srv.filterProducts("1", "23", ">");
	assert(products.size() == 0);

	products = srv.filterProducts("2", "chipsuri", "");
	assert(products.size() == 2);
	testFunction(products.at(0), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(1), "chipsuri", "snacks", 9.1, "Pringles");

	products = srv.filterProducts("2", "sare", "/abc1234XYZ()");
	assert(products.size() == 1);
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");

	products = srv.filterProducts("2", "iaurt", ".");
	assert(products.size() == 1);
	testFunction(products.at(0), "iaurt", "produse lactate", 4.63, "Danone");

	products = srv.filterProducts("2", "branza", "*");
	assert(products.size() == 0);

	products = srv.filterProducts("3", "Delikat", "-");
	assert(products.size() == 2);
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");

	products = srv.filterProducts("3", "Pringles", "dsgf/af?OI,.FHfsoijPJfafsF42asf");
	assert(products.size() == 1);
	testFunction(products.at(0), "chipsuri", "snacks", 9.1, "Pringles");

	products = srv.filterProducts("3", "Danone", ".--/");
	assert(products.size() == 1);
	testFunction(products.at(0), "iaurt", "produse lactate", 4.63, "Danone");

	products = srv.filterProducts("3", "Chio", "&&132s");
	assert(products.size() == 0);
}

void TestingService::runTestsServiceSortProducts() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	vector<Product> products;

	try {
		products = srv.sortProducts("1", "c");
		assert(false);
	}
	catch (const RepoException& ex) {
		assert(ex.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snacksuri", 9.6, "Lays");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snacks", 9.1, "Pringles");

	products = srv.sortProducts("1", "c");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(2), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(3), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(4), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(5), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("1", "d");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(2), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(3), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(4), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(5), "boia", "condimente", 0.999, "Delikat");

	products = srv.sortProducts("2", "C");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(2), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(3), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(4), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(5), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("2", "d");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(2), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(3), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(4), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(5), "boia", "condimente", 0.999, "Delikat");

	products = srv.sortProducts("3", "c");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(2), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(3), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(4), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(5), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("3", "D");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(2), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(3), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(4), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(5), "boia", "condimente", 0.999, "Delikat");

	try {
		products = srv.sortProducts("1", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Ordine de sortare invalida!\n");
	}

	try {
		products = srv.sortProducts("2", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Ordine de sortare invalida!\n");
	}

	try {
		products = srv.sortProducts("3", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Ordine de sortare invalida!\n");
	}

	try {
		products = srv.sortProducts("", "c");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de sortare invalid!\n");
	}

	try {
		products = srv.sortProducts("", "d");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de sortare invalid!\n");
	}

	try {
		products = srv.sortProducts("", "C");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de sortare invalid!\n");
	}

	try {
		products = srv.sortProducts("", "D");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Criteriu de sortare invalid!\n");
	}

	srv.add("hartie igienica", "produse de baie", 3.678, "Zewa");
	srv.add("hartie igienica", "hartie parfumata", 8.4, "Emeka");
	srv.add("hartie igienica", "igiena", 7.42, "Milde");

	products = srv.sortProducts("3", "C");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(2), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(3), "hartie igienica", "hartie parfumata", 8.4, "Emeka");
	testFunction(products.at(4), "hartie igienica", "igiena", 7.42, "Milde");
	testFunction(products.at(5), "hartie igienica", "produse de baie", 3.678, "Zewa");
	testFunction(products.at(6), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(7), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(8), "sare", "condimente", 11, "Maggi");

	products = srv.sortProducts("3", "d");
	testFunction(products.at(0), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(1), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(2), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(3), "hartie igienica", "produse de baie", 3.678, "Zewa");
	testFunction(products.at(4), "hartie igienica", "igiena", 7.42, "Milde");
	testFunction(products.at(5), "hartie igienica", "hartie parfumata", 8.4, "Emeka");
	testFunction(products.at(6), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(7), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(8), "boia", "condimente", 0.999, "Delikat");

	srv.add("tuica de prune", "alcool", 6.325, "Maramures");
	srv.add("tuica de prune", "alcool", 13, "Ardealu");

	products = srv.sortProducts("3", "c");
	testFunction(products.at(0), "boia", "condimente", 0.999, "Delikat");
	testFunction(products.at(1), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(2), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(3), "hartie igienica", "hartie parfumata", 8.4, "Emeka");
	testFunction(products.at(4), "hartie igienica", "igiena", 7.42, "Milde");
	testFunction(products.at(5), "hartie igienica", "produse de baie", 3.678, "Zewa");
	testFunction(products.at(6), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(7), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(8), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(9), "tuica de prune", "alcool", 6.325, "Maramures");
	testFunction(products.at(10), "tuica de prune", "alcool", 13, "Ardealu");

	products = srv.sortProducts("3", "d");
	testFunction(products.at(0), "tuica de prune", "alcool", 6.325, "Maramures");
	testFunction(products.at(1), "tuica de prune", "alcool", 13, "Ardealu");
	testFunction(products.at(2), "sare", "condimente", 11, "Maggi");
	testFunction(products.at(3), "parmezan", "condimente", 8.301, "Delikat");
	testFunction(products.at(4), "iaurt", "produse lactate", 4.63, "Danone");
	testFunction(products.at(5), "hartie igienica", "produse de baie", 3.678, "Zewa");
	testFunction(products.at(6), "hartie igienica", "igiena", 7.42, "Milde");
	testFunction(products.at(7), "hartie igienica", "hartie parfumata", 8.4, "Emeka");
	testFunction(products.at(8), "chipsuri", "snacksuri", 9.6, "Lays");
	testFunction(products.at(9), "chipsuri", "snacks", 9.1, "Pringles");
	testFunction(products.at(10), "boia", "condimente", 0.999, "Delikat");
}

void TestingService::runTestsAdaugareCos() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.adaugareCos("chipsuri", "Lays");
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snaksuri", 9.6, "Lays");
	srv.add("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("pasta de dinti", "igiena", 7.12, "Colgate");
	srv.add("iaurt", "produse lactate", 5.013, "Milka UK");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snaksuri", 1.53, "Chio");
	srv.add("chipsuri", "snaksuri", 9.1, "Pringles");

	try {
		srv.adaugareCos("", "");
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n[!]Producator invalid!\n");
	}

	try {
		srv.adaugareCos("", "producator");
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Nume invalid!\n");
	}

	try {
		srv.adaugareCos("nume produs", "");
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Producator invalid!\n");
	}

	try {
		srv.adaugareCos("chipsuri", "Colgate");
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Produsul cautat nu se afla in stoc!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("iaurt", "Delikat");
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Produsul cautat nu se afla in stoc!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("iaurt", "Pringles");
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Produsul cautat nu se afla in stoc!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("boia", "Delikat");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("boia", "Delikat");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("iaurt", "Danone");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("boia", "Delikat");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("chipsuri", "Chio");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.del("chipsuri", "Chio");

	try {
		srv.adaugareCos("chipsuri", "Chio");
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Produsul cautat nu se afla in stoc!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}

	try {
		srv.adaugareCos("sare", "Maggi");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.modify("sare", "condimente traditionale", 13.265, "Maggi");

	try {
		srv.adaugareCos("sare", "Maggi");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	srv.del("sare", "Maggi");

	try {
		srv.adaugareCos("sare", "Maggi");
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Produsul cautat nu se afla in stoc!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}
}

void TestingService::cmpDouble(const double& a, const double& b) const noexcept
{
	assert(fabs(a - b) < 1e-12);
}

void TestingService::runTestsTotalCos() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	assert(srv.totalCos() < 1e-12);

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snaksuri", 9.6, "Lays");
	srv.add("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("pasta de dinti", "igiena", 7.12, "Colgate");

	srv.adaugareCos("chipsuri", "Lays");
	cmpDouble(srv.totalCos(), 9.6);

	srv.adaugareCos("chipsuri", "Lays");
	cmpDouble(srv.totalCos(), 9.6 + 9.6);

	srv.adaugareCos("pasta de dinti", "Colgate");
	cmpDouble(srv.totalCos(), 9.6 + 9.6 + 7.12);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	cmpDouble(srv.totalCos(), 9.6 + 9.6 + 7.12 + 13.9841);

	srv.adaugareCos("pasta de dinti", "Colgate");
	cmpDouble(srv.totalCos(), 9.6 + 9.6 + 7.12 + 13.9841 + 7.12);

	srv.adaugareCos("iaurt", "Danone");
	cmpDouble(srv.totalCos(), 9.6 + 9.6 + 7.12 + 13.9841 + 7.12 + 4.63);

	srv.adaugareCos("chipsuri", "Lays");
	cmpDouble(srv.totalCos(), 9.6 + 9.6 + 7.12 + 13.9841 + 7.12 + 4.63 + 9.6);

	srv.adaugareCos("boia", "Delikat");
	cmpDouble(srv.totalCos(), 9.6 + 9.6 + 7.12 + 13.9841 + 7.12 + 4.63 + 9.6 + 0.999);
}

void TestingService::runTestsCantitateCos() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	assert(srv.cantitateCos() == 0);

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snaksuri", 9.6, "Lays");
	srv.add("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("pasta de dinti", "igiena", 7.12, "Colgate");

	srv.adaugareCos("chipsuri", "Lays");
	assert(srv.cantitateCos() == 1);

	srv.adaugareCos("chipsuri", "Lays");
	assert(srv.cantitateCos() == 2);

	srv.adaugareCos("pasta de dinti", "Colgate");
	assert(srv.cantitateCos() == 3);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	assert(srv.cantitateCos() == 4);

	srv.adaugareCos("pasta de dinti", "Colgate");
	assert(srv.cantitateCos() == 5);

	srv.adaugareCos("iaurt", "Danone");
	assert(srv.cantitateCos() == 6);

	srv.adaugareCos("chipsuri", "Lays");
	assert(srv.cantitateCos() == 7);

	srv.adaugareCos("boia", "Delikat");
	assert(srv.cantitateCos() == 8);
}

void TestingService::runTestsGolireCos() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	cmpDouble(srv.totalCos(), 0); // assert(srv.totalCos() < 1e-12);
	assert(srv.cantitateCos() == 0);

	try {
		srv.golireCos();
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Nu exista produse in cosul de cumparaturi!\n");
	}

	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snaksuri", 1.53, "Chio");
	srv.add("chipsuri", "snaksuri", 9.1, "Pringles");

	srv.adaugareCos("parmezan", "Delikat");
	srv.adaugareCos("chipsuri", "Pringles");
	srv.adaugareCos("chipsuri", "Pringles");
	srv.adaugareCos("sare", "Maggi");
	srv.adaugareCos("parmezan", "Delikat");
	srv.adaugareCos("chipsuri", "Pringles");
	srv.adaugareCos("chipsuri", "Chio");
	srv.adaugareCos("sare", "Maggi");

	assert(srv.totalCos() != 0);
	assert(srv.cantitateCos() == 8);

	srv.golireCos();

	cmpDouble(srv.totalCos(), 0); // assert(srv.totalCos() < 1e-12);
	assert(srv.cantitateCos() == 0);
}

void TestingService::runTestsGenerareCos() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	cmpDouble(srv.totalCos(), 0);
	assert(srv.cantitateCos() == 0);

	try {
		srv.generareCos("abc");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.generareCos(".385");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.generareCos("f921asf1");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Informatia introdusa nu este un numar intreg!\n");
	}

	try {
		srv.generareCos("-25");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numarul introdus nu este o valoare pozitiva!\n");
	}

	try {
		srv.generareCos("-371");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numarul introdus nu este o valoare pozitiva!\n");
	}

	try {
		srv.generareCos("-1");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numarul introdus nu este o valoare pozitiva!\n");
	}

	try {
		srv.generareCos("5");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		srv.generareCos("0");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		srv.generareCos("13");
		assert(false);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	srv.add("iaurt", "produse lactate", 4.63, "Danone");
	srv.add("chipsuri", "snaksuri", 9.6, "Lays");
	srv.add("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("pasta de dinti", "igiena", 7.12, "Colgate");
	srv.add("iaurt", "produse lactate", 5.013, "Milka UK");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");
	srv.add("chipsuri", "snaksuri", 1.53, "Chio");
	srv.add("chipsuri", "snaksuri", 9.1, "Pringles");

	try {
		srv.generareCos("3");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(srv.totalCos() != 0);
	assert(srv.cantitateCos() == 3);

	try {
		srv.generareCos("5");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(srv.totalCos() != 0);
	assert(srv.cantitateCos() == 8);

	try {
		srv.generareCos("0");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(srv.totalCos() != 0);
	assert(srv.cantitateCos() == 8);

	try {
		srv.generareCos("1");
		assert(true);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(srv.totalCos() != 0);
	assert(srv.cantitateCos() == 9);
}

void TestingService::runTestsExportCos() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		srv.exportCos("cos", "html");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos.html") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}

	try {
		srv.exportCos("cos", "csv");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos.csv") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}

	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("pasta de dinti", "igiena", 7.12, "Colgate");
	srv.add("iaurt", "produse lactate", 5.013, "Milka UK");
	srv.add("sare", "condimente", 11, "Maggi");
	srv.add("parmezan", "condimente", 8.301, "Delikat");

	srv.generareCos("9");

	try {
		srv.exportCos("", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numele fisierului nu poate fi vid!\n");
	}

	try {
		srv.exportCos("", "html");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numele fisierului nu poate fi vid!\n");
	}

	try {
		srv.exportCos("", "CSV");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numele fisierului nu poate fi vid!\n");
	}

	try {
		srv.exportCos("", "abc");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Numele fisierului nu poate fi vid!\n");
	}

	try {
		srv.exportCos("cos", "");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Tip fisier export invalid!\n");
	}

	try {
		srv.exportCos("cos", "abc");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Tip fisier export invalid!\n");
	}

	try {
		srv.exportCos("cos", "=/fg123");
		assert(false);
	}
	catch (const ServiceException& se) {
		assert(se.getMessage() == "[!]Tip fisier export invalid!\n");
	}

	try {
		srv.exportCos("cos1", "cSv");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos1.csv") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.exportCos("cos2", "html");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos2.html") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.exportCos("cos3", "CSV");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos3.csv") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.exportCos("cos4", "hTml");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos4.html") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}

	try {
		srv.exportCos("cos5", "CsV");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\cos5.csv") == 0);
	}
	catch (const ServiceException&) {
		assert(false);
	}
}

void TestingService::cmpCantityCos(const Service& srv, const int& a, const int& b, const int& c, const int& d, const int& e) const
{
	const auto& list{ srv.getCosCumparaturi() };

	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "chipsuri" && prod.getProducer() == "Lays"; }) == a);
	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "ton in ulei" && prod.getProducer() == "Tonno Rio Mare"; }) == b);
	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "boia" && prod.getProducer() == "Delikat"; }) == c);
	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "pasta de dinti" && prod.getProducer() == "Colgate"; }) == d);
	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "iaurt" && prod.getProducer() == "Milka UK"; }) == e);
}

void TestingService::runTestsGetCosCumparaturi() const
{
	RepoProducts repo;
	Service srv{ repo, valid };

	try {
		assert(srv.getCosCumparaturi().size() == 0);
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Nu exista produse in cosul de cumparaturi!\n");
	}

	srv.add("chipsuri", "snaksuri", 9.6, "Lays");
	srv.add("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare");
	srv.add("boia", "condimente", 0.999, "Delikat");
	srv.add("pasta de dinti", "igiena", 7.12, "Colgate");
	srv.add("iaurt", "produse lactate", 5.013, "Milka UK");

	srv.adaugareCos("iaurt", "Milka UK");
	assert(srv.getCosCumparaturi().size() == 1);
	cmpCantityCos(srv, 0, 0, 0, 0, 1);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	assert(srv.getCosCumparaturi().size() == 2);
	cmpCantityCos(srv, 0, 1, 0, 0, 1);

	srv.adaugareCos("pasta de dinti", "Colgate");
	assert(srv.getCosCumparaturi().size() == 3);
	cmpCantityCos(srv, 0, 1, 0, 1, 1);

	srv.adaugareCos("pasta de dinti", "Colgate");
	assert(srv.getCosCumparaturi().size() == 4);
	cmpCantityCos(srv, 0, 1, 0, 2, 1);

	srv.adaugareCos("chipsuri", "Lays");
	assert(srv.getCosCumparaturi().size() == 5);
	cmpCantityCos(srv, 1, 1, 0, 2, 1);

	srv.adaugareCos("iaurt", "Milka UK");
	assert(srv.getCosCumparaturi().size() == 6);
	cmpCantityCos(srv, 1, 1, 0, 2, 2);

	srv.adaugareCos("boia", "Delikat");
	assert(srv.getCosCumparaturi().size() == 7);
	cmpCantityCos(srv, 1, 1, 1, 2, 2);

	srv.adaugareCos("pasta de dinti", "Colgate");
	assert(srv.getCosCumparaturi().size() == 8);
	cmpCantityCos(srv, 1, 1, 1, 3, 2);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	assert(srv.getCosCumparaturi().size() == 9);
	cmpCantityCos(srv, 1, 2, 1, 3, 2);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	assert(srv.getCosCumparaturi().size() == 10);
	cmpCantityCos(srv, 1, 3, 1, 3, 2);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	assert(srv.getCosCumparaturi().size() == 11);
	cmpCantityCos(srv, 1, 4, 1, 3, 2);

	srv.adaugareCos("boia", "Delikat");
	assert(srv.getCosCumparaturi().size() == 12);
	cmpCantityCos(srv, 1, 4, 2, 3, 2);

	srv.adaugareCos("iaurt", "Milka UK");
	assert(srv.getCosCumparaturi().size() == 13);
	cmpCantityCos(srv, 1, 4, 2, 3, 3);

	srv.adaugareCos("ton in ulei", "Tonno Rio Mare");
	assert(srv.getCosCumparaturi().size() == 14);
	cmpCantityCos(srv, 1, 5, 2, 3, 3);

	srv.adaugareCos("chipsuri", "Lays");
	assert(srv.getCosCumparaturi().size() == 15);
	cmpCantityCos(srv, 2, 5, 2, 3, 3);

	srv.adaugareCos("chipsuri", "Lays");
	assert(srv.getCosCumparaturi().size() == 16);
	cmpCantityCos(srv, 3, 5, 2, 3, 3);

	srv.golireCos();
	try {
		assert(srv.getCosCumparaturi().size() == 0);
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Nu exista produse in cosul de cumparaturi!\n");
	}

	srv.generareCos("5");
	assert(srv.getCosCumparaturi().size() == 5);

	srv.generareCos("3");
	assert(srv.getCosCumparaturi().size() == 8);

	srv.generareCos("1");
	assert(srv.getCosCumparaturi().size() == 9);

	srv.generareCos("11");
	assert(srv.getCosCumparaturi().size() == 20);

	srv.generareCos("0");
	assert(srv.getCosCumparaturi().size() == 20);
}

void TestingService::runTestsService() const
{
	runTestsServiceCmpStrings();
	runTestsServiceVerifyIfDouble();
	runTestsServiceVerifyIfInteger();

	runTestsServiceAdd();
	runTestsServiceDel();
	runTestsServiceModify();
	runTestsServiceSearch();
	runTestsServiceGetAll();
	runTestsCountType();
	runTestsUndo();

	runTestsServiceFilterProducts();
	runTestsServiceSortProducts();

	runTestsAdaugareCos();
	runTestsTotalCos();
	runTestsCantitateCos();
	runTestsGolireCos();
	runTestsGenerareCos();
	runTestsExportCos();
	runTestsGetCosCumparaturi();
}