#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Widget.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>

class TextBox : public Widget {
public:
    TextBox(std::string mensagem, sf::FloatRect dimensions, bool instantaneo = true, float tempoEspera = 0.f);

    void draw(sf::RenderTarget& target) override;
    void update(const float deltaTime = 0.f) override;

    void setFonte(std::string caminhoFonte, unsigned tamanho = 30u);

    void setTextSettings(const sf::Color& novaCorFonte = sf::Color::White, unsigned tamanhoFonte = 30U, const sf::Color& novaCorSub = sf::Color::Transparent, float tamanhoSub = 1.f);

    void setMensagem(std::string mensagem);
private:
    void split(std::string frase);
    bool precisaNovaLinha() const;
private:
    std::vector<std::string> palavras;
    sf::Text jaEscrito;

    std::shared_ptr<sf::Font> fonte;

    float tempoEspera, tempoPassado;
    bool instantaneo;
};

#endif