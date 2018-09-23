#include "Button.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

Button::Button(std::string mensagem, sf::FloatRect dimensions, sf::Color corInativo, sf::Color corHover, sf::Color corSelecionado) :

Widget(std::make_unique<sf::RectangleShape>(sf::Vector2f(dimensions.width, dimensions.height))),
corInativo(corInativo),
corHover(corHover),
corSelecionado(corSelecionado),
mensagem(mensagem, dimensions)

{
    this->corAtual = corInativo;
    this->mensagem.setFonte("Fonts/fonte.ttf");
    this->mensagem.setTextSettings({1.f, 1.f}, sf::Color::Black, sf::Color::White, 0.2f);

    formato->setPosition(dimensions.left, dimensions.top);
}

void Button::draw(sf::RenderTarget& target) {
    Widget::draw(target);
    mensagem.draw(target);
}

void Button::update(const float deltaTime) {
    if (hovering)
        corAtual = corHover;
    else if (used)
        corAtual = corSelecionado;
    else
        corAtual = corInativo;
    
    mensagem.update(deltaTime);
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