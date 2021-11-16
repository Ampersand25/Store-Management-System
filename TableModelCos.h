#pragma once

#include "Product.h"
#include "CosCumparaturi.h"
#include "CosException.h"

#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class TableModelCos : public QAbstractTableModel {
private:
	CosCumparaturi& cos;
	bool visible;

public:
	TableModelCos() = delete;

	TableModelCos(CosCumparaturi& cos) : cos{ cos }, visible{ true } {

	}

	TableModelCos(TableModelCos& ot) = delete;

	TableModelCos& operator=(TableModelCos& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return (visible) ? (cos.nrProduseCos()) : (0);
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

	void setCosCumparaturi() {
		emit layoutChanged();
	}

	void setVisible(const bool value) {
		this->visible = value; // visible = value;

		this->setCosCumparaturi(); // setCosCumparaturi();
		                           // emit layoutChanged();
	}

	~TableModelCos() = default;
};