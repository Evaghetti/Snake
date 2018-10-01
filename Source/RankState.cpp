#include "RankState.h"

#include "FrameWork/GUI/TextBox.h"
#include "FrameWork/GUI/Button.h"
#include "MenuState.h"

#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <fstream>
#include <vector>

RankState::RankState(sf::RenderWindow& window, bool adcionar) : GameState(window) {
    auto temp = std::make_unique<TextBox>("Ranking", sf::FloatRect(240.f, -100.f, 100.f, 150.f));

    temp->setFonte("Fonts/fonte.ttf");
    temp->setTextSettings(sf::Color::White, 75, sf::Color::Black);

    gui.emplace_back(std::move(temp));

    temp = std::make_unique<TextBox>(lerArquivo(), sf::FloatRect(240.f, 100.f, 400.f, 380.f));
    temp->setFonte("Fonts/fonte.ttf");
    temp->setTextSettings(sf::Color::White, 30, sf::Color::Black);

    gui.emplace_back(std::move(temp));
    gui.emplace_back(std::make_unique<Button>("Voltar", sf::FloatRect(540.f, 430.f, 100.f, 50.f), sf::Color::Red, sf::Color(200, 0, 0)));
}

void RankState::handleInput() {
    sf::Event e;

    while (window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                for (auto &it : gui)
                    it->update(e.key.code);
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseMoved:
                for (auto& it : gui)
                    it->update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                break;

            default: continue;
        }
    }
}

void RankState::update() {
    const float deltaTime = getDeltaTime();

    for (auto& it : gui)
        it->update(deltaTime);
}

void RankState::draw() {
    window.clear(sf::Color::Green);

    for (auto& it : gui)
        it->draw(window);

    window.display();
}

bool RankState::works() const {
    return GameState::works() && !gui.back()->foiUsado();
}

std::unique_ptr<GameState> RankState::wichChange() const {
    return std::make_unique<MenuState>(window);
}

std::string RankState::lerArquivo() const {
    std::ifstream arquivo("data", std::ios::binary);
    std::vector<unsigned> pontos;
    std::string ret;
    unsigned valorAtual;

    while (!arquivo.eof()) {
        arquivo.read(reinterpret_cast<char*>(&valorAtual), sizeof(unsigned));

        pontos.push_back(valorAtual);
    }
    
    std::sort(pontos.rbegin(), pontos.rend());
    for (auto it = pontos.begin(); it != pontos.begin() + 5; it++)
        ret.append("NOME\t" + std::to_string(*it) + "\n");
    return ret;
}