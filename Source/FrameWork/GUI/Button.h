#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include <memory>

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
    void setTextSettings(const sf::Color& corTexto, 
        unsigned tamanhoFonte = 30U,
        const sf::Color& corSublinhado = sf::Color::Transparent,
        float tamanhoSublinhado = 1.f
    );

    bool podeSerUsado() const override;
    bool foiUsado() const override;
private:
    bool hovering, used, ativo;

    const sf::Color corInativo, corHover, corSelecionado;

    std::shared_ptr<sf::Font> fonte;
    sf::Color corAtual;
    sf::Text texto;
};

#endif