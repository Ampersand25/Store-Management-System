#include "Redo.h"

// RedoAdauga
void RedoAdauga::doRedo()
{
	// operatia inversa undo adauga este adaugarea
	// cum produsul (obiectul de clasa Product) a fost sters din repository la operatie de undo adauga/adaugare, apeland metoda doRedo il vom adauga din nou in repo
	repo.addProduct(product); // adaugam produsul product in repo apeland metoda publica addProduct
}

string RedoAdauga::typeRedo() const
{
	// s-a facut redo pentru operatia de undo adaugare (s-a apelat polimorfic metoda doRedo a unui obiect de clasa RedoAdauga)
	return "[+]Redo opeatie undo adaugare realizat cu succes!\n"; // string (mesaj) care sa indice ca operatia de redo s-a efectuat cu succes pentru undo adaugare
}

Product RedoAdauga::getProduct() const
{
	return product; // return this->product;
}

REDO_TYPE RedoAdauga::whatRedo() const
{
	return ADD_TYPE_REDO;
}
// ~RedoAdauga

// RedoModifica
void RedoModifica::doRedo()
{
	// operatia inversa undo modifica este tot modificarea
	// cum produsul (obiectul de clasa Product) a fost modificat/actualizat in repository, apeland metoda doRedo il vom aduce la configuratia initiala de dinainte de undo
	repo.modifyProduct(product); // modificam produsul product in repo apeland metoda publica modifyProduct
}

string RedoModifica::typeRedo() const
{
	// s-a facut redo pentru operatia de undo modificare (s-a apelat polimorfic metoda doRedo a unui obiect de clasa RedoModifica)
	return "[+]Redo opeatie undo modificare realizat cu succes!\n"; // string (mesaj) care sa indice ca operatia de redo s-a efectuat cu succes pentru undo modificare
}

Product RedoModifica::getProduct() const
{
	return product; // return this->product;
}

REDO_TYPE RedoModifica::whatRedo() const
{
	return UPDATE_TYPE_REDO;
}
// ~RedoModifica

// RedoSterge
void RedoSterge::doRedo()
{
	// operatia inversa undo sterge este stergerea
	// cum produsul (obiectul de clasa Product) a fost adaugat in repository la operatie de undo sterge/stergere, apeland metoda doRedo il vom sterge din nou din repo
	repo.deleteProduct(product.getName(), product.getProducer()); // stergem/eliminam produsul product din repo apeland metoda publica deleteProduct
}

string RedoSterge::typeRedo() const
{
	// s-a facut redo pentru operatia de undo stergere (s-a apelat polimorfic metoda doRedo a unui obiect de clasa RedoSterge)
	return "[+]Redo opeatie undo stergere realizat cu succes!\n"; // string (mesaj) care sa indice ca operatia de redo s-a efectuat cu succes pentru undo stergere
}

Product RedoSterge::getProduct() const
{
	return product; // return this->product;
}

REDO_TYPE RedoSterge::whatRedo() const
{
	return REMOVE_TYPE_REDO;
}
// ~RedoSterge