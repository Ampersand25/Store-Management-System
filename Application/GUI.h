#pragma once

#include "Service.h"
#include "HistogramGUI.h"
#include "PercentageHistogramGUI.h"
#include "ListModelTypes.h"
#include "TipuriProduseGUI.h"
#include "ListModelCos.h"
#include "TableModelCos.h"
#include "ListModelProducts.h"
#include "TableModelProducts.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qbuttongroup.h>
#include <QtWidgets/qradiobutton.h>
#include <QtWidgets/qslider.h>
#include <QtWidgets/qtabwidget.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtableview.h>

class GUI : public QWidget
{
private:
	// atribute/campuri si metode private

	// atribute/campuri private

	bool database_repo;

	Service& srv; // referinta la un obiect de clasa Service

	QPushButton* btn_adaugare_cumparaturi_main = new QPushButton{ "Adauga produs in cos" };
	QPushButton* btn_stergere_cumparaturi_main = new QPushButton{ "Sterge continut cos" };
	QPushButton* btn_generare_cumparaturi_main = new QPushButton{ "Genereaza cos" };

	QPushButton* btn_CosCRUDGUI = new QPushButton{ "CosCRUDGUI" };
	QPushButton* btn_CosReadOnlyGUI = new QPushButton{ "CosReadOnlyGUI" };

	QPushButton* btn_cos = new QPushButton{ "Cumparaturi" };

	QSlider* sld_cumparaturi_main = new QSlider;
	QSpinBox* sld_value_cumparaturi_main = new QSpinBox;

	QPushButton* btn_add = new QPushButton{ "&Adaugare" };
	QPushButton* btn_modify = new QPushButton{ "&Modificare" };
	QPushButton* btn_delete = new QPushButton{ "S&tergere" };
	QPushButton* btn_search = new QPushButton{ "&Cautare" };

	QPushButton* btn_type = new QPushButton{ "Afisar&e" };
	QPushButton* btn_info_types = new QPushButton{ "&Info tipuri" };
	QPushButton* btn_undo = new QPushButton{ "&Undo" };
	QPushButton* btn_redo = new QPushButton{ "&Redo" };

	QPushButton* btn_dbg = new QPushButton{ "&Debug" };
	QPushButton* btn_clear = new QPushButton{ "C&lear" };
	QPushButton* btn_exit = new QPushButton{ "E&xit" };

	QCheckBox* checkbox_cresc = new QCheckBox("crescator", nullptr);
	QCheckBox* checkbox_descresc = new QCheckBox("descrescator", nullptr);

	QButtonGroup* sort_group = new QButtonGroup();

	QRadioButton* radio_btn_cresc = new QRadioButton("crescator");
	QRadioButton* radio_btn_descresc = new QRadioButton("descrescator");

	QPushButton* btn_sort = new QPushButton{ "&Sortare" };

	QCheckBox* checbox_less = new QCheckBox("mai mic (<)", nullptr);
	QCheckBox* checkbox_equal = new QCheckBox("egal (=)", nullptr);
	QCheckBox* checkbox_greater = new QCheckBox("mai mare (>)", nullptr);

	QButtonGroup* filter_group = new QButtonGroup(nullptr);

	QRadioButton* radio_btn_less = new QRadioButton("mai mic (<)", nullptr);
	QRadioButton* radio_btn_equal = new QRadioButton("egal (=)", nullptr);
	QRadioButton* radio_btn_greater = new QRadioButton("mai mare (>)", nullptr);

	QPushButton* btn_filter = new QPushButton{ "&Filtrare" };

	QLineEdit* name_line_edit = new QLineEdit;
	QLineEdit* type_line_edit = new QLineEdit;
	QLineEdit* price_line_edit = new QLineEdit;
	QLineEdit* producer_line_edit = new QLineEdit;

	QLabel* filter_crt_label = new QLabel{ "Nume/Tip/Pret/Producator filtrare" };
	QLineEdit* filter_crt_line_edit = new QLineEdit;

	QListWidget* lst_products = new QListWidget();
	QTableWidget* tbl_products = new QTableWidget();

	QListView* lst_products_view = new QListView{};
	QTableView* tbl_products_view = new QTableView{};

	ListModelProducts* lst_products_model;
	TableModelProducts* tbl_products_model;

	QTabWidget* products_tab = new QTabWidget();

	QListWidget* lst_types = new QListWidget();

	QLineEdit* fisier_export_line_edit = new QLineEdit;

	QCheckBox* checkbox_export_fisier_csv = new QCheckBox("CSV", nullptr);
	QCheckBox* checkbox_export_fisier_html = new QCheckBox("HTML", nullptr);

	QSpinBox* no_prods = new QSpinBox(nullptr);

	QPushButton* btn_golire_cos = new QPushButton{ "Golire" };
	QPushButton* btn_adaugare_cos = new QPushButton{ "Adaugare" };
	QPushButton* btn_tiparire_cos = new QPushButton{ "Tiparire" };
	QPushButton* btn_export_cos = new QPushButton{ "Export" };
	QPushButton* btn_generare_cos = new QPushButton{ "Generare" };

	QPushButton* btn_clear_cos = new QPushButton{ "Clear" };
	QPushButton* btn_close_cos = new QPushButton{ "Close" };

	QLineEdit* name_cos_line_edit = new QLineEdit;
	QLineEdit* type_cos_line_edit = new QLineEdit;
	QLineEdit* price_cos_line_edit = new QLineEdit;
	QLineEdit* producer_cos_line_edit = new QLineEdit;

	QLineEdit* total_price_cos_line_edit = new QLineEdit;
	QLineEdit* total_products_cos_line_edit = new QLineEdit;

	QWidget* cos_widget = nullptr;
	TipuriProduseWidget* tipuri_produse_widget = nullptr; // QWidget* tipuri_produse_widget = nullptr;

	Histogram* hist_widget = nullptr; // QWidget* hist_widget = nullptr;
	PercentageHistogram* percentage_hist_widget = nullptr; // QWidget* percentage_hist_widget = nullptr;

	//QListWidget* lst_cumparaturi = new QListWidget();
	//QTableWidget* tbl_cumparaturi = new QTableWidget();

	QListView* lst_cumparaturi_view = new QListView;
	QTableView* tbl_cumparaturi_view = new QTableView;

	ListModelCos* lst_cumparaturi_model = new ListModelCos{ srv.getCosSrv() };
	TableModelCos* tbl_cumparaturi_model = new TableModelCos{ srv.getCosSrv() };

	QComboBox* sort_options_combo_box = new QComboBox;
	QComboBox* filter_options_combo_box = new QComboBox;

	const QIcon shopping_cart_icon{ "./Logo-uri aplicatie/shoppingCartIcon" };
	const QIcon store_icon{ "./Logo-uri aplicatie/storeIcon" };
	const QIcon product_icon{ "./Logo-uri aplicatie/productIcon" };
	const QIcon cos_read_only_icon{ "./Logo-uri aplicatie/shoppingReadOnlyIcon" };
	const QIcon cos_crud_icon{ "./Logo-uri aplicatie/shoppingCRUDIcon" };

	const QPixmap sad_pix_map{ "./Logo-uri aplicatie/sad" };
	const QPixmap happy_pix_map{ "./Logo-uri aplicatie/happy" };

	unsigned number_of_undo;
	unsigned number_of_redo;

	// metode private

	//void initMeniuTipuriProduse(const dictionary& types_map);

	void addCumparaturiToList(QListWidget* lst, const vector<Product>& lista_cumparaturi);
	void addCumparaturiToTable(QTableWidget* tbl, const vector<Product>& lista_cumparaturi);

	QListWidgetItem* last_selected_item_list_cos;
	QLabel* lbl_selected_item_list_cos{ nullptr };
	QDialog* dialog_selected_item_list_cos{ nullptr };

	void setShortcutsCosCumparaturi();
	void setToolTipsCosCumparaturi();

	void initMeniuCosCumparaturi();
	void connectSignalsCosCumparaturi();
	void setInitialStateCosCumparaturi();

	void addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const;

	void sortProductsGUI(const string& sort_criterion);

	bool filteredGUI(const vector<Product>& filtered_list, const Product& prod);
	void showFilteredList(const vector<Product>& filtered_list);
	void filterProductsGUI(const string& criterion, const string& sgn);

	void addProductsToList(const vector<Product>& prods);
	void addProductsToTable(const vector<Product>& prods);

	QListWidgetItem* last_selected_item_list;
	QLabel* lbl_selected_item_list{ nullptr };
	QDialog* dialog_selected_item_list{ nullptr };

	void addShortcuts();
	void addToolTips();
	void addPlaceholderText();

	void initGuiCmp();
	void connectSignals();
	void setInitialState();

	// Varianta veche (fara Observer)
	QWidget* cosCRUDGUI_wdg;

	void initGuiCmpCosCRUDGUI();
	void connectSignalsCosCRUDGUI();
	void setInitialStateCosCRUDGUI();

	QSpinBox* spin_box_cos_crud;

	QPushButton* btn_gen_cos_crud;
	QPushButton* btn_gol_cos_crud;

	QListWidget* lst_cos_crud;
	QTableWidget* tbl_cos_crud;

	QTabWidget* tab_cos_crud;

public:
	// metode publice

	// constructor default (implicit) al unui obiect de clasa GUI
	// impiedicam instantierea de obiecte de clasa GUI folosind constructorul default (fara parametrii)
	GUI() = delete;

	// constructor custom al unui obiect de clasa GUI
	GUI(Service& srv, bool database_repo) : srv{ srv }, database_repo{ database_repo } {
		initGuiCmp();
		connectSignals();
		setInitialState();
	}

	// method that disables the btn_info_types button if the input parameter disable is true
	// if disable parameter is false then the button will not be disabled (will remain enabled)
	//void disableInfoTipuri(bool disable)
	//{
	//	btn_info_types->setDisabled(disable);
	//}
};