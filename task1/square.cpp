#include "square.h"
constexpr double kMaxSquareSide = 1000.0;

//const int kCircleScaleFactor2 = 2;  // For calculating the circle diamete

double Square_Figure::get_area(const ShapeItem& shapeItem) {
  return std::pow(shapeItem.rect.width(), 2);  //a*a
}

double Square_Figure::get_perimeter(const ShapeItem& shapeItem) {
  return 4 * shapeItem.rect.width();  //4*a
}

void Square_Figure::rotate_Shape(int index, QList<ShapeItem>& shapes) {
  ShapeItem& shape_item = shapes[index];
  QPoint center = shape_item.rect.center();
  int width = shape_item.rect.width();
  shape_item.rect.setRect(center.x() - (width / 2), center.y() - (width / 2),
                          width, width);  //тоже сместили и тп
}

void Square_Figure::edit_Square(int shapeIndex, QList<ShapeItem>& shapes,
                                QWidget* parent) {
  if (shapeIndex < 0 || shapeIndex >= shapes.size() ||
      shapes[shapeIndex].shape != Square) {
    return;
  }
  bool ok;
  int current_side = shapes[shapeIndex].rect.width();  // квадрат
  int new_side = QInputDialog::getInt(
      parent, "Изменить сторону квадрата",
      QString("Текущая сторона: %1\nВведите новую сторону:").arg(current_side),
      current_side, 1, kMaxSquareSide, 1, &ok);
  if (ok) {
    QRect old_rect = shapes[shapeIndex].rect;
    QPoint center = old_rect.center();
    shapes[shapeIndex].rect.setRect(center.x() - (new_side / 2),
                                    center.y() - (new_side / 2), new_side,
                                    new_side);
    parent->update();
  }
}
