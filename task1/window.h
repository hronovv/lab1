#ifndef WINDOW_H
#define WINDOW_H
#include "base_figure.h"
#include "circle.h"
#include "diamond.h"
#include "ellipse.h"
#include "hexagon.h"
#include "pentagon.h"
#include "qtlibs.h"
#include "rectangle.h"
#include "shape.h"
#include "square.h"
#include "star.h"
#include "triangle.h"

class Window : public QWidget {
  Q_OBJECT

 public:
  static QPoint calculateCenterOfMass(const ShapeItem& shapeItem);
  QList<ShapeItem> shapes;
  explicit Window(QWidget* parent = nullptr);
 public slots:
  void rotateShapeByAngle(int shapeIndex);
  void clearCenterOfMassPoint();
  void clearContent();
  void editSquare(int shapeIndex);
  void editCircle(int shapeIndex);
  void selectShape(Shape shape);
  void selectColor();
  void undoLastDrawing();
  void changeColor(int index);
  void showContextMenu(int shapeIndex);
  void rotateShape(int index);
  void deleteShape(int index);
  static double calculateArea(const ShapeItem& shapeItem);
  static double calculatePerimeter(const ShapeItem& shapeItem);

 protected:
  void paintEvent(QPaintEvent*) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  QRect originalRect;
  bool movingShape{false};    // Флаг, указывающий, перемещаем ли мы фигуру
  int shapeIndex{-1};         // Индекс фигуры, которую мы перемещаем
  QPoint lastMousePos;        // Последняя позиция мыши
  bool scalingActive{false};  // Флаг для масштабирования
  double scaleFactor{1.0};    // Коэффициент масштабирования
  bool drawFigure{false};
  QPoint startPoint;
  QPoint endPoint;
  QPoint centerOfMassPoint;  // NEW: Store the center of mass point
  bool showCenterOfMassPoint{
      false};  // NEW: Flag to determine whether to show the point
  void moveCenterOfMass(int shapeIndex);
  QColor brushColor{Qt::white};
  Shape scaleShape{None};
  Shape currentShape{None};  // Store currently selected shape
  static void drawCircle(QPainter& painter, const QRect& rect);
  static void drawEllipse(QPainter& painter, const QRect& rect);
  static void drawDiamond(
      QPainter& painter,
      const QRect& rect);  // Новая функция для рисования ромба
};
#endif  // WINDOW_H
