#include "TestingExceptionRepo.h"
#include "ExceptionRepo.h"
#include "RepoException.h"

#include <cassert> // #include <assert.h>
#include <cmath>   // #include <math.h>
#include <exception>
#include <cstring> // #include <string.h>

using std::exception;

void TestingExceptionRepo::testFunction(const Product& p, const Product& ot) const noexcept
{
	assert(p.getName() == ot.getName());
	assert(p.getType() == ot.getType());
	assert(fabs(p.getPrice() - ot.getPrice()) < 1e-12);
	assert(p.getProducer() == ot.getProducer());
}

void TestingExceptionRepo::runTestsRepoLen() const
{
	ExceptionRepo ex_repo{ 1 };

	try {
		ex_repo.len();
		assert(false);
	}
	catch (const exception& ex) {
		const char* msg = "[!]Exception!\n";
		assert(!strcmp(ex.what(), msg));
	}

	ExceptionRepo repo{ 0 };

	assert(repo.len() == 0); // assert(!repo.len());
}

void TestingExceptionRepo::runTestsRepoGetAll() const
{
	ExceptionRepo ex_repo{ 1 };

	try {
		ex_repo.getAll();
		assert(false);
	}
	catch (const exception& ex) {
		const char* msg = "[!]Exception!\n";
		assert(!strcmp(ex.what(), msg));
	}

	ExceptionRepo repo{ 0 };

	try {
		repo.getAll();
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
}

void TestingExceptionRepo::runTestsRepoAddProduct() const
{
	ExceptionRepo ex_repo{ 1 };

	try {
		ex_repo.addProduct(Product{ "nume produs", "tip produs", 0.50185303, "producator" });
		assert(false);
	}
	catch (const exception& ex) {
		const char* msg = "[!]Exception!\n";
		assert(!strcmp(ex.what(), msg));
	}

	ExceptionRepo repo{ 0 };

	const Product product_1{ "pasta de dinti", "produse de igiena personala", 5.731, "Colgate" };

	repo.addProduct(product_1);

	assert(repo.len() == 1);
	testFunction(repo.getAll().at(0), product_1);

	try {
		repo.addProduct(product_1);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}
	
	const Product product_2{ "pasta de dinti", "produse de igiena personala", 0.57, "Sensodyne" };

	repo.addProduct(product_2);

	assert(repo.len() == 2);
	auto list{ repo.getAll() };
	assert(list.size() == 2);
	testFunction(list.at(0), product_1);
	testFunction(list.at(1), product_2);

	const Product product_3{ "boia", "condimente", 16, "Maggi" };

	repo.addProduct(product_3);

	assert(repo.len() == 3);
	list = repo.getAll();
	assert(list.size() == 3);
	testFunction(list.at(0), product_3);
	testFunction(list.at(1), product_1);
	testFunction(list.at(2), product_2);

	const Product product_4{ "boia", "condimente", 8.491, "Delikat" };

	repo.addProduct(product_4);

	assert(repo.len() == 4);
	list = repo.getAll();
	assert(list.size() == 4);
	testFunction(list.at(0), product_4);
	testFunction(list.at(1), product_3);
	testFunction(list.at(2), product_1);
	testFunction(list.at(3), product_2);

	const Product product_5{ "chipsuri", "snacksuri", 4.16, "Lays" };

	repo.addProduct(product_5);

	assert(repo.len() == 5);
	list = repo.getAll();
	assert(list.size() == 5);
	testFunction(list.at(0), product_4);
	testFunction(list.at(1), product_3);
	testFunction(list.at(2), product_5);
	testFunction(list.at(3), product_1);
	testFunction(list.at(4), product_2);

	const Product product_6{ "chipsuri", "produse de rontait", 1.79, "Pringles" };

	repo.addProduct(product_6);

	assert(repo.len() == 6);
	list = repo.getAll();
	assert(list.size() == 6);
	testFunction(list.at(0), product_4);
	testFunction(list.at(1), product_3);
	testFunction(list.at(2), product_5);
	testFunction(list.at(3), product_6);
	testFunction(list.at(4), product_1);
	testFunction(list.at(5), product_2);

	const Product product_7{ "chipsuri", "snacksuri", 6.8, "Chio Chips" };

	repo.addProduct(product_7);

	assert(repo.len() == 7);
	list = repo.getAll();
	assert(list.size() == 7);
	testFunction(list.at(0), product_4);
	testFunction(list.at(1), product_3);
	testFunction(list.at(2), product_7);
	testFunction(list.at(3), product_5);
	testFunction(list.at(4), product_6);
	testFunction(list.at(5), product_1);
	testFunction(list.at(6), product_2);

	const Product product_8{ "apa de gura", "igiena", 0.6803, "Colgate" };

	repo.addProduct(product_8);

	assert(repo.len() == 8);
	list = repo.getAll();
	assert(list.size() == 8);
	testFunction(list.at(0), product_8);
	testFunction(list.at(1), product_4);
	testFunction(list.at(2), product_3);
	testFunction(list.at(3), product_7);
	testFunction(list.at(4), product_5);
	testFunction(list.at(5), product_6);
	testFunction(list.at(6), product_1);
	testFunction(list.at(7), product_2);

	const Product product_9{ "tuica", "alcool", 5.361, "Bucovina" };

	repo.addProduct(product_9);

	assert(repo.len() == 9);
	list = repo.getAll();
	assert(list.size() == 9);
	testFunction(list.at(0), product_8);
	testFunction(list.at(1), product_4);
	testFunction(list.at(2), product_3);
	testFunction(list.at(3), product_7);
	testFunction(list.at(4), product_5);
	testFunction(list.at(5), product_6);
	testFunction(list.at(6), product_1);
	testFunction(list.at(7), product_2);
	testFunction(list.at(8), product_9);

	try {
		repo.addProduct(product_1);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_2);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_3);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_4);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_5);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_6);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_7);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_8);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	try {
		repo.addProduct(product_9);
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs deja existent!\n");
	}

	assert(repo.len() == 9);
	list = repo.getAll();
	assert(list.size() == 9);

	repo.deleteProduct(product_7.getName(), product_7.getProducer());

	assert(repo.len() == 8);
	list = repo.getAll();
	assert(list.size() == 8);

	repo.deleteProduct(product_2.getName(), product_2.getProducer());

	assert(repo.len() == 7);
	list = repo.getAll();
	assert(list.size() == 7);

	repo.deleteProduct(product_4.getName(), product_4.getProducer());

	assert(repo.len() == 6);
	list = repo.getAll();
	assert(list.size() == 6);

	repo.deleteProduct(product_9.getName(), product_9.getProducer());

	assert(repo.len() == 5);
	list = repo.getAll();
	assert(list.size() == 5);

	repo.addProduct(product_2);

	assert(repo.len() == 6);
	list = repo.getAll();
	assert(list.size() == 6);

	repo.addProduct(product_4);

	assert(repo.len() == 7);
	list = repo.getAll();
	assert(list.size() == 7);

	repo.addProduct(product_7);

	assert(repo.len() == 8);
	list = repo.getAll();
	assert(list.size() == 8);

	repo.addProduct(product_9);

	assert(repo.len() == 9);
	list = repo.getAll();
	assert(list.size() == 9);
}

void TestingExceptionRepo::runTestsRepoDeleteProduct() const
{
	ExceptionRepo ex_repo{ 1 };

	try {
		ex_repo.deleteProduct("nume produs", "producator");
		assert(false);
	}
	catch (const exception& ex) {
		const char* msg = "[!]Exception!\n";
		assert(!strcmp(ex.what(), msg));
	}

	ExceptionRepo repo{ 0 };

	const Product prod_1{ "ton in ulei", "alimente din peste", 0.573, "Rio Mare" };
	const Product prod_2{ "chipsuri", "snacks", 4, "Lays" };
	const Product prod_3{ "chipsuri", "snacks", 9.231, "Chio" };
	const Product prod_4{ "sardine", "alimente din peste", 6.1, "Rio Mare" };
	const Product prod_5{ "chipsuri", "snacks", 5.32, "Pringles" };

	try {
		repo.deleteProduct(prod_1.getName(), prod_1.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.deleteProduct(prod_2.getName(), prod_2.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.deleteProduct(prod_3.getName(), prod_3.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.deleteProduct(prod_4.getName(), prod_4.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.deleteProduct(prod_5.getName(), prod_5.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	repo.addProduct(prod_1);
	repo.addProduct(prod_2);
	repo.addProduct(prod_3);
	repo.addProduct(prod_4);
	repo.addProduct(prod_5);

	assert(repo.len() == 5);
	auto list{ repo.getAll() };
	assert(list.size() == 5);

	testFunction(list.at(0), prod_3);
	testFunction(list.at(1), prod_2);
	testFunction(list.at(2), prod_5);
	testFunction(list.at(3), prod_4);
	testFunction(list.at(4), prod_1);

	try {
		repo.deleteProduct("ton in ulei", "Rio");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	try {
		repo.deleteProduct("chipsuri", "Chio Chips");
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	repo.deleteProduct(prod_2.getName(), prod_2.getProducer());

	assert(repo.len() == 4);
	list = repo.getAll();
	assert(list.size() == 4);

	testFunction(list.at(0), prod_3);
	testFunction(list.at(1), prod_5);
	testFunction(list.at(2), prod_4);
	testFunction(list.at(3), prod_1);

	repo.deleteProduct(prod_3.getName(), prod_3.getProducer());

	assert(repo.len() == 3);
	list = repo.getAll();
	assert(list.size() == 3);

	testFunction(list.at(0), prod_5);
	testFunction(list.at(1), prod_4);
	testFunction(list.at(2), prod_1);

	repo.deleteProduct(prod_1.getName(), prod_1.getProducer());

	assert(repo.len() == 2);
	list = repo.getAll();
	assert(list.size() == 2);

	testFunction(list.at(0), prod_5);
	testFunction(list.at(1), prod_4);

	repo.deleteProduct(prod_5.getName(), prod_5.getProducer());

	assert(repo.len() == 1);
	list = repo.getAll();
	assert(list.size() == 1);

	testFunction(list.at(0), prod_4);

	repo.addProduct(prod_1);

	assert(repo.len() == 2);
	list = repo.getAll();
	assert(list.size() == 2);

	testFunction(list.at(0), prod_4);
	testFunction(list.at(1), prod_1);

	repo.addProduct(prod_3);

	assert(repo.len() == 3);
	list = repo.getAll();
	assert(list.size() == 3);

	testFunction(list.at(0), prod_3);
	testFunction(list.at(1), prod_4);
	testFunction(list.at(2), prod_1);

	repo.deleteProduct(prod_4.getName(), prod_4.getProducer());

	assert(repo.len() == 2);
	list = repo.getAll();
	assert(list.size() == 2);

	testFunction(list.at(0), prod_3);
	testFunction(list.at(1), prod_1);

	repo.deleteProduct(prod_1.getName(), prod_1.getProducer());

	assert(repo.len() == 1);
	list = repo.getAll();
	assert(list.size() == 1);

	testFunction(list.at(0), prod_3);

	repo.deleteProduct(prod_3.getName(), prod_3.getProducer());

	assert(repo.len() == 0);
	
	try {
		repo.getAll();
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}
}

void TestingExceptionRepo::runTestsRepoModifyProduct() const
{
	ExceptionRepo ex_repo{ 1 };

	try {
		ex_repo.modifyProduct(Product{ "nume produs", "tip nou produs", 6.841, "producator" });
		assert(false);
	}
	catch (const exception& ex) {
		const char* msg = "[!]Exception!\n";
		assert(!strcmp(ex.what(), msg));
	}

	ExceptionRepo repo{ 0 };

	try {
		repo.modifyProduct(Product{ "lapte de vaca", "produse lactate", 11.472, "Fulga" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	const Product prod_1{ "crema de maini", "ingrijire", 5.843, "Nivea" };
	const Product prod_2{ "crema de maini", "produse de ingrijire personala", 21.5, "Dove" };
	const Product prod_3{ "lapte de vaca", "lactate", 9.6, "Fulga" };
	const Product prod_4{ "acadele", "dulciuri", 13.78, "Joe" };
	const Product prod_5{ "lapte de vaca", "produse lactate", 6.36105, "Napolact" };
	const Product prod_6{ "crema de maini", "ingrijire", 3, "Neutrogena" };

	repo.addProduct(prod_1);
	repo.addProduct(prod_2);
	repo.addProduct(prod_3);
	repo.addProduct(prod_4);
	repo.addProduct(prod_5);
	repo.addProduct(prod_6);

	assert(repo.len() == 6);
	auto list{ repo.getAll() };
	assert(list.size() == 6);

	testFunction(list.at(0), prod_4);
	testFunction(list.at(1), prod_2);
	testFunction(list.at(2), prod_6);
	testFunction(list.at(3), prod_1);
	testFunction(list.at(4), prod_3);
	testFunction(list.at(5), prod_5);

	try {
		repo.modifyProduct(Product{ "lapte", "produse lactate", 11.472, "Fulga" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	try {
		repo.modifyProduct(Product{ "lapte de vaca", "produse din lapte", 5.23, "Lapte Napolact" });
		assert(false);
	}
	catch (const RepoException& re) {
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	const Product new_prod_2{ "crema de maini", "creme naturale", 7.241, "Dove" };
	const Product new_prod_4{ "acadele", "produse dulci", 9.5, "Joe" };
	const Product new_prod_3{ "lapte de vaca", "produse lactate", 1.5306, "Fulga" };

	repo.modifyProduct(new_prod_2);
	repo.modifyProduct(new_prod_4);
	repo.modifyProduct(new_prod_3);

	assert(repo.len() == 6);
	list = repo.getAll();
	assert(list.size() == 6);

	testFunction(list.at(0), new_prod_4);
	testFunction(list.at(1), new_prod_2);
	testFunction(list.at(2), prod_6);
	testFunction(list.at(3), prod_1);
	testFunction(list.at(4), new_prod_3);
	testFunction(list.at(5), prod_5);
}

void TestingExceptionRepo::runTestsRepoSearchProduct() const
{
	ExceptionRepo ex_repo{ 1 };

	try {
		ex_repo.searchProduct("nume produs", "producator");
		assert(false);
	}
	catch (const exception& ex) {
		const char* msg = "[!]Exception!\n";
		assert(!strcmp(ex.what(), msg));
	}
	
	ExceptionRepo repo{ 0 };

	const Product prod_1{ "crema de maini", "ingrijire", 5.843, "Nivea" };
	const Product prod_2{ "lapte de vaca", "lactate", 9.6, "Fulga" };
	const Product prod_3{ "acadele", "dulciuri", 13.78, "Joe" };
	const Product prod_4{ "crema de maini", "produse de ingrijire personala", 21.5, "Dove" };
	const Product prod_5{ "crema de maini", "ingrijire", 3, "Neutrogena" };
	const Product prod_6{ "lapte de vaca", "produse lactate", 6.36105, "Napolact" };

	try {
		repo.searchProduct(prod_1.getName(), prod_1.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.searchProduct(prod_2.getName(), prod_2.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.searchProduct(prod_3.getName(), prod_3.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.searchProduct(prod_4.getName(), prod_4.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.searchProduct(prod_5.getName(), prod_5.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	try {
		repo.searchProduct(prod_6.getName(), prod_6.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Nu exista produse in magazin!\n");
	}

	repo.addProduct(prod_1);
	repo.addProduct(prod_2);
	repo.addProduct(prod_3);
	repo.addProduct(prod_4);
	repo.addProduct(prod_5);
	repo.addProduct(prod_6);

	auto searched_prod{ repo.searchProduct(prod_1.getName(), prod_1.getProducer()) };
	testFunction(searched_prod, prod_1);

	searched_prod = repo.searchProduct(prod_2.getName(), prod_2.getProducer());
	testFunction(searched_prod, prod_2);

	searched_prod = repo.searchProduct(prod_3.getName(), prod_3.getProducer());
	testFunction(searched_prod, prod_3);

	searched_prod = repo.searchProduct(prod_4.getName(), prod_4.getProducer());
	testFunction(searched_prod, prod_4);

	searched_prod = repo.searchProduct(prod_5.getName(), prod_5.getProducer());
	testFunction(searched_prod, prod_5);

	searched_prod = repo.searchProduct(prod_6.getName(), prod_6.getProducer());
	testFunction(searched_prod, prod_6);

	const Product prod_7{ "acadele", "dulciuri", 0.6, "Alfers" };
	const Product prod_8{ "telemea de oaie", "lactate", 4.261, "Olympus" };

	try {
		repo.searchProduct(prod_7.getName(), prod_7.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	try {
		repo.searchProduct(prod_8.getName(), prod_8.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	repo.addProduct(prod_7);
	searched_prod = repo.searchProduct(prod_7.getName(), prod_7.getProducer());
	testFunction(searched_prod, prod_7);

	repo.addProduct(prod_8);
	searched_prod = repo.searchProduct(prod_8.getName(), prod_8.getProducer());
	testFunction(searched_prod, prod_8);

	repo.deleteProduct(prod_3.getName(), prod_3.getProducer());

	try {
		repo.searchProduct(prod_3.getName(), prod_3.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	repo.deleteProduct(prod_1.getName(), prod_1.getProducer());

	try {
		repo.searchProduct(prod_1.getName(), prod_1.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	repo.deleteProduct(prod_4.getName(), prod_4.getProducer());

	try {
		repo.searchProduct(prod_4.getName(), prod_4.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	repo.deleteProduct(prod_7.getName(), prod_7.getProducer());

	try {
		repo.searchProduct(prod_7.getName(), prod_7.getProducer());
		assert(false);
	}
	catch (const RepoException& re)
	{
		assert(re.getMessage() == "[!]Produs inexistent!\n");
	}

	repo.addProduct(prod_3);
	searched_prod = repo.searchProduct(prod_3.getName(), prod_3.getProducer());
	testFunction(searched_prod, prod_3);
}

void TestingExceptionRepo::runTestsExceptionRepo() const
{
	runTestsRepoLen();
	runTestsRepoGetAll();
	runTestsRepoAddProduct();
	runTestsRepoDeleteProduct();
	runTestsRepoModifyProduct();
	runTestsRepoSearchProduct();

	system("CLS");
}