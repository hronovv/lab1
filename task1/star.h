#ifndef STAR_H
#define STAR_H
#include "base_figure.h"
class Star_Figure: public Base_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;
    double get_perimeter(const ShapeItem &shapeItem) override;
    QPoint get_centerOfMass(const ShapeItem &shapeItem) override;
    QPolygon createStar(const QPoint &center, int radius, int points, double innerRadiusRatio);
};
#endif //STAR_H
