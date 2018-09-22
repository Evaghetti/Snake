#include "PlayState.h"

#include <SFML/Window/Event.hpp>

PlayState::PlayState(sf::RenderWindow* window) : GameState(window), player({8.f, 8.f}, {16.f, 16.f}) {}

void PlayState::handleInput() {
    sf::Event e;

    while (window->pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window->close();
    }
}

void PlayState::update() {
    const float deltaTime = getDeltaTime();

    player.update(deltaTime);
}

void PlayState::draw() {
    window->clear();

    player.draw(*window);

    window->display();
}