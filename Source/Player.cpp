#include "Player.h"

#include <SFML/Window/Keyboard.hpp>

Player::Player(const sf::Vector2f& position, const sf::Vector2f& velocity) : position(position), velocityInicial(velocity), animation("Images/snake.png", 16, 16, 2, 1) {
    animation.applyTexture(sprite);

    animation.addInterval("cabeca", 0, 1);
    animation.addInterval("corpo", 1, 2);

    animation.setInterval("cabeca");

    sprite.setPosition(position);
    this->velocity = sf::Vector2f(velocityInicial.x, 0.f);

    tempoPassado = 0.f;
}

void Player::update(const float deltaTime) {
    animation.update(deltaTime);
    animation.applyTo(sprite);

    sf::Vector2i input(
        sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A),
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)
    );

    if (input != sf::Vector2i(0, 0)) {
        if (input.x != 0 && input.y != 0)
            input.x = 0;
        velocity = sf::Vector2f(velocityInicial.x * input.x, velocityInicial.y * input.y);
    }
    tempoPassado += deltaTime;
    if (tempoPassado >= tempoParaAndar) {
        position += velocity;
        
        tempoPassado = 0.f;
    }

    sprite.setPosition(position);
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}