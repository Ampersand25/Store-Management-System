#include "CosCRUDGUI.h"
#include "CosException.h"
#include "ServiceException.h"
#include "RepoException.h"

#include <QtWidgets>

#include <random> // pentru std::random_device, std::mt19937 si std::uniform_int_distribution

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::to_string;

void CosCRUDGUI::addCumparaturiToList(QListWidget* lst, const vector<Product>& lista_cumparaturi)
{
	lst->clear();

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

void CosCRUDGUI::addCumparaturiToTable(QTableWidget* tbl, const vector<Product>& lista_cumparaturi)
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

void CosCRUDGUI::setUpMasterDetail()
{
	lst_cos_model->setProducts();
	tbl_cos_model->setProducts();

	try {
		const auto lista_cumparaturi{ cos.getCos() };

		/*addCumparaturiToList(lst_cos, lista_cumparaturi);
		addCumparaturiToTable(tbl_cos, lista_cumparaturi);*/
		btn_gol->setDisabled(false);
	}
	catch (const CosException&) {
		/*addCumparaturiToList(lst_cos, vector<Product>());
		addCumparaturiToTable(tbl_cos, vector<Product>());*/
		btn_gol->setDisabled(true);
	}
}

void CosCRUDGUI::initGuiCmpCosCRUDGUI()
{
	lst_cos_view = new QListView;
	tbl_cos_view = new QTableView;

	lst_cos_model = new ListModelCosCRUDGUI(cos);
	tbl_cos_model = new TableModelCosCRUDGUI(cos);

	lst_cos_view->setUniformItemSizes(true);
	lst_cos_view->setModel(lst_cos_model);
	tbl_cos_view->setModel(tbl_cos_model);

	mt19937 mt{ random_device{}() };

	const uniform_int_distribution<> dist_x(0, 1000);
	const uniform_int_distribution<> dist_y(0, 400);

	const auto ax{ dist_x(mt) };
	const auto ay{ dist_y(mt) };

	this->move(ax, ay);

	//const QIcon cos_crud_icon{ "./Logo-uri aplicatie/CosCRUDIcon" };
	const QIcon cos_crud_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\CosCRUDIcon" };

	this->setWindowTitle("Fereastra CosCRUDGUI");
	this->setWindowIcon(cos_crud_icon);

	QVBoxLayout* main_ly = new QVBoxLayout;

	lst_cos = new QListWidget;
	tbl_cos = new QTableWidget;

	tab = new QTabWidget;

	// Varianta de liste/tabele fara model-view
	//tab->addTab(lst_cos, "Lista produse cos");
	//tab->addTab(tbl_cos, "Tabel produse cos");
	
	// Varianta de liste/tabele cu model-view
	tab->addTab(lst_cos_view, "Lista produse cos");
	tab->addTab(tbl_cos_view, "Tabel produse cos");

	main_ly->addWidget(tab);

	this->setLayout(main_ly);

	QVBoxLayout* btns_ly = new QVBoxLayout;

	QHBoxLayout* layout = new QHBoxLayout;

	QLabel* lbl = new QLabel{ "Numar produse generare" };

	spin_box = new QSpinBox;

	spin_box->setMinimum(MIN_SLD);
	spin_box->setMaximum(MAX_SLD);
	spin_box->setValue(CURR_SLD);

	btn_gen = new QPushButton{ "Generare cos de cumparaturi" };
	btn_gol = new QPushButton{ "Golire cos de cumparaturi" };

	layout->addWidget(lbl);
	//layout->addStretch();

	layout->addWidget(spin_box);
	//layout->addStretch();

	layout->addWidget(btn_gen);

	btns_ly->addLayout(layout);
	btns_ly->addWidget(btn_gol);

	main_ly->addLayout(btns_ly);

	this->show();
}

void CosCRUDGUI::connectSignalsCosCRUDGUI()
{
	cos.attachObserver(this);

	//QObject::connect(this, &QWidget::close, nullptr, [&]() {
	//		cos.detachObserver(this); // this->~CosCRUDGUI();
	//		});

	QObject::connect(lst_cos_view->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		const auto sel{ lst_cos_view->selectionModel()->selectedIndexes() };

		if (!sel.isEmpty()) // if (sel.size())
		{
			const auto& selected_index{ sel.at(0) };

			if (selected_index.row())
				lst_cos_model->setLastSelectedItem(selected_index.row());
			else
				lst_cos_model->setLastSelectedItem(-1);
		}
		});

	QObject::connect(btn_gen, &QPushButton::clicked, this, [&]() {
		const auto val{ spin_box->value() };

		QMessageBox* msg = new QMessageBox;

		try {
			cos.genereazaCos(val);
			btn_gol->setDisabled(false);

			msg->setText("[*]Generarea cosului de cumparaturi s-a realizat cu succes!\n[$]Pret total: " + QString::number(cos.getTotal()) + "\n[#]Numar total produse cos: " + QString::number(cos.nrProduseCos()));
		}
		catch (const RepoException& re) {
			qDebug() << QString::fromStdString(re.getMessage());

			msg->setText(QString::fromStdString(re.getMessage()));
		}
		catch (const ServiceException& se) {
			qDebug() << QString::fromStdString(se.getMessage());

			msg->setText(QString::fromStdString(se.getMessage()));
		}

		msg->show();

		lst_cos_model->setProducts();
		tbl_cos_model->setProducts();

		const auto lista_cumparaturi{ cos.getCos() };

		/*addCumparaturiToList(lst_cos, lista_cumparaturi);
		addCumparaturiToTable(tbl_cos, lista_cumparaturi);*/
		});

	QObject::connect(btn_gol, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa stergeti toate produsele din cosul de cumparaturi?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked

			try {
				cos.golesteCos();
				btn_gol->setDisabled(true);

				//msg->setText("[*]Toate produsele din cosul de cumparaturi au fost eliminate cu succes!\n[$]Pret total: " + QString::number(srv.totalCos()) + "\n[#]Numar total produse cos: 0");
				msg->setText("[*]Toate produsele din cosul de cumparaturi au fost eliminate cu succes!\n[$]Pret total: 0\n[#]Numar total produse cos: 0");
			}
			catch (const CosException& ce) {
				qDebug() << QString::fromStdString(ce.getMessage());

				msg->setText(QString::fromStdString(ce.getMessage()));
			}

			msg->show();

			lst_cos_model->setProducts();
			tbl_cos_model->setProducts();

			/*addCumparaturiToList(lst_cos, vector<Product>());
			addCumparaturiToTable(tbl_cos, vector<Product>());*/

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

void CosCRUDGUI::setInitialStateCosCRUDGUI()
{
	setUpMasterDetail();
}