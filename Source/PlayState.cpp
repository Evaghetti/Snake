#include "PlayState.h"

#include <SFML/Window/Event.hpp>

#include <algorithm>

PlayState::PlayState(sf::RenderWindow* window) : GameState(window), player(SnakeBody({640.f / 2.f - 8.f, 480.f / 2 - 8.f})) {}

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
    if (player.comeu(apple)) {
        player.aumentarCorpo();

        const auto& corpo = player.getCorpo();
        do {
            apple.respawn();
        } while(player.comeu(apple) || std::any_of(corpo.begin(), corpo.end(), [&](auto a) {
            return a.colidiuCom(apple);
        }));
    }
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