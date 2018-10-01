#include "PlayState.h"

#include "RankState.h"

#include <SFML/Window/Event.hpp>

#include <algorithm>

PlayState::PlayState(sf::RenderWindow& window) : GameState(window), player(SnakeBody({640.f / 2.f - 8.f, 480.f / 2 - 8.f})) {
    for (int i = 0; i < 5; i++)
        apples.emplace_back(Apple());
}

void PlayState::handleInput() {
    sf::Event e;

    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();
    }
}

void PlayState::update() {
    const float deltaTime = getDeltaTime();

    player.update(deltaTime);
    for (auto it = apples.begin(); it != apples.end(); it++) {
        Apple& apple = *it;

        if (player.comeu(apple)) {
            player.aumentarCorpo();

            const auto& corpo = player.getCorpo();
            int cont = 0;
            do {
                apple.respawn();
            } while(player.comeu(apple) || std::any_of(corpo.begin(), corpo.end(), [&](auto a) {
                return a.colidiuCom(apple) && ++cont < 640 * 480;
            }));

            if (cont == 640 * 480) {
                apples.erase(it);
                it--;                
            }
        }
    }
}

void PlayState::draw() {
    window.clear();

    player.draw(window);
    for (auto& it : apples)
        it.draw(window);

    window.display();
}

bool PlayState::works() const {
    return GameState::works() && !player.morreu();
}

std::unique_ptr<GameState> PlayState::wichChange() const {
    return std::make_unique<RankState>(window);
}