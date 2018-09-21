#include "Player.h"

Player::Player(const sf::Vector2f& position) : position(position), animation("Images/snake.png", 16, 16, 2, 1) {
    animation.applyTexture(sprite);

    animation.addInterval("cabeca", 0, 1);
    animation.addInterval("corpo", 1, 2);

    animation.setInterval("cabeca");

    sprite.setPosition(position);
}

void Player::update(const float deltaTime) {
    animation.update(deltaTime);
    animation.applyTo(sprite);

    sprite.setPosition(position);
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}