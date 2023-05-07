#pragma once

#include "CosCumparaturi.h"
#include "Observer.h"

#include <QtWidgets/qwidget.h>
#include <qpainter.h>

#include <random> // pentru std::random_device, std::mt19937 si std::uniform_int_distribution

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

#define MAX(a, b) \
	(((a) > (b)) ? (a) : (b))

class CosReadOnlyGUI : public QWidget, public Observer {
private:
	//const QIcon cos_read_only_icon{ "./Logo-uri aplicatie/CosReadOnlyIcon" };
	const QIcon cos_read_only_icon{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\CosReadOnlyIcon" };

	//QImage img1{ "./Logo-uri aplicatie/happy_sad" };
	QImage img1{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\happy_sad" };

	//QImage img2{ "./Logo-uri aplicatie/happy" };
	QImage img2{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\happy" };

	//QImage img3{ "./Logo-uri aplicatie/xoaye" };
	QImage img3{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\xoaye" };

	//QImage img4{ "./Logo-uri aplicatie/amogus" };
	QImage img4{ "C:\\Users\\Admin\\Documents\\VS Projects\\Lab10-11\\MagazinGUI\\Logo-uri aplicatie\\amogus" };

	mt19937 mt{ random_device{}() };

	const int size_1{ 50 };
	const int size_2{ 100 };

	CosCumparaturi& cos;

public:
	CosReadOnlyGUI() = delete;

	CosReadOnlyGUI(CosReadOnlyGUI& ot) = delete;

	CosReadOnlyGUI& operator=(CosReadOnlyGUI& ot) = delete;

	CosReadOnlyGUI(CosCumparaturi& cos) : cos{ cos } {
		cos.attachObserver(this);

		this->setWindowTitle("Fereastra CosReadOnlyGUI");
		this->setWindowIcon(cos_read_only_icon);

		const uniform_int_distribution<> dist_x(0, 900);
		const uniform_int_distribution<> dist_y(0, 300);

		const auto ax{ dist_x(mt) };
		const auto ay{ dist_y(mt) };

		this->move(ax, ay);

		this->setMinimumWidth(500);
		this->setMinimumHeight(500);

		//QObject::connect(this, &QWidget::close, nullptr, [&]() {
		//	cos.detachObserver(this); // this->~CosReadOnlyGUI();
		//	});
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		int cos_size;

		try {
			cos_size = cos.nrProduseCos();
		}
		catch (const CosException&) {
			cos_size = 0;
		}

		QPainter painter{ this };

		const uniform_int_distribution<> dist_bin(0, 1);
		const uniform_int_distribution<> dist_x(0, this->width() - MAX(MAX(img1.width(), size_1), MAX(img2.width(), size_2)));
		const uniform_int_distribution<> dist_y(0, this->height() - MAX(MAX(img1.height(), size_1), MAX(img2.height(), size_2)));
		const uniform_int_distribution<> dist_color(0, 255);
		const uniform_int_distribution<> dist_xoaye(1, 420);

		for (auto i{ 0 }; i < cos_size; ++i)
		{
			const int x{ dist_x(mt) }; // width
			const int y{ dist_y(mt) }; // height

			QPoint point{ x, y };
			
			const auto luck{ dist_xoaye(mt) };

			//if (luck <= 6)
			//	painter.drawImage(point, img3);
			//else if(luck <= 12)
			//	painter.drawImage(point, img4);
			if (!dist_bin(mt))
			{
				// Varianta cu imagini
				if (!dist_bin(mt))
					painter.drawImage(point, img1);
				else
					painter.drawImage(point, img2);
			}
			else {
				// Varianta cu dreptunghiuri orizontale si verticale
				painter.setBrush(QBrush(QColor::fromRgb(dist_color(mt), dist_color(mt), dist_color(mt), 255), Qt::SolidPattern));

				QRect rect;

				rect.setX(x);
				rect.setY(y);

				if (!dist_bin(mt))
				{
					rect.setHeight(size_1);
					rect.setWidth(size_2);
				}
				else {
					rect.setHeight(size_2);
					rect.setWidth(size_1);
				}

				painter.drawPolygon(rect); // painter.drawRect(rect);
			}
		}
	}

	void closeEvent(QCloseEvent* event) override {
		this->~CosReadOnlyGUI();
	}

	~CosReadOnlyGUI() {
		cos.detachObserver(this);
	}
};