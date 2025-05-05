#include "rectangle.h"

double Rectangle_Figure::get_area(const ShapeItem& shapeItem) {
  return shapeItem.rect.width() * shapeItem.rect.height();  //школа
}

double Rectangle_Figure::get_perimeter(const ShapeItem& shapeItem) {
  return 2 * (shapeItem.rect.width() + shapeItem.rect.height());  //школа
}

void Rectangle_Figure::rotate_Shape(int shapeIndex, QList<ShapeItem>& shapes) {
  ShapeItem& shape_item = shapes[shapeIndex];
  QPoint center = shape_item.rect.center();
  int width = shape_item.rect.width();
  int height = shape_item.rect.height();
  shape_item.rect.setRect(center.x() - (height / 2), center.y() - (width / 2),
                          height, width);  //тоже как и у эллипса
}

void Rectangle_Figure::rotatePolygon(int shapeIndex, ShapeItem& shapeItem,
                                     int angle) {
  QPoint center = get_centerOfMass(shapeItem);
  QTransform transform;
  transform.translate(center.x(), center.y());
  transform.rotate(angle);
  transform.translate(-center.x(), -center.y());
  QPolygon original;
  original
      << shapeItem.rect.topLeft() << shapeItem.rect.topRight()
      << shapeItem.rect.bottomRight()
      << shapeItem.rect.bottomLeft();  //создали новый многоугольника и потом
  QPolygon rotated;
  for (QPoint p : original) {
    rotated << transform.map(
        p);  //все что в трансформ + записываем в новый полигон
  }
  shapeItem.polygon = rotated;
  shapeItem.rect =
      rotated.boundingRect();  // также поворачиваем и тп + область новая
}
