#pragma once

#include "Service.h"

#include <QtWidgets/qwidget.h>
#include <qpainter.h>
#include <qicon.h>

#include <random> // pentru std::random_device, std::mt19937 si std::uniform_int_distribution

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

class Histogram : public QWidget, public Observer {
private:
	const QIcon histogram_icon{ "./Logo-uri aplicatie/histogramIcon" };

	const QString histogram_title{ "Histograma tipuri produse" };

	mt19937 mt{ random_device{}() };

	Service& srv;

public:
	Histogram() = delete;

	Histogram(Histogram& ot) = delete;

	Histogram& operator=(Histogram& ot) = delete;

	Histogram(Service& srv) : srv{ srv } {
		srv.attachObserver(this);

		this->setWindowTitle(histogram_title);
		this->setWindowIcon(histogram_icon);

		/*QObject::connect(this, &QWidget::close, nullptr, [&]() {
			srv.detachObserver(this); // this->~Histogram();
			});*/
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter painter{ this };

		uniform_int_distribution<> dist_color(0, 255);

		auto cont{ 0 };
		const auto fixed_increase{ 50 };
		const auto fixed_height{ 50 };

		for (const auto& elem : srv.countType())
		{
			QRect rect;

			rect.setX(0);
			rect.setY(cont);

			auto width{ 100 * elem.second.second };

			rect.setHeight(fixed_height);
			rect.setWidth(width);

			painter.setBrush(QBrush(QColor::fromRgb(dist_color(mt), dist_color(mt), dist_color(mt), 255), Qt::SolidPattern));
			painter.drawRect(rect);

			painter.drawText(width + 10, cont + fixed_increase / 2, QString::number(elem.second.second));
			painter.drawText(5, cont + fixed_increase / 2, QString::fromStdString(elem.first));

			cont += fixed_increase;
		}
	}

	void closeEvent(QCloseEvent* event) override {
		this->~Histogram();
	}

	~Histogram() {
		srv.detachObserver(this);
	}
};