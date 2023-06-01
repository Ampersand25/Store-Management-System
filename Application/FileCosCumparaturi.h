#pragma once

#include "CosCumparaturi.h"

#define TKey Product // definim TKey ca fiind Product (clasa)

class FileCosCumparaturi : public CosCumparaturi
{
private:
	// atribute private

	string filename;

	// metode (functii) private

	void loadFromFile();

	void writeToFile();

public:
	FileCosCumparaturi() = delete;

	FileCosCumparaturi(AbstractRepo& repo, const string& filename) : CosCumparaturi(repo), filename{ filename } {
		this->loadFromFile(); // loadFromFile();
	}

	void golesteCos() override;

	void adaugaInCos(const string& name, const string& producer) override;

	void genereazaCos(unsigned number_of_products) override;

	void modificaProduseCos(const TKey& product) override;

	void stergeProduseCos(const string& name, const string& producer) noexcept override;

	void eliminaProdusCos(const string& name, const string& producer) override;

	~FileCosCumparaturi() = default;
};