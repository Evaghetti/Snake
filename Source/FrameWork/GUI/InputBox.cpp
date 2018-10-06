#include "InputBox.h"

#include "../Manager.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>

InputBox::InputBox(const sf::FloatRect& dimensions, int tamanhoMaximo) 
:

Widget(std::make_unique<sf::RectangleShape>(sf::Vector2f(dimensions.width, dimensions.height))),
tamanhoMaximo(tamanhoMaximo)

{
    formato->setPosition(dimensions.left, dimensions.top);

    fonte = FontManager::carregar("Fonts/fonte.ttf");
    textoNaTela.setFont(*fonte);

    selecionado = false;

    textoNaTela.setString(std::wstring(tamanhoMaximo + 1, 'A'));
    while (!cabeDentro()) {
        unsigned tamanhoAtual = textoNaTela.getCharacterSize();

        textoNaTela.setCharacterSize(tamanhoAtual - 1);
    }

    textoNaTela.setPosition(dimensions.left, dimensions.top);
    textoNaTela.setString("");
    textoNaTela.setColor(sf::Color::Black);
}

void InputBox::update(const float deltaTime) {
    if (!cabeDentro())
        digitado.pop_back();

    textoNaTela.setString(digitado);
}

void InputBox::update(const sf::Keyboard::Key keyPressed, const wchar_t valor) {
    if (selecionado && valor != -1 && valor != 0x08) 
        digitado += valor;
    else if (keyPressed == sf::Keyboard::BackSpace) {
        if (digitado.length() > 0) 
            digitado.pop_back();
    }
    update();
}

void InputBox::update(const sf::Vector2f& mousePosition) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        selecionado = formato->getGlobalBounds().contains(mousePosition);
        
    update();
}

void InputBox::draw(sf::RenderTarget& target) {
    Widget::draw(target);

    target.draw(textoNaTela);
}

std::wstring InputBox::getString() {
    digitado.clear();
    return L"NOME";
}

bool InputBox::cabeDentro() const {
    auto caixaTexto = textoNaTela.getGlobalBounds();
    auto caixaFormato = formato->getGlobalBounds();

    return  caixaTexto.width <= caixaFormato.width && caixaTexto.height <= caixaFormato.height;
}