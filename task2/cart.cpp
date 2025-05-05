#include "cart.h"

Cart::Cart(QWidget* parent) : RectangleWidget(parent) {}

void Cart::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setBrush(Qt::white);
  painter.drawEllipse(x_ + 120, y_ + 140, 80, 80);
  painter.drawEllipse(x_ + 300, y_ + 140, 80, 80);
  painter.setBrush(Qt::black);
  painter.drawEllipse(x_ + 130, y_ + 150, 60, 60);
  painter.drawEllipse(x_ + 310, y_ + 150, 60, 60);
  painter.setBrush(Qt::yellow);
  QPolygon cart_base;
  cart_base << QPoint(x_ + 100, y_ + 140) << QPoint(x_ + 400, y_ + 140)
            << QPoint(x_ + 500, y_) << QPoint(x_ + 440, y_)
            << QPoint(x_ + 440, y_ - 90) << QPoint(x_ + 280, y_ - 90)
            << QPoint(x_ + 280, y_) << QPoint(x_, y_);
  painter.drawPolygon(cart_base);
  painter.setPen(Qt::red);
  painter.setFont(QFont("Arial", 50, QFont::Bold));
  painter.drawText(QRect(x_ + 115, y_ + 20, 40, 100), Qt::AlignLeft, "Я");
  painter.setPen(Qt::black);
  painter.setBrush(Qt::black);
  painter.drawEllipse(x_ + 350, y_ - 80, 30, 30);
  painter.drawRect(x_ + 355, y_ - 50, 20, 50);
  painter.drawRect(x_ + 365, y_ - 40, 50, 10);
  painter.setBrush(Qt::NoBrush);
  painter.drawEllipse(x_ + 415, y_ - 53, 18, 30);
  painter.setFont(QFont("Arial", 50));
  painter.drawText(QRect(x_ + 155, y_ + 20, 300, 100), Qt::AlignLeft,
                   "ндекс Еда");
}
