#include "SnakeBody.h"

#include <SFML/Window/Keyboard.hpp>

SnakeBody::SnakeBody(const sf::Vector2f& position, bool cabeca) : 

GameObject(position, sf::FloatRect(position, {16.f, 16.f}), {-8.f, -8.f}), 
animation("Images/snake.png", 16, 16, 2, 1), 
velocityInicial({16.f, 16.f}) 

{
    animation.addInterval("cabeca", 0, 1);
    animation.addInterval("corpo", 1, 2);

    animation.setInterval((cabeca) ? "cabeca" : "corpo");
    animation.applyTexture(sprite);
    animation.applyTo(sprite);
    
    this->velocity = sf::Vector2f(velocityInicial.x, 0.f);

    sprite.setPosition(position);
    sprite.setOrigin(8.f, 8.f);
    sprite.setRotation(90.f);

    tempoPassado = 0.f;
}

void SnakeBody::update(const float deltaTime) {
    animation.update(deltaTime);
    animation.applyTo(sprite);

    sf::Vector2i input(
        sf::Keyboard::isKeyPressed(sf::Keyboard::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::A),
        sf::Keyboard::isKeyPressed(sf::Keyboard::S) - sf::Keyboard::isKeyPressed(sf::Keyboard::W)
    );

    if (input != sf::Vector2i(0, 0) && getSign(input.x) != getSign(velocity.x) && getSign(input.y) != getSign(velocity.y)) {
        if (input.x != 0 && input.y != 0)
            input.x = 0;

        velocity = sf::Vector2f(velocityInicial.x * input.x, velocityInicial.y * input.y);
         
        switch(input.x) {
            case 1:
                sprite.setRotation(90.f);
                break;
            case -1:
                sprite.setRotation(-90.f);
                break;
        }
        switch(input.y) {
            case 1:
                sprite.setRotation(180.f);
                break;
            case -1:
                sprite.setRotation(0.f);
                break;
        }
        
    }

    tempoPassado += deltaTime;
    if (tempoPassado >= tempoParaAndar) {
        position += velocity;
        
        tempoPassado = 0.f;
        moveu = true;
    }
    else
        moveu = false;

    sprite.setPosition(position);
    GameObject::update(deltaTime);
}

void SnakeBody::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}

sf::Vector2f SnakeBody::getVelocity() const {
    return velocity;
}

sf::Vector2f SnakeBody::getPosition() const {
    return position;
}

bool SnakeBody::acabouDeMover() const {
    return moveu;
}

void SnakeBody::setRotation(const SnakeBody& snakeBody) {
    sprite.setRotation(snakeBody.sprite.getRotation());
}

void SnakeBody::setPosition(const sf::Vector2f& snakeBody) {
    sprite.setPosition(snakeBody);
    position = snakeBody;
}
