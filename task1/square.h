#ifndef SQUARE_H
#define SQUARE_H
#include "rectangle.h"
class Square_Figure : public Rectangle_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;
    double get_perimeter(const ShapeItem &shapeItem) override;
    void rotate_Shape(int index,QList<ShapeItem> &shapes) override;
    static void edit_Square(int shapeIndex, QList<ShapeItem> &shapes, QWidget *parent);
};
#endif //SQUARE_H
