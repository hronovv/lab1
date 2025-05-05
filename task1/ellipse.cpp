#include "ellipse.h"
constexpr double kEllipseRatio = 2.0;

double Ellipse_Figure::get_area(const ShapeItem& shapeItem) {
  return M_PI * (shapeItem.rect.width() / kEllipseRatio) *
         (shapeItem.rect.height() /
          kEllipseRatio);  //pab(через интеграл можно вывести. МАТ АНАЛИЗ!)
}

double Ellipse_Figure::get_perimeter(const ShapeItem& shapeItem) {
  double a = shapeItem.rect.width() / kEllipseRatio;   // большая полуось
  double b = shapeItem.rect.height() / kEllipseRatio;  // малая полуось
  return 4 * ((M_PI * a * b + (a - b) * (a - b)) /
              (a - b));  // 0,63% погрешность аппроксимация
}

void Ellipse_Figure::rotate_Shape(int shapeIndex, QList<ShapeItem>& shapes) {
  ShapeItem& shape_item = shapes[shapeIndex];
  QRect rect = shape_item.rect;
  QPoint center = rect.center();
  int width = rect.width();
  int height = rect.height();
  shape_item.rect.setRect(
      center.x() - (height / 2), center.y() - (width / 2), height,
      width);  //перемещаем область и пересоздаем эллипс, перемещая координаты и длины и ширины местами поменяли
}
