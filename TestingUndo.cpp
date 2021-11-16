#include "TestingUndo.h"
#include "Repository.h"
#include "Product.h"

#include <cassert> // #include <assert.h>
#include <cmath>   // #include <math.h>

void TestingUndo::cmpDouble(const double& a, const double& b) const noexcept
{
	assert(fabs(a - b) < 1e-12);
}

void TestingUndo::testFunction(const Product& product_1, const Product& product_2) const noexcept
{
	assert(product_1.getName() == product_2.getName());
	assert(product_1.getType() == product_2.getType());
	cmpDouble(product_1.getPrice(), product_2.getPrice());
	assert(product_1.getProducer() == product_2.getProducer());
}

void TestingUndo::runTestsUndoAdauga() const
{
	RepoProducts repo;
	Product product_1{"x", "y", 4.73, "z"};
	Product product_2{ "a", "b", 16.361, "c" };
	Product product_3{ "d", "e", 8.3, "f" };

	assert(repo.len() == 0);

	repo.addProduct(product_1);
	assert(repo.len() == 1);
	testFunction(repo.getAll().at(0), product_1);

	repo.addProduct(product_2);
	assert(repo.len() == 2);
	testFunction(repo.getAll().at(0), product_1);
	testFunction(repo.getAll().at(1), product_2);

	repo.addProduct(product_3);
	assert(repo.len() == 3);
	testFunction(repo.getAll().at(0), product_1);
	testFunction(repo.getAll().at(1), product_2);
	testFunction(repo.getAll().at(2), product_3);

	UndoAdauga undo_adauga_2{repo, product_2};
	undo_adauga_2.doUndo();
	assert(repo.len() == 2);
	testFunction(repo.getAll().at(0), product_1);
	testFunction(repo.getAll().at(1), product_3);

	UndoAdauga undo_adauga_1{ repo, product_1 };
	undo_adauga_1.doUndo();
	assert(repo.len() == 1);
	testFunction(repo.getAll().at(0), product_3);

	UndoAdauga undo_adauga_3{ repo, product_3 };
	undo_adauga_3.doUndo();
	assert(repo.len() == 0);
}

void TestingUndo::runTestsUndoSterge() const
{
	RepoProducts repo;
	Product product_1{ "nume produs 1", "tip produs 1", 7.423, "producator 1" };
	Product product_2{ "nume produs 2", "tip produs 2", 0.40530123, "producator 2" };
	Product product_3{ "nume produs 3", "tip produs 3", 10, "producator 3" };

	assert(repo.len() == 0);

	UndoSterge undo_sterge_3{ repo, product_3 };
	undo_sterge_3.doUndo();
	assert(repo.len() == 1);
	testFunction(repo.getAll().at(0), product_3);

	UndoSterge undo_sterge_2{ repo, product_2 };
	undo_sterge_2.doUndo();
	assert(repo.len() == 2);
	testFunction(repo.getAll().at(0), product_3);
	testFunction(repo.getAll().at(1), product_2);

	UndoSterge undo_sterge_1{ repo, product_1 };
	undo_sterge_1.doUndo();
	assert(repo.len() == 3);
	testFunction(repo.getAll().at(0), product_3);
	testFunction(repo.getAll().at(1), product_2);
	testFunction(repo.getAll().at(2), product_1);
}

void TestingUndo::runTestsUndoModifica() const
{
	RepoProducts repo;
	Product product_1{ "pasta de dinti", "produse de igiena personala", 5.32, "Colgate" };
	Product product_2{ "chipsuri", "snacksuri", 3.605, "Lays" };
	Product product_3{ "boia", "condimente/conservanti", 7.6, "Delikat" };
	Product product_4{ "chipsuri", "snacksuri", 9.41, "Chio" };

	assert(repo.len() == 0);

	repo.addProduct(product_3), assert(repo.len() == 1), testFunction(repo.getAll().at(0), product_3);
	repo.addProduct(product_2), assert(repo.len() == 2), testFunction(repo.getAll().at(1), product_2);
	repo.addProduct(product_4), assert(repo.len() == 3), testFunction(repo.getAll().at(2), product_4);
	repo.addProduct(product_1), assert(repo.len() == 4), testFunction(repo.getAll().at(3), product_1);

	testFunction(repo.getAll().at(0), product_3);
	testFunction(repo.getAll().at(1), product_2);
	testFunction(repo.getAll().at(2), product_4);
	testFunction(repo.getAll().at(3), product_1);

	Product new_product_1{ "pasta de dinti", "igiena orala", 17.652, "Colgate" };
	Product new_product_2{ "chipsuri", "produse de rontait", 8, "Lays" };
	Product new_product_3{ "boia", "prafuri magice", 3.51, "Delikat" };
	Product new_product_4{ "chipsuri", "alimente", 0.56, "Chio" };

	UndoModifica undo_modifica_2{ repo, new_product_2 };
	undo_modifica_2.doUndo();
	testFunction(repo.getAll().at(0), product_3);
	testFunction(repo.getAll().at(1), new_product_2);
	testFunction(repo.getAll().at(2), product_4);
	testFunction(repo.getAll().at(3), product_1);

	UndoModifica undo_modifica_1{ repo, new_product_1 };
	undo_modifica_1.doUndo();
	testFunction(repo.getAll().at(0), product_3);
	testFunction(repo.getAll().at(1), new_product_2);
	testFunction(repo.getAll().at(2), product_4);
	testFunction(repo.getAll().at(3), new_product_1);

	UndoModifica undo_modifica_4{ repo, new_product_4 };
	undo_modifica_4.doUndo();
	testFunction(repo.getAll().at(0), product_3);
	testFunction(repo.getAll().at(1), new_product_2);
	testFunction(repo.getAll().at(2), new_product_4);
	testFunction(repo.getAll().at(3), new_product_1);

	UndoModifica undo_modifica_3{ repo, new_product_3 };
	undo_modifica_3.doUndo();
	testFunction(repo.getAll().at(0), new_product_3);
	testFunction(repo.getAll().at(1), new_product_2);
	testFunction(repo.getAll().at(2), new_product_4);
	testFunction(repo.getAll().at(3), new_product_1);
}

void TestingUndo::runTestsUndo() const
{
	runTestsUndoAdauga();
	runTestsUndoSterge();
	runTestsUndoModifica();
}
