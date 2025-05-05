#include "window.h"
#include "CenterOfMassWindow.h"
#include "ShapeCharacteristicsWindow.h"

// константы
const int kClearButtonWidth = 150;
const int kClearButtonHeight = 45;
const int kColorButtonWidth = 150;
const int kColorButtonHeight = 45;
const int kAllowDrawButtonWidth = 200;
const int kAllowDrawButtonHeight = 40;
const int kDeleteButtonWidth = 400;
const int kDeleteButtonHeight = 45;
const int kPiRatio = 2;
const int kPointRadius = 5;
const double kDiamondScale = 0.5;
const int kRectangleRadius = 2;
const int kDiamondTop = 4;
const double kCenterXScale = 0.5;

const int kStar5Points = 5;
const int kStar6Points = 6;
const int kPentagon5Points = 5;
const int kHexagon6Points = 6;
const int kStar8Points = 8;
const int kCircleScaleFactor = 2;
const int kDegrees360 = 360;
const double kMouseMovementBuffer = 2.0;
const int kShapesRotation = 90;

Rectangle_Figure* rectangle = new Rectangle_Figure;
Square_Figure* square = new Square_Figure;
Diamond_Figure* diamond = new Diamond_Figure;
Circle_Figure* circle = new Circle_Figure;
Ellipse_Figure* ellipse = new Ellipse_Figure;
Triangle_Figure* triangle = new Triangle_Figure;
Pentagon_Figure* pentagon = new Pentagon_Figure;
Hexagon_Figure* hexagon = new Hexagon_Figure;
Star_Figure* star = new Star_Figure;

Window::Window(QWidget* parent) : QWidget(parent) {
  // --- Button Block ---
  auto* clear_button = new QPushButton("Очистить");
  auto* color_button = new QPushButton("Выбрать цвет");
  auto* delete_button = new QPushButton("Удалить последнюю фигуру");
  auto* allow_draw_button = new QToolButton();

  clear_button->setFixedSize(kClearButtonWidth, kClearButtonHeight);
  color_button->setFixedSize(kColorButtonWidth, kColorButtonHeight);
  allow_draw_button->setFixedSize(kAllowDrawButtonWidth,
                                  kAllowDrawButtonHeight);
  delete_button->setFixedSize(kDeleteButtonWidth, kDeleteButtonHeight);

  allow_draw_button->setText("Выбрать фигуру");
  clear_button->setStyleSheet("font-size: 20px");
  color_button->setStyleSheet("font-size: 20px");
  allow_draw_button->setStyleSheet("font-size: 20px");
  delete_button->setStyleSheet("font-size: 20px");

  connect(clear_button, &QPushButton::clicked, this, &Window::clearContent);
  connect(color_button, &QPushButton::clicked, this, &Window::selectColor);
  connect(delete_button, &QPushButton::clicked, this, &Window::undoLastDrawing);

  // Context menu for shape selection
  auto* figure_menu = new QMenu(this);

  figure_menu->addAction("Произвольное рисование", this,
                         [this]() { selectShape(Freehand); });
  figure_menu->addAction("Прямоугольник", this,
                         [this]() { selectShape(Rectangle); });
  figure_menu->addAction("Квадрат", this, [this]() { selectShape(Square); });
  figure_menu->addAction("Треугольник", this,
                         [this]() { selectShape(Triangle); });
  figure_menu->addAction("Ромб", this, [this]() { selectShape(Diamond); });
  figure_menu->addAction("Эллипс", this, [this]() { selectShape(Ellipse); });
  figure_menu->addAction("Круг", this, [this]() { selectShape(Circle); });
  figure_menu->addAction("Пятиугольник", this,
                         [this]() { selectShape(Pentagon); });
  figure_menu->addAction("Шестиугольник", this,
                         [this]() { selectShape(Hexagon); });
  figure_menu->addAction("5-конечная звезда", this,
                         [this]() { selectShape(Star5); });
  figure_menu->addAction("6-конечная звезда", this,
                         [this]() { selectShape(Star6); });
  figure_menu->addAction("8-конечная звезда", this,
                         [this]() { selectShape(Star8); });
  allow_draw_button->setMenu(figure_menu);
  allow_draw_button->setPopupMode(QToolButton::InstantPopup);

  auto* button_layout = new QHBoxLayout();
  button_layout->addWidget(delete_button);
  button_layout->addWidget(clear_button);
  button_layout->addWidget(color_button);
  button_layout->addWidget(allow_draw_button);
  button_layout->setAlignment(Qt::AlignRight);

  auto* main_layout = new QVBoxLayout(this);
  main_layout->addLayout(button_layout);
  main_layout->addStretch();

  setLayout(main_layout);
}

void Window::showContextMenu(int shapeIndex) {
  QMenu context_menu(this);
  QAction* rotate_action =
      context_menu.addAction("Повернуть фигуру на 90 градусов");
  connect(rotate_action, &QAction::triggered, this,
          [this, shapeIndex]() { rotateShape(shapeIndex); });
  QAction* delete_action = context_menu.addAction("Удалить фигуру");
  connect(delete_action, &QAction::triggered, this,
          [this, shapeIndex]() { deleteShape(shapeIndex); });
  QAction* center_of_mass_action =
      context_menu.addAction("Показать центр масс");
  connect(center_of_mass_action, &QAction::triggered, this,
          [this, shapeIndex]() {
            QPoint center_of_mass = calculateCenterOfMass(shapes[shapeIndex]);
            centerOfMassPoint = center_of_mass;
            showCenterOfMassPoint = true;
            update();
            auto* center_of_mass_window =
                new CenterOfMassWindow(center_of_mass, this);
            center_of_mass_window->show();
          });
  QAction* move_center_of_mass_action =
      context_menu.addAction("Сдвинуть центр масс");
  connect(move_center_of_mass_action, &QAction::triggered, this,
          [this, shapeIndex]() { moveCenterOfMass(shapeIndex); });
  QAction* show_characteristics_action =
      context_menu.addAction("Показать характеристики");
  connect(show_characteristics_action, &QAction::triggered, this,
          [this, shapeIndex]() {
            auto* characteristics_window = new ShapeCharacteristicsWindow(
                calculateArea(shapes[shapeIndex]),
                calculatePerimeter(shapes[shapeIndex]), this);
            characteristics_window->show();
          });
  QAction* change_color_action = context_menu.addAction("Изменить цвет");
  connect(change_color_action, &QAction::triggered, this,
          [this, shapeIndex]() { changeColor(shapeIndex); });

  if (shapes[shapeIndex].shape != Circle) {
    QAction* change_angle_action = context_menu.addAction("Повернуть");
    connect(change_angle_action, &QAction::triggered, this,
            [this, shapeIndex]() { rotateShapeByAngle(shapeIndex); });
  }
  if (shapes[shapeIndex].shape == Square) {
    QAction* edit_square_action =
        context_menu.addAction("Изменить сторону квадрата");
    connect(edit_square_action, &QAction::triggered, this,
            [this, shapeIndex]() { editSquare(shapeIndex); });
  } else if (shapes[shapeIndex].shape == Circle) {
    QAction* edit_circle_action =
        context_menu.addAction("Изменить радиус круга");
    connect(edit_circle_action, &QAction::triggered, this,
            [this, shapeIndex]() { editCircle(shapeIndex); });
  }
  context_menu.exec(QCursor::pos());
}

void Window::clearContent() {
  shapes.clear();
  currentShape = None;
  this->update();
}

void Window::selectShape(Shape shape) {
  currentShape = shape;  // Set the currently selected shape
}

void Window::changeColor(int index) {
  QColor figure_color =
      QColorDialog::getColor(brushColor, this, "Выбрать цвет");
  if (figure_color.isValid()) {
    shapes[index].color = figure_color;
  }
}

void Window::selectColor() {
  QColor color = QColorDialog::getColor(brushColor, this, "Выбрать цвет");
  if (color.isValid()) {
    brushColor = color;
  }
}

void Window::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  for (const ShapeItem& shape_item : shapes) {
    painter.setBrush(shape_item.color);
    switch (shape_item.shape) {
      case Square:
      case Rectangle:
        painter.drawRect(shape_item.rect);
        break;
      case Circle:
        drawCircle(painter, shape_item.rect);
        break;
      case Ellipse:
        drawEllipse(painter, shape_item.rect);
        break;
      case Diamond:
        drawDiamond(painter, shape_item.rect);  // Рисуем ромб
        break;
      case Star5:
      case Star6:
      case Star8:
        painter.drawPolygon(shape_item.polygon);
        break;
      case Freehand:
        painter.drawPolyline(QPolygon(shape_item.points));
        break;
      case Triangle:
      case Hexagon:
      case Pentagon:
        painter.drawPolygon(shape_item.polygon);
        break;
      default:
        break;
    }
  }

  if (drawFigure) {
    painter.setBrush(brushColor);
    if (currentShape == Rectangle) {
      QRect temp_rect = QRect(startPoint, endPoint).normalized();
      painter.drawRect(temp_rect);
    } else if (currentShape == Square) {
      int side = std::max(std::abs(endPoint.x() - startPoint.x()),
                          std::abs(endPoint.y() - startPoint.y()));
      QRect temp_square = QRect(startPoint, QSize(side, side)).normalized();
      painter.drawRect(temp_square);
    } else if (currentShape == Circle) {
      drawCircle(painter, QRect(startPoint, endPoint).normalized());
    } else if (currentShape == Ellipse) {
      drawEllipse(painter, QRect(startPoint, endPoint).normalized());
    } else if (currentShape == Star5) {
      QPoint center = (startPoint + endPoint) / 2;
      int radius = std::max(std::abs(endPoint.x() - startPoint.x()),
                            std::abs(endPoint.y() - startPoint.y())) /
                   kCircleScaleFactor;
      QPolygon temp_star =
          star->createStar(center, radius, kStar5Points, kDiamondScale);
      painter.drawPolygon(temp_star);
    } else if (currentShape == Star6) {
      QPoint center = (startPoint + endPoint) / 2;
      int radius = std::max(std::abs(endPoint.x() - startPoint.x()),
                            std::abs(endPoint.y() - startPoint.y())) /
                   kCircleScaleFactor;
      QPolygon temp_star =
          star->createStar(center, radius, kStar6Points, kDiamondScale);
      painter.drawPolygon(temp_star);
    } else if (currentShape == Star8) {
      QPoint center = (startPoint + endPoint) / 2;
      int radius = std::max(std::abs(endPoint.x() - startPoint.x()),
                            std::abs(endPoint.y() - startPoint.y())) /
                   kCircleScaleFactor;
      QPolygon temp_star =
          star->createStar(center, radius, kStar8Points, kDiamondScale);
      painter.drawPolygon(temp_star);
    } else if (currentShape == Diamond) {
      QRect diamond_rect = QRect(startPoint, endPoint).normalized();
      drawDiamond(painter, diamond_rect);  // Рисуем ромб
    } else if (currentShape == Freehand) {
      // Implement specific drawing for freehand here
    } else if (currentShape == Triangle) {
      QPointF p1((startPoint.x() * 1.0 + endPoint.x()) / 2, startPoint.y());
      QPointF p2(startPoint.x(), endPoint.y());
      QPointF p3(endPoint.x(), endPoint.y());
      QPolygon triangle;
      triangle << p1.toPoint() << p2.toPoint() << p3.toPoint();
      painter.drawPolygon(triangle);
    } else if (currentShape == Hexagon) {
      QPolygon temp_hexagon;
      for (int i = 0; i < kHexagon6Points; ++i) {
        double angle = kPiRatio * M_PI * i / kHexagon6Points;
        QPointF point = QPointF(
            ((startPoint.x() + endPoint.x()) * kCenterXScale) +
                ((endPoint.x() - startPoint.x()) * kCenterXScale * cos(angle)),
            ((startPoint.y() + endPoint.y()) * kCenterXScale) +
                ((endPoint.y() - startPoint.y()) * kCenterXScale * sin(angle)));
        temp_hexagon << point.toPoint();
      }
      painter.drawPolygon(temp_hexagon);
    } else if (currentShape == Pentagon) {
      QPolygon temp_pentagon;
      QPointF center = QPointF((startPoint.x() + endPoint.x()) * kCenterXScale,
                               startPoint.y());
      double radius = std::hypot(endPoint.x() - startPoint.x(),
                                 endPoint.y() - startPoint.y()) /
                      kCircleScaleFactor;
      for (int i = 0; i < kPentagon5Points; ++i) {
        double angle = (kPiRatio * M_PI * i / kPentagon5Points) -
                       M_PI / kPiRatio;  // Keep top vertex at the top
        QPointF point = QPointF(center.x() + (radius * cos(angle)),
                                center.y() + (radius * sin(angle)));
        temp_pentagon << point.toPoint();
      }
      painter.drawPolygon(
          temp_pentagon);  // Draw the pentagon shape temporarily
    }
  }
  if (showCenterOfMassPoint) {
    painter.setBrush(Qt::red);
    painter.drawEllipse(
        centerOfMassPoint, kPointRadius,
        kPointRadius);  // Draw a red circle at the center of mass position
  }
}

void Window::drawCircle(QPainter& painter, const QRect& rect) {
  int radius = std::max(rect.width(), rect.height()) / kRectangleRadius;
  QPoint center = rect.center();
  QRect circle_rect(
      center - QPoint(radius, radius),
      QSize(radius * kCircleScaleFactor, radius * kCircleScaleFactor));
  painter.drawEllipse(circle_rect);
}

void Window::drawDiamond(QPainter& painter, const QRect& rect) {
  QPoint center = rect.center();
  QPolygon diamond;
  diamond << QPoint(center.x(), rect.top())     // Top point
          << QPoint(rect.right(), center.y())   // Right point
          << QPoint(center.x(), rect.bottom())  // Bottom point
          << QPoint(rect.left(), center.y());   // Left point
  painter.drawPolygon(diamond);
}

void Window::drawEllipse(QPainter& painter, const QRect& rect) {
  painter.drawEllipse(rect);
}

void Window::mousePressEvent(QMouseEvent* event) {
  if (currentShape != None && event->button() == Qt::LeftButton) {
    startPoint = event->pos();
    endPoint = startPoint;
    drawFigure = true;
    if (currentShape == Freehand) {
      ShapeItem freehand_item;
      freehand_item.shape = Freehand;
      freehand_item.color = brushColor;
      freehand_item.points.append(startPoint);
      shapes.append(freehand_item);
    }
  }
  if (movingShape && event->button() == Qt::LeftButton) {
    QPoint cursor_pos = QCursor::pos();
    for (int i = 0; i < shapes.size(); ++i) {
      if (shapes[i].rect.contains(event->pos()) ||
          shapes[i].polygon.containsPoint(mapFromGlobal(cursor_pos),
                                          Qt::OddEvenFill)) {
        shapeIndex = i;               // Запоминаем индекс фигуры
        lastMousePos = event->pos();  // Сохраняем начальную позицию мыши
        break;
      }
    }
  }
}

void Window::mouseMoveEvent(QMouseEvent* event) {
  if (currentShape != None && ((event->buttons() & Qt::LeftButton) != 0u)) {
    endPoint = event->pos();
    update();

    if (currentShape == Freehand) {
      shapes.last().points.append(endPoint);
    }
  }

  QPoint cursor_pos = event->pos();  // Позиция курсора

  if (shapeIndex == -1 && movingShape) {
    for (int i = 0; i < shapes.size(); ++i) {
      if (shapes[i].rect.contains(cursor_pos) ||
          shapes[i].polygon.containsPoint(cursor_pos, Qt::OddEvenFill)) {
        shapeIndex = i;  // Запоминаем индекс выбранной фигуры
        lastMousePos = cursor_pos;
        break;
      }
    }
  }

  if (shapeIndex != -1 && movingShape) {
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    ShapeItem& shape_item = shapes[shapeIndex];

    // Перемещение фигуры
    int dx = cursor_pos.x() - lastMousePos.x();
    int dy = cursor_pos.y() - lastMousePos.y();

    shape_item.rect.translate(dx, dy);
    shape_item.polygon.translate(dx, dy);

    lastMousePos = cursor_pos;

    update();
  }

  if (shapeIndex == -1 && scalingActive) {
    for (int i = 0; i < shapes.size(); ++i) {
      if (shapes[i].rect.contains(cursor_pos) ||
          shapes[i].polygon.containsPoint(cursor_pos, Qt::OddEvenFill)) {
        shapeIndex = i;  // Запоминаем индекс выбранной фигуры
        lastMousePos = cursor_pos;
        break;
      }
    }
  }

  if (scalingActive && shapeIndex != -1) {
    ShapeItem& shape_item = shapes[shapeIndex];
    if (shape_item.shape == Freehand) {
      return;
    }

    QPoint center_of_mass = calculateCenterOfMass(shape_item);

    // нашли смещение относительно центра
    QPointF current_pos = event->pos();
    QPointF prev_pos = lastMousePos;

    // расстояния вектора до курсора
    QPointF prev_vector = prev_pos - center_of_mass;
    QPointF current_vector = current_pos - center_of_mass;

    // нашли расстояние длины
    double prev_len = sqrt((prev_vector.x() * prev_vector.x()) +
                           (prev_vector.y() * prev_vector.y()));
    double current_len = sqrt((current_vector.x() * current_vector.x()) +
                              (current_vector.y() * current_vector.y()));

    if (prev_len < 1.0) {
      prev_len = 1.0;  // защита деления на ноль
    }
    double scale_factor = current_len / prev_len;

    // масштабируем фигуру относительно центра масс
    switch (shape_item.shape) {
      case Rectangle:
      case Square: {
        QSize new_size(shape_item.rect.width() * scale_factor,
                       shape_item.rect.height() * scale_factor);
        QRect new_rect(QPoint(0, 0), new_size);
        new_rect.moveCenter(center_of_mass);
        shape_item.rect = new_rect;
        break;
      }
      case Circle:
      case Ellipse: {
        // центр фиксируем и меняем размер
        QSize new_size(shape_item.rect.width() * scale_factor,
                       shape_item.rect.height() * scale_factor);
        QRect new_rect(QPoint(0, 0), new_size);
        new_rect.moveCenter(center_of_mass);  // фиксируем центр масс
        shape_item.rect = new_rect;
        break;
      }
      case Diamond: {
        // Масштабируем базовый прямоугольник
        QSize new_size(shape_item.rect.width() * scale_factor,
                       shape_item.rect.height() * scale_factor);
        QRect new_rect(QPoint(0, 0), new_size);
        new_rect.moveCenter(center_of_mass);  // Фиксируем центр

        // Заново создаем точки ромба из нового прямоугольника
        QPolygon diamond;
        diamond << QPoint(new_rect.center().x(), new_rect.top())
                << QPoint(new_rect.right(), new_rect.center().y())
                << QPoint(new_rect.center().x(), new_rect.bottom())
                << QPoint(new_rect.left(), new_rect.center().y());

        shape_item.rect = new_rect;    // Обновляем базовый rect
        shape_item.polygon = diamond;  // Обновляем полигон ромба
        break;
      }
      case Triangle:
      case Pentagon:
      case Hexagon:
      case Star5:
      case Star6:
      case Star8: {
        QPolygon scaled_poly;
        for (QPoint p : shape_item.polygon) {
          // Масштабируем каждую точку относительно центра
          QPointF offset = p - center_of_mass;
          QPointF scaled_point = center_of_mass + offset * scale_factor;
          scaled_poly << scaled_point.toPoint();
        }
        shape_item.polygon = scaled_poly;
        shape_item.rect = scaled_poly.boundingRect();
        break;
      }
      default:
        break;
    }

    lastMousePos = event->pos();  // Обновляем позицию мыши
    update();
  }
}

void Window::mouseReleaseEvent(QMouseEvent* event) {
  endPoint = event->pos();
  if (currentShape != None) {
    ShapeItem item;
    item.color = brushColor;
    if (currentShape == Freehand) {
      item.shape = Freehand;
    }
    if (currentShape == Rectangle) {
      item.shape = Rectangle;
      item.rect = QRect(startPoint, endPoint).normalized();
    } else if (currentShape == Square) {
      int side = std::max(std::abs(endPoint.x() - startPoint.x()),
                          std::abs(endPoint.y() - startPoint.y()));
      item.shape = Square;
      item.rect = QRect(startPoint, QSize(side, side)).normalized();
    } else if (currentShape == Circle) {
      item.shape = Circle;
      item.rect = QRect(startPoint, endPoint).normalized();
    } else if (currentShape == Ellipse) {
      item.shape = Ellipse;
      item.rect = QRect(startPoint, endPoint).normalized();
    } else if (currentShape == Star5) {
      int radius = std::max(std::abs(endPoint.x() - startPoint.x()),
                            std::abs(endPoint.y() - startPoint.y())) /
                   kCircleScaleFactor;
      QPoint center = (startPoint + endPoint) / 2;
      item.shape = Star5;
      item.polygon =
          star->createStar(center, radius, kStar5Points, kDiamondScale);
    } else if (currentShape == Star6) {
      int radius = std::max(std::abs(endPoint.x() - startPoint.x()),
                            std::abs(endPoint.y() - startPoint.y())) /
                   kCircleScaleFactor;
      QPoint center = (startPoint + endPoint) / 2;
      item.shape = Star6;
      item.polygon =
          star->createStar(center, radius, kStar6Points, kDiamondScale);
    } else if (currentShape == Star8) {
      int radius = std::max(std::abs(endPoint.x() - startPoint.x()),
                            std::abs(endPoint.y() - startPoint.y())) /
                   kCircleScaleFactor;
      QPoint center = (startPoint + endPoint) / 2;
      item.shape = Star8;
      item.polygon =
          star->createStar(center, radius, kStar8Points, kDiamondScale);
    } else if (currentShape == Triangle) {
      QPointF p1((startPoint.x() + endPoint.x()) * kCenterXScale,
                 startPoint.y());
      QPointF p2(startPoint.x(), endPoint.y());
      QPointF p3(endPoint.x(), endPoint.y());
      QPolygon triangle;
      triangle << p1.toPoint() << p2.toPoint() << p3.toPoint();
      item.shape = Triangle;
      item.polygon = triangle;
    } else if (currentShape == Pentagon) {
      QPolygon pentagon;
      QPointF center = QPointF((startPoint.x() + endPoint.x()) * kCenterXScale,
                               startPoint.y());
      double radius = std::hypot(endPoint.x() - startPoint.x(),
                                 endPoint.y() - startPoint.y()) /
                      kCircleScaleFactor;
      for (int i = 0; i < kPentagon5Points; ++i) {
        double angle =
            (kPiRatio * M_PI * i / kPentagon5Points) - M_PI / kPiRatio;
        QPointF point = QPointF(center.x() + (radius * cos(angle)),
                                center.y() + (radius * sin(angle)));
        pentagon << point.toPoint();
      }
      item.shape = Pentagon;
      item.polygon = pentagon;
      item.rect = pentagon.boundingRect();
    } else if (currentShape == Hexagon) {
      QPolygon hexagon;
      for (int i = 0; i < kHexagon6Points; ++i) {
        double angle = kPiRatio * M_PI * i / kHexagon6Points;
        QPointF point = QPointF(
            ((startPoint.x() + endPoint.x()) * kCenterXScale) +
                ((endPoint.x() - startPoint.x()) * kCenterXScale * cos(angle)),
            ((startPoint.y() + endPoint.y()) * kCenterXScale) +
                ((endPoint.y() - startPoint.y()) * kCenterXScale * sin(angle)));
        hexagon << point.toPoint();
      }
      item.shape = Hexagon;
      item.polygon = hexagon;
      item.rect = hexagon.boundingRect();
    } else if (currentShape == Diamond) {
      item.shape = Diamond;
      item.rect = QRect(startPoint, endPoint).normalized();
      // Создаем полигон ромба
      QPolygon diamond;
      diamond << QPoint(item.rect.center().x(), item.rect.top())
              << QPoint(item.rect.right(), item.rect.center().y())
              << QPoint(item.rect.center().x(), item.rect.bottom())
              << QPoint(item.rect.left(), item.rect.center().y());
      item.polygon = diamond;
    }
    shapes.append(item);
    drawFigure = false;
    this->update();
  }

  if (event->button() == Qt::LeftButton) {
    this->setCursor(QCursor(Qt::ArrowCursor));
    movingShape =
        false;        // Устанавливаем флаг в false, когда кнопка мыши отпущена
    shapeIndex = -1;  // Сбрасываем индекс фигуры
  }
}

void Window::rotateShape(int index) {
  ShapeItem& shape_item = shapes[index];
  if (shapes[index].shape == Rectangle) {
    rectangle->rotate_Shape(index, shapes);
  } else if (shapes[index].shape == Square) {
    square->rotate_Shape(index, shapes);
  } else if (shape_item.shape == Diamond) {
    diamond->rotate_Shape(index, shapes);
  } else if (shape_item.shape == Circle) {
    circle->rotate_Shape(index, shapes);
  } else if (shape_item.shape == Ellipse) {
    ellipse->rotate_Shape(index, shapes);
  } else if (shape_item.shape == Star5 || shape_item.shape == Star6 ||
             shape_item.shape == Star8 || shape_item.shape == Triangle ||
             shape_item.shape == Hexagon ||
             shape_item.shape ==
                 Pentagon) {  // короче виртуальный для всех остальных
    triangle->rotate_Shape(index, shapes);  // одинаково работает для всех
  }
  this->update();
}

void Window::undoLastDrawing() {
  if (!shapes.isEmpty()) {
    shapes.removeLast();
    update();
  }
}

void Window::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Z) {
    undoLastDrawing();
  } else if (event->key() == Qt::Key_R) {
    QPoint cursor_pos = QCursor::pos();
    for (int i = 0; i < shapes.size(); ++i) {
      if (shapes[i].rect.contains(mapFromGlobal(cursor_pos)) ||
          shapes[i].polygon.containsPoint(mapFromGlobal(cursor_pos),
                                          Qt::OddEvenFill)) {
        showContextMenu(i);
      }
    }
  } else if (!shapes.isEmpty() && event->key() == Qt::Key_F) {
    currentShape = None;  // Например, перемещение при нажатой клавише "F"
    movingShape = true;   // Устанавливаем флаг в true для перемещения
  } else if (!shapes.isEmpty() && event->key() == Qt::Key_G) {
    scalingActive = true;
    currentShape = None;
  }
}

void Window::deleteShape(int index) {
  if (index >= 0 && index < shapes.size()) {
    shapes.removeAt(index);
    update();
  }
}

QPoint Window::calculateCenterOfMass(const ShapeItem& shapeItem) {
  switch (shapeItem.shape) {
    case Rectangle:
      return rectangle->get_centerOfMass(shapeItem);
    case Square:
      return square->get_centerOfMass(shapeItem);
    case Diamond:
      return diamond->get_centerOfMass(shapeItem);
    case Circle:
      return circle->get_centerOfMass(shapeItem);
    case Ellipse:
      return ellipse->get_centerOfMass(shapeItem);
    case Triangle:
      return triangle->get_centerOfMass(shapeItem);
    case Pentagon:
      return pentagon->get_centerOfMass(shapeItem);
    case Hexagon:
      return hexagon->get_centerOfMass(shapeItem);
    case Star5:
    case Star6:
    case Star8:
      return star->get_centerOfMass(shapeItem);
    default:
      return {};  // Возврат в случае, если фигура не распознана
  }
}

void Window::clearCenterOfMassPoint() {
  showCenterOfMassPoint = false;  // Set the flag to false
  this->update();                 // Request a repaint
}

double Window::calculateArea(const ShapeItem& shapeItem) {
  double area{};
  switch (shapeItem.shape) {
    case Rectangle:
      area = rectangle->get_area(shapeItem);
      break;
    case Square:
      area = square->get_area(shapeItem);
      break;
    case Diamond:
      area = diamond->get_area(shapeItem);
      break;
    case Circle:
      area = square->get_area(shapeItem);
      break;
    case Ellipse:
      area = ellipse->get_area(shapeItem);
      break;
    case Triangle:
      area = triangle->get_area(shapeItem);
      break;
    case Pentagon:
      area = pentagon->get_area(shapeItem);
      break;
    case Hexagon:
      area = hexagon->get_area(shapeItem);
      break;
    case Star5:
    case Star6:
    case Star8:
      area = star->get_area(shapeItem);
      break;
    default:
      break;
  }
  return area;
}

double Window::calculatePerimeter(const ShapeItem& shapeItem) {
  double perimeter = 0.0;
  switch (shapeItem.shape) {
    case Rectangle:
      perimeter = rectangle->get_perimeter(shapeItem);
      break;
    case Square:
      perimeter = square->get_perimeter(shapeItem);
      break;
    case Diamond:
      perimeter = diamond->get_perimeter(shapeItem);
      break;
    case Circle:
      perimeter = circle->get_perimeter(shapeItem);
      break;
    case Ellipse:
      perimeter = ellipse->get_perimeter(shapeItem);
      break;
    case Triangle:
      if (shapeItem.polygon.size() == 3) {
        perimeter = triangle->get_perimeter(shapeItem);
      }
      break;
    case Pentagon:
      perimeter = pentagon->get_perimeter(shapeItem);
      break;
    case Hexagon:
      perimeter = hexagon->get_perimeter(shapeItem);
      break;
    case Star5:
    case Star6:
    case Star8:
      perimeter = star->get_perimeter(shapeItem);
      break;
    default:
      break;
  }
  return perimeter;
}

void Window::moveCenterOfMass(int shapeIndex) {
  if (shapes[shapeIndex].shape == Rectangle ||
      shapes[shapeIndex].shape == Square ||
      shapes[shapeIndex].shape == Diamond ||
      shapes[shapeIndex].shape == Circle ||
      shapes[shapeIndex].shape == Ellipse) {
    rectangle->move_center_offMass(shapeIndex, shapes, this);  // одинаково
  } else {
    triangle->move_center_offMass(shapeIndex, shapes, this);  // одинаково
  }
}

void Window::keyReleaseEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_F && !shapes.empty()) {
    movingShape = false;  // Устанавливаем флаг в false, когда клавиша отпущена
    currentShape = shapes[shapes.size() - 1].shape;
    shapeIndex = -1;  // Сбрасываем индекс фигуры
  } else if (event->key() == Qt::Key_G) {
    scalingActive = false;  // Выключаем режим масштабирования
    currentShape = shapes[shapes.size() - 1].shape;
    shapeIndex = -1;
    update();
  }
}

void Window::editSquare(int shapeIndex) {
  Square_Figure::edit_Square(shapeIndex, shapes, this);
}

void Window::editCircle(int shapeIndex) {
  Circle_Figure::edit_Circle(shapeIndex, shapes, this);
}

void Window::rotateShapeByAngle(int shapeIndex) {
  if (shapeIndex < 0 || shapeIndex >= shapes.size()) {
    return;
  }
  bool ok;
  int angle = QInputDialog::getInt(this, "Повернуть фигуру",
                                   "Введите угол поворота (градусы):", 0,
                                   -kDegrees360, kDegrees360, 1, &ok);
  if (ok) {
    ShapeItem& shape_item = shapes[shapeIndex];
    switch (shape_item.shape) {
      case Rectangle:
        rectangle->rotatePolygon(shapeIndex, shape_item, angle);
        break;
      case Square:
        square->rotatePolygon(shapeIndex, shape_item, angle);
        break;
      case Ellipse:
        ellipse->rotatePolygon(shapeIndex, shape_item, angle);
        break;
      case Circle:
        circle->rotatePolygon(shapeIndex, shape_item, angle);
        break;
      case Diamond:
        diamond->rotatePolygon(shapeIndex, shape_item, angle);
        break;
      case Triangle:
      case Hexagon:
      case Pentagon:
      case Star5:
      case Star6:
      case Star8:
        star->rotatePolygon(shapeIndex, shape_item, angle);
        break;
      default:
        break;
    }

    this->update();
  }
}
