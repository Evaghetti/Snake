#include "MenuState.h"

#include "PlayState.h"

#include <SFML/Window/Event.hpp>

MenuState::MenuState(sf::RenderWindow* window) : 

GameState(window),
teste({0.f, 0.f, 100.f, 100.f}), 
teste2("Snake snakeado", {0.f, 150.f, 100.f, 100.f})

{
    teste2.setFonte("Fonts/fonte.ttf");
    teste2.setOutlineColor(sf::Color::Red, 2.f);
}

void MenuState::handleInput() {
    sf::Event e;

    while (window->pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                teste.update(e.key.code);
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseMoved:
                teste.update(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
                break;

            default: continue;
        }
    }
}

void MenuState::update() {
    const float deltaTime = getDeltaTime();
    teste.update();
    teste2.update(deltaTime);
}

void MenuState::draw() {
    window->clear(sf::Color::Green);

    teste.draw(*window);
    teste2.draw(*window);

    window->display();
}

bool MenuState::works() const {
    return GameState::works() && !teste.foiUsado();
}

std::unique_ptr<GameState> MenuState::wichChange() const {
    if (teste.foiUsado())
        return std::make_unique<PlayState>(window);
    return nullptr;
}