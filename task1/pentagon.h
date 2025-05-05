#ifndef PENTAGON_H
#define PENTAGON_H
#include "base_figure.h"
class Pentagon_Figure : public Base_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;
    double get_perimeter(const ShapeItem &shapeItem) override;
    QPoint get_centerOfMass(const ShapeItem &shapeItem) override;
};
#endif //PENTAGON_H
