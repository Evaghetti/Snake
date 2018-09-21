#include "PlayState.h"

#include <SFML/Window/Event.hpp>

PlayState::PlayState(sf::RenderWindow* window) : GameState(window), player({50.f, 50.f}, {50.f, 50.f}) {}

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