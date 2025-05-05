#include "base_figure.h"

#include <__ranges/transform_view.h>

double Base_Figure::get_area(const ShapeItem& shapeItem) {
  return 0.0;
}

double Base_Figure::get_perimeter(const ShapeItem& shapeItem) {
  return 0.0;
}

QPoint Base_Figure::get_centerOfMass(const ShapeItem& shapeItem) {
  return shapeItem.rect.center();
}

void Base_Figure::rotate_Shape(int shapeIndex, QList<ShapeItem>& shapes) {
  ShapeItem& shape_item = shapes[shapeIndex];
  QPoint center = shape_item.polygon.boundingRect().center();
  for (int i = 0; i < shape_item.polygon.size(); ++i) {
    QPoint pt = shape_item.polygon[i];
    pt -= center;  //смещаем каждую точку в начало координат
    int x_new = -pt.y();
    int y_new = pt.x();  // поворот на 90
    shape_item.polygon[i] =
        QPoint(x_new, y_new) + center;  //вернули назад в исходный центр
  }
}

void Base_Figure::move_center_offMass(int shapeIndex, QList<ShapeItem>& shapes,
                                      QWidget* parent) {
  QPoint center_of_mass = get_centerOfMass(shapes[shapeIndex]);
  bool ok;
  QString new_center = QInputDialog::getText(
      nullptr, "Сдвинуть центр масс",
      QString("Текущий центр масс: (%1, %2)\nВведите новые "
              "координаты центра масс, разделенные запятой:")
          .arg(center_of_mass.x())
          .arg(center_of_mass.y()),
      QLineEdit::Normal, "", &ok);

  if (ok && !new_center.isEmpty()) {
    QStringList coordinates = new_center.split(",");
    // проверка
    if (coordinates.size() == 2) {
      bool x_ok, y_ok;
      int new_x = coordinates[0].trimmed().toInt(&x_ok);
      int new_y = coordinates[1].trimmed().toInt(&y_ok);

      // корректность ввода
      if (x_ok && y_ok) {
        int dx = new_x - center_of_mass.x();
        int dy = new_y - center_of_mass.y();
        // сдвигаем
        shapes[shapeIndex].rect.moveLeft(shapes[shapeIndex].rect.left() + dx);
        shapes[shapeIndex].rect.moveBottom(shapes[shapeIndex].rect.bottom() +
                                           dy);
        shapes[shapeIndex].polygon.translate(
            dx, dy);       //передаем новые координаты полигону
        parent->update();  //перерисуем
      } else {
        // при ошибке
        QMessageBox::warning(
            nullptr, "Ошибка",
            "Введите корректные числовые значения для координат.");
      }
    } else {
      // при ошибке
      QMessageBox::warning(nullptr, "Ошибка",
                           "Введите две координаты, разделённые запятой.");
    }
  }
}

void Base_Figure::rotatePolygon(int shapeIndex, ShapeItem& shapeItem,
                                int angle) {
  QPoint center = get_centerOfMass(shapeItem);  //центр находим
  QTransform transform;  //создаем объект трансформ для преобразования
  transform.translate(center.x(),
                      center.y());  //перемещает систему координат в центр масс
  transform.rotate(angle);          //на угол повернули
  transform.translate(-center.x(),
                      -center.y());  // и назад вернули систему координат
  QPolygon rotated_poly;
  for (QPoint p : shapeItem.polygon) {
    rotated_poly << transform.map(p);  //отстраиваем новый
  }
  shapeItem.polygon = rotated_poly;  //присваиваем новый полигон в вектор
  shapeItem.rect = rotated_poly.boundingRect();  //новая область
}
