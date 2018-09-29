#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

#include "TextBox.h"

class Button : public Widget {
public:
    Button(std::string mensagem, sf::FloatRect dimensions, 
        sf::Color corInativo = sf::Color::White, 
        sf::Color corHover = {25, 25, 25}, 
        sf::Color corSelecionado = sf::Color::Black
    );

    void draw(sf::RenderTarget& target) override;

    void update(const float deltaTime = 0.f) override;
	void update(const sf::Keyboard::Key keyPressed) override;
    void update(const sf::Vector2f& mousePosition) override;

    void setHover();

    bool podeSerUsado() const override;
    bool foiUsado() const override;
private:
    bool hovering, used, ativo;

    const sf::Color corInativo, corHover, corSelecionado;
    TextBox mensagem;
    sf::Color corAtual;
};

#endif