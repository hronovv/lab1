#ifndef DIAMOND_H
#define DIAMOND_H
#include "window.h"
class Diamond_Figure : public Rectangle_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;
    double get_perimeter(const ShapeItem &shapeItem) override;
    void rotatePolygon(int shapeIndex, ShapeItem &shapeItem, int angle) override;
};
#endif //DIAMOND_H
