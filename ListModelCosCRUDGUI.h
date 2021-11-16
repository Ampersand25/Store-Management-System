#pragma once

#include "Product.h"
#include "CosCumparaturi.h"
#include "CosException.h"

#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class ListModelCosCRUDGUI : public QAbstractListModel {
private:
	CosCumparaturi& cos;
	int last_selected_item;

public:
	ListModelCosCRUDGUI() = delete;

	ListModelCosCRUDGUI(CosCumparaturi& cos) : cos{ cos }, last_selected_item{ -1 } {
		
	}

	ListModelCosCRUDGUI(ListModelCosCRUDGUI& ot) = delete;

	ListModelCosCRUDGUI& operator=(ListModelCosCRUDGUI& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cos.nrProduseCos() + 1;
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 1;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			
			if (!index.row())
			{
				font.setItalic(true);
				font.setBold(true);
			}
			else {
				font.setItalic(false);
				font.setBold(false);
			}

			return font;
		}
		else if (role == Qt::BackgroundRole)
		{
			if (last_selected_item == index.row())
			{
				QColor color{ 0, 114, 181 };

				return QBrush(color, Qt::SolidPattern);
			}

			return QBrush(Qt::white, Qt::SolidPattern);
		}
		else if (role == Qt::TextAlignmentRole)
			return Qt::AlignLeft;
		else if (role == Qt::DisplayRole)
		{
			qDebug() << "row: " << index.row();

			try {
				auto products{ cos.getCos() };

				if (!index.row())
					return QString("Produsele existente in cosul de cumparaturi sunt:");

				const auto prod{ products.at(index.row() - (size_t)1) };

				const auto qname = QString::fromStdString(prod.getName());
				const auto qtype = QString(QString::fromStdString(prod.getType()));
				const auto qprice = QString::number(prod.getPrice());
				const auto qproducer = QString::fromStdString(prod.getProducer());

				return QString::number(index.row()) + ": " + qname + " | " + qtype + " | " + qprice + " | " + qproducer;
			}
			catch (const CosException&) {
				return QString("Nu exista momentan produse adaugate in cosul de cumparaturi!");
			}
		}

		return QVariant();
	}

	void setProducts() {
		emit layoutChanged();
	}

	void setLastSelectedItem(const int& last) {
		this->last_selected_item = last; // last_selected_item = last;
	}

	~ListModelCosCRUDGUI() = default;
};