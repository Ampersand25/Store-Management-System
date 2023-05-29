#pragma once

#include "Observer.h"
#include "Service.h"
#include "ListModelTypes.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistview.h>

class TipuriProduseWidget : public QWidget, public Observer {
private:
	const QIcon types_icon{ "./Logo-uri aplicatie/typesIcon" };

	const QString types_title{ "Tipuri produse" };

	Service& srv;

	QListView* lst_types_view = new QListView;
	ListModelTypes* lst_types_model = new ListModelTypes(srv);

public:
	TipuriProduseWidget() = delete;

	TipuriProduseWidget(TipuriProduseWidget& ot) = delete;

	TipuriProduseWidget& operator=(TipuriProduseWidget& ot) = delete;

	TipuriProduseWidget(Service& srv) : srv{ srv } {
		srv.attachObserver(this);

		this->setWindowTitle(types_title);
		this->setWindowIcon(types_icon);

		QVBoxLayout* ly = new QVBoxLayout;

		this->setLayout(ly);

		QLabel* lbl = new QLabel;

		lbl->setText("Tipuri de produse existente in magazinul virtual");
		QFont font_lbl = lbl->font();
		font_lbl.setWeight(QFont::Bold);
		lbl->setFont(font_lbl);
		lbl->setAlignment(Qt::AlignHCenter);

		ly->addWidget(lbl);

		lst_types_view->setUniformItemSizes(true);
		lst_types_view->setModel(lst_types_model);

		ly->addWidget(lst_types_view); // varianta cu model-view

		/*QObject::connect(this, &QWidget::close, nullptr, [&]() {
			srv.detachObserver(this); // this->~TipuriProduse();
			});*/

		QObject::connect(lst_types_view->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
			const auto sel{ lst_types_view->selectionModel()->selectedIndexes() };

			if (!sel.isEmpty()) // if (sel.size())
			{
				const auto& selected_index{ sel.at(0) };

				if (selected_index.row())
					lst_types_model->setLastSelectedItem(selected_index.row());
				else
					lst_types_model->setLastSelectedItem(-1);
			}
			});
	}

	void update() override {
		lst_types_model->setTypes();
	}

	void closeEvent(QCloseEvent* event) override {
		this->~TipuriProduseWidget();
	}

	~TipuriProduseWidget() {
		srv.detachObserver(this);
	}
};