#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include "FrameWork/Animation.h"
#include "FrameWork/GameObject.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>

class SnakeBody : public GameObject {
public:
    SnakeBody(const sf::Vector2f& position, const sf::Vector2f& velocity, bool cabeca = true);

    void update(const float deltaTime) override;
    void draw(sf::RenderTarget& target) override;
private:
    Animation animation;
    sf::Vector2f position, velocityInicial, velocity;
    sf::Sprite sprite;

    float tempoPassado;

    static constexpr float tempoParaAndar = .25f;
};

#endif