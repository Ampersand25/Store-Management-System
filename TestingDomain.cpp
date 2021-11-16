#include "TestingDomain.h"
#include "Product.h"

#include <cassert> // #include <assert.h>
#include <cmath>   // #include <math.h>

void TestingDomain::runTestsDomainCopyConstructor() const
{
	Product prod{ "chipsuri", "snacksuri", 5.37, "Pringles" };

	assert(prod.getName() == "chipsuri");
	assert(prod.getType() == "snacksuri");
	assert(fabs(prod.getPrice() - 5.37) < 1e-12);
	assert(prod.getProducer() == "Pringles");

	Product copy{ prod };

	assert(copy.getName() == prod.getName());
	assert(copy.getType() == prod.getType());
	assert(fabs(copy.getPrice() - prod.getPrice()) < 1e-12);
	assert(copy.getProducer() == prod.getProducer());

	assert(copy.getName() == "chipsuri");
	assert(copy.getType() == "snacksuri");
	assert(fabs(copy.getPrice() - 5.37) < 1e-12);
	assert(copy.getProducer() == "Pringles");

	Product copy_2{ copy };

	assert(copy_2.getName() == prod.getName());
	assert(copy_2.getType() == prod.getType());
	assert(fabs(copy_2.getPrice() - prod.getPrice()) < 1e-12);
	assert(copy_2.getProducer() == prod.getProducer());

	assert(copy_2.getName() == copy.getName());
	assert(copy_2.getType() == copy.getType());
	assert(fabs(copy_2.getPrice() - copy.getPrice()) < 1e-12);
	assert(copy_2.getProducer() == copy.getProducer());

	assert(copy_2.getName() == "chipsuri");
	assert(copy_2.getType() == "snacksuri");
	assert(fabs(copy_2.getPrice() - 5.37) < 1e-12);
	assert(copy_2.getProducer() == "Pringles");
}

void TestingDomain::runTestsDomainGetters() const
{
	Product p{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };

	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse lactate");
	assert(fabs(p.getPrice() - 6.99) < 1e-12);
	assert(p.getProducer() == "Milka UK");
}

void TestingDomain::runTestsDomainSetters() const
{
	Product p{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };

	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse lactate");
	assert(fabs(p.getPrice() - 6.99) < 1e-12);
	assert(p.getProducer() == "Milka UK");

	p.setType("produse curatenie");
	
	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse curatenie");
	assert(fabs(p.getPrice() - 6.99) < 1e-12);
	assert(p.getProducer() == "Milka UK");

	p.setPrice(25.1375);

	assert(p.getName() == "Milka cu lapte");
	assert(p.getType() == "produse curatenie");
	assert(fabs(p.getPrice() - 25.1375) < 1e-12);
	assert(p.getProducer() == "Milka UK");
}

void TestingDomain::runTestsDomainCmpProducts() const
{
	Product p{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };

	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 25.1375, "Milka UK" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse curatenie", 6.99, "Milka UK" }) == 0);

	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 25.1375, "Milka UK" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Detergent lichid LENOR", "produse lactate", 6.99, "Milka UK" }) == 0);

	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 25.1375, "Milka UK" }) == 1);
	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse curatenie", 6.99, "Milka UK" }) == 1);

	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 25.1375, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 25.1375, "Milka UK" }) == 1);
	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 6.99, "LENOR" }) == 0);
	assert(p.cmpProducts({ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" }) == 1);
}

void TestingDomain::runTestsDomainStrProduct() const
{
	Product p1{ "Milka cu lapte", "produse lactate", 6.99, "Milka UK" };
	assert(p1.strProduct() == "Nume: Milka cu lapte\nTip: produse lactate\nPret: 6.990000\nProducator: Milka UK\n");

	Product p2{ "Detergent lichid LENOR", "produse curatenie", 25.1375, "LENOR" };
	assert(p2.strProduct() == "Nume: Detergent lichid LENOR\nTip: produse curatenie\nPret: 25.137500\nProducator: LENOR\n");

	Product p3{ "Chipsuri Lays cu branza", "produs alimentar", 3.847193, "Lays" };
	assert(p3.strProduct() == "Nume: Chipsuri Lays cu branza\nTip: produs alimentar\nPret: 3.847193\nProducator: Lays\n");

	Product p4{ "Parmezan", "condimente", 132.03813752742, "Broccoli INC" };
	assert(p4.strProduct() == "Nume: Parmezan\nTip: condimente\nPret: 132.038138\nProducator: Broccoli INC\n");
}

void TestingDomain::runTestsLessOperator() const
{
	Product product_1{ "Chipsuri cu smantana", "produse de rontait", 6.73, "Chio" };
	Product product_2{ "Chipsuri cu sare", "snacksuri", 4.61, "Lays" };
	Product product_3{ "Chipsuri cu sare", "produse de rontait", 9, "Lays" };
	Product product_4{ "Chipsuri cu sare", "produse de rontait", 1.68383, "Pringles" };
	Product product_5{ "Chipsuri cu smantana", "snacksuri", 2.68, "Chio" };

	assert(product_1 < product_1 == false);
	assert(product_2 < product_2 == false);
	assert(product_3 < product_3 == false);
	assert(product_4 < product_4 == false);
	assert(product_5 < product_5 == false);

	assert(product_1 < product_2 == false);
	assert(product_2 < product_1 == true);

	assert(product_1 < product_3 == false);
	assert(product_3 < product_1 == true);

	assert(product_1 < product_5 == false);
	assert(product_5 < product_1 == false);

	assert(product_2 < product_3 == false);
	assert(product_3 < product_2 == false);

	assert(product_2 < product_3 == false);
	assert(product_3 < product_2 == false);

	assert(product_2 < product_4 == true);
	assert(product_4 < product_2 == false);

	assert(product_3 < product_4 == true);
	assert(product_4 < product_3 == false);

	Product product_6{ "Pasta de dinti", "igiena orala", 8, "" };
	Product product_7{ "Apa de gura", "igiena personala", 3.5917, "" };
	Product product_8{ "Boia", "condimente", 13.501, "" };

	assert(product_6 < product_6 == false);
	assert(product_7 < product_7 == false);
	assert(product_8 < product_8 == false);

	assert(product_1 < product_1 == false);
	assert(product_1 < product_1 == false);

	assert(product_1 < product_1 == false);
	assert(product_1 < product_1 == false);

	assert(product_6 < product_7 == false);
	assert(product_7 < product_6 == true);

	assert(product_6 < product_8 == false);
	assert(product_8 < product_6 == true);

	assert(product_7 < product_8 == true);
	assert(product_8 < product_7 == false);
}

void TestingDomain::runTestsEqualOperator() const
{
	Product prod_1{ "Pasta de dinti", "igiena orala", 5.731, "Colgate" };
	Product prod_2{ "Pasta de dinti", "igiena", 3.69, "Sensodyne" };
	Product prod_3{ "Periuta de dinti", "igiena personala", 11, "Sensodyne" };
	Product prod_4{ "Pasta de dinti", "ingrijire dentara", 7.3014, "Colgate" };
	Product prod_5{ "Periuta de dinti", "igiena personala", 0.61, "Sensodyne" };

	// Comparam primul produs (prod_1) cu toate produsele

	assert((prod_1 == prod_1) == true);

	assert((prod_1 == prod_2) == false);
	assert((prod_2 == prod_1) == false);

	assert((prod_1 == prod_3) == false);
	assert((prod_3 == prod_1) == false);

	assert((prod_1 == prod_4) == true);
	assert((prod_4 == prod_1) == true);

	assert((prod_1 == prod_5) == false);
	assert((prod_5 == prod_1) == false);

	// Comparam cel de al doilea produs (prod_2) cu toate produsele ramase

	assert((prod_2 == prod_2) == true);

	assert((prod_2 == prod_3) == false);
	assert((prod_3 == prod_2) == false);

	assert((prod_2 == prod_4) == false);
	assert((prod_4 == prod_2) == false);

	assert((prod_2 == prod_5) == false);
	assert((prod_5 == prod_2) == false);

	// Comparam cel de al trilea produs (prod_3) cu toate produsele ramase

	assert((prod_3 == prod_3) == true);

	assert((prod_3 == prod_4) == false);
	assert((prod_4 == prod_3) == false);

	assert((prod_3 == prod_5) == true);
	assert((prod_5 == prod_3) == true);

	// Comparam cel de al patrulea produs (prod_4) cu toate produsele ramase

	assert((prod_4 == prod_4) == true);

	assert((prod_4 == prod_5) == false);
	assert((prod_5 == prod_4) == false);

	// Comparam cel de al cincilea produs (prod_5) cu toate produsele ramase (adica doar cu el)

	assert((prod_5 == prod_5) == true);
}

void TestingDomain::runTestsNotEqualOperator() const
{
	Product product_1{ "boia", "ingrediente mancare", 0.641, "Delikat" };
	Product product_2{ "paprika", "condimente", 13.5, "Delikat" };
	Product product_3{ "paprika", "ingrediente mancare", 9, "Maggi" };
	Product product_4{ "boia", "ingrediente mancare", 1.5803, "Maggi" };
	Product product_5{ "boia", "condimente", 4.63, "Delikat" };
	Product product_6{ "paprika", "condimente", 3.5, "Maggi" };
	Product product_7{ "boia", "condimente", 7.38, "Maggi" };
	Product product_8{ "paprika", "ingrediente mancare", 11.890, "Delikat" };

	// Comparam produsele intre ele

	assert((product_1 != product_1) == false);
	assert((product_2 != product_2) == false);
	assert((product_3 != product_3) == false);
	assert((product_4 != product_4) == false);
	assert((product_5 != product_5) == false);
	assert((product_6 != product_6) == false);
	assert((product_7 != product_7) == false);
	assert((product_8 != product_8) == false);

	// Comparam primul produs (product_1) cu toate

	assert((product_1 != product_2) == true) , assert((product_2 != product_1) == true);
	assert((product_1 != product_3) == true) , assert((product_3 != product_1) == true);
	assert((product_1 != product_4) == true) , assert((product_4 != product_1) == true);
	assert((product_1 != product_5) == false), assert((product_5 != product_1) == false);
	assert((product_1 != product_6) == true) , assert((product_6 != product_1) == true);
	assert((product_1 != product_7) == true) , assert((product_7 != product_1) == true);
	assert((product_1 != product_8) == true) , assert((product_8 != product_1) == true);

	// Comparam al doilea produs (product_2) cu toate ramase

	assert((product_2 != product_3) == true) , assert((product_3 != product_2) == true);
	assert((product_2 != product_4) == true) , assert((product_4 != product_2) == true);
	assert((product_2 != product_5) == true) , assert((product_5 != product_2) == true);
	assert((product_2 != product_6) == true) , assert((product_6 != product_2) == true);
	assert((product_2 != product_7) == true) , assert((product_7 != product_2) == true);
	assert((product_2 != product_8) == false), assert((product_8 != product_2) == false);

	// Comparam al treilea produs (product_3) cu toate ramase

	assert((product_3 != product_4) == true) , assert((product_4 != product_3) == true);
	assert((product_3 != product_5) == true) , assert((product_5 != product_3) == true);
	assert((product_3 != product_6) == false), assert((product_6 != product_3) == false);
	assert((product_3 != product_7) == true) , assert((product_7 != product_3) == true);
	assert((product_3 != product_8) == true) , assert((product_8 != product_3) == true);

	// Comparam al patrulea produs (product_4) cu toate ramase

	assert((product_4 != product_5) == true) , assert((product_5 != product_4) == true);
	assert((product_4 != product_6) == true) , assert((product_6 != product_4) == true);
	assert((product_4 != product_7) == false), assert((product_7 != product_4) == false);
	assert((product_4 != product_8) == true) , assert((product_8 != product_4) == true);

	// Comparam al cincilea produs (product_5) cu toate ramase

	assert((product_5 != product_6) == true), assert((product_6 != product_5) == true);
	assert((product_5 != product_7) == true), assert((product_7 != product_5) == true);
	assert((product_5 != product_8) == true), assert((product_8 != product_5) == true);

	// Comparam al saselea produs (product_6) cu toate ramase

	assert((product_6 != product_7) == true), assert((product_7 != product_6) == true);
	assert((product_6 != product_8) == true), assert((product_8 != product_6) == true);

	// Comparam al saptelea produs (product_7) cu toate ramase (adica doar cu produsul product_8)

	assert((product_7 != product_8) == true), assert((product_8 != product_7) == true);
}

void TestingDomain::runTestsAssignmentOperator() const
{
	Product prod_1{ "abc de fg", "condimente", 4.731, "Delikat" };
	Product prod_2{ "x yz klmnopqrt tu", "produse de igiena personala", 9.52, "Colgate Company" };
	Product prod_3{ "rs tuv wzy", "produse lactate", 1.053, "Milka" };
	Product prod_4{ "kl mno p", "snacksuri", 5, "Chio UK" };

	assert(prod_1.getName() == "abc de fg");
	assert(prod_1.getType() == "condimente");
	assert(fabs(prod_1.getPrice() - 4.731) < 1e-12);
	assert(prod_1.getProducer() == "Delikat");

	assert(prod_2.getName() == "x yz klmnopqrt tu");
	assert(prod_2.getType() == "produse de igiena personala");
	assert(fabs(prod_2.getPrice() - 9.52) < 1e-12);
	assert(prod_2.getProducer() == "Colgate Company");

	assert(prod_3.getName() == "rs tuv wzy");
	assert(prod_3.getType() == "produse lactate");
	assert(fabs(prod_3.getPrice() - 1.053) < 1e-12);
	assert(prod_3.getProducer() == "Milka");

	assert(prod_4.getName() == "kl mno p");
	assert(prod_4.getType() == "snacksuri");
	assert(fabs(prod_4.getPrice() - 5) < 1e-12);
	assert(prod_4.getProducer() == "Chio UK");

	prod_1 = prod_2 = prod_3 = prod_4;

	assert(prod_1.getName() == "kl mno p");
	assert(prod_1.getType() == "snacksuri");
	assert(fabs(prod_1.getPrice() - 5) < 1e-12);
	assert(prod_1.getProducer() == "Chio UK");

	assert(prod_1.getName() == prod_2.getName());
	assert(prod_1.getType() == prod_2.getType());
	assert(fabs(prod_1.getPrice() - prod_2.getPrice()) < 1e-12);
	assert(prod_1.getProducer() == prod_2.getProducer());

	assert(prod_1.getName() == prod_3.getName());
	assert(prod_1.getType() == prod_3.getType());
	assert(fabs(prod_1.getPrice() - prod_3.getPrice()) < 1e-12);
	assert(prod_1.getProducer() == prod_3.getProducer());

	assert(prod_1.getName() == prod_4.getName());
	assert(prod_1.getType() == prod_4.getType());
	assert(fabs(prod_1.getPrice() - prod_4.getPrice()) < 1e-12);
	assert(prod_1.getProducer() == prod_4.getProducer());

	assert(prod_2.getName() == prod_3.getName());
	assert(prod_2.getType() == prod_3.getType());
	assert(fabs(prod_2.getPrice() - prod_3.getPrice()) < 1e-12);
	assert(prod_2.getProducer() == prod_3.getProducer());

	assert(prod_2.getName() == prod_4.getName());
	assert(prod_2.getType() == prod_4.getType());
	assert(fabs(prod_2.getPrice() - prod_4.getPrice()) < 1e-12);
	assert(prod_2.getProducer() == prod_4.getProducer());

	assert(prod_3.getName() == prod_4.getName());
	assert(prod_3.getType() == prod_4.getType());
	assert(fabs(prod_3.getPrice() - prod_4.getPrice()) < 1e-12);
	assert(prod_3.getProducer() == prod_4.getProducer());

	Product prod_5{ "abc", "tip produs", 0.683, "producator" };
	Product prod_6{ "defgh", "tip", 3.3, "prod" };

	assert(prod_5.getName() == "abc");
	assert(prod_5.getType() == "tip produs");
	assert(fabs(prod_5.getPrice() - 0.683) < 1e-12);
	assert(prod_5.getProducer() == "producator");

	assert(prod_6.getName() == "defgh");
	assert(prod_6.getType() == "tip");
	assert(fabs(prod_6.getPrice() - 3.3) < 1e-12);
	assert(prod_6.getProducer() == "prod");

	prod_5 = prod_6;

	assert(prod_5.getName() == "defgh");
	assert(prod_5.getType() == "tip");
	assert(fabs(prod_5.getPrice() - 3.3) < 1e-12);
	assert(prod_5.getProducer() == "prod");

	assert(prod_5.getName() == prod_6.getName());
	assert(prod_5.getType() == prod_6.getType());
	assert(fabs(prod_5.getPrice() - prod_6.getPrice()) < 1e-12);
	assert(prod_5.getProducer() == prod_6.getProducer());
}

void TestingDomain::runTestsDomain() const
{
	runTestsDomainCopyConstructor();
	runTestsDomainGetters();
	runTestsDomainSetters();
	runTestsDomainCmpProducts();
	runTestsDomainStrProduct();
	runTestsLessOperator();
	runTestsEqualOperator();
	runTestsNotEqualOperator();
	runTestsAssignmentOperator();
}