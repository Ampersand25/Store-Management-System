#include "GUI.h"
#include "RepoException.h"
#include "ServiceException.h"
#include "ProductException.h"
#include "CosException.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"

#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>

#include <random> // pentru std::random_device, std::mt19937 si std::uniform_int_distribution

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::to_string;

//void GUI::initMeniuTipuriProduse(const dictionary& types_map)
//{
//	tipuri_produse_widget = new QWidget{};
//	tipuri_produse_widget->setWindowTitle("Tipuri produse");
//	tipuri_produse_widget->setWindowIcon(types_icon);
//
//	QVBoxLayout* ly = new QVBoxLayout;
//
//	tipuri_produse_widget->setLayout(ly);
//
//	QLabel* lbl = new QLabel;
//
//	lbl->setText("Tipuri de produse existente in stoc:");
//	lbl->setAlignment(Qt::AlignHCenter);
//
//	ly->addWidget(lbl);
//	
//	// Varianta fara model-view
//	//lst_types->clear();
//
//	// Varianta cu model-view
//	lst_types_model = new ListModelTypes(types_map);
//
//	lst_types_view->setUniformItemSizes(true);
//	lst_types_view->setModel(lst_types_model);
//
//// Varianta fara model-view
////#define type first
////#define freq second
////
////	for (const auto elem : types_map)
////	{
////		const auto key{ elem.first };
////		const auto value{ elem.second };
////
////		QListWidgetItem* item = new QListWidgetItem{ "Exista " + QString::number(value.freq) + " produse cu tipul \"" + QString::fromStdString(key) + "\" in magazin!\n" };
////
////		lst_types->addItem(item);
////	}
////
////#undef type
////#undef freq
//	
//	//ly->addWidget(lst_types);    // varianta fara model-view
//	ly->addWidget(lst_types_view); // varianta cu model-view
//
//	tipuri_produse_widget->show();
//}

void GUI::initMeniuCosCumparaturi()
{
	cos_widget = new QWidget{};
	cos_widget->setWindowTitle("Cos de cumparaturi");
	cos_widget->setWindowIcon(shopping_cart_icon);

	QVBoxLayout* ly = new QVBoxLayout;

	cos_widget->setLayout(ly);

	QHBoxLayout* upper_ly = new QHBoxLayout;

	QLabel* title_lbl = new QLabel;
	title_lbl->setText("Meniu cos cumparaturi");
	QFont font_title_lbl = title_lbl->font();
	font_title_lbl.setWeight(QFont::Bold);
	title_lbl->setFont(font_title_lbl);
	title_lbl->setAlignment(Qt::AlignHCenter);

	upper_ly->addWidget(title_lbl);

	ly->addLayout(upper_ly);

	QHBoxLayout* lower_ly = new QHBoxLayout;

	QVBoxLayout* left_ly = new QVBoxLayout;

	QLabel* cos_lst_lbl = new QLabel;
	cos_lst_lbl->setText("Lista cu produsele din cosul de cumparaturi");
	QFont font_cos_lst_lbl = cos_lst_lbl->font();
	font_cos_lst_lbl.setWeight(QFont::Bold);
	cos_lst_lbl->setFont(font_cos_lst_lbl);
	cos_lst_lbl->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(cos_lst_lbl);
	left_ly->addWidget(lst_cumparaturi_view);

	QLabel* cos_tbl_lbl = new QLabel;
	cos_tbl_lbl->setText("Tabel cu produsele din cosul de cumparaturi");
	QFont font_cos_tbl_lbl = cos_tbl_lbl->font();
	font_cos_tbl_lbl.setWeight(QFont::Bold);
	cos_tbl_lbl->setFont(font_cos_tbl_lbl);
	cos_tbl_lbl->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(cos_tbl_lbl);
	//left_ly->addWidget(tbl_cumparaturi);

	/*tbl_cumparaturi_view = new QTableView;

	tbl_cumparaturi_model = new TableModelCos{ srv.getCosSrv() };

	tbl_cumparaturi_view->setModel(tbl_cumparaturi_model);*/

	left_ly->addWidget(tbl_cumparaturi_view);

	lower_ly->addLayout(left_ly);

	QVBoxLayout* right_ly = new QVBoxLayout;

	QLabel* produs_cos_lbl = new QLabel;
	produs_cos_lbl->setText("Informatii produs - cos de cumparaturi");
	QFont font_produs_cos_lbl = produs_cos_lbl->font();
	font_produs_cos_lbl.setWeight(QFont::Bold);
	produs_cos_lbl->setFont(font_produs_cos_lbl);
	produs_cos_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(produs_cos_lbl);

	QFormLayout* form_ly_1 = new QFormLayout;

	QLabel* name_label = new QLabel{ "Nume" };
	QLabel* type_label = new QLabel{ "Tip" };
	QLabel* price_label = new QLabel{ "Pret" };
	QLabel* producer_label = new QLabel{ "Producator" };

	type_cos_line_edit->setReadOnly(true);
	price_cos_line_edit->setReadOnly(true);

	form_ly_1->addRow(name_label, name_cos_line_edit);
	form_ly_1->addRow(type_label, type_cos_line_edit);
	form_ly_1->addRow(price_label, price_cos_line_edit);
	form_ly_1->addRow(producer_label, producer_cos_line_edit);

	right_ly->addLayout(form_ly_1);
	right_ly->addStretch();

	QLabel* lbl_info_cos = new QLabel;
	lbl_info_cos->setText("Detalii cos de cumparaturi");
	QFont font_lbl_info_cos = lbl_info_cos->font();
	font_lbl_info_cos.setWeight(QFont::Bold);
	lbl_info_cos->setFont(font_lbl_info_cos);
	lbl_info_cos->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(lbl_info_cos);

	QFormLayout* form_ly_2 = new QFormLayout;

	QLabel* total_price_label = new QLabel{ "Pret total produse cos" };
	QLabel* total_products_label = new QLabel{ "Numar total produse cos" };

	total_price_cos_line_edit->setReadOnly(true);
	total_products_cos_line_edit->setReadOnly(true);

	total_price_cos_line_edit->setAlignment(Qt::AlignCenter);
	total_products_cos_line_edit->setAlignment(Qt::AlignCenter);

	form_ly_2->addRow(total_price_label, total_price_cos_line_edit);
	form_ly_2->addRow(total_products_label, total_products_cos_line_edit);

	right_ly->addLayout(form_ly_2);
	right_ly->addStretch();

	/*
	QVBoxLayout* total_price_ly = new QVBoxLayout;

	QLabel* total_price_label = new QLabel;
	total_price_label->setText("Pret total cos cumparaturi");
	total_price_label->setAlignment(Qt::AlignHCenter);

	QLineEdit* total_price_edt = new QLineEdit{ "" };

	total_price_ly->addWidget(total_price_label);
	total_price_ly->addWidget(total_price_edt);

	right_ly->addLayout(total_price_ly);
	right_ly->addStretch();
	*/

	QLabel* options_lbl = new QLabel;
	options_lbl->setText("Optiuni gestionare cos de cumparaturi");
	QFont font_options_lbl = options_lbl->font();
	font_options_lbl.setWeight(QFont::Bold);
	options_lbl->setFont(font_options_lbl);
	options_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_lbl);

	QHBoxLayout* btns_ly_1 = new QHBoxLayout;

	btns_ly_1->addWidget(btn_adaugare_cos);
	btns_ly_1->addWidget(btn_stergere_cos);
	btns_ly_1->addWidget(btn_golire_cos);
	btns_ly_1->addWidget(btn_tiparire_cos);

	right_ly->addLayout(btns_ly_1);

	QLabel* options_generare_lbl = new QLabel;
	options_generare_lbl->setText("Optiuni generare cos de cumparaturi");
	QFont font_options_generare_lbl = options_generare_lbl->font();
	font_options_generare_lbl.setWeight(QFont::Bold);
	options_generare_lbl->setFont(font_options_generare_lbl);
	options_generare_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_generare_lbl);

	QHBoxLayout* generare_ly = new QHBoxLayout;

	QLabel* no_prods_generare_lbl = new QLabel;
	no_prods_generare_lbl->setText("Numar produse generare");

	generare_ly->addWidget(no_prods_generare_lbl);

	no_prods->setMinimum(1);
	no_prods->setMaximum(100);
	no_prods->setValue(1);
	generare_ly->addWidget(no_prods);

	right_ly->addLayout(generare_ly);

	right_ly->addWidget(btn_generare_cos);

	QLabel* options_search_product_shopping_cart_lbl = new QLabel;
	options_search_product_shopping_cart_lbl->setText("Optiuni cautare produs in cosul de cumparaturi");
	QFont font_options_search_product_shopping_cart_lbl = options_search_product_shopping_cart_lbl->font();
	font_options_search_product_shopping_cart_lbl.setWeight(QFont::Bold);
	options_search_product_shopping_cart_lbl->setFont(font_options_search_product_shopping_cart_lbl);
	options_search_product_shopping_cart_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_search_product_shopping_cart_lbl);

	QVBoxLayout* search_shopping_cart_ly = new QVBoxLayout;

	QHBoxLayout* search_shopping_cart_options_ly = new QHBoxLayout;
	search_shopping_cart_options_ly->addWidget(search_shopping_cart_combo_box);
	search_shopping_cart_options_ly->addWidget(search_product_shopping_cart_line_edit);

	QHBoxLayout* search_shopping_cart_button_ly = new QHBoxLayout;
	search_shopping_cart_button_ly->addWidget(btn_cautare_cos);

	search_shopping_cart_ly->addLayout(search_shopping_cart_options_ly);
	search_shopping_cart_ly->addLayout(search_shopping_cart_button_ly);

	right_ly->addLayout(search_shopping_cart_ly);

	QLabel* options_export_lbl = new QLabel;
	options_export_lbl->setText("Optiuni export cos de cumparaturi");
	QFont font_options_export_lbl = options_export_lbl->font();
	font_options_export_lbl.setWeight(QFont::Bold);
	options_export_lbl->setFont(font_options_export_lbl);
	options_export_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_export_lbl);

	QFormLayout* export_form_ly = new QFormLayout;

	QLabel* fisier_export_label = new QLabel{ "Nume fisier export" };

	export_form_ly->addRow(fisier_export_label, fisier_export_line_edit);

	right_ly->addLayout(export_form_ly);

	QLabel* lbl_export = new QLabel{ "Tip fisier export" };

	QHBoxLayout* export_checkers_ly = new QHBoxLayout;

	export_checkers_ly->addWidget(lbl_export);
	export_checkers_ly->addWidget(checkbox_export_fisier_csv);
	export_checkers_ly->addWidget(checkbox_export_fisier_html);

	right_ly->addLayout(export_checkers_ly);

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_export_cos);

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_clear_cos);
	btns_ly_3->addWidget(btn_close_cos);

	right_ly->addLayout(btns_ly_3);

	lower_ly->addLayout(right_ly);

	ly->addLayout(lower_ly);

	cos_widget->show();
}

void GUI::connectSignalsCosCumparaturi()
{
	//QObject::connect(lst_cumparaturi, &QListWidget::itemSelectionChanged, this, [&]() {
	//	auto sel{ lst_cumparaturi->selectedItems() };

	//	if (last_selected_item_list_cos != nullptr)
	//		last_selected_item_list_cos->setBackground(Qt::white);

	//	if (sel.isEmpty()) // if (!sel.size())
	//	{
	//		name_cos_line_edit->setText("");
	//		type_cos_line_edit->setText("");
	//		price_cos_line_edit->setText("");
	//		producer_cos_line_edit->setText("");
	//	}
	//	else {
	//		const auto lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

	//		if (lst.size() != 4)
	//			return;

	//		name_cos_line_edit->setText(lst.at(0).toLocal8Bit().constData());
	//		type_cos_line_edit->setText(lst.at(1).toLocal8Bit().constData());
	//		price_cos_line_edit->setText(lst.at(2).toLocal8Bit().constData());
	//		producer_cos_line_edit->setText(lst.at(3).toLocal8Bit().constData());

	//		last_selected_item_list_cos = lst_cumparaturi->selectedItems().at(0);
	//		last_selected_item_list_cos->setBackground(Qt::cyan);

	//		/*
	//		if (lbl_selected_item_list_cos != nullptr)
	//			lbl_selected_item_list_cos->close();

	//		lbl_selected_item_list_cos = new QLabel;
	//		lbl_selected_item_list_cos->setWindowIcon(product_icon);
	//		lbl_selected_item_list_cos->setWindowTitle("Produs selectat");
	//		lbl_selected_item_list_cos->setText("Nume: " + name_cos_line_edit->text() + "\nTip: " + type_cos_line_edit->text() + "\nPret: " + price_cos_line_edit->text() + "\nProducator: " + producer_cos_line_edit->text());
	//		lbl_selected_item_list_cos->setAlignment(Qt::AlignHCenter);
	//		lbl_selected_item_list_cos->show(); // lbl_selected_item_list_cos->exec();
	//		*/

	//		//if (dialog_selected_item_list_cos != nullptr)
	//		//	dialog_selected_item_list_cos->close();

	//		dialog_selected_item_list_cos = new QDialog;

	//		QVBoxLayout* main_ly = new QVBoxLayout;

	//		QFormLayout* form_ly = new QFormLayout;

	//		QLabel* name_lbl = new QLabel{ "Nume" };
	//		QLabel* type_lbl = new QLabel{ "Tip" };
	//		QLabel* price_lbl = new QLabel{ "Pret" };
	//		QLabel* producer_lbl = new QLabel{ "Producator" };

	//		QLineEdit* name_edt = new QLineEdit;
	//		QLineEdit* type_edt = new QLineEdit;
	//		QLineEdit* price_edt = new QLineEdit;
	//		QLineEdit* producer_edt = new QLineEdit;

	//		name_edt->setReadOnly(true);
	//		type_edt->setReadOnly(true);
	//		price_edt->setReadOnly(true);
	//		producer_edt->setReadOnly(true);

	//		name_edt->setText(name_cos_line_edit->text());
	//		type_edt->setText(type_cos_line_edit->text());
	//		price_edt->setText(price_cos_line_edit->text());
	//		producer_edt->setText(producer_cos_line_edit->text());

	//		form_ly->addRow(name_lbl, name_edt);
	//		form_ly->addRow(type_lbl, type_edt);
	//		form_ly->addRow(price_lbl, price_edt);
	//		form_ly->addRow(producer_lbl, producer_edt);

	//		main_ly->addLayout(form_ly);

	//		QPushButton* btn_close_dialog = new QPushButton("&Close");

	//		main_ly->addWidget(btn_close_dialog);

	//		QObject::connect(btn_close_dialog, &QPushButton::clicked, dialog_selected_item_list_cos, [&]() {
	//			dialog_selected_item_list_cos->close();
	//			});

	//		dialog_selected_item_list_cos->setLayout(main_ly);
	//		dialog_selected_item_list_cos->setModal(true);
	//		dialog_selected_item_list_cos->setWindowIcon(product_icon);
	//		dialog_selected_item_list_cos->setWindowTitle("Info produs selectat");

	//		dialog_selected_item_list_cos->show();
	//	}
	//	});

	//QObject::connect(tbl_cumparaturi, &QTableWidget::itemSelectionChanged, this, [&]() {
	//	auto sel{ tbl_cumparaturi->selectedItems() };

	//	if (sel.isEmpty()) // if (!sel.size())
	//	{
	//		name_cos_line_edit->setText("");
	//		type_cos_line_edit->setText("");
	//		price_cos_line_edit->setText("");
	//		producer_cos_line_edit->setText("");
	//	}
	//	else {
	//		const QStringList lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

	//		if (lst.size() != 4)
	//			return;

	//		name_cos_line_edit->setText(lst.at(0).toLocal8Bit().constData());
	//		type_cos_line_edit->setText(lst.at(1).toLocal8Bit().constData());
	//		price_cos_line_edit->setText(lst.at(2).toLocal8Bit().constData());
	//		producer_cos_line_edit->setText(lst.at(3).toLocal8Bit().constData());
	//	}
	//	});

	QObject::connect(lst_cumparaturi_view->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		const auto sel{ lst_cumparaturi_view->selectionModel()->selectedIndexes() };

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_cos_line_edit->setText("");
			type_cos_line_edit->setText("");
			price_cos_line_edit->setText("");
			producer_cos_line_edit->setText("");
		}
		else {
			const auto& selected_index{ sel.at(0) };

			const auto lst{ selected_index.data(Qt::UserRole).toStringList() };

			if (!lst.size())
			{
				lst_cumparaturi_model->setLastSelectedItem(-1);

				return;
			}

			lst_cumparaturi_model->setLastSelectedItem(selected_index.row());

			const QString qname{ lst.at(0) };     // const QString qname{ lst.at(0).toLocal8Bit().constData() };
			const QString qtype{ lst.at(1) };     // const QString qtype{ lst.at(1).toLocal8Bit().constData() };
			const QString qprice{ lst.at(2) };    // const QString qprice{ lst.at(2).toLocal8Bit().constData() };
			const QString qproducer{ lst.at(3) }; // const QString qproducer{ lst.at(3).toLocal8Bit().constData() };

			name_cos_line_edit->setText(qname);
			type_cos_line_edit->setText(qtype);
			price_cos_line_edit->setText(qprice);
			producer_cos_line_edit->setText(qproducer);

			dialog_selected_item_list_cos = new QDialog;

			QVBoxLayout* main_ly = new QVBoxLayout;

			QFormLayout* form_ly = new QFormLayout;

			QLabel* name_lbl = new QLabel{ "Nume" };
			QLabel* type_lbl = new QLabel{ "Tip" };
			QLabel* price_lbl = new QLabel{ "Pret" };
			QLabel* producer_lbl = new QLabel{ "Producator" };

			QLineEdit* name_edt = new QLineEdit;
			QLineEdit* type_edt = new QLineEdit;
			QLineEdit* price_edt = new QLineEdit;
			QLineEdit* producer_edt = new QLineEdit;

			name_edt->setReadOnly(true);
			type_edt->setReadOnly(true);
			price_edt->setReadOnly(true);
			producer_edt->setReadOnly(true);

			name_edt->setText(name_cos_line_edit->text().trimmed());
			type_edt->setText(type_cos_line_edit->text().trimmed());
			price_edt->setText(price_cos_line_edit->text().trimmed());
			producer_edt->setText(producer_cos_line_edit->text().trimmed());

			form_ly->addRow(name_lbl, name_edt);
			form_ly->addRow(type_lbl, type_edt);
			form_ly->addRow(price_lbl, price_edt);
			form_ly->addRow(producer_lbl, producer_edt);

			main_ly->addLayout(form_ly);

			QPushButton* btn_close_dialog = new QPushButton("&Close");

			main_ly->addWidget(btn_close_dialog);

			QObject::connect(btn_close_dialog, &QPushButton::clicked, dialog_selected_item_list_cos, [&]() {
				dialog_selected_item_list_cos->close();
				});

			dialog_selected_item_list_cos->setLayout(main_ly);
			dialog_selected_item_list_cos->setModal(true);
			dialog_selected_item_list_cos->setWindowIcon(item_shopping_cart_icon);
			dialog_selected_item_list_cos->setWindowTitle("Info produs selectat");

			dialog_selected_item_list_cos->show();
		}
		});


	QObject::connect(tbl_cumparaturi_view->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		const auto sel{ tbl_cumparaturi_view->selectionModel()->selectedIndexes() };

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_cos_line_edit->setText("");
			type_cos_line_edit->setText("");
			price_cos_line_edit->setText("");
			producer_cos_line_edit->setText("");
		}
		else {
			const auto selected_row{ sel.at(0).row() };

			const auto name_index{ tbl_cumparaturi_view->model()->index(selected_row, 0) };
			const auto type_index{ tbl_cumparaturi_view->model()->index(selected_row, 1) };
			const auto price_index{ tbl_cumparaturi_view->model()->index(selected_row, 2) };
			const auto producer_index{ tbl_cumparaturi_view->model()->index(selected_row, 3) };

			const auto name_cos_value{ tbl_cumparaturi_view->model()->data(name_index, Qt::DisplayRole).toString() };
			const auto type_cos_value{ tbl_cumparaturi_view->model()->data(type_index, Qt::DisplayRole).toString() };
			const auto price_cos_value{ tbl_cumparaturi_view->model()->data(price_index, Qt::DisplayRole).toString() };
			const auto producer_cos_value{ tbl_cumparaturi_view->model()->data(producer_index, Qt::DisplayRole).toString() };

			name_cos_line_edit->setText(name_cos_value);
			type_cos_line_edit->setText(type_cos_value);
			price_cos_line_edit->setText(price_cos_value);
			producer_cos_line_edit->setText(producer_cos_value);
		}
		});

	QObject::connect(btn_adaugare_cos, &QPushButton::clicked, this, [&]() {
		const auto name{ name_cos_line_edit->text().trimmed() };
		const auto producer{ producer_cos_line_edit->text().trimmed() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Adaugare produs in cosul de cumparaturi");

		try {
			srv.adaugareCos(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());
			//btn_golire_cos->setDisabled(false);
			//btn_stergere->setDisabled(false);

			msg->setText("[*]Adaugarea produsului in cos s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
			msg->setIcon(QMessageBox::Information);

			lst_cumparaturi_model->setVisible(true);
			tbl_cumparaturi_model->setVisible(true);
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			msg->setText(QString::fromStdString(ce.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_stergere_cos, &QPushButton::clicked, this, [&]() {
		const auto name{ name_cos_line_edit->text().trimmed() };
		const auto producer{ producer_cos_line_edit->text().trimmed() };
		
		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare stergere produs din cosul de cumparaturi");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Sunteti sigur ca doriti sa stergeti produsul cu numele \"" + name + "\" si producatorul \"" + producer + "\"din cos?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Stergere produs din cosul de cumparaturi");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				srv.eliminareProdusCos(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());

				msg->setText("[*]Stergerea produsului din cos s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.cantitateCos()));
				msg->setIcon(QMessageBox::Information);

				lst_cumparaturi_model->setVisible(true);
				tbl_cumparaturi_model->setVisible(true);

				name_cos_line_edit->setText("");
				type_cos_line_edit->setText("");
				price_cos_line_edit->setText("");
				producer_cos_line_edit->setText("");
			}
			catch (const CosException& ce) {
				qDebug() << QString::fromStdString(ce.getMessage());

				msg->setText(QString::fromStdString(ce.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}
			catch (const RepoException& re) {
				qDebug() << QString::fromStdString(re.getMessage());

				msg->setText(QString::fromStdString(re.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}
			catch (const ServiceException& se) {
				qDebug() << QString::fromStdString(se.getMessage());

				msg->setText(QString::fromStdString(se.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show();

			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_golire_cos, &QPushButton::clicked, this, [&]() {
		//last_selected_item_list_cos = nullptr;

		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare golire cos");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Sunteti sigur ca doriti sa goliti cosul de cumparaturi?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Golire cos de cumparaturi");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				srv.golireCos();
				//btn_golire_cos->setDisabled(true);
				//btn_stergere->setDisabled(true);

				//msg->setText("[*]Golirea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: 0");
				msg->setText("[*]Golirea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: 0\n[#]Numar total produse cos: 0");
				msg->setIcon(QMessageBox::Information);

				lst_cumparaturi_model->setVisible(true);
				tbl_cumparaturi_model->setVisible(true);
			}
			catch (const CosException& ce) {
				qDebug() << QString::fromStdString(ce.getMessage());

				msg->setText(QString::fromStdString(ce.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show();

			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_tiparire_cos, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		try {
			const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

			//addCumparaturiToList(lst_cumparaturi, lista_cumparaturi);
			//addCumparaturiToTable(tbl_cumparaturi, lista_cumparaturi);

			lst_cumparaturi_model->setVisible(true);
			tbl_cumparaturi_model->setVisible(true);
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			//addCumparaturiToList(lst_cumparaturi, vector<Product>());
			//addCumparaturiToTable(tbl_cumparaturi, vector<Product>());
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_generare_cos, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		const auto number{ no_prods->text().trimmed() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Generare cos de cumparaturi");

		try {
			srv.generareCos(number.toLocal8Bit().constData());
			//btn_golire_cos->setDisabled(false);
			//btn_stergere->setDisabled(false);

			msg->setText("[*]Generarea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
			msg->setIcon(QMessageBox::Information);

			lst_cumparaturi_model->setVisible(true);
			tbl_cumparaturi_model->setVisible(true);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(search_shopping_cart_combo_box, &QComboBox::currentIndexChanged, this, [&]() {
		if (!search_shopping_cart_combo_box->currentIndex())
			search_product_shopping_cart_line_edit->setPlaceholderText("Introduceti nume produs...");
		else if (search_shopping_cart_combo_box->currentIndex() == 1)
			search_product_shopping_cart_line_edit->setPlaceholderText("Introduceti tip produs...");
		else if (search_shopping_cart_combo_box->currentIndex() == 2)
			search_product_shopping_cart_line_edit->setPlaceholderText("Introduceti pret produs...");
		else // else if (search_shopping_cart_combo_box->currentIndex() == 3)
			search_product_shopping_cart_line_edit->setPlaceholderText("Introduceti producator produs...");
		});

	QObject::connect(btn_cautare_cos, &QPushButton::clicked, this, [&]() {
		const auto search_criteria{ search_shopping_cart_combo_box->currentText() };
		const auto search_text{ search_product_shopping_cart_line_edit->text().trimmed() };

		QString search_filter_qstring{ "" };
		
		if (!search_criteria.compare("Nume"))
			search_filter_qstring = "numele";
		else if (!search_criteria.compare("Tip"))
			search_filter_qstring = "tipul";
		else if (!search_criteria.compare("Pret"))
			search_filter_qstring = "pretul";
		else // else if (!search_criteria.compare("Producator"))
			search_filter_qstring = "producatorul";

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Cautare produs in cosul de cumparaturi");

		try {
			auto cont{ srv.searchProductInShoppingCart(search_criteria.toStdString(), search_text.toStdString()) };
			
			if (cont)
			{
				msg->setText("[*]Exista #" + QString::number(cont) + " produse cu " + search_filter_qstring + " \"" + search_text + "\" in cosul de cumparaturi!");
				msg->setIcon(QMessageBox::Information);
			}
			else
			{
				msg->setText("[*]Nu exista niciun produs cu " + search_filter_qstring + " \"" + search_text + "\" in cosul de cumparaturi!");
				msg->setIcon(QMessageBox::Warning);
			}
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			msg->setText(QString::fromStdString(ce.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();
		});

	QObject::connect(btn_export_cos, &QPushButton::clicked, this, [&]() {
		const auto filename{ fisier_export_line_edit->text().trimmed() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Export cos de cumparaturi");

		try {
			auto ok{ false };

			if (checkbox_export_fisier_csv->isChecked())
			{
				ok = true;
				srv.exportCos(filename.toLocal8Bit().constData(), "csv");
			}

			if (checkbox_export_fisier_html->isChecked())
			{
				ok = true;
				srv.exportCos(filename.toLocal8Bit().constData(), "html");
			}

			if (!ok)
			{
				msg->setText("Nu a fost selectat tipul fisierului de export!\nAlegeti tipul fisierului in care sa se faca exportul cosului de cumparaturi!");
				msg->setIcon(QMessageBox::Warning);
			}
			else
			{
				msg->setText("[*]Exportul in fisier s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
				msg->setIcon(QMessageBox::Information);
			}
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			msg->setText(QString::fromStdString(ce.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_clear_cos, &QPushButton::clicked, this, [&]() {
		name_cos_line_edit->setText("");
		type_cos_line_edit->setText("");
		price_cos_line_edit->setText("");
		producer_cos_line_edit->setText("");

		last_selected_item_list_cos = nullptr;

		//lst_cumparaturi->clear();
		//tbl_cumparaturi->clear();

		//tbl_cumparaturi->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

		lst_cumparaturi_model->setVisible(false);
		tbl_cumparaturi_model->setVisible(false);

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});

	QObject::connect(btn_close_cos, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare inchidere cos");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Sunteti sigur ca doriti sa inchideti fereastra curenta?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			cos_widget->close();
			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

		try {
			total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		}
		catch (const CosException&) {
			total_products_cos_line_edit->setText("0");
		}
		});
}

void GUI::addCumparaturiToList(QListWidget* lst, const vector<Product>& lista_cumparaturi)
{
	lst->clear();

	//total_price_cos_line_edit->setText("0");
	//total_products_cos_line_edit->setText("0");

	auto idx{ 0 };

	for (const auto& product : lista_cumparaturi)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Produsele existente in cosul de cumparaturi sunt:" };
			lst->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_name{ product.getName() };
		auto str_type{ product.getType() };
		auto str_price{ to_string(product.getPrice()) };
		auto str_producer{ product.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		lst->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Nu exista momentan produse adaugate in cosul de cumparaturi!" };
		lst->addItem(item);
	}
}

void GUI::addCumparaturiToTable(QTableWidget* tbl, const vector<Product>& lista_cumparaturi)
{
	tbl->clear();

	auto rows{ (int)lista_cumparaturi.size() };
	auto cols{ 4 };

	tbl->setRowCount(rows);
	tbl->setColumnCount(cols);

	tbl->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

	auto row{ 0 };

	for (const auto& product : lista_cumparaturi)
	{
		const auto q_str_name{ QString::fromStdString(product.getName()) };
		const auto q_str_type{ QString::fromStdString(product.getType()) };
		const auto q_str_price{ QString::fromStdString(to_string(product.getPrice())) };
		const auto q_str_producer{ QString::fromStdString(product.getProducer()) };

		const QStringList q_string_list{ q_str_name, q_str_type, q_str_price, q_str_producer };

		QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(product.getName()));
		name_item->setTextAlignment(Qt::AlignHCenter);
		name_item->setData(Qt::UserRole, QStringList(q_string_list));
		name_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(product.getType()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));
		type_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* price_item = new QTableWidgetItem(QString::number(product.getPrice()));
		price_item->setTextAlignment(Qt::AlignHCenter);
		price_item->setData(Qt::UserRole, QStringList(q_string_list));
		price_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* producer_item = new QTableWidgetItem(QString::fromStdString(product.getProducer()));
		producer_item->setTextAlignment(Qt::AlignHCenter);
		producer_item->setData(Qt::UserRole, QStringList(q_string_list));
		producer_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		tbl->setItem(row, 0, name_item);
		tbl->setItem(row, 1, type_item);
		tbl->setItem(row, 2, price_item);
		tbl->setItem(row, 3, producer_item);

		++row;
	}
}

void GUI::setShortcutsCosCumparaturi()
{
	QAction* action_btn_adaugare_cos = new QAction(cos_widget);
	action_btn_adaugare_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
	connect(action_btn_adaugare_cos, &QAction::triggered, btn_adaugare_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_adaugare_cos);

	QAction* action_btn_stergere_cos = new QAction(cos_widget);
	action_btn_stergere_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
	connect(action_btn_stergere_cos, &QAction::triggered, btn_stergere_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_stergere_cos);

	QAction* action_btn_golire_cos = new QAction(cos_widget);
	action_btn_golire_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	connect(action_btn_golire_cos, &QAction::triggered, btn_golire_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_golire_cos);

	QAction* action_btn_tiparire_cos = new QAction(cos_widget);
	action_btn_tiparire_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
	connect(action_btn_tiparire_cos, &QAction::triggered, btn_tiparire_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_tiparire_cos);

	QAction* action_btn_generare_cos = new QAction(cos_widget);
	action_btn_generare_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	connect(action_btn_generare_cos, &QAction::triggered, btn_generare_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_generare_cos);

	QAction* action_btn_cautare_cos = new QAction(cos_widget);
	action_btn_cautare_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
	connect(action_btn_cautare_cos, &QAction::triggered, btn_cautare_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_cautare_cos);

	QAction* action_btn_export_cos = new QAction(cos_widget);
	action_btn_export_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_E));
	connect(action_btn_export_cos, &QAction::triggered, btn_export_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_export_cos);

	QAction* action_btn_clear_cos = new QAction(cos_widget);
	action_btn_clear_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
	connect(action_btn_clear_cos, &QAction::triggered, btn_clear_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_clear_cos);

	QAction* action_btn_close_cos = new QAction(cos_widget);
	action_btn_close_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
	connect(action_btn_close_cos, &QAction::triggered, btn_close_cos, &QPushButton::click);

	cos_widget->addAction(action_btn_close_cos);
}

void GUI::setToolTipsCosCumparaturi()
{
	name_cos_line_edit->setToolTip("Nume (string) produs din cosul de cumparaturi");
	type_cos_line_edit->setToolTip("Tip (string) produs din cosul de cumparaturi");
	price_cos_line_edit->setToolTip("Pret (double) produs din cosul de cumparaturi");
	producer_cos_line_edit->setToolTip("Producator (string) produs din cosul de cumparaturi");

	total_price_cos_line_edit->setToolTip("Pretul total al produselor din cosul de cumparaturi");
	total_products_cos_line_edit->setToolTip("Numarul total de produse din cosul de cumparaturi");

	btn_adaugare_cos->setToolTip("Adaugare produs in cosul de cumparaturi");
	btn_stergere_cos->setToolTip("Stergere produs din cosul de cumparaturi");
	btn_golire_cos->setToolTip("Golire continut cos de cumparaturi");
	btn_tiparire_cos->setToolTip("Afisarea continutului cosului de cumparaturi sub forma de lista si tabel");

	btn_generare_cos->setToolTip("Generare produse pentru cosul de cumparaturi");
	
	btn_cautare_cos->setToolTip("Cautare produs in cosul de cumparaturi");

	btn_export_cos->setToolTip("Export continut cos de cumparaturi intr-un fisier (CSV sau/si HTML)");

	search_product_shopping_cart_line_edit->setToolTip("Nume/Tip/Pret/Producator dupa care sa se realizeze cautarea");

	search_shopping_cart_combo_box->setToolTip("Selectare optiune cautare produs in cosul de cumparaturi");

	checkbox_export_fisier_csv->setToolTip("Fisier Comma-Separated Values (deschidere cu Excel)");
	checkbox_export_fisier_html->setToolTip("Fisier HyperText Markup Language (deschidere in browser)");

	btn_clear_cos->setToolTip("Golire lista/tabel");
	btn_close_cos->setToolTip("Inchidere fereastra");

	fisier_export_line_edit->setToolTip("Numele fisierului in care sa se faca exportul cosului de cumparaturi");

	no_prods->setToolTip("Spin box care controleaza cate produse sa se genereze pentru cosul de cumparaturi");
}

void GUI::setPlaceholdersCosCumparaturi()
{
	name_cos_line_edit->setPlaceholderText("Introduceti numele produsului...");
	type_cos_line_edit->setPlaceholderText("Introduceti tipul produsului...");
	price_cos_line_edit->setPlaceholderText("Introduceti pretul produsului...");
	producer_cos_line_edit->setPlaceholderText("Introduceti producatorul produsului...");

	search_product_shopping_cart_line_edit->setPlaceholderText("Introduceti nume produs...");

	fisier_export_line_edit->setPlaceholderText("Introduceti numele fisierului...");
}

void GUI::setInitialStateCosCumparaturi()
{
	setShortcutsCosCumparaturi();
	setToolTipsCosCumparaturi();
	setPlaceholdersCosCumparaturi();

	last_selected_item_list_cos = new QListWidgetItem;

	try {
		const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

		//addCumparaturiToList(lst_cumparaturi, lista_cumparaturi);
		//addCumparaturiToTable(tbl_cumparaturi, lista_cumparaturi);
	}
	catch (const CosException&) {
		//addCumparaturiToList(lst_cumparaturi, vector<Product>());
		//addCumparaturiToTable(tbl_cumparaturi, vector<Product>());
	}

	total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

	try {
		total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
		//btn_golire_cos->setDisabled(false);
	}
	catch (const CosException&) {
		total_products_cos_line_edit->setText("0");
		//btn_golire_cos->setDisabled(true);
	}

	search_shopping_cart_combo_box->clear();

	search_shopping_cart_combo_box->addItem("Nume");
	search_shopping_cart_combo_box->addItem("Tip");
	search_shopping_cart_combo_box->addItem("Pret");
	search_shopping_cart_combo_box->addItem("Producator");
}

void GUI::initGuiCmp()
{
	try {
		lst_products_model = new ListModelProducts(srv.getAll());
		tbl_products_model = new TableModelProducts(srv.getAll());
	}
	catch (const RepoException&) {
		lst_products_model = new ListModelProducts(vector<Product>());
		tbl_products_model = new TableModelProducts(vector<Product>());
	}

	this->setWindowTitle("Magazin Virtual");
	this->setWindowIcon(store_icon);

	QHBoxLayout* main_ly = new QHBoxLayout;
	setLayout(main_ly);

	QVBoxLayout* left_ly = new QVBoxLayout;

	QLabel* lbl_products = new QLabel{ "Produse disponibile in stoc" };
	QFont font_lbl_products = lbl_products->font();
	font_lbl_products.setWeight(QFont::Bold);
	lbl_products->setFont(font_lbl_products);
	lbl_products->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(lbl_products);

	QHBoxLayout* products_show = new QHBoxLayout;

	// Var I
	//products_show->addWidget(lst_products);
	//products_show->addWidget(tbl_products);

	// Var II
	//products->addTab(lst_products, "Lista produse magazin");
	//products->addTab(tbl_products, "Tabel produse magazin");

	lst_products_view->setModel(lst_products_model);
	products_tab->addTab(lst_products_view, "Lista produse magazin");

	tbl_products_view->setModel(tbl_products_model);
	products_tab->addTab(tbl_products_view, "Tabel produse magazin");

	products_show->addWidget(products_tab);

	left_ly->addLayout(products_show);

	//left_ly->addStretch();

	QLabel* sort = new QLabel{ "Optiuni sortare" };
	QFont font_sort = sort->font();
	font_sort.setWeight(QFont::Bold);
	sort->setFont(font_sort);
	sort->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(sort);

	QLabel* lbl = new QLabel{ "Ordinea de sortare" };

	QHBoxLayout* sort_checkers_ly = new QHBoxLayout;

	sort_checkers_ly->addWidget(lbl);

	//sort_checkers_ly->addWidget(checbox_cresc);
	//sort_checkers_ly->addWidget(checkbox_descresc);

	sort_group->addButton(radio_btn_cresc);
	sort_group->addButton(radio_btn_descresc);

	sort_checkers_ly->addWidget(radio_btn_cresc);
	sort_checkers_ly->addWidget(radio_btn_descresc);

	left_ly->addLayout(sort_checkers_ly);

	QHBoxLayout* btns_sort_ly = new QHBoxLayout;

	sort_options_combo_box->addItem("Nume");
	sort_options_combo_box->addItem("Tip");
	sort_options_combo_box->addItem("Nume + tip");
	sort_options_combo_box->addItem("Pret");
	sort_options_combo_box->addItem("Producator");

	btns_sort_ly->addWidget(sort_options_combo_box);
	btns_sort_ly->addWidget(btn_sort);

	//btns_sort_ly->addWidget(btn_sort_name);
	//btns_sort_ly->addStretch();

	//btns_sort_ly->addWidget(btn_sort_name_plus_type);
	//btns_sort_ly->addStretch();

	//btns_sort_ly->addWidget(btn_sort_price);
	//btns_sort_ly->addStretch();

	left_ly->addLayout(btns_sort_ly);

	//left_ly->addStretch();

	QLabel* filter = new QLabel{ "Optiuni filtrare" };
	QFont font_filter = filter->font();
	font_filter.setWeight(QFont::Bold);
	filter->setFont(font_filter);
	filter->setAlignment(Qt::AlignHCenter);
	left_ly->addWidget(filter);

	QFormLayout* filter_form_ly = new QFormLayout;

	//QLabel* filter_crt_label = new QLabel{ "Nume/Pret/Producator filtrare" };
	//QLineEdit* filter_crt_line_edit = new QLineEdit;

	filter_form_ly->addRow(filter_crt_label, filter_crt_line_edit);

	left_ly->addLayout(filter_form_ly);

	QLabel* lbl_filter_price = new QLabel{ "Criteriu filtrare pret" };

	QHBoxLayout* filter_price_checkers_ly = new QHBoxLayout;

	filter_price_checkers_ly->addWidget(lbl_filter_price);

	//filter_price_checkers_ly->addWidget(checbox_less);
	//filter_price_checkers_ly->addWidget(checkbox_equal);
	//filter_price_checkers_ly->addWidget(checkbox_greater);

	filter_group->addButton(radio_btn_less);
	filter_group->addButton(radio_btn_equal);
	filter_group->addButton(radio_btn_greater);

	filter_price_checkers_ly->addWidget(radio_btn_less);
	filter_price_checkers_ly->addWidget(radio_btn_equal);
	filter_price_checkers_ly->addWidget(radio_btn_greater);

	left_ly->addLayout(filter_price_checkers_ly);

	QHBoxLayout* btns_filter_ly = new QHBoxLayout;

	filter_options_combo_box->addItem("Nume");
	filter_options_combo_box->addItem("Tip");
	filter_options_combo_box->addItem("Pret");
	filter_options_combo_box->addItem("Producator");

	btns_filter_ly->addWidget(filter_options_combo_box);
	btns_filter_ly->addWidget(btn_filter);

	//btns_filter_ly->addWidget(btn_filter_name);
	//btns_filter_ly->addStretch();

	//btns_filter_ly->addWidget(btn_filter_type);
	//btns_filter_ly->addStretch();

	//btns_filter_ly->addWidget(btn_filter_price);
	//btns_filter_ly->addStretch();

	left_ly->addLayout(btns_filter_ly);

	main_ly->addLayout(left_ly);

	// main_ly->addStretch();

	QVBoxLayout* right_ly = new QVBoxLayout;

	main_ly->addLayout(right_ly);

	QLabel* products_label = new QLabel{ "Informatii produs - stoc magazin" };
	QFont font_products_label = products_label->font();
	font_products_label.setWeight(QFont::Bold);
	products_label->setFont(font_products_label);
	products_label->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(products_label);

	QFormLayout* form_ly = new QFormLayout;

	QLabel* name_label = new QLabel{ "Nume" };
	QLabel* type_label = new QLabel{ "Tip" };
	QLabel* price_label = new QLabel{ "Pret" };
	QLabel* producer_label = new QLabel{ "Producator" };

	//QLineEdit* name_line_edit = new QLineEdit;
	//QLineEdit* type_line_edit = new QLineEdit;
	//QLineEdit* price_line_edit = new QLineEdit;
	//QLineEdit* producer_line_edit = new QLineEdit;

	form_ly->addRow(name_label, name_line_edit);
	form_ly->addRow(type_label, type_line_edit);
	form_ly->addRow(price_label, price_line_edit);
	form_ly->addRow(producer_label, producer_line_edit);

	right_ly->addLayout(form_ly);

	right_ly->addStretch();

	// Buton de pls pp
	QHBoxLayout* pp_ly = new QHBoxLayout;

	// Make the button "invisible"
	/*
	QBrush tb(Qt::transparent); // Transparent brush, solid pattern
	btn_pls_pp->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb)); // Set every color roles to the transparent brush
	btn_pls_pp->setFlat(true);

	pp_ly->addWidget(btn_pls_pp);

	right_ly->addLayout(pp_ly);

	right_ly->addStretch();
	*/

	QLabel* cumparaturi = new QLabel{ "Optiuni gestionare cos de cumparaturi" };
	QFont font_cumparaturi = cumparaturi->font();
	font_cumparaturi.setWeight(QFont::Bold);
	cumparaturi->setFont(font_cumparaturi);
	cumparaturi->setAlignment(Qt::AlignHCenter);
	right_ly->addWidget(cumparaturi);

	QHBoxLayout* cos_ly = new QHBoxLayout;

	QVBoxLayout* left_cos_ly = new QVBoxLayout;

	QHBoxLayout* lay = new QHBoxLayout;

	sld_value_cumparaturi_main->setMinimum(1);
	sld_value_cumparaturi_main->setMaximum(100);
	sld_value_cumparaturi_main->setValue(1);

	lay->addWidget(new QLabel{ "Numar produse generare" });
	lay->addWidget(sld_value_cumparaturi_main);

	left_cos_ly->addLayout(lay);

	QHBoxLayout* btns_cos_ly = new QHBoxLayout;

	btns_cos_ly->addWidget(btn_adaugare_cumparaturi_main);
	//btns_cos_ly->addStretch();

	btns_cos_ly->addWidget(btn_stergere_cumparaturi_main);
	//btns_cos_ly->addStretch();

	btns_cos_ly->addWidget(btn_generare_cumparaturi_main);
	//btns_cos_ly->addStretch();

	left_cos_ly->addLayout(btns_cos_ly);

	QHBoxLayout* btns_cos_ly_extra = new QHBoxLayout;

	btns_cos_ly_extra->addWidget(btn_CosCRUDGUI);
	//btns_cos_ly_extra->addStretch();

	btns_cos_ly_extra->addWidget(btn_CosReadOnlyGUI);
	//btns_cos_ly_extra->addStretch();

	left_cos_ly->addLayout(btns_cos_ly_extra);

	left_cos_ly->addWidget(btn_cos);
	//left_cos_ly->addStretch();

	cos_ly->addLayout(left_cos_ly);

	sld_cumparaturi_main->setMinimum(0);
	sld_cumparaturi_main->setMaximum(101);
	sld_cumparaturi_main->setValue(1);
	sld_cumparaturi_main->setOrientation(Qt::Vertical);

	cos_ly->addWidget(sld_cumparaturi_main);

	right_ly->addLayout(cos_ly);

	right_ly->addStretch();

	QLabel* general = new QLabel{ "Optiuni gestionare stoc magazin" };
	QFont font_general = general->font();
	font_general.setWeight(QFont::Bold);
	general->setFont(font_general);
	general->setAlignment(Qt::AlignHCenter);
	right_ly->addWidget(general);

	QHBoxLayout* btns_ly_1 = new QHBoxLayout;

	btns_ly_1->addWidget(btn_add);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_modify);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_delete);
	//btns_ly_1->addStretch();

	right_ly->addLayout(btns_ly_1);

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_search);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_type);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_info_types);
	//btns_ly_2->addStretch();

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_undo);
	//btns_ly_3->addStretch();

	btns_ly_3->addWidget(btn_redo);
	//btns_ly_3->addStretch();

	btns_ly_3->addWidget(btn_dbg);
	//btns_ly_3->addStretch();

	right_ly->addLayout(btns_ly_3);

	QHBoxLayout* btns_ly_4 = new QHBoxLayout;

	btns_ly_4->addWidget(btn_clear);
	//btns_ly_4->addStretch();

	btns_ly_4->addWidget(btn_exit);
	//btns_ly_4->addStretch();

	right_ly->addLayout(btns_ly_4);
}

void GUI::addDebug(const string& name, const string& type, const double& price, const string& producer, unsigned& cont) const
{
	try {
		srv.add(name, type, price, producer);
		++cont;
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());
	}
}

void GUI::sortProductsGUI(const string& sort_criterion)
{
	try {
		//const auto cresc{ checbox_cresc->isChecked() };
		//const auto descresc{ checkbox_descresc->isChecked() };

		const auto cresc{ radio_btn_cresc->isChecked() };
		const auto descresc{ radio_btn_descresc->isChecked() };

		if (!(cresc ^ descresc))
		{
			QMessageBox* msg{ new QMessageBox };
			msg->setWindowTitle("Sortare invalida");

			if (!(cresc && descresc))
			{
				msg->setText("Nu a fost selectata ordinea de sortare!\nAlegeti ordinea de sortare dorita bifand casuta corespunzatoare!");
				msg->setIcon(QMessageBox::Warning);
			}
			//else
			//	msg->setText("Au fost selectate ambele ordini de sortare!\nBifati o singura casuta din cele doua existente!");

			msg->show(); // msg->exec();

			return;
		}

		const auto crt{ sort_criterion };
		const auto ord{ ((cresc) ? ("c") : ("d")) }; // const auto ord{ ((cresc) ? ("C") : ("D")) };

		const auto& sorted_products{ srv.sortProducts(crt, ord) };

		//addProductsToList(sorted_products);
		//addProductsToTable(sorted_products);

		lst_products_model->setFilter(false);
		lst_products_model->setVisible(sorted_products, true);
		// lst_products_model->setDataChanged(sorted_products);

		tbl_products_model->setVisible(sorted_products, true);
		// tbl_products_model->setDataChanged(sorted_products);
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Exceptie in repozitoriu");
		msg->setIcon(QMessageBox::Critical);
		msg->setText(QString::fromStdString(re.getMessage()));
		msg->show(); // msg->exec();

		//addProductsToList(vector<Product>());
		//addProductsToTable(vector<Product>());
	}
}

bool GUI::filteredGUI(const vector<Product>& filtered_list, const Product& prod)
{
	for (const auto& filtered_prod : filtered_list)
		if (prod == filtered_prod)
			return true;

	return false;
}

void GUI::showFilteredList(const vector<Product>& filtered_list)
{
	addProductsToTable(filtered_list);

	lst_products->clear();

	auto idx{ 0 };

	/*vector<Product> prods;

	try {
		prods = srv.getAll();
	}
	catch (const RepoException&) {
		prods = vector<Product>();
	}*/

	const auto& prods{ srv.getAll() };

	for (const auto& prod : prods)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Lista de produse existente in magazin:" };
			lst_products->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		const auto& str_name{ prod.getName() };
		const auto& str_type{ prod.getType() };
		const auto str_price{ to_string(prod.getPrice()) };
		const auto& str_producer{ prod.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		if (filteredGUI(filtered_list, prod))
			item->setBackground(Qt::green);
		else
			item->setBackground(Qt::red);

		lst_products->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Nu exista momentan produse disponibile in stoc!" };
		lst_products->addItem(item);
	}
}

void GUI::filterProductsGUI(const string& criterion, const string& sgn)
{
	const auto& crt{ criterion };
	const auto& filter{ filter_crt_line_edit->text().trimmed() };
	const auto& sign{ sgn };

	try {
		//const auto& filtered_list{ srv.filterProducts(crt, filter.toLocal8Bit().constData(), sign) };
		const auto& filtered_list{ srv.filterProducts(crt, filter.toStdString(), sign) };

		//showFilteredList(filtered_list);

		lst_products_model->setFilter(true);
		lst_products_model->setFilteredList(filtered_list);
		tbl_products_model->setVisible(filtered_list, true);
	}
	catch (const RepoException& re) {
		qDebug() << QString::fromStdString(re.getMessage());

		QMessageBox* msg{ new QMessageBox };
		msg->setWindowTitle("Exceptie in repozitoriu");
		msg->setIcon(QMessageBox::Critical);
		msg->setText(QString::fromStdString(re.getMessage()));
		msg->show(); // msg->exec();
	}
	catch (const ServiceException& se) {
		qDebug() << QString::fromStdString(se.getMessage());

		QMessageBox* msg{ new QMessageBox };
		msg->setWindowTitle("Exceptie in service");
		msg->setIcon(QMessageBox::Critical);
		msg->setText(QString::fromStdString(se.getMessage())); // msg->setText("[X]Pretul de filtrare nu este un numar!");
		msg->show(); // msg->exec();
	}
}

QString pls_pp()
{
	QString pp{ "8" };

	mt19937 mt{ random_device{}() };
	uniform_int_distribution<> dist(0, 15);

	const int pp_size{ dist(mt) };

	for (auto i{ 0 }; i != pp_size; ++i, pp += "=");

	return pp + "D";
}

void GUI::initGuiCmpCosCRUDGUI()
{
	cosCRUDGUI_wdg = new QWidget;

	cosCRUDGUI_wdg->setWindowTitle("Fereastra CosCRUDGUI");
	cosCRUDGUI_wdg->setWindowIcon(cos_crud_icon);

	QVBoxLayout* main_ly = new QVBoxLayout;

	lst_cos_crud = new QListWidget;
	tbl_cos_crud = new QTableWidget;

	tab_cos_crud = new QTabWidget;

	tab_cos_crud->addTab(lst_cos_crud, "Lista produse cos");
	tab_cos_crud->addTab(tbl_cos_crud, "Tabel produse cos");

	main_ly->addWidget(tab_cos_crud);

	cosCRUDGUI_wdg->setLayout(main_ly);

	QVBoxLayout* btns_ly = new QVBoxLayout;

	QHBoxLayout* layout = new QHBoxLayout;

	QLabel* lbl = new QLabel{ "Numar produse generare" };

	spin_box_cos_crud = new QSpinBox;

	spin_box_cos_crud->setMinimum(1);
	spin_box_cos_crud->setMaximum(100);
	spin_box_cos_crud->setValue(1);

	btn_gen_cos_crud = new QPushButton{ "Generare cos de cumparaturi" };
	btn_gen_cos_crud = new QPushButton{ "Golire cos de cumparaturi" };

	layout->addWidget(lbl);
	//layout->addStretch();

	layout->addWidget(spin_box_cos_crud);
	//layout->addStretch();

	layout->addWidget(btn_gen_cos_crud);

	btns_ly->addLayout(layout);
	btns_ly->addWidget(btn_gol_cos_crud);

	main_ly->addLayout(btns_ly);

	cosCRUDGUI_wdg->show();
}

void GUI::connectSignalsCosCRUDGUI()
{
	QObject::connect(btn_gen_cos_crud, &QPushButton::clicked, this, [&]() {
		const auto val{ spin_box_cos_crud->value() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Generare cos de cumparaturi");

		try {
			srv.generareCos(to_string(val));
			//btn_golire_cos->setDisabled(false);
			//btn_stergere->setDisabled(false);
			//btn_gol->setDisabled(false);

			msg->setText("[*]Generarea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
			msg->setIcon(QMessageBox::Information);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();

		if (cos_widget != nullptr)
		{
			total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

			try {
				total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
			}
			catch (const CosException&) {
				total_products_cos_line_edit->setText("0");
			}
		}

		const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

		addCumparaturiToList(lst_cos_crud, lista_cumparaturi);
		addCumparaturiToTable(tbl_cos_crud, lista_cumparaturi);
		});

	QObject::connect(btn_gol_cos_crud, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare golire cos");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Sunteti sigur ca doriti sa stergeti toate produsele din cosul de cumparaturi?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Golire cos de cumparaturi");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				srv.golireCos();
				//btn_stergere->setDisabled(true);
				//btn_gol->setDisabled(true);

				//if (cos_widget != nullptr)
				//	btn_golire_cos->setDisabled(true);

				//msg->setText("[*]Toate produsele din cosul de cumparaturi au fost eliminate cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: 0");
				msg->setText("[*]Toate produsele din cosul de cumparaturi au fost eliminate cu succes!\n[$]Pret total: 0\n[#]Numar total produse cos: 0");
				msg->setIcon(QMessageBox::Information);
			}
			catch (const CosException& ce) {
				qDebug() << QString::fromStdString(ce.getMessage());

				msg->setText(QString::fromStdString(ce.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show();

			addCumparaturiToList(lst_cos_crud, vector<Product>());
			addCumparaturiToTable(tbl_cos_crud, vector<Product>());

			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		if (cos_widget != nullptr)
		{
			total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

			try {
				total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
			}
			catch (const CosException&) {
				total_products_cos_line_edit->setText("0");
			}
		}
		});
}

void GUI::setInitialStateCosCRUDGUI()
{
	try {
		const auto& lista_cumparaturi{ srv.getCosCumparaturi() };

		addCumparaturiToList(lst_cos_crud, lista_cumparaturi);
		addCumparaturiToTable(tbl_cos_crud, lista_cumparaturi);
		//btn_gol->setDisabled(false);
	}
	catch (const CosException&) {
		addCumparaturiToList(lst_cos_crud, vector<Product>());
		addCumparaturiToTable(tbl_cos_crud, vector<Product>());
		//btn_gol->setDisabled(true);
	}
}

void GUI::connectSignals()
{
	//QObject::connect(lst_products, &QListWidget::itemSelectionChanged, this, [&]() {
	//	auto sel{ lst_products->selectedItems() };

	//	if (last_selected_item_list != nullptr)
	//		last_selected_item_list->setBackground(Qt::white);

	//	if (sel.isEmpty()) // if (!sel.size())
	//	{
	//		name_line_edit->setText("");
	//		type_line_edit->setText("");
	//		price_line_edit->setText("");
	//		producer_line_edit->setText("");
	//	}
	//	else {
	//		const auto lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

	//		if (lst.size() != 4)
	//			return;

	//		name_line_edit->setText(lst.at(0).toLocal8Bit().constData());
	//		type_line_edit->setText(lst.at(1).toLocal8Bit().constData());
	//		price_line_edit->setText(lst.at(2).toLocal8Bit().constData());
	//		producer_line_edit->setText(lst.at(3).toLocal8Bit().constData());

	//		lst_products->selectedItems().at(0)->setBackground(Qt::magenta);
	//		last_selected_item_list = lst_products->selectedItems().at(0);

	//		/*
	//		if (lbl_selected_item_list != nullptr)
	//			lbl_selected_item_list->close();

	//		lbl_selected_item_list = new QLabel;
	//		lbl_selected_item_list->setWindowIcon(product_icon);
	//		lbl_selected_item_list->setWindowTitle("Produs selectat");
	//		lbl_selected_item_list->setText("Nume: " + name_line_edit->text() + "\nTip: " + type_line_edit->text() + "\nPret: " + price_line_edit->text() + "\nProducator: " + producer_line_edit->text());
	//		lbl_selected_item_list->setAlignment(Qt::AlignHCenter);
	//		lbl_selected_item_list->show(); // lbl_selected_item_list->exec();
	//		*/

	//		//if (dialog_selected_item_list != nullptr)
	//		//	dialog_selected_item_list->close();

	//		dialog_selected_item_list = new QDialog;

	//		QVBoxLayout* main_ly = new QVBoxLayout;

	//		QFormLayout* form_ly = new QFormLayout;

	//		QLabel* name_lbl = new QLabel{ "Nume" };
	//		QLabel* type_lbl = new QLabel{ "Tip" };
	//		QLabel* price_lbl = new QLabel{ "Pret" };
	//		QLabel* producer_lbl = new QLabel{ "Producator" };

	//		QLineEdit* name_edt = new QLineEdit;
	//		QLineEdit* type_edt = new QLineEdit;
	//		QLineEdit* price_edt = new QLineEdit;
	//		QLineEdit* producer_edt = new QLineEdit;

	//		name_edt->setReadOnly(true);
	//		type_edt->setReadOnly(true);
	//		price_edt->setReadOnly(true);
	//		producer_edt->setReadOnly(true);

	//		name_edt->setText(name_line_edit->text());
	//		type_edt->setText(type_line_edit->text());
	//		price_edt->setText(price_line_edit->text());
	//		producer_edt->setText(producer_line_edit->text());

	//		form_ly->addRow(name_lbl, name_edt);
	//		form_ly->addRow(type_lbl, type_edt);
	//		form_ly->addRow(price_lbl, price_edt);
	//		form_ly->addRow(producer_lbl, producer_edt);

	//		main_ly->addLayout(form_ly);

	//		QPushButton* btn_close_dialog = new QPushButton("&Close");

	//		main_ly->addWidget(btn_close_dialog);

	//		QObject::connect(btn_close_dialog, &QPushButton::clicked, dialog_selected_item_list, [&]() {
	//			dialog_selected_item_list->close();
	//			});

	//		dialog_selected_item_list->setLayout(main_ly);
	//		dialog_selected_item_list->setModal(true);
	//		dialog_selected_item_list->setWindowIcon(product_icon);
	//		dialog_selected_item_list->setWindowTitle("Info produs selectat");

	//		dialog_selected_item_list->show();
	//	}
	//	});

	//QObject::connect(tbl_products, &QTableWidget::itemSelectionChanged, this, [&]() {
	//	auto sel{ tbl_products->selectedItems() };

	//	if (sel.isEmpty()) // if (!sel.size())
	//	{
	//		name_line_edit->setText("");
	//		type_line_edit->setText("");
	//		price_line_edit->setText("");
	//		producer_line_edit->setText("");
	//	}
	//	else {
	//		const QStringList lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

	//		if (lst.size() != 4)
	//			return;

	//		name_line_edit->setText(lst.at(0).toLocal8Bit().constData());
	//		type_line_edit->setText(lst.at(1).toLocal8Bit().constData());
	//		price_line_edit->setText(lst.at(2).toLocal8Bit().constData());
	//		producer_line_edit->setText(lst.at(3).toLocal8Bit().constData());
	//	}
	//	});

	QObject::connect(lst_products_view->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		const auto sel{ lst_products_view->selectionModel()->selectedIndexes() };

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_line_edit->setText("");
			type_line_edit->setText("");
			price_line_edit->setText("");
			producer_line_edit->setText("");
		}
		else {
			const auto& selected_index{ sel.at(0) };

			const auto lst{ selected_index.data(Qt::UserRole).toStringList() };

			if (!lst.size())
			{
				lst_products_model->setLastSelectedItem(-1);

				return;
			}

			lst_products_model->setLastSelectedItem(selected_index.row());

			const QString qname{ lst.at(0) };     // const QString qname{ lst.at(0).toLocal8Bit().constData() };
			const QString qtype{ lst.at(1) };     // const QString qtype{ lst.at(1).toLocal8Bit().constData() };
			const QString qprice{ lst.at(2) };    // const QString qprice{ lst.at(2).toLocal8Bit().constData() };
			const QString qproducer{ lst.at(3) }; // const QString qproducer{ lst.at(3).toLocal8Bit().constData() };

			name_line_edit->setText(qname);
			type_line_edit->setText(qtype);
			price_line_edit->setText(qprice);
			producer_line_edit->setText(qproducer);

			dialog_selected_item_list = new QDialog;

			QVBoxLayout* main_ly = new QVBoxLayout;

			QFormLayout* form_ly = new QFormLayout;

			QLabel* name_lbl = new QLabel{ "Nume" };
			QLabel* type_lbl = new QLabel{ "Tip" };
			QLabel* price_lbl = new QLabel{ "Pret" };
			QLabel* producer_lbl = new QLabel{ "Producator" };

			QLineEdit* name_edt = new QLineEdit;
			QLineEdit* type_edt = new QLineEdit;
			QLineEdit* price_edt = new QLineEdit;
			QLineEdit* producer_edt = new QLineEdit;

			name_edt->setReadOnly(true);
			type_edt->setReadOnly(true);
			price_edt->setReadOnly(true);
			producer_edt->setReadOnly(true);

			name_edt->setText(name_line_edit->text().trimmed());
			type_edt->setText(type_line_edit->text().trimmed());
			price_edt->setText(price_line_edit->text().trimmed());
			producer_edt->setText(producer_line_edit->text().trimmed());

			form_ly->addRow(name_lbl, name_edt);
			form_ly->addRow(type_lbl, type_edt);
			form_ly->addRow(price_lbl, price_edt);
			form_ly->addRow(producer_lbl, producer_edt);

			main_ly->addLayout(form_ly);

			QPushButton* btn_close_dialog = new QPushButton("&Close");

			main_ly->addWidget(btn_close_dialog);

			QObject::connect(btn_close_dialog, &QPushButton::clicked, dialog_selected_item_list, [&]() {
				dialog_selected_item_list->close();
				});

			dialog_selected_item_list->setLayout(main_ly);
			dialog_selected_item_list->setModal(true);
			dialog_selected_item_list->setWindowIcon(product_icon);
			dialog_selected_item_list->setWindowTitle("Info produs selectat");

			dialog_selected_item_list->show();
		}
		});

	QObject::connect(tbl_products_view->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		const auto sel{ tbl_products_view->selectionModel()->selectedIndexes() };

		if (sel.isEmpty()) // if (!sel.size())
		{
			name_line_edit->setText("");
			type_line_edit->setText("");
			price_line_edit->setText("");
			producer_line_edit->setText("");
		}
		else {
			const auto selected_row{ sel.at(0).row() };

			const auto name_index{ tbl_products_view->model()->index(selected_row, 0) };
			const auto type_index{ tbl_products_view->model()->index(selected_row, 1) };
			const auto price_index{ tbl_products_view->model()->index(selected_row, 2) };
			const auto producer_index{ tbl_products_view->model()->index(selected_row, 3) };

			const auto name_cos_value{ tbl_products_view->model()->data(name_index, Qt::DisplayRole).toString() };
			const auto type_cos_value{ tbl_products_view->model()->data(type_index, Qt::DisplayRole).toString() };
			const auto price_cos_value{ tbl_products_view->model()->data(price_index, Qt::DisplayRole).toString() };
			const auto producer_cos_value{ tbl_products_view->model()->data(producer_index, Qt::DisplayRole).toString() };

			name_line_edit->setText(name_cos_value);
			type_line_edit->setText(type_cos_value);
			price_line_edit->setText(price_cos_value);
			producer_line_edit->setText(producer_cos_value);
		}
		});

	QObject::connect(sld_value_cumparaturi_main, &QSpinBox::valueChanged, this, [&]() {
		// Slider
		sld_cumparaturi_main->setValue(sld_value_cumparaturi_main->value());
		});

	QObject::connect(sld_cumparaturi_main, &QSlider::sliderMoved, this, [&]() {
		// SpinBox
		sld_value_cumparaturi_main->setValue(sld_cumparaturi_main->value());
		});

	QObject::connect(btn_adaugare_cumparaturi_main, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		const auto name{ name_line_edit->text().trimmed() };
		const auto producer{ producer_line_edit->text().trimmed() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Adaugare produs in cosul de cumparaturi");

		try {
			srv.adaugareCos(name.toStdString(), producer.toStdString());
			//btn_golire_cos->setDisabled(false);
			//btn_stergere->setDisabled(false);

			msg->setText("[*]Adaugarea produsului in cos s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
			msg->setIcon(QMessageBox::Information);
		}
		catch (const CosException& ce) {
			qDebug() << QString::fromStdString(ce.getMessage());

			msg->setText(QString::fromStdString(ce.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();

		if (cos_widget != nullptr)
		{
			total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

			try {
				total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
			}
			catch (const CosException&) {
				total_products_cos_line_edit->setText("0");
			}
		}
		});

	QObject::connect(btn_stergere_cumparaturi_main, &QPushButton::clicked, this, [&]() {
		//last_selected_item_list_cos = nullptr;

		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare golire cos");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Sunteti sigur ca doriti sa stergeti toate produsele din cosul de cumparaturi?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Golire produse din cosul de cumparaturi");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				srv.golireCos();
				//btn_stergere->setDisabled(true);

				//if(cos_widget != nullptr)
				//	btn_golire_cos->setDisabled(true);

				//msg->setText("[*]Toate produsele din cosul de cumparaturi au fost eliminate cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: 0");
				msg->setText("[*]Toate produsele din cosul de cumparaturi au fost eliminate cu succes!\n[$]Pret total: 0\n[#]Numar total produse cos: 0");
				msg->setIcon(QMessageBox::Information);
			}
			catch (const CosException& ce) {
				qDebug() << QString::fromStdString(ce.getMessage());

				msg->setText(QString::fromStdString(ce.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show();

			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		if (cos_widget != nullptr)
		{
			total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

			try {
				total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
			}
			catch (const CosException&) {
				total_products_cos_line_edit->setText("0");
			}
		}
		});

	QObject::connect(btn_generare_cumparaturi_main, &QPushButton::clicked, this, [&]() {
		last_selected_item_list_cos = nullptr;

		// const auto val{ sld_value_cumparaturi_main->value() };
		const auto val{ sld_value_cumparaturi_main->value() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Generare cos de cumparaturi");

		try {
			srv.generareCos(to_string(val));
			//btn_golire_cos->setDisabled(false);
			//btn_stergere->setDisabled(false);

			msg->setText("[*]Generarea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: " + QString::number(srv.getCosCumparaturi().size()));
			msg->setIcon(QMessageBox::Information);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show();

		if (cos_widget != nullptr)
		{
			total_price_cos_line_edit->setText(QString::number(srv.totalCos()));

			try {
				total_products_cos_line_edit->setText(QString::number(srv.getCosCumparaturi().size()));
			}
			catch (const CosException&) {
				total_products_cos_line_edit->setText("0");
			}
		}
		});
	
	QObject::connect(btn_CosCRUDGUI, &QPushButton::clicked, this, [&]() {
		/*
		// Initialize GUI components
		initGuiCmpCosCRUDGUI();

		// Connect signals and slots
		connectSignalsCosCRUDGUI();

		// Set initial GUI state
		setInitialStateCosCRUDGUI();
		*/

		CosCRUDGUI* cosCRUDGUI = new CosCRUDGUI{ srv.getCosSrv() };

		/*
		mt19937 mt{ random_device{}() };
		const uniform_int_distribution<> dist_x(0, 1000);
		const uniform_int_distribution<> dist_y(0, 400);

		const auto ax{ dist_x(mt) };
		const auto ay{ dist_y(mt) };

		cosCRUDGUI->move(ax, ay);
		*/

		cosCRUDGUI->show();
		});

	QObject::connect(btn_CosReadOnlyGUI, &QPushButton::clicked, this, [&]() {
		CosReadOnlyGUI* cosReadOnlyGUI_wdg = new CosReadOnlyGUI{ srv.getCosSrv() };

		/*
		mt19937 mt{ random_device{}() };
		const uniform_int_distribution<> dist_x(0, 900);
		const uniform_int_distribution<> dist_y(0, 300);

		const auto ax{ dist_x(mt) };
		const auto ay{ dist_y(mt) };

		cosReadOnlyGUI_wdg->move(ax, ay);
		*/

		cosReadOnlyGUI_wdg->show();
		});

	QObject::connect(btn_add, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto name{ name_line_edit->text().trimmed() };
		const auto type{ type_line_edit->text().trimmed() };
		const auto price{ price_line_edit->text().trimmed() };
		const auto producer{ producer_line_edit->text().trimmed() };

		int ret;

		if (name.isEmpty() || type.isEmpty() || price.isEmpty() || producer.isEmpty())
			ret = QMessageBox::Yes;
		else
		{
			QMessageBox msg_box;
			msg_box.setWindowTitle("Confirmare adaugare produs");
			msg_box.setIcon(QMessageBox::Question);
			msg_box.setText("Operatia de adaugare in curs de procesare...");
			msg_box.setInformativeText("Sunteti sigur ca doriti sa adaugati produsul cu numele \"" + name + "\", tipul\"" + type + "\", pretul \"" + price + "\" si producatorul \"" + producer + "\"?");
			msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			msg_box.setDefaultButton(QMessageBox::Yes);

			ret = msg_box.exec();
		}

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Adaugare produs in stocul magazinului");

		double pr;

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				//srv.verifyIfDouble(price.toLocal8Bit().constData());
				srv.verifyIfDouble(price.toStdString());
			}
			catch (const ServiceException& se) {
				msg->setText(QString::fromStdString(se.getMessage()));
				msg->setIcon(QMessageBox::Critical);
				msg->show();

				return;
			}

			//const auto pr{ strtod(price.toLocal8Bit().constData(), nullptr) };
			pr = stod(price.toStdString(), nullptr);

			try {
				//srv.add(name.toLocal8Bit().constData(), type.toLocal8Bit().constData(), pr, producer.toLocal8Bit().constData());
				srv.add(name.toStdString(), type.toStdString(), pr, producer.toStdString());

				++number_of_undo;
				if (!btn_undo->isEnabled())
					btn_undo->setDisabled(false);

				msg->setText("[*]Adaugarea s-a realizat cu succes!");
				msg->setIcon(QMessageBox::Information);

				btn_modify->setEnabled(true); // btn_modify->setDisabled(false);
				btn_delete->setEnabled(true); // btn_delete->setDisabled(false);
				btn_search->setEnabled(true); // btn_search->setDisabled(false);

				lst_products_model->setFilter(false);
				lst_products_model->setVisible(srv.getAll(), true);
				tbl_products_model->setVisible(srv.getAll(), true);
			}
			catch (const ProductException& pe) {
				qDebug() << QString::fromStdString(pe.getMessage());

				msg->setText(QString::fromStdString(pe.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}
			catch (const RepoException& re) {
				qDebug() << QString::fromStdString(re.getMessage());

				msg->setText(QString::fromStdString(re.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show();

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_modify, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto name{ name_line_edit->text().trimmed() };
		const auto type{ type_line_edit->text().trimmed() };
		const auto price{ price_line_edit->text().trimmed() };
		const auto producer{ producer_line_edit->text().trimmed() };

		int ret;

		if (name.isEmpty() || producer.isEmpty())
			ret = QMessageBox::Yes;
		else
		{
			QMessageBox msg_box;
			msg_box.setWindowTitle("Confirmare modificare produs");
			msg_box.setIcon(QMessageBox::Question);
			msg_box.setText("Operatia de modificare in curs de procesare...");
			msg_box.setInformativeText("Sunteti sigur ca doriti sa modificati produsul cu numele \"" + name + "\" si producatorul \"" + producer + "\"?");
			msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			msg_box.setDefaultButton(QMessageBox::Yes);

			ret = msg_box.exec();
		}

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Modificare produs existent in stocul magazinului");

		double pr;

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				//srv.verifyIfDouble(price.toLocal8Bit().constData());
				srv.verifyIfDouble(price.toStdString());
			}
			catch (const ServiceException& se) {
				msg->setText(QString::fromStdString(se.getMessage()));
				msg->setIcon(QMessageBox::Critical);
				msg->show();

				return;
			}

			//const auto pr{ strtod(price.toLocal8Bit().constData(), nullptr) };
			pr = stod(price.toStdString(), nullptr);

			try {
				//srv.modify(name.toLocal8Bit().constData(), type.toLocal8Bit().constData(), pr, producer.toLocal8Bit().constData());
				srv.modify(name.toStdString(), type.toStdString(), pr, producer.toStdString());

				++number_of_undo;
				if (!btn_undo->isEnabled())
					btn_undo->setDisabled(false);

				msg->setText("[*]Modificarea s-a realizat cu succes!");
				msg->setIcon(QMessageBox::Information);

				lst_products_model->setFilter(false);
				lst_products_model->setVisible(srv.getAll(), true);
				tbl_products_model->setVisible(srv.getAll(), true);
			}
			catch (const ProductException& pe) {
				qDebug() << QString::fromStdString(pe.getMessage());

				msg->setText(QString::fromStdString(pe.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}
			catch (const RepoException& re) {
				qDebug() << QString::fromStdString(re.getMessage());

				msg->setText(QString::fromStdString(re.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show(); // msg->exec();

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_delete, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto name{ name_line_edit->text().trimmed() };
		const auto producer{ producer_line_edit->text().trimmed() };

		int ret;

		if (name.isEmpty() || producer.isEmpty())
			ret = QMessageBox::Yes;
		else
		{
			QMessageBox msg_box;
			msg_box.setWindowTitle("Confirmare stergere produs");
			msg_box.setIcon(QMessageBox::Question);
			msg_box.setText("Operatia de stergere in curs de procesare...");
			msg_box.setInformativeText("Sunteti sigur ca doriti sa stergeti produsul cu numele \"" + name + "\" si producatorul \"" + producer + "\"?");
			msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			msg_box.setDefaultButton(QMessageBox::Yes);

			ret = msg_box.exec();
		}

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Stergere produs existent din stocul magazinului");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				//srv.del(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData());
				srv.del(name.toStdString(), producer.toStdString());

				++number_of_undo;
				if (!btn_undo->isEnabled())
					btn_undo->setDisabled(false);

				msg->setText("[*]Stergerea s-a realizat cu succes!");
				msg->setIcon(QMessageBox::Information);

				if (!srv.numberOfProducts())
				{
					btn_modify->setEnabled(false); // btn_modify->setDisabled(true);
					btn_delete->setEnabled(false); // btn_delete->setDisabled(true);
					btn_search->setEnabled(false); // btn_search->setDisabled(true);
				}

				name_line_edit->setText("");
				type_line_edit->setText("");
				price_line_edit->setText("");
				producer_line_edit->setText("");

				lst_products_model->setFilter(false);

				try {
					lst_products_model->setVisible(srv.getAll(), true);
					tbl_products_model->setVisible(srv.getAll(), true);
				}
				catch (const RepoException&) {
					lst_products_model->setVisible(vector<Product>(), true);
					tbl_products_model->setVisible(vector<Product>(), true);
				}
			}
			catch (const ServiceException& se) {
				qDebug() << QString::fromStdString(se.getMessage());

				msg->setText(QString::fromStdString(se.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}
			catch (const RepoException& re) {
				qDebug() << QString::fromStdString(re.getMessage());

				msg->setText(QString::fromStdString(re.getMessage()));
				msg->setIcon(QMessageBox::Critical);
			}

			msg->show(); // msg->exec();

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_search, &QPushButton::clicked, this, [&]() {
		const auto name{ name_line_edit->text().trimmed() };
		const auto producer{ producer_line_edit->text().trimmed() };

		QMessageBox* msg = new QMessageBox;
		msg->setWindowTitle("Cautare produs in stocul magazinului");

		try {
			//const auto& p{ srv.search(name.toLocal8Bit().constData(), producer.toLocal8Bit().constData()) };
			const auto& p{ srv.search(name.toStdString(), producer.toStdString()) };

			msg->setText("Produsul cautat este:\n\nNume: "
				+ QString::fromStdString(p.getName()) + "\nTip: "
				+ QString::fromStdString(p.getType()) + "\nPret: "
				+ QString::number(p.getPrice()) + "\nProducator: "
				+ QString::fromStdString(p.getProducer()));
			msg->setIcon(QMessageBox::Information);

			type_line_edit->setText(QString::fromStdString(p.getType()));
			price_line_edit->setText(QString::number(p.getPrice()));
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
			msg->setIcon(QMessageBox::Critical);
		}

		msg->show(); // msg->exec();
		});

	QObject::connect(btn_sort, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		const auto option{ sort_options_combo_box->currentText() }; // const QString option{ sort_options_combo_box->currentText() };

		if (option == "Nume")
			sortProductsGUI("1");
		else if (option == "Pret")
			sortProductsGUI("2");
		else if (option == "Nume + tip") // else
			sortProductsGUI("3");
		else if (option == "Tip")
			sortProductsGUI("4");
		else if (option == "Producator")
			sortProductsGUI("5");
		});

	QObject::connect(btn_filter, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		if (!filter_crt_line_edit->text().trimmed().length())
		{
			QMessageBox* msg = new QMessageBox;
			msg->setWindowTitle("Filtru invalid");
			
			msg->setText("Filtrul introdus este vid (nu este un filtru valid)!");
			msg->setIcon(QMessageBox::Warning);

			msg->show(); // msg->exec();

			return;
		}

		const auto option{ filter_options_combo_box->currentText() }; // const QString option{ filter_options_combo_box->currentText() };

		if (option == "Pret")
		{
			string sgn;

			//const auto less{ checbox_less->isChecked() };
			//const auto equal{ checkbox_equal->isChecked() };
			//const auto greater{ checkbox_greater->isChecked() };

			const auto less{ radio_btn_less->isChecked() };
			const auto equal{ radio_btn_equal->isChecked() };
			const auto greater{ radio_btn_greater->isChecked() };

			const auto sum{ less + equal + greater };

			if (sum != 1)
			{
				QMessageBox* msg = new QMessageBox;
				msg->setWindowTitle("Filtrare pret invalida");

				if (!sum)
				{
					msg->setText("Nu a fost selectat niciun simbol de inegalitate!\nBifati o casuta la alegere!");
					msg->setIcon(QMessageBox::Warning);
				}
				//else
				//	msg->setText("Au fost selectate prea multe simboluri de inegalitate!\nBifati o singura casuta!");

				msg->show(); // msg->exec();

				return;
			}

			//if (checbox_less->isChecked())
			//	sgn = "<";
			//else if (checkbox_equal->isChecked())
			//	sgn = "=";
			//else
			//	sgn = ">";

			if (radio_btn_less->isChecked())
				sgn = "<";
			else if (radio_btn_equal->isChecked())
				sgn = "=";
			else if (radio_btn_greater->isChecked())
				sgn = ">";

			filterProductsGUI("1", sgn);
		}
		else if (option == "Nume")
			filterProductsGUI("2", "");
		else if (option == "Producator")
			filterProductsGUI("3", "");
		else if (option == "Tip")
			filterProductsGUI("4", "");
		});

	QObject::connect(btn_type, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		try {
			const auto& products{ srv.getAll() };

			//addProductsToList(products);
			//addProductsToTable(products);

			lst_products_model->setFilter(false);
			lst_products_model->setVisible(srv.getAll(), true);
			tbl_products_model->setVisible(srv.getAll(), true);
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			//addProductsToList(vector<Product>());
			//addProductsToTable(vector<Product>());
		}
		});

	QObject::connect(btn_info_types, &QPushButton::clicked, this, [&]() {
		if (tipuri_produse_widget != nullptr && tipuri_produse_widget->isEnabled())
		{
			tipuri_produse_widget->setDisabled(true); // tipuri_produse_widget->setEnabled(false);
			tipuri_produse_widget->close();
		}

		if (hist_widget != nullptr && hist_widget->isEnabled())
		{
			hist_widget->setDisabled(true); // hist_widget->setEnabled(false);
			hist_widget->close();
		}

		if (percentage_hist_widget != nullptr && percentage_hist_widget->isEnabled())
		{
			percentage_hist_widget->setDisabled(true); // percentage_hist_widget->setEnabled(false);
			percentage_hist_widget->close();
		}

		try {
			const auto& types_map{ srv.countType() };

			hist_widget = new Histogram{ srv };
			hist_widget->show();

			percentage_hist_widget = new PercentageHistogram{ srv };
			percentage_hist_widget->show();
			
			if (!database_repo_flag)
			{
				tipuri_produse_widget = new TipuriProduseWidget{ srv };
				tipuri_produse_widget->show();
			}
			else
			{
				hist_widget->setFixedHeight(hist_widget->height());
				hist_widget->setFixedWidth(hist_widget->width());

				percentage_hist_widget->setFixedHeight(percentage_hist_widget->height());
				percentage_hist_widget->setFixedWidth(percentage_hist_widget->width());
			}
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			QMessageBox* msg_box = new QMessageBox;
			msg_box->setWindowTitle("Exceptie in repozitoriu");
			msg_box->setIcon(QMessageBox::Critical);
			msg_box->setText("[!]Nu exista produse in magazin!");
			msg_box->show();
		}
		});

	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare operatie de undo");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Operatia de undo in curs de procesare...");
		msg_box.setInformativeText("Sunteti sigur ca doriti sa continuati?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::Yes);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg_dbg = new QMessageBox;
		msg_dbg->setWindowTitle("Operatie de undo");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				msg_dbg->setText(QString::fromStdString(srv.undo()));
				msg_dbg->setIcon(QMessageBox::Information);

				++number_of_redo;
				if (!btn_redo->isEnabled())
					btn_redo->setDisabled(false);

				--number_of_undo;
				if (!number_of_undo)
					btn_undo->setDisabled(true);

				if (!srv.numberOfProducts())
				{
					btn_modify->setEnabled(false); // btn_modify->setDisabled(true);
					btn_delete->setEnabled(false); // btn_delete->setDisabled(true);
					btn_search->setEnabled(false); // btn_search->setDisabled(true);
				}
				else
				{
					btn_modify->setEnabled(true); // btn_modify->setDisabled(false);
					btn_delete->setEnabled(true); // btn_delete->setDisabled(false);
					btn_search->setEnabled(true); // btn_search->setDisabled(false);
				}

				lst_products_model->setFilter(false);

				try {
					lst_products_model->setVisible(srv.getAll(), true);
					tbl_products_model->setVisible(srv.getAll(), true);
				}
				catch (const RepoException&) {
					lst_products_model->setVisible(vector<Product>(), true);
					tbl_products_model->setVisible(vector<Product>(), true);
				}
			}
			catch (const ServiceException& se) {
				qDebug() << QString::fromStdString(se.getMessage());

				btn_undo->setDisabled(true);

				msg_dbg->setText(QString::fromStdString(se.getMessage()));
				msg_dbg->setIcon(QMessageBox::Critical);
			}

			msg_dbg->exec();

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_redo, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare operatie de redo");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Operatia de redo in curs de procesare...");
		msg_box.setInformativeText("Sunteti sigur ca doriti sa continuati?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::Yes);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg_dbg = new QMessageBox;
		msg_dbg->setWindowTitle("Operatie de redo");

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				msg_dbg->setText(QString::fromStdString(srv.redo()));
				msg_dbg->setIcon(QMessageBox::Information);

				--number_of_redo;
				if (!number_of_redo)
					btn_redo->setDisabled(true);

				++number_of_undo;
				if (!btn_undo->isEnabled())
					btn_undo->setDisabled(false);

				if (!srv.numberOfProducts())
				{
					btn_modify->setEnabled(false); // btn_modify->setDisabled(true);
					btn_delete->setEnabled(false); // btn_delete->setDisabled(true);
					btn_search->setEnabled(false); // btn_search->setDisabled(true);
				}
				else
				{
					btn_modify->setEnabled(true); // btn_modify->setDisabled(false);
					btn_delete->setEnabled(true); // btn_delete->setDisabled(false);
					btn_search->setEnabled(true); // btn_search->setDisabled(false);
				}

				lst_products_model->setFilter(false);

				try {
					lst_products_model->setVisible(srv.getAll(), true);
					tbl_products_model->setVisible(srv.getAll(), true);
				}
				catch (const RepoException&) {
					lst_products_model->setVisible(vector<Product>(), true);
					tbl_products_model->setVisible(vector<Product>(), true);
				}
			}
			catch (const ServiceException& se) {
				qDebug() << QString::fromStdString(se.getMessage());

				btn_redo->setDisabled(true);

				msg_dbg->setText(QString::fromStdString(se.getMessage()));
				msg_dbg->setIcon(QMessageBox::Critical);
			}

			msg_dbg->exec();

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_cos, &QPushButton::clicked, this, [&]() {
		lst_cumparaturi_view->setUniformItemSizes(true);
		lst_cumparaturi_view->setModel(lst_cumparaturi_model);
		lst_cumparaturi_model->setVisible(true);

		tbl_cumparaturi_view->setModel(tbl_cumparaturi_model);
		tbl_cumparaturi_model->setVisible(true);

		if (cos_widget == nullptr)
			connectSignalsCosCumparaturi();
		else if (cos_widget->isEnabled())
		{
			cos_widget->setDisabled(true);
			cos_widget->close();
		}

		initMeniuCosCumparaturi();
		setInitialStateCosCumparaturi();
		});

	QObject::connect(btn_dbg, &QPushButton::clicked, this, [&]() {
		unsigned cont{ 0 };

		addDebug("iaurt", "produse lactate", 4.63, "Danone", cont);
		addDebug("chipsuri", "snacksuri", 9.6, "Lays", cont);
		addDebug("rozmarin", "condimente", 1.68, "Kamis", cont);
		addDebug("ton in ulei", "conserve", 13.9841, "Tonno Rio Mare", cont);
		addDebug("boia", "condimente", 0.999, "Delikat", cont);
		addDebug("maioneza", "sosuri", 5.891, "Hellmann's", cont);
		addDebug("suc", "bauturi racoritoare", 6.9, "Pepsi", cont);
		addDebug("pasta de dinti", "igiena", 7.12, "Colgate", cont);
		addDebug("tigari", "cancerigene", 8.4018, "Marlboro", cont);
		addDebug("iaurt", "produse lactate", 5.013, "Milka UK", cont);
		addDebug("sare", "condimente", 11, "Maggi", cont);
		addDebug("suc", "bauturi racoritoare", 15.5, "Coca-Cola", cont);
		addDebug("tigari", "cancerigene", 5.83, "Kent", cont);
		addDebug("tigari", "cancerigene", 17.25, "Camel", cont);
		addDebug("parmezan", "condimente", 8.301, "Delikat", cont);
		addDebug("chipsuri", "snacksuri", 1.53, "Chio", cont);
		addDebug("chipsuri", "snacksuri", 9.1, "Pringles", cont);
		addDebug("coriandru", "condimente", 0.0471, "Knorr", cont);
		addDebug("tigari", "cancerigene", 21, "Pall Mall", cont);
		addDebug("ketchup", "sosuri", 4.2810, "Heinz", cont);

		QMessageBox msg_dbg;
		msg_dbg.setWindowTitle("Adaugare produse debug");

		if (!cont)
		{
			msg_dbg.setText("[X]Nu au fost adaugate produse noi in stoc!");
			msg_dbg.setIcon(QMessageBox::Warning);
		}
		else
		{
			++number_of_undo;

			if (!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			msg_dbg.setText("[*]Au fost adaugate " + QString::number(cont) + " produse noi in stoc!");
			msg_dbg.setIcon(QMessageBox::Information);

			btn_modify->setEnabled(true); // btn_modify->setDisabled(false);
			btn_delete->setEnabled(true); // btn_delete->setDisabled(false);
			btn_search->setEnabled(true); // btn_search->setDisabled(false);

			lst_products_model->setFilter(false);
			lst_products_model->setVisible(srv.getAll(), true);
			tbl_products_model->setVisible(srv.getAll(), true);
		}

		msg_dbg.exec();
		});

	QObject::connect(btn_clear, &QPushButton::clicked, this, [&]() {
		last_selected_item_list = nullptr;

		name_line_edit->setText("");
		type_line_edit->setText("");
		price_line_edit->setText("");
		producer_line_edit->setText("");

		//lst_products->clear();
		//tbl_products->clear();

		//tbl_products->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

		lst_products_model->setFilter(false);

		try {
			lst_products_model->setVisible(srv.getAll(), false);
			tbl_products_model->setVisible(srv.getAll(), false);
		}
		catch (const RepoException&) {
			lst_products_model->setVisible(vector<Product>(), false);
			tbl_products_model->setVisible(vector<Product>(), false);
		}
		});

	QObject::connect(btn_exit, &QPushButton::clicked, this, []() {
		QMessageBox msg_box;
		msg_box.setWindowTitle("Confirmare inchidere aplicatie");
		msg_box.setIcon(QMessageBox::Question);
		msg_box.setText("Sunteti sigur ca doriti sa iesiti din aplicatie?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			exit(0);
			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});
}

void GUI::addProductsToList(const vector<Product>& prods)
{
	lst_products->clear();

	auto idx{ 0 };

	for (const auto& prod : prods)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Lista de produse existente in magazin:" };
			lst_products->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		const auto& str_name{ prod.getName() };
		const auto& str_type{ prod.getType() };
		const auto str_price{ to_string(prod.getPrice()) };
		const auto& str_producer{ prod.getProducer() };
		const auto str_product{ str_name + sep + str_type + sep + str_price + sep + str_producer };

		QListWidgetItem* item = new QListWidgetItem{ QString::number(idx) + ": " + QString::fromStdString(str_product) };

		const auto q_str_name{ QString::fromStdString(str_name) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		const auto q_str_price{ QString::fromStdString(str_price) };
		const auto q_str_producer{ QString::fromStdString(str_producer) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		lst_products->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Nu exista momentan produse disponibile in stoc!" };
		lst_products->addItem(item);
	}
}

void GUI::addProductsToTable(const vector<Product>& prods)
{
	tbl_products->clear();

	auto rows{ (int)prods.size() };
	auto cols{ 4 };

	tbl_products->setRowCount(rows);
	tbl_products->setColumnCount(cols);

	tbl_products->setHorizontalHeaderLabels({ "Nume", "Tip", "Pret", "Producator" });

	auto row{ 0 };

	for (const auto& prod : prods)
	{
		const auto& q_str_name{ QString::fromStdString(prod.getName()) };
		const auto& q_str_type{ QString::fromStdString(prod.getType()) };
		const auto q_str_price{ QString::fromStdString(to_string(prod.getPrice())) };
		const auto& q_str_producer{ QString::fromStdString(prod.getProducer()) };

		const QStringList q_string_list{ q_str_name, q_str_type, q_str_price, q_str_producer };

		QTableWidgetItem* name_item = new QTableWidgetItem(QString::fromStdString(prod.getName()));
		name_item->setTextAlignment(Qt::AlignHCenter);
		name_item->setData(Qt::UserRole, QStringList(q_string_list));
		name_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(prod.getType()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));
		type_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* price_item = new QTableWidgetItem(QString::number(prod.getPrice()));
		price_item->setTextAlignment(Qt::AlignHCenter);
		price_item->setData(Qt::UserRole, QStringList(q_string_list));
		price_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* producer_item = new QTableWidgetItem(QString::fromStdString(prod.getProducer()));
		producer_item->setTextAlignment(Qt::AlignHCenter);
		producer_item->setData(Qt::UserRole, QStringList(q_string_list));
		producer_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		tbl_products->setItem(row, 0, name_item);
		tbl_products->setItem(row, 1, type_item);
		tbl_products->setItem(row, 2, price_item);
		tbl_products->setItem(row, 3, producer_item);

		++row;
	}
}

void GUI::addShortcuts()
{
	QAction* action_btn_adaugare_cumparaturi_main = new QAction(this);
	action_btn_adaugare_cumparaturi_main->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
	connect(action_btn_adaugare_cumparaturi_main, &QAction::triggered, btn_adaugare_cumparaturi_main, &QPushButton::click);

	this->addAction(action_btn_adaugare_cumparaturi_main);

	QAction* action_btn_stergere_cumparaturi_main = new QAction(this);
	action_btn_stergere_cumparaturi_main->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	connect(action_btn_stergere_cumparaturi_main, &QAction::triggered, btn_stergere_cumparaturi_main, &QPushButton::click);

	this->addAction(action_btn_stergere_cumparaturi_main);

	QAction* action_btn_generare_cumparaturi_main = new QAction(this);
	action_btn_generare_cumparaturi_main->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_G));
	connect(action_btn_generare_cumparaturi_main, &QAction::triggered, btn_generare_cumparaturi_main, &QPushButton::click);

	this->addAction(action_btn_generare_cumparaturi_main);

	QAction* action_btn_CosCRUDGUI = new QAction(this);
	action_btn_CosCRUDGUI->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
	connect(action_btn_CosCRUDGUI, &QAction::triggered, btn_CosCRUDGUI, &QPushButton::click);

	this->addAction(action_btn_CosCRUDGUI);

	QAction* action_btn_CosReadOnlyGUI = new QAction(this);
	action_btn_CosReadOnlyGUI->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
	connect(action_btn_CosReadOnlyGUI, &QAction::triggered, btn_CosReadOnlyGUI, &QPushButton::click);

	this->addAction(action_btn_CosReadOnlyGUI);

	QAction* action_btn_cos = new QAction(this);
	action_btn_cos->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
	connect(action_btn_cos, &QAction::triggered, btn_cos, &QPushButton::click);

	this->addAction(action_btn_cos);
}

void GUI::addToolTips()
{
	name_line_edit->setToolTip("Numele produsului (text)");
	type_line_edit->setToolTip("Tipul produsului (text)");
	price_line_edit->setToolTip("Pretul produsului (valoare numerica reala)");
	producer_line_edit->setToolTip("Producatorul produsului (text)");

	btn_adaugare_cumparaturi_main->setToolTip("Adaugare produs in cosul de cumparaturi");
	btn_stergere_cumparaturi_main->setToolTip("Golire continut cos de cumparaturi");
	btn_generare_cumparaturi_main->setToolTip("Generare continut cos de cumparaturi");
	
	btn_CosCRUDGUI->setToolTip("Deschidere fereastra CosCRUDGUI");
	btn_CosReadOnlyGUI->setToolTip("Deschidere fereastra CosReadOnlyGUI");
	
	btn_cos->setToolTip("Deschidere fereastra pentru gestiunea cosului de cumparaturi");
	
	btn_add->setToolTip("Adaugare produs nou in stocul magazinului");
	btn_modify->setToolTip("Modificare produs existent din stocul magazinului");
	btn_delete->setToolTip("Stergere/Eliminare produs existent din stocul magazinului");
	
	btn_search->setToolTip("Cautare produs in stocul magazinului");
	btn_type->setToolTip("Afisare stoc magazin");
	btn_info_types->setToolTip("Deschidere ferestre care contin statistici privind distributia produselor in stoc");
	
	btn_undo->setToolTip("Anularea ultimei operatii de adaugare/modificare/stergere");
	btn_redo->setToolTip("Refacerea ultimei operatii anulate folosind undo");
	btn_dbg->setToolTip("Adaugare produse de test in stocul magazinului");
	
	btn_clear->setToolTip("Stergere continut lista/tabel");
	btn_exit->setToolTip("Inchidere aplicatie");
	
	btn_sort->setToolTip("Sortare produse din stocul magazinului");
	
	btn_filter->setToolTip("Filtrare produse din stocul magazinului");

	radio_btn_cresc->setToolTip("Sortare in ordine crescatoare");
	radio_btn_descresc->setToolTip("Sortare in ordine descrescatoare");

	sort_options_combo_box->setToolTip("Alegere optiune de sortare");

	radio_btn_less->setToolTip("Filtrare dupa pret mai mic strict");
	radio_btn_equal->setToolTip("Filtrare dupa pret egal");
	radio_btn_greater->setToolTip("Filtrare dupa pret mai mare strict");

	filter_options_combo_box->setToolTip("Alegere optiune de filtrare");

	filter_crt_line_edit->setToolTip("Alegeti filtrul dupa care sa se faca filtrarea produselor din magazin");

	sld_cumparaturi_main->setToolTip("Slider care controleaza cate produse sa fie generate in cosul de cumparaturi");
	sld_value_cumparaturi_main->setToolTip("Spin box care controleaza cate produse sa fie generate in cosul de cumparaturi");
}

void GUI::addPlaceholderText()
{
	name_line_edit->setPlaceholderText("Introduceti numele produsului...");
	type_line_edit->setPlaceholderText("Introduceti tipul produsului...");
	price_line_edit->setPlaceholderText("Introduceti pretul produsului...");
	producer_line_edit->setPlaceholderText("Introduceti producatorul produsului...");

	filter_crt_line_edit->setPlaceholderText("Introduceti filtru...");
}

void GUI::setInitialState()
{
	try {
		lst_products_model->setVisible(srv.getAll(), true);
		tbl_products_model->setVisible(srv.getAll(), true);
	}
	catch (const RepoException&) {
		lst_products_model->setVisible(vector<Product>(), true);
		tbl_products_model->setVisible(vector<Product>(), true);

		btn_modify->setEnabled(false); // btn_modify->setDisabled(true);
		btn_delete->setEnabled(false); // btn_delete->setDisabled(true);
		btn_search->setEnabled(false); // btn_search->setDisabled(true);
	}
	
	addShortcuts();
	addToolTips();
	addPlaceholderText();

	last_selected_item_list = new QListWidgetItem;

	number_of_undo = 0;
	btn_undo->setDisabled(true);

	number_of_redo = 0;
	btn_redo->setDisabled(true);

	//btn_stergere->setDisabled(true);

	/*try {
		const auto& products{ srv.getAll() };

		addProductsToList(products);
		addProductsToTable(products);
	}
	catch (const RepoException&) {
		addProductsToList(vector<Product>());
		addProductsToTable(vector<Product>());
	}*/
}