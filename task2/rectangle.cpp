#include "rectangle.h"

RectangleWidget::RectangleWidget(QWidget* parent)
    : QWidget(parent), x_(50), y_(400), dx_(0), dy_(0) {
  setFocusPolicy(Qt::StrongFocus);  // фокус виджета на ввод от клавиатуры/мышки
  timer_ = new QTimer(this);        //таймер
  connect(timer_, &QTimer::timeout, this, &RectangleWidget::updatePosition);
  timer_->start(kMilSec / kFps);

  // Создаем кнопки
  auto* left_button = new QPushButton("Left⬅️");
  auto* right_button = new QPushButton("Right➡️");
  auto* up_button = new QPushButton("Up⬆️");
  auto* down_button = new QPushButton("Down⬇️");

  up_button->setFixedSize(kButtonSize, kButtonSize);
  down_button->setFixedSize(kButtonSize, kButtonSize);
  left_button->setFixedSize(kButtonSize, kButtonSize);
  right_button->setFixedSize(kButtonSize, kButtonSize);

  // Устанавливаем стиль для изменения размера шрифта
  QString set_font_size = "font-size: " + QString::number(kFontSizePx) + "px;";
  left_button->setStyleSheet(set_font_size);
  right_button->setStyleSheet(set_font_size);
  up_button->setStyleSheet(set_font_size);
  down_button->setStyleSheet(set_font_size);

  // Подключаем сигналы нажатия кнопок
  connect(left_button, &QPushButton::pressed, this, &RectangleWidget::moveLeft);
  connect(right_button, &QPushButton::pressed, this,
          &RectangleWidget::moveRight);
  connect(up_button, &QPushButton::pressed, this, &RectangleWidget::moveUp);
  connect(down_button, &QPushButton::pressed, this, &RectangleWidget::moveDown);

  // Подключаем сигналы отпускания кнопок
  connect(left_button, &QPushButton::released, this,
          &RectangleWidget::stopHorizontalMovement);
  connect(right_button, &QPushButton::released, this,
          &RectangleWidget::stopHorizontalMovement);
  connect(up_button, &QPushButton::released, this,
          &RectangleWidget::stopVerticalMovement);
  connect(down_button, &QPushButton::released, this,
          &RectangleWidget::stopVerticalMovement);

  // Создаём сеточный макет
  auto* button_layout = new QGridLayout();

  // Добавляем кнопки в определённые ячейки
  button_layout->addWidget(up_button, 0, 1);
  button_layout->addWidget(left_button, 1, 0);
  button_layout->addWidget(down_button, 1, 1);
  button_layout->addWidget(right_button, 1, 2);
  button_layout->setAlignment(Qt::AlignCenter);

  // Создаем вертикальный макет и добавляем кнопки вниз
  auto* main_layout = new QVBoxLayout(this);

  main_layout->addStretch();  // Добавляем пружину для отступа
  main_layout->addLayout(button_layout);
  button_layout->setAlignment(Qt::AlignRight);

  setLayout(main_layout);
}

void RectangleWidget::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  painter.setBrush(Qt::darkGreen);
  painter.drawRect(x_, y_, 150, 350);
}

void RectangleWidget::keyPressEvent(QKeyEvent* event) {
  if (event->isAutoRepeat()) {
    return;
  }
  switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
      dx_ = -kSpeedX;
      break;
    case Qt::Key_D:
    case Qt::Key_Right:
      dx_ = kSpeedX;
      break;
    case Qt::Key_W:
    case Qt::Key_Up:
      dy_ = -kSpeedY;
      break;
    case Qt::Key_Down:
    case Qt::Key_S:
      dy_ = kSpeedY;
      break;
    default:
      break;
  }
}

void RectangleWidget::keyReleaseEvent(QKeyEvent* event) {
  if (event->isAutoRepeat()) {
    return;
  }
  switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_D:
    case Qt::Key_Left:
    case Qt::Key_Right:
      dx_ = 0;
      break;
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_Up:
    case Qt::Key_Down:
      dy_ = 0;
      break;
  }
}

void RectangleWidget::updatePosition() {
  x_ += dx_;
  y_ += dy_;
  if (x_ < 0) {
    x_ = 0;
  }
  if (y_ - 90 < 0) {
    y_ = 90;
  }
  if (x_ + 500 > width()) {
    x_ = width() - 500;
  }
  if (y_ + 220 > height()) {
    y_ = height() - 220;
  }
  update();
}

void RectangleWidget::moveLeft() {
  dx_ = -kSpeedX;
}

void RectangleWidget::moveRight() {
  dx_ = kSpeedX;
}

void RectangleWidget::moveUp() {
  dy_ = -kSpeedY;
}

void RectangleWidget::moveDown() {
  dy_ = kSpeedY;
}

void RectangleWidget::stopHorizontalMovement() {
  dx_ = 0;
}

void RectangleWidget::stopVerticalMovement() {
  dy_ = 0;
}
