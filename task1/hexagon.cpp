#include "hexagon.h"
constexpr double kHexagonRatio = 2.0;
constexpr double kHexagonNumber = 6.0;

double Hexagon_Figure::get_area(const ShapeItem& shapeItem) {
  double side_length = shapeItem.rect.width() /
                       kHexagonRatio;  //половина длины как радиус равен стороне
  return (3 * sqrt(3) / 2) *
         std::pow(side_length, 2);  //формула площади правильного шестиугольника
}

double Hexagon_Figure::get_perimeter(const ShapeItem& shapeItem) {
  double side_length =
      shapeItem.rect.width() / kHexagonRatio;  //сторона как радиус описанной
  return kHexagonNumber * side_length;         //умножаем на кол-во сторон
}
