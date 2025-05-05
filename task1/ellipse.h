#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "base_figure.h"
class Ellipse_Figure: public Base_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;
    double get_perimeter(const ShapeItem &shapeItem) override;
    void rotate_Shape(int shapeIndex, QList<ShapeItem> &shapes) override;
};
#endif //ELLIPSE_H
