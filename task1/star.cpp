#include "star.h"
constexpr double kStarRatio = 2.0;

double Star_Figure::get_area(const ShapeItem& shapeItem) {
  double area = 0.0;
  const QPolygon& polygon = shapeItem.polygon;
  long long num_points = polygon.size();
  for (int i = 0; i < num_points; ++i) {
    QPoint p1 = polygon[i];
    QPoint p2 = polygon[(i + 1) % num_points];
    area += p1.x() * p2.y() - p2.x() * p1.y();
  }
  return std::abs(area) / kStarRatio;  // через формулу Гаусса
}

double Star_Figure::get_perimeter(const ShapeItem& shapeItem) {
  double perimeter = 0.0;
  const QPolygon& polygon = shapeItem.polygon;
  int num_points = polygon.size();

  for (int i = 0; i < num_points; ++i) {
    QPoint p1 = polygon[i];
    QPoint p2 = polygon[(i + 1) % num_points];
    perimeter +=
        QLineF(p1, p2)
            .length();  //соединяем и qline линию длиной, в периметр суммируем
  }
  return perimeter;
}

QPoint Star_Figure::get_centerOfMass(const ShapeItem& shapeItem) {
  qreal x_sum = 0, y_sum = 0;
  for (const QPoint& point : shapeItem.polygon) {
    x_sum += point.x();
    y_sum += point.y();
  }
  return QPoint(
      x_sum / shapeItem.polygon.size(),
      y_sum / shapeItem.polygon.size());  //все точки икс и игрек на кол-во
}

QPolygon Star_Figure::createStar(const QPoint& center, int radius, int points,
                                 double innerRadiusRatio) {
  QPolygon star;
  double angle_offset = -M_PI / 2;
  int sides = points * 2;
  for (int i = 0; i < sides; ++i) {
    double r = (i % 2 == 0) ? radius : (radius * innerRadiusRatio);
    double theta = M_PI * i / points + angle_offset;
    int x = center.x() + (r * cos(theta));
    int y = center.y() + (r * sin(theta));
    star << QPoint(x, y);  //
  }
  return star;  //формула для создания звезды
}
