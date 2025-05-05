#include "diamond.h"
constexpr double kRadiusRatio = 2.0;

double Diamond_Figure::get_area(const ShapeItem& shapeItem) {
  return shapeItem.rect.width() * shapeItem.rect.height() /
         kRadiusRatio;  //полупроизведение диагоналей
}

double Diamond_Figure::get_perimeter(const ShapeItem& shapeItem) {
  double d1 = shapeItem.rect.width();
  double d2 = shapeItem.rect.height();
  double side_length = std::sqrt(std::pow(d1 / kRadiusRatio, 2) +
                                 std::pow(d2 / kRadiusRatio, 2));
  return 4 *
         side_length;  //теорема пифагора для полудиагоналей нашли сторону и умножили на 4
}

void Diamond_Figure::rotatePolygon(int shapeIndex, ShapeItem& shapeItem,
                                   int angle) {
  QPoint center = get_centerOfMass(shapeItem);
  QTransform transform;
  transform.translate(center.x(), center.y());
  transform.rotate(angle);
  transform.translate(-center.x(), -center.y());
  QPolygon rotated_diamond;
  for (QPoint p : shapeItem.polygon) {
    rotated_diamond << transform.map(p);
  }
  shapeItem.polygon = rotated_diamond;
  shapeItem.rect = rotated_diamond.boundingRect();  //аналогично поворот
}
