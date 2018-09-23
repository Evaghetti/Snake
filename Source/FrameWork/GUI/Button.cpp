#include "Button.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

Button::Button(sf::FloatRect dimensions, sf::Color corInativo, sf::Color corHover, sf::Color corSelecionado) :

Widget(std::make_unique<sf::RectangleShape>(sf::Vector2f(dimensions.width, dimensions.height))),
corInativo(corInativo),
corHover(corHover),
corSelecionado(corSelecionado)

{
    this->corAtual = corInativo;

    formato->setPosition(dimensions.left, dimensions.top);
}

void Button::update(const float deltaTime) {
    if (hovering)
        corAtual = corHover;
    else if (used)
        corAtual = corSelecionado;
    else
        corAtual = corInativo;
    
    formato->setFillColor(corAtual);
}

void Button::update(const sf::Keyboard::Key keyPressed) {
    used = hovering && keyPressed == sf::Keyboard::Enter;

    update();
}

void Button::update(const sf::Vector2f& mousePosition) {
    hovering = formato->getGlobalBounds().contains(mousePosition);
    used = hovering && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    update();
}

void Button::setHover() {
    hovering = !hovering;
}

bool Button::podeSerUsado() const {
    return taAtivo() && hovering;
}

bool Button::foiUsado() const {
    return used;
}