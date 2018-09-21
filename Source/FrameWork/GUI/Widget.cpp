#include "Widget.h"

Widget::Widget(const sf::Vector2f & position) : position(position) {}

void Widget::handleInput() {
  throw "handleInput não implementado np Widget";
}

void Widget::handleMouse(const sf::Vector2f& mousePos) {
  throw "Hande mouse não implementado no Widget";
}
