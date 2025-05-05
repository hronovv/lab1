#include <bits/stdc++.h>
#include <QApplication>
#include <QKeyEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include "window.h"
constexpr int kWidth = 3000;
constexpr int kHeight = 1800;

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Window window;
  window.resize(kWidth, kHeight);
  window.show();
  return QApplication::exec();
}
