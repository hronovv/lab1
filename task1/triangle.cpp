#include "triangle.h"
constexpr double kTriangleRatio = 2.0;

double Triangle_Figure::get_area(const ShapeItem& shapeItem) {
  const QPolygon& triangle =
      shapeItem
          .polygon;  // можно было убрать и чисто shapeItem.polygon, но читабельнее
  return std::abs((triangle[0].x() * (triangle[1].y() - triangle[2].y()) +
                   triangle[1].x() * (triangle[2].y() - triangle[0].y()) +
                   triangle[2].x() * (triangle[0].y() - triangle[1].y())) /
                  kTriangleRatio);  //гаусса
}

double Triangle_Figure::get_perimeter(const ShapeItem& shapeItem) {
  double perimeter = 0.0;
  for (int i = 0; i < 3; ++i) {
    perimeter += std::sqrt(
        std::pow(shapeItem.polygon[i].x() - shapeItem.polygon[(i + 1) % 3].x(),
                 2) +
        std::pow(shapeItem.polygon[i].y() - shapeItem.polygon[(i + 1) % 3].y(),
                 2));
  }
  return perimeter;  //суммируем расстояния
}

QPoint Triangle_Figure::get_centerOfMass(const ShapeItem& shapeItem) {
  qreal x_sum = 0, y_sum = 0;
  for (const QPoint& point : shapeItem.polygon) {
    x_sum += point.x();
    y_sum += point.y();
  }
  return QPoint(
      x_sum / shapeItem.polygon.size(),
      y_sum / shapeItem.polygon.size());  //все иксы и игреки на кол-во
}
