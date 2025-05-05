#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "base_figure.h" // Убедитесь, что этот файл подключен правильно
class Rectangle_Figure : public Base_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;     // Теперь это правильно
    double get_perimeter(const ShapeItem &shapeItem) override; // Теперь это правильно
    void rotate_Shape(int shapeIndex, QList<ShapeItem> &shapes) override;
    void rotatePolygon(int shapeIndex, ShapeItem &shapeItem, int angle) override;
};

#endif // RECTANGLE_H
