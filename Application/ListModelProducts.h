#pragma once

#include "Product.h"
#include "Service.h"
#include "ServiceException.h"

#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

#include <algorithm>

using std::find_if;

class ListModelProducts : public QAbstractListModel {
private:
	vector<Product> prods, filtered_prods;
	bool visible, filter_selected;
	int last_selected_item;

public:
	ListModelProducts() = delete;

	ListModelProducts(const vector<Product>& prods) : prods{ prods }, filtered_prods{ vector<Product>() }, visible{ true }, filter_selected{ false }, last_selected_item{ -1 } {

	}

	ListModelProducts(ListModelProducts& ot) = delete;

	ListModelProducts& operator=(ListModelProducts& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return (visible) ? (prods.size() + 1) : (0);
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 1;
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
		{
			if (!filter_selected || !index.row())
			{
				if (last_selected_item == index.row())
				{
					QColor color{ 210, 56, 108 };

					return QBrush(color, Qt::SolidPattern);
				}

				return QBrush(Qt::white, Qt::SolidPattern);
			}

			const auto prod{ prods.at(index.row() - (size_t)1) };

			if (find_if(filtered_prods.begin(), filtered_prods.end(), [&prod](const Product& ot) {return prod == ot; }) != filtered_prods.end())
				return QBrush(Qt::green, Qt::SolidPattern);

			return QBrush(Qt::red, Qt::SolidPattern);
		}
		else if (role == Qt::TextAlignmentRole)
			return Qt::AlignLeft;
		else if (role == Qt::UserRole)
		{
			if (!index.row())
				return QVariant{};

			const auto prod{ prods.at(index.row() - (size_t)1) };

			const auto qname{ QString::fromStdString(prod.getName()) };
			const auto qtype{ QString(QString::fromStdString(prod.getType())) };
			const auto qprice{ QString::number(prod.getPrice()) };
			const auto qproducer{ QString::fromStdString(prod.getProducer()) };

			return QStringList{ qname, qtype, qprice, qproducer };
		}
		else if (role == Qt::DisplayRole)
		{
			qDebug() << "row: " << index.row();

			if (!index.row())
				return QString("Produsele existente in cosul de cumparaturi sunt:");

			const auto prod{ prods.at(index.row() - (size_t)1) };

			const auto qname{ QString::fromStdString(prod.getName()) };
			const auto qtype{ QString(QString::fromStdString(prod.getType())) };
			const auto qprice{ QString::number(prod.getPrice()) };
			const auto qproducer{ QString::fromStdString(prod.getProducer()) };

			return QString::number(index.row()) + ": " + qname + " | " + qtype + " | " + qprice + " | " + qproducer;
		}

		return QVariant();
	}

	void setFilter(const bool status) {
		filter_selected = status;
	}

	void setFilteredList(const vector<Product>& filtered) {
		this->visible = true; // visible = true;

		this->setFilter(true); // setFilter(true);
		// filter_selected = true;

		filtered_prods = filtered;

		emit layoutChanged();
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

	void setLastSelectedItem(const int& last) {
		this->last_selected_item = last; // last_selected_item = last;
	}

	~ListModelProducts() = default;
};