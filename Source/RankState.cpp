#include "RankState.h"

#include "FrameWork/GUI/InputBox.h"
#include "FrameWork/GUI/TextBox.h"
#include "FrameWork/GUI/Button.h"
#include "FrameWork/Manager.h"
#include "MenuState.h"

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <map>

RankState::RankState(sf::RenderWindow& window, bool adcionar, int pontos) 

:

GameState(window),
fundo(sf::Quads, 6000),
pontosPraAdd(pontos),
adcionando(adcionar)

{
    if (adcionar) 
        ajeitarEntrada();
    else
        ajeitarRank();
    gui.emplace_back(std::make_unique<Button>("Voltar", sf::FloatRect(540.f, 430.f, 100.f, 50.f), sf::Color::Red, sf::Color(200, 0, 0)));    
    
    float row = 0.f;
    for (unsigned i = 0; i < fundo.getVertexCount(); i += 4) {
        
        fundo[i].position = sf::Vector2f(float(((i / 4) * 16) % 656), row * 16.f);
        fundo[i + 1].position = sf::Vector2f(float(((i / 4) * 16) % 656) + 16.f + 16.f, row * 16.f);
        fundo[i + 2].position = sf::Vector2f(float(((i / 4) * 16) % 656) + 16.f + 16.f, row * 16.f + 16.f);
        fundo[i + 3].position = sf::Vector2f(float(((i / 4) * 16) % 656), row * 16.f + 16.f);

        fundo[i].texCoords = sf::Vector2f(0.f, 0.f);
        fundo[i + 1].texCoords = sf::Vector2f(16.f, 0.f);
        fundo[i + 2].texCoords = sf::Vector2f(16.f, 16.f);
        fundo[i + 3].texCoords = sf::Vector2f(0.f, 16.f);

        if (((i / 4) * 16) % 656 == 0 && i > 0)
            row++;
    }
    texturaFundo = TextureManager::carregar("Images/grama.png");
}

void RankState::handleInput() {
    sf::Event e;

    while (window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::TextEntered:
                for (auto &it : gui)
                    it->update(sf::Keyboard::Unknown, e.text.unicode);
                break;
            case sf::Event::KeyPressed:
                for (auto &it : gui)
                    it->update(e.key.code, -1);
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

    if (InputBox* entrada = dynamic_cast<InputBox*>(gui.front().get())) {
        if (entrada->foiUsado()) {
            escrerArquivo(entrada->getString());

            gui.erase(gui.begin(), gui.begin() + 2);
        }
    }
    else 
        ajeitarRank();
}

void RankState::draw() {
    window.clear();

    window.draw(fundo, texturaFundo.get());

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
    std::map<int, std::string, std::greater<int>> rank;
    std::string ret;

    if (arquivo.is_open()) {
        std::string nome;
        int pontos;

        while (std::getline(arquivo, nome)) {
            arquivo.read(reinterpret_cast<char*>(&pontos), sizeof(pontos));

            rank.insert({pontos, nome});
        }
        
        arquivo.close();
    }
    
    while (rank.size() > 5)
        rank.erase(--rank.end());
    for (auto &it : rank)
        ret.append(it.second + "\t" + std::to_string(it.first) + "\n");
    return ret;
}

void RankState::escrerArquivo(const std::string& nome) const {
    std::ofstream arquivo("data", std::ios::binary | std::ios::app);

    arquivo << nome << std::endl;
    arquivo.write(reinterpret_cast<const char*>(&pontosPraAdd), sizeof(pontosPraAdd));

    arquivo.close();
}

void RankState::ajeitarRank() {
    auto temp = std::make_unique<TextBox>("Ranking", sf::FloatRect(240.f, -100.f, 100.f, 150.f));

    temp->setFonte("Fonts/fonte.ttf");
    temp->setTextSettings(sf::Color::White, 75, sf::Color::Black);

    gui.insert(gui.begin(), std::move(temp));

    temp = std::make_unique<TextBox>(lerArquivo(), sf::FloatRect(265.f, 100.f, 400.f, 380.f), false, .025f);
    temp->setFonte("Fonts/fonte.ttf");
    temp->setTextSettings(sf::Color::White, 30, sf::Color::Black);
    
    gui.insert(gui.begin(), std::move(temp));
}

void RankState::ajeitarEntrada() {
    auto temp = std::make_unique<TextBox>("Digite seu nome", sf::FloatRect(120.f, 0.f, 340.f, 150.f));

    temp->setFonte("Fonts/fonte.ttf");
    temp->setTextSettings(sf::Color::White, 75, sf::Color::Black);

    gui.insert(gui.begin(), std::move(temp));
    gui.insert(gui.begin(),std::make_unique<InputBox>(sf::FloatRect(200, 220, 220, 50), 10));
}