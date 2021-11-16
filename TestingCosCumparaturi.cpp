#include "TestingCosCumparaturi.h"
#include "CosException.h"
#include "RepoException.h"
#include "Product.h"

#include <cassert> // #include <assert.h>
#include <algorithm>

using std::count_if;

void TestingCosCumparaturi::cmpDouble(const double& a, const double& b) const noexcept
{
	assert(fabs(a - b) < 1e-12);
}

void TestingCosCumparaturi::runTestsConstructor() const noexcept
{
	RepoProducts repository;
	CosCumparaturi cos{ repository };

	assert(cos.nrProduseCos() == 0);
	cmpDouble(cos.getTotal(), 0);
}

void TestingCosCumparaturi::runTestsAdaugaInCos() const
{
	assert(cos_cumparaturi.nrProduseCos() == 0);
	cmpDouble(cos_cumparaturi.getTotal(), 0);

	try {
		cos_cumparaturi.adaugaInCos("chipsuri", "Lays");
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	assert(cos_cumparaturi.nrProduseCos() == 0);
	cmpDouble(cos_cumparaturi.getTotal(), 0);

	repo.addProduct(Product{ "chipsuri", "rontanele", 13.561, "Chio" });

	try {
		cos_cumparaturi.adaugaInCos("chipsuri", "Lays");
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Produsul cautat nu se afla in stoc!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 0);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 0);

	try {
		cos_cumparaturi.adaugaInCos("chipsuri", "Chio");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 1);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 1);

	repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });

	try {
		cos_cumparaturi.adaugaInCos("vegeta", "Vegeta");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 2);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 1 + 5.7 * 0 + 9.0 * 1 + 21.47 * 0);

	try {
		cos_cumparaturi.adaugaInCos("vegeta", "Vegeta");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 3);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 1 + 5.7 * 0 + 9.0 * 2 + 21.47 * 0);

	try {
		cos_cumparaturi.adaugaInCos("pasta de dinti", "Colgate");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 4);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 1 + 5.7 * 1 + 9.0 * 2 + 21.47 * 0);

	try {
		cos_cumparaturi.adaugaInCos("chipsuri", "Chio");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 5);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 2 + 5.7 * 1 + 9.0 * 2 + 21.47 * 0);

	try {
		cos_cumparaturi.adaugaInCos("chipsuri", "Lays");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 6);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 2 + 5.7 * 1 + 9.0 * 2 + 21.47 * 1);

	try {
		cos_cumparaturi.adaugaInCos("pasta de dinti", "Colgate");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 7);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 2 + 5.7 * 2 + 9.0 * 2 + 21.47 * 1);

	try {
		cos_cumparaturi.adaugaInCos("vegeta", "Vegeta");
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 8);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 2 + 5.7 * 2 + 9.0 * 3 + 21.47 * 1);
}

void TestingCosCumparaturi::runTestsGolesteCos() const
{
	assert(cos_cumparaturi.nrProduseCos() == 8);
	cmpDouble(cos_cumparaturi.getTotal(), 13.561 * 2 + 5.7 * 2 + 9.0 * 3 + 21.47 * 1);
	
	try {
		cos_cumparaturi.golesteCos();
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 0);
	cmpDouble(cos_cumparaturi.getTotal(), 0);

	try {
		cos_cumparaturi.golesteCos();
		assert(false);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Nu exista produse in cosul de cumparaturi!\n");
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 0);
	cmpDouble(cos_cumparaturi.getTotal(), 0);
}

void TestingCosCumparaturi::runTestsGenereazaCos() const
{
	try {
		cos_cumparaturi.genereazaCos(13);
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 13);
	assert(cos_cumparaturi.getTotal() != 0);

	try {
		cos_cumparaturi.genereazaCos(2);
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 15);
	assert(cos_cumparaturi.getTotal() != 0);

	try {
		cos_cumparaturi.genereazaCos(7);
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 22);
	assert(cos_cumparaturi.getTotal() != 0);

	try {
		cos_cumparaturi.genereazaCos(0);
		assert(true);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_cumparaturi.nrProduseCos() == 22);
	assert(cos_cumparaturi.getTotal() != 0);

	repo.deleteProduct("chipsuri", "Lays");
	repo.deleteProduct("chipsuri", "Chio");
	repo.deleteProduct("pasta de dinti", "Colgate");
	repo.deleteProduct("vegeta", "Vegeta");

	try {
		cos_cumparaturi.genereazaCos(4);
		assert(false);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
}

void TestingCosCumparaturi::runTestsExportCosFisierCSV() const
{
	try {
		cos_cumparaturi.exportCosFisierCSV("test");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\test.csv") == 0);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	RepoProducts repo_gol;
	CosCumparaturi cos_gol{ repo_gol };

	assert(cos_gol.nrProduseCos() == 0);
	cmpDouble(cos_gol.getTotal(), 0);

	try {
		cos_gol.exportCosFisierCSV("test_gol");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\test_gol.csv") == 0);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_gol.nrProduseCos() == 0);
	cmpDouble(cos_gol.getTotal(), 0);
}

void TestingCosCumparaturi::runTestsExportCosFisierHTML() const
{
	try {
		cos_cumparaturi.exportCosFisierHTML("test");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\test.html") == 0);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	RepoProducts repo_gol;
	CosCumparaturi cos_gol{ repo_gol };

	assert(cos_gol.nrProduseCos() == 0);
	cmpDouble(cos_gol.getTotal(), 0);

	try {
		cos_gol.exportCosFisierHTML("test_gol2");
		assert(true);
		assert(remove(".\\Export cos cumparaturi\\test_gol2.html") == 0);
	}
	catch (const CosException&) {
		assert(false);
	}
	catch (const RepoException&) {
		assert(false);
	}

	assert(cos_gol.nrProduseCos() == 0);
	cmpDouble(cos_gol.getTotal(), 0);
}

void TestingCosCumparaturi::runTestsExportCosFisier() const
{
	runTestsExportCosFisierCSV();
	runTestsExportCosFisierHTML();
}

void TestingCosCumparaturi::runTestsGetTotal() const
{
	CosCumparaturi cos{ repo };

	repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });

	cmpDouble(cos.getTotal(), 0);

	cos.adaugaInCos("chipsuri", "Lays");
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 0 + 21.47 * 1);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 0 + 21.47 * 1);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 0 + 21.47 * 1);

	cos.adaugaInCos("chipsuri", "Lays");
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 0 + 21.47 * 2);

	cos.adaugaInCos("vegeta", "Vegeta");
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 1 + 21.47 * 2);

	cos.adaugaInCos("chipsuri", "Lays");
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 1 + 21.47 * 3);

	cos.adaugaInCos("vegeta", "Vegeta");
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 2 + 21.47 * 3);

	cos.adaugaInCos("chipsuri", "Lays");
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 2 + 21.47 * 4);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	cmpDouble(cos.getTotal(), 5.7 * 3 + 9.0 * 2 + 21.47 * 4);

	cos.adaugaInCos("vegeta", "Vegeta");
	cmpDouble(cos.getTotal(), 5.7 * 3 + 9.0 * 3 + 21.47 * 4);

	cos.adaugaInCos("vegeta", "Vegeta");
	cmpDouble(cos.getTotal(), 5.7 * 3 + 9.0 * 4 + 21.47 * 4);

	cos.adaugaInCos("vegeta", "Vegeta");
	cmpDouble(cos.getTotal(), 5.7 * 3 + 9.0 * 5 + 21.47 * 4);

	cos.golesteCos();
	cmpDouble(cos.getTotal(), 0);
}

void TestingCosCumparaturi::runTestsNrProduseCos() const
{
	CosCumparaturi cos{ repo };

	// repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	// repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });

	assert(cos.nrProduseCos() == 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 1);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 2);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 3);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 4);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 5);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 6);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 7);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 8);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 9);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 10);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 11);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 12);

	cos.golesteCos();
	assert(cos.nrProduseCos() == 0);
}

void TestingCosCumparaturi::cmpCantity(const CosCumparaturi& cos, const int& x, const int& y, const int& z) const
{
	const auto& list{ cos.getCos() };

	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "pasta de dinti" && prod.getProducer() == "Colgate"; }) == x);
	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "vegeta" && prod.getProducer() == "Vegeta"; }) == y);
	assert(count_if(list.begin(), list.end(), [](const Product& prod) {return prod.getName() == "chipsuri" && prod.getProducer() == "Lays"; }) == z);
}

void TestingCosCumparaturi::runTestsGetCos() const
{
	CosCumparaturi cos{ repo };

	// repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	// repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });

	try {
		assert(cos.getCos().size() == 0);
	}
	catch (const CosException& ce) {
		assert(ce.getMessage() == "[!]Nu exista produse in cosul de cumparaturi!\n");
	}

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.getCos().size() == 1);
	cmpCantity(cos, 0, 1, 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.getCos().size() == 2);
	cmpCantity(cos, 0, 1, 1);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.getCos().size() == 3);
	cmpCantity(cos, 0, 1, 2);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.getCos().size() == 4);
	cmpCantity(cos, 0, 2, 2);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.getCos().size() == 5);
	cmpCantity(cos, 1, 2, 2);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.getCos().size() == 6);
	cmpCantity(cos, 1, 3, 2);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.getCos().size() == 7);
	cmpCantity(cos, 1, 4, 2);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.getCos().size() == 8);
	cmpCantity(cos, 2, 4, 2);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.getCos().size() == 9);
	cmpCantity(cos, 3, 4, 2);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.getCos().size() == 10);
	cmpCantity(cos, 4, 4, 2);
}

void TestingCosCumparaturi::runTestsStergeProduseCos() const
{
	CosCumparaturi cos{ repo };

	// repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	// repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });

	repo.addProduct(Product{ "chipsuri", "rontanele", 0.5, "Chio" });

	assert(cos.nrProduseCos() == 0);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 0 + 21.47 * 0 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 1);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 1 + 21.47 * 0 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 2);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 2 + 21.47 * 0 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 3);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 2 + 21.47 * 1 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 4);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 3 + 21.47 * 1 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 5);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 3 + 21.47 * 2 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 6);
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 3 + 21.47 * 2 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 7);
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 3 + 21.47 * 3 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 8);
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 9);
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 10);
	cmpDouble(cos.getTotal(), 5.7 * 3 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 11);
	cmpDouble(cos.getTotal(), 5.7 * 4 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 12);
	cmpDouble(cos.getTotal(), 5.7 * 4 + 9.0 * 4 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 13);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 14);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 5 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 15);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 6 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 16);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 6 + 0.5 * 1);

	cos.adaugaInCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 17);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 6 + 0.5 * 2);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 18);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 7 + 0.5 * 2);

	cos.adaugaInCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 19);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3);

	repo.addProduct(Product{ "pasta de dinti", "igiena", 3.109, "Sensodyne" });

	cos.adaugaInCos("pasta de dinti", "Sensodyne");
	assert(cos.nrProduseCos() == 20);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3 + 3.109 * 1);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3 + 3.109 * 1);

	// Stergere

	// repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	// repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 0.5, "Chio" });
	// repo.addProduct(Product{ "pasta de dinti", "igiena", 3.109, "Sensodyne" });

	cos.stergeProduseCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 21 - 7);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 4 + 21.47 * 0 + 0.5 * 3 + 3.109 * 1);

	cos.stergeProduseCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 21 - 7 - 4);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 0 + 21.47 * 0 + 0.5 * 3 + 3.109 * 1);

	cos.stergeProduseCos("pasta de dinti", "Sensodyne");
	assert(cos.nrProduseCos() == 21 - 7 - 4 - 1);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 0 + 21.47 * 0 + 0.5 * 3 + 3.109 * 0);

	cos.stergeProduseCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 21 - 7 - 4 - 1 - 6);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 0 + 21.47 * 0 + 0.5 * 3 + 3.109 * 0);

	cos.stergeProduseCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 21 - 7 - 4 - 1 - 6 - 3);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 0 + 21.47 * 0 + 0.5 * 0 + 3.109 * 0);
}

void TestingCosCumparaturi::runTestsModificaProduseCos() const
{
	CosCumparaturi cos{ repo };

	// repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	// repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 0.5, "Chio" });
	// repo.addProduct(Product{ "pasta de dinti", "igiena", 3.109, "Sensodyne" });

	assert(cos.nrProduseCos() == 0);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 0 + 21.47 * 0 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 1);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 1 + 21.47 * 0 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 2);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 2 + 21.47 * 0 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 3);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 2 + 21.47 * 1 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 4);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 3 + 21.47 * 1 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 5);
	cmpDouble(cos.getTotal(), 5.7 * 0 + 9.0 * 3 + 21.47 * 2 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 6);
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 3 + 21.47 * 2 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 7);
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 3 + 21.47 * 3 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 8);
	cmpDouble(cos.getTotal(), 5.7 * 1 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 9);
	cmpDouble(cos.getTotal(), 5.7 * 2 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 10);
	cmpDouble(cos.getTotal(), 5.7 * 3 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 11);
	cmpDouble(cos.getTotal(), 5.7 * 4 + 9.0 * 3 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("vegeta", "Vegeta");
	assert(cos.nrProduseCos() == 12);
	cmpDouble(cos.getTotal(), 5.7 * 4 + 9.0 * 4 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 13);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 4 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 14);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 5 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 15);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 6 + 0.5 * 0);

	cos.adaugaInCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 16);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 6 + 0.5 * 1);

	cos.adaugaInCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 17);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 6 + 0.5 * 2);

	cos.adaugaInCos("chipsuri", "Lays");
	assert(cos.nrProduseCos() == 18);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 7 + 0.5 * 2);

	cos.adaugaInCos("chipsuri", "Chio");
	assert(cos.nrProduseCos() == 19);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3);

	cos.adaugaInCos("pasta de dinti", "Sensodyne");
	assert(cos.nrProduseCos() == 20);
	cmpDouble(cos.getTotal(), 5.7 * 5 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3 + 3.109 * 1);

	cos.adaugaInCos("pasta de dinti", "Colgate");
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3 + 3.109 * 1);

	// Modificare

	// repo.addProduct(Product{ "pasta de dinti", "igiena orala", 5.7, "Colgate" });
	// repo.addProduct(Product{ "vegeta", "condimenete", 9, "Vegeta" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 21.47, "Lays" });
	// repo.addProduct(Product{ "chipsuri", "rontanele", 0.5, "Chio" });
	// repo.addProduct(Product{ "pasta de dinti", "igiena", 3.109, "Sensodyne" });

	cos.modificaProduseCos(Product{ "pasta de dinti", "tip nou pasta", 17.2, "Sensodyne" });
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3 + 17.2 * 1);

	cos.modificaProduseCos(Product{ "pasta de dinti", "tip nou nou pasta", 2, "Sensodyne" });
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 9.0 * 4 + 21.47 * 7 + 0.5 * 3 + 2.0 * 1);

	cos.modificaProduseCos(Product{ "vegeta", "tip nou vegeta", 0.6813, "Vegeta" });
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 5.7 * 6 + 0.6813 * 4 + 21.47 * 7 + 0.5 * 3 + 2.0 * 1);

	cos.modificaProduseCos(Product{ "pasta de dinti", "tip nou pasta de dinti", 11.8, "Colgate" });
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 11.8 * 6 + 0.6813 * 4 + 21.47 * 7 + 0.5 * 3 + 2.0 * 1);

	cos.modificaProduseCos(Product{ "vegeta", "tip nou nou vegeta", 31, "Vegeta" });
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 11.8 * 6 + 31.0 * 4 + 21.47 * 7 + 0.5 * 3 + 2.0 * 1);

	cos.modificaProduseCos(Product{ "chipsuri", "tip nou chipsuri", 2.056, "Chio" });
	assert(cos.nrProduseCos() == 21);
	cmpDouble(cos.getTotal(), 11.8 * 6 + 31.0 * 4 + 21.47 * 7 + 2.056 * 3 + 2.0 * 1);
}

void TestingCosCumparaturi::runTestsCosCumparaturi() const
{
	runTestsConstructor();
	runTestsAdaugaInCos();
	runTestsGolesteCos();
	runTestsGenereazaCos();
	runTestsExportCosFisier();
	runTestsGetTotal();
	runTestsNrProduseCos();
	runTestsGetCos();
	runTestsStergeProduseCos();
	runTestsModificaProduseCos();
}