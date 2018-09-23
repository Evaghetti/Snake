#include "Widget.h"

Widget::Widget(std::unique_ptr<sf::Shape> formato, bool ativo) {
    this->formato = std::move(formato);
    this->ativo = ativo;
}

void Widget::draw(sf::RenderTarget& target) {
    target.draw(*formato);
}

void Widget::update(const sf::Keyboard::Key keyPressed) {update();}
void Widget::update(const sf::Vector2f& mousePosition) {update();}

void Widget::setAtivo() {
    setAtivo(!ativo);
}

void Widget::setAtivo(bool ativo) {
    this->ativo = ativo;
}

bool Widget::taAtivo() const {
    return ativo;
}
