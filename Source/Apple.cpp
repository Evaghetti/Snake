#include "Apple.h"


Apple::Apple() :

GameObject({0.f, 0.f}, sf::FloatRect(position, {16.f, 16.f})),
animation("Images/apple.png", 16, 16, 1, 1)

{
    animation.applyTexture(sprite);
    animation.applyTo(sprite);
    
    respawn();
    GameObject::update(0.f);
}

void Apple::update(const float deltaTime) {
    if (foiComida) {
        respawn();
        foiComida = false;
    }

    sprite.setPosition(position);
    GameObject::update(deltaTime);
}

void Apple::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}

void Apple::comer() {
    foiComida = true;
}

void Apple::respawn(int maxX, int maxY) {
    do {
        position.x = generator.range(0, maxX - 16);
        position.y = generator.range(0, maxY - 16);
    } while((int)position.x % 16 != 0.f || (int)position.y % 16 != 0.f);
}