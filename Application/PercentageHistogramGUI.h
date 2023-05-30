#pragma once

#include "Service.h"

#include <QtWidgets/qwidget.h>
#include <qpainter.h>
#include <qicon.h>

#include <random> // pentru std::random_device, std::mt19937 si std::uniform_int_distribution

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

class PercentageHistogram : public QWidget, public Observer {
private:
	const QIcon percentage_histogram_icon{ "./Logo-uri aplicatie/percentageHistogramIcon" };

	const QString percentagehistogram_title{ "Histograma tipuri produse (cu procente)" };

	mt19937 mt{ random_device{}() };

	Service& srv;

public:
	PercentageHistogram() = delete;

	PercentageHistogram(PercentageHistogram& ot) = delete;

	PercentageHistogram& operator=(PercentageHistogram& ot) = delete;

	PercentageHistogram(Service& srv) : srv{ srv } {
		srv.attachObserver(this);

		this->setWindowTitle(percentagehistogram_title);
		this->setWindowIcon(percentage_histogram_icon);

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

		const auto total_number_of_products{ srv.numberOfProducts() };

		for (const auto& elem : srv.countType())
		{
			QRect rect;

			rect.setX(0);
			rect.setY(cont);

			const double percentage = (elem.second.second * 100.0) / total_number_of_products;

			auto width{ 5 * percentage };

			rect.setHeight(fixed_height);
			rect.setWidth(width);

			painter.setBrush(QBrush(QColor::fromRgb(dist_color(mt), dist_color(mt), dist_color(mt), 255), Qt::SolidPattern));
			painter.drawRect(rect);

			QFont font;
			font.setBold(true);
			painter.setFont(font);

			painter.drawText(width + 10, cont + fixed_increase / 2, QString::fromStdString(elem.first));
			painter.drawText(5, cont + fixed_increase / 2, QString::number(percentage) + "%");

			cont += fixed_increase;
		}
	}

	void closeEvent(QCloseEvent* event) override {
		this->~PercentageHistogram();
	}

	~PercentageHistogram() {
		srv.detachObserver(this);
	}
};