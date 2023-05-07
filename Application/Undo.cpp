#include "Undo.h"

// Clasa UndoAdauga

void UndoAdauga::doUndo()
{
	// operatia inversa adaugarii este stergerea
	// cum produsul (obiectul de clasa Product) a fost adaugat in repository, apeland metoda doUndo il vom sterge/elimina din repo
	repo.deleteProduct(product.getName(), product.getProducer()); // stergem produsul product din repo apeland metoda publica deleteProduct
}

string UndoAdauga::typeUndo()
{
	// s-a facut undo pentru operatia de adaugare (s-a apelat polimorfic metoda doUndo a unui obiect de clasa UndoAdauga)
	return "[+]Undo adaugare realizat cu succes!\n"; // string (mesaj) care sa indice ca undo-ul s-a efectuat pentru adaugare
}

// Clasa UndoModifica

void UndoModifica::doUndo()
{
	// operatia inversa modificarii este tot modificarea
	// cum produsul (obiectul de clasa Product) a fost modificat/actualizat in repository, apeland metoda doUndo il vom aduce la configuratia initiala de dinainte de modificare
	repo.modifyProduct(product); // modificam produsul product in repo apeland metoda publica modifyProduct
}

string UndoModifica::typeUndo()
{
	// s-a facut undo pentru operatia de modificare (s-a apelat polimorfic metoda doUndo a unui obiect de clasa UndoModifica)
	return "[+]Undo modificare realizat cu succes!\n"; // string (mesaj) care sa indice ca undo-ul s-a efectuat pentru modificare
}

// Clasa UndoSterge

void UndoSterge::doUndo()
{
	// operatia inversa stergerii este adaugarea
	// cum produsul (obiectul de clasa Product) a fost sters/eliminat din repository, apeland metoda doUndo il vom re-adauga
	repo.addProduct(product); // adaugam produsul product in repo apeland metoda publica addProduct
}

string UndoSterge::typeUndo()
{
	// s-a facut undo pentru operatia de stergere (s-a apelat polimorfic metoda doUndo a unui obiect de clasa UndoSterge)
	return "[+]Undo stergere realizat cu succes!\n"; // string (mesaj) care sa indice ca undo-ul s-a efectuat pentru stergere
}