#ifndef SNAKE_H
#define SNAKE_H

#include "SnakeBody.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <vector>

class Snake {
public:
    Snake(const SnakeBody& head, int tamanho = 3);

    void update(const float deltaTime);
    void draw(sf::RenderTarget& target);

    void aumentarCorpo();

    bool morreu() const;
    bool comeu(const GameObject& apple) const;

    const std::vector<SnakeBody>& getCorpo() const;
private:
    std::vector<SnakeBody> corpo;
    SnakeBody head;
};


#endif