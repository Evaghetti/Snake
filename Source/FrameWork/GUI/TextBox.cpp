#include "TextBox.h"

#include "../Manager.h"

#include <SFML/Graphics/RectangleShape.hpp>

#include <sstream>

TextBox::TextBox(std::string mensagem, sf::FloatRect dimensions, bool instantaneo, float tempoEspera) :

Widget(std::make_unique<sf::RectangleShape>(sf::Vector2f(dimensions.width, dimensions.height)))

{
    formato->setPosition(dimensions.left, dimensions.top);
    jaEscrito.setPosition(dimensions.left, dimensions.top);
    
    this->instantaneo = instantaneo;
    this->tempoEspera = tempoEspera;

    split(mensagem);
    setBoxColor(sf::Color::Transparent);
    setOutlineColor(sf::Color::Transparent);
}

void TextBox::draw(sf::RenderTarget& target) {
    Widget::draw(target);
    target.draw(jaEscrito);
}

void TextBox::update(const float deltaTime) {
    if (instantaneo) {
        while (palavras.size() > 0) {
            if (precisaNovaLinha())
                jaEscrito.setString(jaEscrito.getString() + '\n');
            jaEscrito.setString(jaEscrito.getString() + " " + palavras.front());
            palavras.erase(palavras.begin());
        }
    }
    else {
        tempoPassado += deltaTime;
        if (tempoPassado >= tempoEspera && escrevendo) {
            jaEscrito.setString(jaEscrito.getString() + palavras.front().front());
            
            palavras.front().erase(palavras.front().begin());
            if (palavras.front().length() <= 0) {
                palavras.erase(palavras.begin());
                
                if (palavras.size() > 0) 
                    jaEscrito.setString(jaEscrito.getString() + ((precisaNovaLinha()) ? "\n" : " "));
            }

            tempoPassado = 0.f;
        }
    }

    escrevendo = palavras.size() > 0u;
}

void TextBox::setFonte(std::string caminhoFonte, unsigned tamanho) {
    fonte = FontManager::carregar(caminhoFonte);

    jaEscrito.setFont(*fonte);
    jaEscrito.setCharacterSize(tamanho);
}

void TextBox::setOutlineColor(const sf::Color& novaCor, float tamanho) {
    formato->setOutlineColor(novaCor);
    formato->setOutlineThickness(tamanho);
}

void TextBox::setBoxColor(const sf::Color& novaCor) {
    formato->setFillColor(novaCor);
}

void TextBox::setTextSettings(const sf::Color& novaCorFonte, unsigned tamanhoFonte, const sf::Color& novaCorSub, float tamanhoSub) {
    jaEscrito.setCharacterSize(tamanhoFonte);
    jaEscrito.setFillColor(novaCorFonte);
    jaEscrito.setOutlineColor(novaCorSub);
    jaEscrito.setOutlineThickness(tamanhoSub);
}


void TextBox::setMensagem(std::string mensagem) {
    if (!escrevendo) {
        jaEscrito.setString("");
        split(mensagem);
    }
}

void TextBox::split(std::string frase) {
    std::stringstream ss(frase);
    std::string buffer;
    palavras.clear();

    while (std::getline(ss, buffer, ' '))
        palavras.push_back(buffer);
}

bool TextBox::precisaNovaLinha() const {
    sf::Text temp = jaEscrito;
    temp.setString(temp.getString() + palavras.front());

    sf::FloatRect boxSeEscrever = temp.getGlobalBounds();
    sf::FloatRect caixa = formato->getGlobalBounds();
    
    return  boxSeEscrever.left + boxSeEscrever.width > caixa.left + caixa.width;
}