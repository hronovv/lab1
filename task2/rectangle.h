#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <bits/stdc++.h>
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
constexpr int kFps = 60;
constexpr int kButtonSize = 90;
constexpr int kFontSizePx = 20;
constexpr int kSpeedY = 15;
constexpr int kSpeedX = 25;
constexpr int kWindowWidth = 2000;
constexpr int kWindowHeight = 2000;
constexpr int kMilSec = 1000;

class RectangleWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RectangleWidget(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private slots:
  void updatePosition();
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();
  void stopHorizontalMovement();
  void stopVerticalMovement();

 protected:
  int x_, y_;
  int dx_, dy_;
  QTimer* timer_;
};
#endif  //RECTANGLE_H
