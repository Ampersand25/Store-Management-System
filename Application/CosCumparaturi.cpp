#include "CosCumparaturi.h"
#include "CosException.h"

#include <random>    // pentru std::random_device, std::mt19937 si std::uniform_int_distribution
#include <fstream>   // pentru std::ofstream

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::ofstream;

// un element din dictionar este o pereche <key, value> (<cheie, valoare>)
// unde: key   (cheie)  : TKey   (Product)  - obiect de clasa Product (entitate)
//       value (valoare): TValue (unsigned) - numarul de aparitii al cheii (obiect de clasa Product) in cosul de cumparaturi
#define key first    // atributul cheie al unui element din dictionar
#define value second // atributul valoare al unui element din dictionar (valoare asocita cheii elementului)

bool CosCumparaturi::cosGol() const noexcept
{
	return !cos.size(); // return cos.empty();

	/*
	if (!cos.size())
		return true;
	return false;
	*/
}

void CosCumparaturi::golesteCos()
{
	if (cosGol()) // if (this->cosGol())
		throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	cos.clear();

	total_price = 0;

	this->notify(); // notify();
}

void CosCumparaturi::adaugaInCos(const string& name, const string& producer)
{
	const auto& products{ repo.getAll() };

	const auto& p = find_if(products.begin(),
		products.end(),
		[&name, &producer](const Product& product) noexcept {return product.getName() == name && product.getProducer() == producer; });

	if (p == products.end())
		throw CosException("[!]Produsul cautat nu se afla in stoc!\n");

	const auto& prod{ *p };

	bool found{ false };

	for (const auto& elem : cos)
	{
		if (elem.key == prod)
		{
			++cos[elem.key];
			found = true;

			break;
		}
	}

	if (!found)
		cos[prod] = 1;

	total_price += prod.getPrice();

	this->notify(); // notify();
}

void CosCumparaturi::genereazaCos(unsigned number_of_products)
{
	const auto& products{ repo.getAll() };

	mt19937 mt{ random_device{}() };
	uniform_int_distribution<> dist(0, (int)products.size() - 1);

	for (unsigned i{ 0 }; i < number_of_products; ++i)
	{
		// dist(m) - numar aleator/arbitrar (random) intre [0, size - 1],
		// unde size este numarul de produse (obiecte de clasa Product) din repozitoriu
		const auto& prod{ products.at(dist(mt)) };

		bool found{ false };

		for (const auto& elem : cos)
		{
			if (elem.key == prod)
			{
				++cos[elem.key];
				found = true;

				break;
			}
		}

		if (!found)
			cos[prod] = 1;

		total_price += prod.getPrice();
	}

	if (number_of_products)
		this->notify(); // notify();
}

void CosCumparaturi::exportCosFisierCSV(const string& filename) const
{
	//if (cosGol()) // if (this->cosGol())
	//	throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	const auto path{ ".\\Export cos cumparaturi\\" };        // const string path{ ".\\Export cos cumparaturi\\" };
	const auto extension{ ".csv" };                          // const string extension{ ".csv" };
	const auto full_filename{ path + filename + extension }; // const string full_filename{ path + filename + extension };

	ofstream out{ full_filename }; // ofstream out(full_filename);

	out << "Index,Nume,Tip,Pret,Producator,Cantitate\n"; // de la berlioz10 (aka Dragon Spiridus)

	auto idx{ 0 };

	for (const auto& elem : cos)
	{
		const auto& prod{ elem.key };
		const auto& quantity{ elem.value };

		out << ++idx << ',' <<
			prod.getName() << ',' <<
			prod.getType() << ',' <<
			prod.getPrice() << ',' <<
			prod.getProducer() << ',' <<
			quantity << '\n';
	}

	out.close();
}

void CosCumparaturi::exportCosFisierHTMLOld(const string& filename) const
{
	//if (cosGol()) // if (this->cosGol())
	//	throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	const auto path{ ".\\Export cos cumparaturi\\" };        // const string path{ ".\\Export cos cumparaturi\\" };
	const auto extension{ ".html" };                         // const string extension{ ".html" };
	const auto full_filename{ path + filename + extension }; // const string full_filename{ path + filename + extension };

	ofstream out{ full_filename }; // ofstream out(full_filename);

	/*
	out << "<!DOCTYPE html>\n";
	out << "<html>\n";
	out << "<body>\n";

	out << "\n<h1>Cos de cumparaturi</h1>\n";

	out << "\n<p>\n";

	if (cosGol()) // if (this->cosGol())
		out << "Momentan nu exista produse in cosul de cumparaturi!\n";
	else {
		auto cont{ 0 };

		for (const auto& elem : cos)
		{
			const auto& prod{ elem.key };
			const auto& quantity{ elem.value };

			out << ++cont << ": " <<
			prod.getName() << " | " <<
			prod.getType() << " | " <<
			prod.getPrice() << " | " <<
			prod.getProducer() << " | " <<
			quantity << "<br>";
		}
	}

	out << "</p>\n";

	out << "\n<span style=\"color:blue\">[$]Pret total produse: " << this->getTotal() << "</span>\n";

	out << "</body>\n";
	out << "</html>";

	out.close();
	*/

	out << "<!DOCTYPE html>\n";
	out << "<html lang=\"en\">\n";

	out << "<head>\n";
	out << "<title>Cos produse magazin</title>\n";
	out << "<meta charset=\"utf-8\">\n";
	out << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
	out << "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css\">\n";
	out << "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script>\n";
	out << "<script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js\"></script>\n";
	out << "</head>\n";

	out << "<body>\n";
	out << "<div class=\"cos cumparaturi\">\n";
	out << "<h1><b>Cos de cumparaturi</b></h1>\n";

	if (cosGol()) // if (this->cosGol())
		out << "Momentan nu exista produse in cosul de cumparaturi!\n";
	else {
		out << "<table class=\"table table-bordered\">\n";

		out << "<thead>\n";
		out << "<tr>\n";

		out << "<th style=\"background-color:#E8B5CE;\">#</th>\n";
		out << "<th style=\"background-color:#7FCDCD;\">Nume</th>\n";
		out << "<th style=\"background-color:#BE9EC9;\">Tip</th>\n";
		out << "<th style=\"background-color:#FF6F61;\">Pret</th>\n";
		out << "<th style=\"background-color:#92A8D1;\">Producator</th>\n";
		out << "<th style=\"background-color:#F1EA7F;\">Cantitate</th>\n";

		out << "</tr>\n";
		out << "</thead>\n";

		out << "<tbody>\n";

		auto idx{ 0 };

		for (const auto& elem : cos)
		{
			const auto& prod{ elem.key };
			const auto& quantity{ elem.value };

			out << "<tr>\n"
				<< "<td style=\"background-color:#E8B5CE;\">" << ++idx << "</td>\n"
				<< "<td style=\"background-color:#7FCDCD;\">" << prod.getName() << "</td>\n"
				<< "<td style=\"background-color:#BE9EC9;\">" << prod.getType() << "</td>\n"
				<< "<td style=\"background-color:#FF6F61;\">" << prod.getPrice() << "</td>\n"
				<< "<td style=\"background-color:#92A8D1;\">" << prod.getProducer() << "</td>\n"
				<< "<td style=\"background-color:#F1EA7F;\">" << quantity << "</td>\n"
				<< "</tr>\n";
		}

		out << "</tbody>\n";
		out << "</table>\n";
	}

	out << "</div>\n";

	out << "<h4 style=\"color:green\">[=]Numar total produse cos: " << this->nrProduseCos() << "</h4>\n";
	// out << "<br>";
	out << "<h4 style=\"color:blue\">[$]Pret total produse: " << this->getTotal() << "</h4>\n";

	out << "</body>\n";
	out << "</html>\n";

	out.close();
}

void CosCumparaturi::exportCosFisierHTML(const string& filename) const
{
	//if (cosGol()) // if (this->cosGol())
	//	throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	const auto path{ ".\\Export cos cumparaturi\\" };        // const string path{ ".\\Export cos cumparaturi\\" };
	const auto extension{ ".html" };                         // const string extension{ ".html" };
	const auto full_filename{ path + filename + extension }; // const string full_filename{ path + filename + extension };

	ofstream out{ full_filename }; // ofstream out(full_filename);

	out << "<!DOCTYPE html>\n";
	out << "<html lang=\"ro\">\n";

	out << "<head>\n";
	out << "	<meta charset=\"UTF-8\">\n";
	out << "	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
	out << "	<title>Lista de cumparaturi</title>\n";
	out << "	<style>\n";
	out << "		body {\n";
	out << "			font-family: Orbitron, sans-serif;\n";
	out << "			background-color: #ffa8B6;\n";
	out << "        }\n";
	out << "\n";
	out << "		h1 {\n";
	out << "			color: white;\n";
	out << "        }\n";
	out << "\n";
	out << "		fieldset {\n";
	out << "			color: white;\n";
	out << "			background-color: #8458B3;\n";
	out << "			font-weight: bold;\n";
	out << "        }\n";
	out << "\n";
	out << "        .title-container {\n";
	out << "			text-align: center;\n";
	out << "        }\n";
	out << "\n";
	out << "		legend, span{\n";
	out << "			font-size: 20px;\n";
	out << "        }\n";
	out << "\n";
	out << "		table {\n";
	out << "			width: 100%;\n";
	out << "			text-align: center;\n";
	out << "            font-family: Orbitron, sans-serif;\n";
	out << "            font-size: 30px;\n";
	out << "            border-collapse: collapse;\n";
	out << "            margin: 25px 0;\n";
	out << "            min-width: 400px;\n";
	out << "            border-radius: 5px 5px 0 0;\n";
	out << "            overflow: hidden;\n";
	out << "            box-shadow: 0 0 20px rgba(0, 0, 0, 0.15);\n";
	out << "		}\n";
	out << "\n";
	out << "		table thead tr {\n";
	out << "			background-color: #ffa8B6;\n";
	out << "			color: #8458B3;\n";
	out << "			text-align: center;\n";
	out << "			font-weight: bold;\n";
	out << "		}\n";
	out << "\n";
	out << "		table th,\n";
	out << "		table td{\n";
	out << "			padding: 12px 15px;\n";
	out << "		}\n";
	out << "\n";
	out << "		table tbody tr {\n";
	out << "			border-bottom: 1px solid #ffa8B6;\n";
	out << "		}\n";
	out << "\n";
	out << "		table tbody tr:nth-of-type(odd) {\n";
	out << "			background-color: #8d6ab4;\n";
	out << "			color: #fac7ce;\n";
	out << "		}\n";
	out << "\n";
	out << "		table tbody tr:nth-of-type(even) {\n";
	out << "			background-color: #fac7ce;\n";
	out << "			color: #8d6ab4;\n";
	out << "		}\n";
	out << "\n";
	out << "		table tbody tr:last-of-type {\n";
	out << "			border-bottom: 5px solid #ffa8B6;\n";
	out << "		}\n";
	out << "\n";
	out << "		th, td{\n";
	out << "			border: 5px solid #ffa8B6;\n";
	out << "		}\n";
	out << "\n";
	out << "		label{\n";
	out << "			font-size: 30px;\n";
	out << "			color: #ffa8B6;\n";
	out << "        }\n";
	out << "	</style>\n";
	out << "</head>\n";

	out << "<body>\n";
	out << "	<div class=\"title-container\">\n";
	out << "		<h1><u>Continut cos de cumparaturi</u></h1>\n";
	out << "	</div>\n";
	out << "\n";
	out << "	<br>\n";
	out << "\n";
	out << "	<div class=\"main-div\">\n";
	out << "		<fieldset>\n";
	out << "			<legend>Vizualizare produse cos</legend>\n";
	out << "\n";
	out << "			<div class=\"products-table-container\">\n";

	if (cosGol()) // if (this->cosGol())
		out << "				<label>Momentan nu exista produse in cosul de cumparaturi!</label>\n";
	else {
		out << "				<table class=\"shopping-cart\">\n";
		out << "					<thead>\n";
		out << "						<tr>\n";
		out << "							<th>#</th>\n";
		out << "							<th>Nume</th>\n";
		out << "							<th>Tip</th>\n";
		out << "							<th>Pret</th>\n";
		out << "							<th>Producator</th>\n";
		out << "							<th>Cantitate</th>\n";
		out << "						</tr>\n";
		out << "					</thead>\n";
		out << "					<tbody>\n";

		auto idx{ 0 };

		for (const auto& elem : cos)
		{
			const auto& prod{ elem.key };
			const auto& quantity{ elem.value };

			out << "					<tr>\n"
				<< "						<td>" << ++idx << "</td>\n"
				<< "						<td>" << prod.getName() << "</td>\n"
				<< "						<td>" << prod.getType() << "</td>\n"
				<< "						<td>" << prod.getPrice() << "</td>\n"
				<< "						<td>" << prod.getProducer() << "</td>\n"
				<< "						<td>" << quantity << "</td>\n"
				<< "					</tr>\n";
		}

		out << "					</tbody>\n";
		out << "				</table>\n";
	}

	out << "			</div>\n";
	out << "		</fieldset>\n";
	out << "		<fieldset>\n";
	out << "			<legend>Detalii cos de cumparaturi</legend>\n";
	out << "\n";
	out << "			<div class=\"shopping-cart-details-container\">\n";
	out << "				<label>[=]Numar total produse cos: " << this->nrProduseCos() << "</label>\n";
	out << "				<br>\n";
	out << "				<label>[$]Pret total produse: " << this->getTotal() << "</label>\n";
	out << "			</div>\n";
	out << "		</fieldset>\n";
	out << "	</div>\n";
	out << "</body>\n";
	out << "</html>\n";

	out.close();
}

const double& CosCumparaturi::getTotal() const noexcept
{
	return total_price;

	/*
	double total{ 0 };

	for (const auto& elem : cos)
	{
		const auto& prod{ elem.key };
		const auto& quantity{ elem.value };

		total += prod.getPrice() * quantity;
	}

	return total;
	*/
}

unsigned CosCumparaturi::nrProduseCos() const noexcept
{
	unsigned cont{ 0 };

	for (const auto& elem : cos)
		cont += elem.value;

	return cont;
}

vector<Product> CosCumparaturi::getCos() const
{
	if (cosGol()) // if (this->cosGol())
		throw CosException("[!]Nu exista produse in cosul de cumparaturi!\n");

	vector<Product> prods;

#define pb push_back

	for (const auto& elem : cos)
	{
		const auto& prod{ elem.key };
		const auto& quantity{ elem.value };

		for (unsigned i{ 0 }; i < quantity; ++i)
			prods.pb(prod);
	}

#undef pb

	return prods;
}

void CosCumparaturi::modificaProduseCos(const Product& product)
{
	auto iter{ cos.begin() };

	while (iter != cos.end())
	{
		const auto& elem{ *iter };
		const auto& prod{ elem.key };
		const auto quantity{ elem.value };

		if (prod == product) // if (prod.getName() == product.getName() && prod.getProducer() == product.getProducer())
			// if (prod.cmpProducts(product))
		{
			total_price -= prod.getPrice() * quantity;
			total_price += product.getPrice() * quantity;

			cos.erase(iter);
			cos[product] = quantity;

			this->notify(); // notify();

			return;
		}

		++iter;
	}
}

void CosCumparaturi::stergeProduseCos(const string& name, const string& producer) noexcept
{
	auto iter{ cos.begin() };

	while (iter != cos.end())
	{
		const auto& elem{ *iter };
		const auto& prod{ elem.key };
		const auto& quantity{ elem.value };

		if (prod.getName() == name && prod.getProducer() == producer)
		{
			total_price -= prod.getPrice() * quantity;
			cos.erase(iter);

			this->notify(); // notify();

			return;
		}

		++iter;
	}
}