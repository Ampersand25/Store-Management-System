#pragma once

#include "Product.h"
#include "CosCumparaturi.h"
#include "ListModelCosCRUDGUI.h"
#include "TableModelCosCRUDGUI.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qtabwidget.h>

#include <vector>

using std::vector;

class CosCRUDGUI : public QWidget, public Observer {
private:
	const unsigned MIN_SLD{ 1 };
	const unsigned MAX_SLD{ 100 };
	const unsigned CURR_SLD{ 1 };

	CosCumparaturi& cos;

	QSpinBox* spin_box;

	QPushButton* btn_gen;
	QPushButton* btn_gol;

	QListWidget* lst_cos;
	QTableWidget* tbl_cos;

	ListModelCosCRUDGUI* lst_cos_model;
	TableModelCosCRUDGUI* tbl_cos_model;

	QListView* lst_cos_view;
	QTableView* tbl_cos_view;

	QTabWidget* tab;

	void addCumparaturiToList(QListWidget* lst, const vector<Product>& lista_cumparaturi);
	void addCumparaturiToTable(QTableWidget* tbl, const vector<Product>& lista_cumparaturi);

	void setUpMasterDetail();

	void initGuiCmpCosCRUDGUI();
	void connectSignalsCosCRUDGUI();
	void setInitialStateCosCRUDGUI();

public:
	void update() override {
		setUpMasterDetail();
	}

	CosCRUDGUI() = delete;

	CosCRUDGUI(CosCRUDGUI& ot) = delete;

	CosCRUDGUI& operator=(CosCRUDGUI& ot) = delete;

	CosCRUDGUI(CosCumparaturi& cos) : cos{ cos } {
		// Initialize GUI components
		initGuiCmpCosCRUDGUI();

		// Connect signals and slots
		connectSignalsCosCRUDGUI();

		// Set initial GUI state
		setInitialStateCosCRUDGUI();
	}

	void closeEvent(QCloseEvent* event) override {
		this->~CosCRUDGUI();
	}

	~CosCRUDGUI() {
		cos.detachObserver(this);
	}
};