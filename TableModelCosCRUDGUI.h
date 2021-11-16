#pragma once

#include "Product.h"
#include "CosCumparaturi.h"
#include "CosException.h"

#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class TableModelCosCRUDGUI : public QAbstractTableModel {
private:
	CosCumparaturi& cos;

public:
	TableModelCosCRUDGUI() = delete;

	TableModelCosCRUDGUI(CosCumparaturi& cos) : cos{ cos } {
		
	}

	TableModelCosCRUDGUI(TableModelCosCRUDGUI& ot) = delete;

	TableModelCosCRUDGUI& operator=(TableModelCosCRUDGUI& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cos.nrProduseCos();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			font.setItalic(false);
			font.setBold(true);

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
			font.setItalic(true);
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

			try {
				auto products{ cos.getCos() };
				auto prod{ products.at(index.row()) };

				if (!index.column())
					return QString(QString::fromStdString(prod.getName()));
				else if (index.column() == 1)
					return QString(QString::fromStdString(prod.getType()));
				else if (index.column() == 2)
					return QString(QString::number(prod.getPrice()));
				else if (index.column() == 3) // else
					return QString(QString::fromStdString(prod.getProducer()));
			}
			catch (const CosException&) {
				return QVariant();
			}
		}

		return QVariant();
	}

	void setProducts() {
		emit layoutChanged();
	}

	~TableModelCosCRUDGUI() = default;
};