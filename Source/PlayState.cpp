#include "PlayState.h"

#include <SFML/Window/Event.hpp>

PlayState::PlayState(sf::RenderWindow* window) : GameState(window), player(SnakeBody({8.f, 8.f})) {}

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
    if (player.comeu(apple)) 
        apple.comer();
    apple.update(deltaTime);
}

void PlayState::draw() {
    window->clear();

    player.draw(*window);
    apple.draw(*window);

    window->display();
}

bool PlayState::works() const {
    return GameState::works() && !player.morreu();
}