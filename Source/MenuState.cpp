#include "MenuState.h"

#include "PlayState.h"

#include "FrameWork/GUI/Button.h"
#include "FrameWork/GUI/TextBox.h"

#include <SFML/Window/Event.hpp>

MenuState::MenuState(sf::RenderWindow* window) : GameState(window) {

    auto temp = std::make_unique<TextBox>("Snake", sf::FloatRect(180.f, 0.f, 300.f, 125.f));

    temp->setFonte("Fonts/fonte.ttf");

    temp->setTextSettings({5.5f, 3.f}, sf::Color::White, sf::Color::Black);

    gui.emplace_back(std::move(temp));
    gui.emplace_back(std::make_unique<Button>("Novo Jogo", sf::FloatRect(240.f, 240.f, 180.f, 50.f)));
}

void MenuState::handleInput() {
    sf::Event e;

    while (window->pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                for (auto &it : gui)
                    it->update(e.key.code);
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseMoved:
                for (auto& it : gui)
                    it->update(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
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
    window->clear(sf::Color::Green);

    for (auto& it : gui)
        it->draw(*window);

    window->display();
}

bool MenuState::works() const {
    return GameState::works() && !gui.back()->foiUsado();
}

std::unique_ptr<GameState> MenuState::wichChange() const {
    if (gui.back()->foiUsado())
        return std::make_unique<PlayState>(window);
    return nullptr;
}