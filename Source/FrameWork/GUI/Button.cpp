#include "Button.h"

#include "../Manager.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

Button::Button(std::string mensagem, sf::FloatRect dimensions, sf::Color corInativo, sf::Color corHover, sf::Color corSelecionado) :

Widget(std::make_unique<sf::RectangleShape>(sf::Vector2f(dimensions.width, dimensions.height))),
corInativo(corInativo),
corHover(corHover),
corSelecionado(corSelecionado),
texto(mensagem, *fonte)

{
    this->corAtual = corInativo;

    fonte = FontManager::carregar("Fonts/fonte.ttf");

    texto.setFont(*fonte);
    texto.setPosition(dimensions.left, dimensions.top);
    texto.setFillColor(sf::Color::Black);
    texto.setOutlineColor(sf::Color::White);
    texto.setOutlineThickness(1.f);

    formato->setPosition(dimensions.left, dimensions.top);

    hovering = false;
    used = false;
}

void Button::draw(sf::RenderTarget& target) {
    Widget::draw(target);

    target.draw(texto);
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

void Button::update(const sf::Keyboard::Key keyPressed, const wchar_t tecla) {
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

void Button::setTextSettings(const sf::Color& corTexto, unsigned tamanhoFonte, const sf::Color& corSublinhado, float tamanhoSublinhado) {
    texto.setFillColor(corTexto);
    texto.setOutlineColor(corSublinhado);

    texto.setCharacterSize(tamanhoFonte);
    texto.setOutlineThickness(tamanhoSublinhado);
}

bool Button::podeSerUsado() const {
    return taAtivo() && hovering;
}

bool Button::foiUsado() const {
    return used;
}