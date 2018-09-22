#include "MenuState.h"

#include "PlayState.h"

#include <SFML/Window/Event.hpp>

MenuState::MenuState(sf::RenderWindow* window) : GameState(window) {}

void MenuState::handleInput() {
    sf::Event e;

    while (window->pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                sair = true;
                break;
            default: continue;
        }
    }
}

void MenuState::update() {
    const float deltaTime = getDeltaTime();
}

void MenuState::draw() {
    window->clear(sf::Color::Green);

    window->display();
}

bool MenuState::works() const {
    return GameState::works() && !sair;
}

std::unique_ptr<GameState> MenuState::wichChange() const {
    if (sair)
        return std::make_unique<PlayState>(window);
    return nullptr;
}