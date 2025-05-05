#include "cart.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Cart window;
  window.resize(kWindowWidth, kWindowHeight);
  window.show();
  return QApplication::exec();
}

#include "main.moc"
