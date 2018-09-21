#include "PlayState.h"

#include <SFML/Window/Event.hpp>

PlayState::PlayState(sf::RenderWindow* window) : GameState(window) {}

void PlayState::handleInput() {
    sf::Event e;

    while (window->pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window->close();
    }
}

void PlayState::update() {
    const float deltaTime = getDeltaTime();
}

void PlayState::draw() {
    window->clear();

    window->display();
}