#ifndef INPUTBOX_H
#define INPUTBOX_H

#include "Widget.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>
#include <string>

class InputBox : public Widget {
public:
    InputBox(const sf::FloatRect& dimensions, int tamanhoMaximo);

    void update(const float deltaTime = 0.f) override;
    void update(const sf::Keyboard::Key keyPressed, const wchar_t valor) override;
    void update(const sf::Vector2f& mousePosition) override;

    void draw(sf::RenderTarget& target) override;

    std::wstring getString();
    bool foiUsado() const override;
private:
    bool cabeDentro() const;
private:
    std::wstring digitado;

    std::shared_ptr<sf::Font> fonte;
    sf::Text textoNaTela;

    bool selecionado, terminouDigitar;
    const int tamanhoMaximo;
};

#endif