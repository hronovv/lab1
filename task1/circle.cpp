#include "circle.h"
constexpr double kRadiusRatio = 2.0;
const int kCircleScaleFactor = 2;  // For calculating the circle diamete
const int kMinRadius = 1;
const int kMaxRadius = 1000;

double Circle_Figure::get_area(const ShapeItem& shapeItem) {
  return M_PI * std::pow(shapeItem.rect.width() / kRadiusRatio,
                         2);  //нашли площадь P*r^2
}

double Circle_Figure::get_perimeter(const ShapeItem& shapeItem) {
  return 2 * M_PI * (shapeItem.rect.width() / kRadiusRatio);  // 2pr
}

void Circle_Figure::edit_Circle(int shapeIndex, QList<ShapeItem>& shapes,
                                QWidget* parent) {
  if (shapeIndex < 0 || shapeIndex >= shapes.size() ||
      shapes[shapeIndex].shape != Circle) {
    return;
  }

  bool ok;
  int current_radius = shapes[shapeIndex].rect.width() /
                       kCircleScaleFactor;  // Предполагается, что круг
  int new_radius = QInputDialog::getInt(
      parent, "Изменить радиус круга",
      QString("Текущий радиус: %1\nВведите новый радиус:").arg(current_radius),
      current_radius, kMinRadius, kMaxRadius, 1, &ok);
  if (ok) {
    QRect old_rect = shapes[shapeIndex].rect;
    QPoint center = old_rect.center();
    int diameter = new_radius * kCircleScaleFactor;
    shapes[shapeIndex].rect.setRect(
        center.x() - new_radius, center.y() - new_radius, diameter, diameter);
    parent->update();  //обновляем область и радиус
  }
}
