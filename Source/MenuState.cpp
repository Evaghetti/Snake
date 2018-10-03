#include "MenuState.h"

#include "PlayState.h"
#include "RankState.h"

#include "FrameWork/GUI/Button.h"
#include "FrameWork/GUI/TextBox.h"
#include "FrameWork/Manager.h"

#include <SFML/Window/Event.hpp>

MenuState::MenuState(sf::RenderWindow& window) 

: 
GameState(window),
fundo(sf::Quads, 6000)

{
    auto temp = std::make_unique<TextBox>("Snake", sf::FloatRect(180.f, -75.f, 300.f, 125.f));

    temp->setFonte("Fonts/fonte.ttf");

    temp->setTextSettings(sf::Color::White, 150, sf::Color::Black);

    gui.emplace_back(std::move(temp));
    gui.emplace_back(std::make_unique<Button>("Novo Jogo", sf::FloatRect(240.f, 240.f, 180.f, 50.f)));
    gui.emplace_back(std::make_unique<Button>("Ranking", sf::FloatRect(240.f, 300.f, 180.f, 50.f)));
    gui.emplace_back(std::make_unique<Button>("Sair", sf::FloatRect(240.f, 360.f, 180.f, 50.f)));

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

void MenuState::handleInput() {
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

void MenuState::update() {
    const float deltaTime = getDeltaTime();
    
    for (auto &it : gui)
        it->update(deltaTime);
}

void MenuState::draw() {
    window.clear();

    window.draw(fundo, texturaFundo.get());
    for (auto& it : gui)
        it->draw(window);

    window.display();
}

bool MenuState::works() const {
    return GameState::works() && !std::any_of(gui.begin(), gui.end(), [](const auto& it) {
        return it->foiUsado();
    });
}

std::unique_ptr<GameState> MenuState::wichChange() const {
    if (gui[1]->foiUsado())
        return std::make_unique<PlayState>(window);
    else if (gui[2]->foiUsado())
        return std::make_unique<RankState>(window);
    return nullptr;
}