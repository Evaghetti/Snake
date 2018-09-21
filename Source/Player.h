#ifndef PLAYER_H
#define PLAYER_H

#include "FrameWork/Animation.h"
#include "FrameWork/GameObject.h"

#include <SFML/System/Vector2.hpp>

class Player : public GameObject {
public:
    Player(const sf::Vector2f& position);

    void update(const float deltaTime) override;
    void draw(sf::RenderTarget& target) override;
private:
    Animation animation;
    sf::Vector2f position;
    sf::Sprite sprite;
};

#endif