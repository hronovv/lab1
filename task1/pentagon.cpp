#include "pentagon.h"
constexpr double kPentagonRatio = 5.0;
constexpr double kPentagonRatio2 = 4.0;

double Pentagon_Figure::get_area(const ShapeItem& shapeItem) {
  double side_length =
      std::min(shapeItem.rect.width(), shapeItem.rect.height()) /
      (1.0 + std::tan(M_PI / kPentagonRatio));  //еще одна аппроксимация
  return (1.0 / kPentagonRatio2) *
         sqrt(kPentagonRatio * (kPentagonRatio + 2 * sqrt(kPentagonRatio))) *
         std::pow(side_length, 2);  // формула площади
}

double Pentagon_Figure::get_perimeter(const ShapeItem& shapeItem) {
  return kPentagonRatio *
         std::min(shapeItem.rect.width(), shapeItem.rect.height()) /
         (1.0 + std::tan(M_PI / kPentagonRatio));
}  //умножаем на апроксимированную сторону

QPoint Pentagon_Figure::get_centerOfMass(const ShapeItem& shapeItem) {
  qreal x_sum = 0, y_sum = 0;
  for (const QPoint& point : shapeItem.polygon) {
    x_sum += point.x();
    y_sum += point.y();
  }
  return QPoint(
      x_sum / shapeItem.polygon.size(),
      y_sum /
          shapeItem.polygon.size());  //сумма всех иксов и игреков на их кол-во
}
