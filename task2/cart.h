#ifndef CART_H
#define CART_H
#include "rectangle.h"

class Cart final : public RectangleWidget {

  Q_OBJECT

 public:
  explicit Cart(QWidget* parent = nullptr);

 protected:
  void paintEvent(QPaintEvent*) override;
};
#endif  //CART_H
