#ifndef HEXAGON_H
#define HEXAGON_H
#include "pentagon.h"
class Hexagon_Figure : public Pentagon_Figure {
public:
    double get_area(const ShapeItem &shapeItem) override;
    double get_perimeter(const ShapeItem &shapeItem) override;
};
#endif //HEXAGON_H
