#include "TestingFileRepo.h"
#include "FileRepository.h"

#include <cassert> // #include <assert.h>
// pentru assert
#include <cmath>   // #include <math.h>
				   // pentru fabs (float absolute)
#include <fstream> // pentru std::ifstream si std::ofstream

using std::ifstream;
using std::ofstream;

void TestingFileRepo::testFunction(const Product& p, const string& name, const string& type, const double& price, const string& producer) const noexcept
{
	assert(p.getName() == name);
	assert(p.getType() == type);
	assert(fabs(p.getPrice() - price) < 1e-12);
	assert(p.getProducer() == producer);
}

void TestingFileRepo::runTestsLoadFromFile() const
{
	FileRepoProducts empty_repo{ "empty" };

	assert(empty_repo.len() == 0);

	const string path{ ".\\Fisiere text - repo\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + "testare" + extension };

	ofstream out;

	out.open(full_filename);
	out << "a|b|3.56|c\n";
	out << "x|y|8.4014|z\n";
	out << "d|e|5|f\n";
	out << "k|l|0.6|m\n";
	out.close();

	const FileRepoProducts repo_1{ "testare" };

	assert(repo_1.len() == 4);
	testFunction(repo_1.getAll().at(0), "a", "b", 3.56, "c");
	testFunction(repo_1.getAll().at(1), "x", "y", 8.4014, "z");
	testFunction(repo_1.getAll().at(2), "d", "e", 5, "f");
	testFunction(repo_1.getAll().at(3), "k", "l", 0.6, "m");

	out.open(full_filename);
	out << "pasta de dinti|igiena orala|6.321|Colgate\n";
	out << "chipsuri|snacksuri|4.5|Lays\n";
	out.close();

	const FileRepoProducts repo_2{ "testare" };

	assert(repo_2.len() == 2);
	testFunction(repo_2.getAll().at(0), "pasta de dinti", "igiena orala", 6.321, "Colgate");
	testFunction(repo_2.getAll().at(1), "chipsuri", "snacksuri", 4.5, "Lays");

	out.open(full_filename);
	out.close();

	const FileRepoProducts repo_3{ "testare" };

	assert(repo_3.len() == 0);

	out.open(full_filename);
	out << "boia|condimente/conservanti naturali|7.233053|Delikat\n";
	out.close();

	const FileRepoProducts repo_4{ "testare" };

	assert(repo_4.len() == 1);
	testFunction(repo_4.getAll().at(0), "boia", "condimente/conservanti naturali", 7.233053, "Delikat");

	out.open(full_filename);
	out.close();
}

void TestingFileRepo::runTestsFileRepoAddProduct() const
{
	FileRepoProducts repo{ "testare" };

	assert(repo.len() == 0);

	repo.addProduct(Product{ "a", "b", 5.73, "c" });
	assert(repo.len() == 1);

	repo.addProduct(Product{ "g", "h", 9.146, "i" });
	assert(repo.len() == 2);

	repo.addProduct(Product{ "d", "e", 0.41, "f" });
	assert(repo.len() == 3);

	repo.addProduct(Product{ "x", "y", 5, "z" });
	assert(repo.len() == 4);

	repo.addProduct(Product{ "k", "l", 7.08503, "m" });
	assert(repo.len() == 5);

	const string path{ ".\\Fisiere text - repo\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + "testare" + extension };

	ifstream in(full_filename);

	string line;

	getline(in, line);
	assert(line == "a|b|5.73|c");

	getline(in, line);
	assert(line == "g|h|9.146|i");

	getline(in, line);
	assert(line == "d|e|0.41|f");

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "k|l|7.08503|m");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	ofstream out(full_filename);
	out.close();
}

void TestingFileRepo::runTestsFileRepoDeleteProduct() const
{
	FileRepoProducts repo{ "testare" };

	repo.addProduct(Product{ "a", "b", 5.73, "c" });
	repo.addProduct(Product{ "g", "h", 9.146, "i" });
	repo.addProduct(Product{ "d", "e", 0.41, "f" });
	repo.addProduct(Product{ "x", "y", 5, "z" });
	repo.addProduct(Product{ "k", "l", 7.08503, "m" });

	const string path{ ".\\Fisiere text - repo\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + "testare" + extension };

	string line;

	ifstream in;

	in.open(full_filename);

	getline(in, line);
	assert(line == "a|b|5.73|c");

	getline(in, line);
	assert(line == "g|h|9.146|i");

	getline(in, line);
	assert(line == "d|e|0.41|f");

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "k|l|7.08503|m");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	repo.deleteProduct("g", "i");

	assert(repo.len() == 4);

	in.open(full_filename);

	getline(in, line);
	assert(line == "a|b|5.73|c");

	getline(in, line);
	assert(line == "d|e|0.41|f");

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "k|l|7.08503|m");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	repo.deleteProduct("k", "m");

	assert(repo.len() == 3);

	in.open(full_filename);

	getline(in, line);
	assert(line == "a|b|5.73|c");

	getline(in, line);
	assert(line == "d|e|0.41|f");

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	repo.deleteProduct("d", "f");

	assert(repo.len() == 2);

	in.open(full_filename);

	getline(in, line);
	assert(line == "a|b|5.73|c");

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	repo.deleteProduct("a", "c");

	assert(repo.len() == 1);

	in.open(full_filename);

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	repo.deleteProduct("x", "z");

	assert(repo.len() == 0);

	in.open(full_filename);

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	ofstream out(full_filename);
	out.close();
}

void TestingFileRepo::runTestsFileRepoModifyProduct() const
{
	FileRepoProducts repo{ "testare" };

	repo.addProduct(Product{ "a", "b", 5.73, "c" });
	repo.addProduct(Product{ "g", "h", 9.146, "i" });
	repo.addProduct(Product{ "d", "e", 0.41, "f" });
	repo.addProduct(Product{ "x", "y", 5, "z" });
	repo.addProduct(Product{ "k", "l", 7.08503, "m" });

	const string path{ ".\\Fisiere text - repo\\" };
	const string extension{ ".txt" };
	const string full_filename{ path + "testare" + extension };

	string line;

	ifstream in;

	in.open(full_filename);

	getline(in, line);
	assert(line == "a|b|5.73|c");

	getline(in, line);
	assert(line == "g|h|9.146|i");

	getline(in, line);
	assert(line == "d|e|0.41|f");

	getline(in, line);
	assert(line == "x|y|5|z");

	getline(in, line);
	assert(line == "k|l|7.08503|m");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	repo.modifyProduct(Product{ "d", "condimente pentru mancare", 3, "f" });
	repo.modifyProduct(Product{ "x", "snacksuri", 21.7, "z" });
	repo.modifyProduct(Product{ "k", "produse de frumusete", 9.401, "m" });
	repo.modifyProduct(Product{ "a", "produse de ingrijire personala", 8.345, "c" });
	repo.modifyProduct(Product{ "g", "produse lactate", 31.53, "i" });

	in.open(full_filename);

	getline(in, line);
	assert(line == "a|produse de ingrijire personala|8.345|c");

	getline(in, line);
	assert(line == "g|produse lactate|31.53|i");

	getline(in, line);
	assert(line == "d|condimente pentru mancare|3|f");

	getline(in, line);
	assert(line == "x|snacksuri|21.7|z");

	getline(in, line);
	assert(line == "k|produse de frumusete|9.401|m");

	getline(in, line);
	assert(line == "");

	assert(in.eof());

	in.close();

	ofstream out(full_filename);
	out.close();
}

void TestingFileRepo::runTestsWriteToFile() const
{
	runTestsFileRepoAddProduct();
	runTestsFileRepoDeleteProduct();
	runTestsFileRepoModifyProduct();
}

void TestingFileRepo::runTestsFileRepo() const
{
	runTestsLoadFromFile();
	runTestsWriteToFile();

	remove(".\\Fisiere text - repo\\empty.txt");
	remove(".\\Fisiere text - repo\\testare.txt");

	// remove("C:\\Users\\Admin\\Documents\\VS Projects\\Lab8-9\\1 Magazin\\Fisiere text - repo\\empty.txt");
	// remove("C:\\Users\\Admin\\Documents\\VS Projects\\Lab8-9\\1 Magazin\\Fisiere text - repo\\testare.txt");
}