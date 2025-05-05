#ifndef SHAPE_H
#define SHAPE_H

enum Shape {
  None,
  Rectangle,
  Square,
  Circle,
  Ellipse,
  Triangle,
  Hexagon,
  Pentagon,
  Star5,
  Star6,
  Star8,
  Freehand,
  Diamond
};

struct ShapeItem {
  Shape shape{None};
  QColor color;
  QRect rect;
  QPolygon polygon;
  QList<QPoint> points;  // For freehand drawing
};
#endif  //SHAPE_H
