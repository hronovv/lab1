#ifndef CIRCLE_H
#define CIRCLE_H
#include "ellipse.h"

class Circle_Figure : public Ellipse_Figure {
 public:
  double get_area(const ShapeItem& shapeItem) override;
  double get_perimeter(const ShapeItem& shapeItem) override;
  static void edit_Circle(int shapeIndex, QList<ShapeItem>& shapes,
                          QWidget* parent);
};
#endif  //CIRCLE_H
