#pragma once

#include "Product.h"
#include "Service.h"
#include "ServiceException.h"

#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class TableModelProducts : public QAbstractTableModel {
private:
	vector<Product> prods;
	bool visible;

public:
	TableModelProducts() = delete;

	TableModelProducts(const vector<Product>& prods) : prods{ prods }, visible{ true } {

	}

	TableModelProducts(TableModelProducts& ot) = delete;

	TableModelProducts& operator=(TableModelProducts& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return (visible) ? (prods.size()) : (0);
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			font.setItalic(false);
			font.setBold(false);

			return font;
		}
		else if (role == Qt::BackgroundRole)
			return QBrush(Qt::white, Qt::SolidPattern);
		else if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (!section)
					return QString{ "Nume" };
				else if (section == 1)
					return QString{ "Tip" };
				else if (section == 2)
					return QString{ "Pret" };
				else if (section == 3)
					return QString{ "Producator" };
			}
			else if (orientation == Qt::Vertical)
				return QString{ "%1" }.arg(section + 1);
		}

		return QVariant{};
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			font.setItalic(false);
			font.setBold(false);

			return font;
		}
		else if (role == Qt::BackgroundRole)
			return QBrush(Qt::white, Qt::SolidPattern);
		else if (role == Qt::TextAlignmentRole)
			return Qt::AlignHCenter;
		else if (role == Qt::DisplayRole)
		{
			qDebug() << "row: " << index.row() << " column: " << index.column();

			auto prod{ prods.at(index.row()) };

			if (!index.column())
				return QString(QString::fromStdString(prod.getName()));
			else if (index.column() == 1)
				return QString(QString::fromStdString(prod.getType()));
			else if (index.column() == 2)
				return QString(QString::number(prod.getPrice()));
			else if (index.column() == 3) // else
				return QString(QString::fromStdString(prod.getProducer()));
		}

		return QVariant();
	}

	void setLayoutChanged(const vector<Product>& products) {
		prods = products; // this->prods = products;

		emit layoutChanged();
	}

	void setDataChanged(const vector<Product>& products) {
		this->visible = true; // visible = true;

		prods = products; // this->prods = products;

		const QModelIndex top_left{ createIndex(0, 0) };
		const QModelIndex bottom_right{ createIndex(rowCount(), columnCount()) };

		emit dataChanged(top_left, bottom_right);
	}

	void setVisible(const vector<Product>& products, const bool value) {
		this->visible = value; // visible = value;

		this->setLayoutChanged(products); // setLayoutChanged(products);
		// emit layoutChanged();
	}

	~TableModelProducts() = default;
};