#include "TestingRepo.h"
#include "Repository.h"
#include "RepoException.h"

#include <cassert> // #include <assert.h>
#include <cmath>   // #include <math.h>

void TestingRepo::testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept
{
	assert(p.getName() == name);
	assert(p.getType() == type);
	assert(fabs(p.getPrice() - price) < 1e-12);
	assert(p.getProducer() == producer);
}

void TestingRepo::runTestsRepoAddProduct() const
{
	RepoProducts repo;
	assert(repo.len() == 0);

	try {
		auto products = repo.getAll();
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	repo.addProduct({ "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1" });
	assert(repo.len() == 1);

	auto products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");

	repo.addProduct({ "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2" });
	assert(repo.len() == 2);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");

	repo.addProduct({ "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3" });
	assert(repo.len() == 3);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");

	try {
		repo.addProduct({ "Nume produs 1", "Tip produs 4", 10, "Producator produs 1" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}
	assert(repo.len() == 3);

	try {
		repo.addProduct({ "Nume produs 2", "Tip produs 4", 13.683, "Producator produs 2" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}
	assert(repo.len() == 3);

	try {
		repo.addProduct({ "Nume produs 3", "Tip produs 3", 99.9999, "Producator produs 3" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}
	assert(repo.len() == 3);

	try {
		repo.addProduct({ "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}
	assert(repo.len() == 3);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");

	repo.addProduct({ "Nume produs 1", "Tip produs 4", 21.4, "Producator produs 4" });
	assert(repo.len() == 4);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 1", "Tip produs 4", 21.4, "Producator produs 4");

	repo.addProduct({ "Nume produs 5", "Tip produs 5", 3.98, "Producator produs 2" });
	assert(repo.len() == 5);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 1", "Tip produs 4", 21.4, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3.98, "Producator produs 2");

	repo.addProduct({ "Nume produs 3", "Tip produs 3", 0.75914, "Producator produs 6" });
	assert(repo.len() == 6);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 1", "Tip produs 4", 21.4, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3.98, "Producator produs 2");
	testFunction(products.at(5), "Nume produs 3", "Tip produs 3", 0.75914, "Producator produs 6");
}

void TestingRepo::runTestsRepoDeleteProduct() const
{
	RepoProducts repo;
	assert(repo.len() == 0);

	repo.addProduct(Product{ "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1" });
	repo.addProduct(Product{ "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2" });
	repo.addProduct(Product{ "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3" });
	repo.addProduct(Product{ "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4" });
	repo.addProduct(Product{ "Nume produs 5", "Tip produs 5", 3, "Producator produs 5" });
	assert(repo.len() == 5);

	try {
		repo.deleteProduct("Nume produs 1", "Producator produs 2");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	try {
		repo.deleteProduct("Nume produs 4", "Producator produs 2");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	auto products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	repo.deleteProduct("Nume produs 1", "Producator produs 1");
	assert(repo.len() == 4);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(1), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(2), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");
	testFunction(products.at(3), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	try {
		repo.deleteProduct("Nume produs 1", "Producator produs 1");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 4);

	repo.deleteProduct("Nume produs 5", "Producator produs 5");
	assert(repo.len() == 3);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(1), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(2), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");

	try {
		repo.deleteProduct("Nume produs 5", "Producator produs 5");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 3);

	repo.deleteProduct("Nume produs 3", "Producator produs 3");
	assert(repo.len() == 2);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(1), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");

	try {
		repo.deleteProduct("Nume produs 3", "Producator produs 3");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 2);

	repo.deleteProduct("Nume produs 2", "Producator produs 2");
	assert(repo.len() == 1);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");

	try {
		repo.deleteProduct("Nume produs 2", "Producator produs 2");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 1);

	repo.deleteProduct("Nume produs 4", "Producator produs 4");
	assert(repo.len() == 0);

	try {
		repo.deleteProduct("Nume produs 4", "Producator produs 4");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	assert(repo.len() == 0);

	try {
		repo.deleteProduct("Nume produs 1", "Producator produs 1");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	assert(repo.len() == 0);

	try {
		repo.deleteProduct("Nume produs 2", "Producator produs 2");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	assert(repo.len() == 0);

	try {
		repo.deleteProduct("Nume produs 3", "Producator produs 3");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	assert(repo.len() == 0);

	try {
		repo.deleteProduct("Nume produs 5", "Producator produs 5");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
	assert(repo.len() == 0);

	try {
		products = repo.getAll();
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
}

void TestingRepo::runTestsRepoModifyProduct() const
{
	RepoProducts repo;
	assert(repo.len() == 0);

	try {
		repo.modifyProduct(Product{ "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	repo.addProduct(Product{ "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1" });
	repo.addProduct(Product{ "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2" });
	repo.addProduct(Product{ "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3" });
	repo.addProduct(Product{ "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4" });
	repo.addProduct(Product{ "Nume produs 5", "Tip produs 5", 3, "Producator produs 5" });
	assert(repo.len() == 5);

	try {
		repo.modifyProduct({ "Nume produs 1", "Tip produs 1 nou", 83, "Producator produs 2" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	try {
		repo.modifyProduct({ "Nume produs 3", "Tip produs 2", 178.64, "Producator produs 4" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	try {
		repo.modifyProduct({ "Nume produs 5", "Tip produs 5", 7.351, "Producator produs 3" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	auto products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	repo.modifyProduct({ "Nume produs 1", "Tip produs 1 nou", 69.69, "Producator produs 1" });
	assert(repo.len() == 5);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1 nou", 69.69, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	repo.modifyProduct({ "Nume produs 3", "ABCDEFG", 0.57, "Producator produs 3" });
	assert(repo.len() == 5);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1 nou", 69.69, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "ABCDEFG", 0.57, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	repo.modifyProduct({ "Nume produs 4", "xyz", 34.1, "Producator produs 4" });
	assert(repo.len() == 5);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "Tip produs 1 nou", 69.69, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "ABCDEFG", 0.57, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "xyz", 34.1, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	repo.modifyProduct({ "Nume produs 1", "xyz", 34.1, "Producator produs 1" });
	assert(repo.len() == 5);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "xyz", 34.1, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "ABCDEFG", 0.57, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "xyz", 34.1, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	repo.modifyProduct({ "Nume produs 5", "abcdefghijk", 27.819325, "Producator produs 5" });
	assert(repo.len() == 5);

	products = repo.getAll();
	testFunction(products.at(0), "Nume produs 1", "xyz", 34.1, "Producator produs 1");
	testFunction(products.at(1), "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
	testFunction(products.at(2), "Nume produs 3", "ABCDEFG", 0.57, "Producator produs 3");
	testFunction(products.at(3), "Nume produs 4", "xyz", 34.1, "Producator produs 4");
	testFunction(products.at(4), "Nume produs 5", "abcdefghijk", 27.819325, "Producator produs 5");
}

void TestingRepo::runTestsRepoSearchProduct() const
{
	RepoProducts repo;
	assert(repo.len() == 0);

	try {
		repo.searchProduct("Nume produs 1", "Producator produs 1");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	repo.addProduct(Product{ "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1" });
	repo.addProduct(Product{ "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2" });
	repo.addProduct(Product{ "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3" });
	repo.addProduct(Product{ "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4" });
	repo.addProduct(Product{ "Nume produs 5", "Tip produs 5", 3, "Producator produs 5" });
	assert(repo.len() == 5);

	try {
		repo.searchProduct("Nume produs 2", "Producator produs 1");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	try {
		repo.searchProduct("Nume produs 3", "Producator produs 4");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	try {
		repo.searchProduct("Nume produs 1", "Producator produs 5");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	try {
		repo.searchProduct("Nume produs 4", "Producator produs 2");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}
	assert(repo.len() == 5);

	auto prod = repo.searchProduct("Nume produs 4", "Producator produs 4");
	assert(repo.len() == 5);
	testFunction(prod, "Nume produs 4", "Tip produs 4", 10.8714, "Producator produs 4");

	prod = repo.searchProduct("Nume produs 1", "Producator produs 1");
	assert(repo.len() == 5);
	testFunction(prod, "Nume produs 1", "Tip produs 1", 5.14, "Producator produs 1");

	prod = repo.searchProduct("Nume produs 3", "Producator produs 3");
	assert(repo.len() == 5);
	testFunction(prod, "Nume produs 3", "Tip produs 3", 7.9, "Producator produs 3");

	prod = repo.searchProduct("Nume produs 5", "Producator produs 5");
	assert(repo.len() == 5);
	testFunction(prod, "Nume produs 5", "Tip produs 5", 3, "Producator produs 5");

	prod = repo.searchProduct("Nume produs 2", "Producator produs 2");
	assert(repo.len() == 5);
	testFunction(prod, "Nume produs 2", "Tip produs 2", 13.683, "Producator produs 2");
}

void TestingRepo::runTestsRepo() const
{
	runTestsRepoAddProduct();
	runTestsRepoDeleteProduct();
	runTestsRepoModifyProduct();
	runTestsRepoSearchProduct();
}