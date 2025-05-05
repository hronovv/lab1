#ifndef BASE_FIGURE_H
#define BASE_FIGURE_H
#include "qtlibs.h"
#include "shape.h" // Или другой нужный заголовок

class Base_Figure {
public:
    virtual ~Base_Figure() = default;
    virtual double get_area(const ShapeItem &shapeItem) = 0;
    virtual double get_perimeter(const ShapeItem &shapeItem) = 0;
    virtual QPoint get_centerOfMass(const ShapeItem &shapeItem);
    virtual void rotate_Shape(int shapeIndex, QList<ShapeItem> &shapes);
    virtual void move_center_offMass(int shapeIndex, QList<ShapeItem> &shapes, QWidget *parent);
    virtual void rotatePolygon(int shapeIndex, ShapeItem &shapeItem, int angle);
};

#endif // BASE_FIGURE_H
