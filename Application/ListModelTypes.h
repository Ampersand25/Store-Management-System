#pragma once

#include "Product.h"
#include "Service.h"

#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class ListModelTypes : public QAbstractListModel {
private:
	Service& srv;
	int last_selected_item;

public:
	ListModelTypes() = delete;

	ListModelTypes(Service& srv) : srv{ srv }, last_selected_item{ -1 } {

	}

	ListModelTypes(ListModelTypes& ot) = delete;

	ListModelTypes& operator=(ListModelTypes& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return srv.countType().size();
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
			if (last_selected_item == index.row())
			{
				QColor color{ 191, 214, 65 };

				return QBrush(color, Qt::SolidPattern);
			}

			return QBrush(Qt::white, Qt::SolidPattern);
		}
		else if (role == Qt::TextAlignmentRole)
			return Qt::AlignLeft;
		else if (role == Qt::DisplayRole)
		{
			qDebug() << "row: " << index.row();

			if (!index.row())
				return QString("Exista urmatoarele tipuri de produse in stocul magazinului:");

			unsigned i{ 0 };

			for (const auto& elem : srv.countType())
				if (i == index.row())
				{
					const auto key{ elem.first };
					const auto value{ elem.second };

					if (value.second == 1)
						return QString("Exista un singur produs cu tipul \"" + QString::fromStdString(key) + "\" in magazin!\n");

					return QString("Exista " + QString::number(value.second) + " produse cu tipul \"" + QString::fromStdString(key) + "\" in magazin!\n");
				}
				else
					++i;
		}

		return QVariant();
	}

	void setTypes() {
		emit layoutChanged();
	}

	void setLastSelectedItem(const int& last) {
		this->last_selected_item = last; // last_selected_item = last;
	}

	~ListModelTypes() = default;
};