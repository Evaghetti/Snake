#ifndef APPLE_H
#define APPLE_H

#include "FrameWork/GameObject.h"
#include "FrameWork/Animation.h"
#include "FrameWork/Random.h"

#include <SFML/Graphics/RenderTarget.hpp>

class Apple : public GameObject {
public:
    Apple();

    void update(const float deltaTime) override;
    void draw(sf::RenderTarget& target) override;

    void comer();
private:
    void respawn(int maxX = 640, int maxY = 480);
private:
    Animation animation;
    sf::Sprite sprite;
    Random generator;

    bool foiComida;
};

#endif