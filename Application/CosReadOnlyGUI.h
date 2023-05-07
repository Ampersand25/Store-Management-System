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
	const QIcon cos_read_only_icon{ "./Logo-uri aplicatie/shoppingReadOnlyIcon" };

	QImage img1{ "./Logo-uri aplicatie/sadIcon" };
	QImage img2{ "./Logo-uri aplicatie/happyIcon" };

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

		uniform_int_distribution<> dist_x(0, 900);
		uniform_int_distribution<> dist_y(0, 300);

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

		uniform_int_distribution<> dist_bin(0, 1);
		uniform_int_distribution<> dist_x(0, this->width() - MAX(MAX(img1.width(), size_1), MAX(img2.width(), size_2)));
		uniform_int_distribution<> dist_y(0, this->height() - MAX(MAX(img1.height(), size_1), MAX(img2.height(), size_2)));
		uniform_int_distribution<> dist_color(0, 255);
		uniform_int_distribution<> dist_xoaye(1, 420);

		for (auto i{ 0 }; i < cos_size; ++i)
		{
			const int x{ dist_x(mt) }; // width
			const int y{ dist_y(mt) }; // height

			QPoint point{ x, y };

			const auto luck{ dist_xoaye(mt) };
			
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

			// Varianta cu dreptunghiuri orizontale si verticale si imagini (random)
			//if (!dist_bin(mt))
			//{
			//	// Varianta cu imagini
			//	if (!dist_bin(mt))
			//		painter.drawImage(point, img1);
			//	else
			//		painter.drawImage(point, img2);
			//}
			//else {
			//	// Varianta cu dreptunghiuri orizontale si verticale
			//	painter.setBrush(QBrush(QColor::fromRgb(dist_color(mt), dist_color(mt), dist_color(mt), 255), Qt::SolidPattern));

			//	QRect rect;

			//	rect.setX(x);
			//	rect.setY(y);

			//	if (!dist_bin(mt))
			//	{
			//		rect.setHeight(size_1);
			//		rect.setWidth(size_2);
			//	}
			//	else {
			//		rect.setHeight(size_2);
			//		rect.setWidth(size_1);
			//	}

			//	painter.drawPolygon(rect); // painter.drawRect(rect);
			//}
		}
	}

	void closeEvent(QCloseEvent* event) override {
		this->~CosReadOnlyGUI();
	}

	~CosReadOnlyGUI() {
		cos.detachObserver(this);
	}
};