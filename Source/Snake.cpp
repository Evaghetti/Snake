#include "Snake.h"

#include <iostream>

Snake::Snake(const SnakeBody& head, int tamanho) : head(head) {
    const sf::Vector2f headPosition = this->head.getPosition();
    for (int i = 1; i < tamanho; i++) {
        corpo.emplace_back(SnakeBody(headPosition - sf::Vector2f(16.f * i, headPosition.y), false));
        corpo.back().setRotation(head);
    }
}

void Snake::update(const float deltaTime) {
    head.update(deltaTime);
    
    if (head.acabouDeMover()) {
        for (int i = corpo.size() - 1; i > 0; i--) {
            corpo[i].setPosition(corpo[i - 1].getPosition());
            corpo[i].setRotation(corpo[i - 1]);
        }
        corpo.front().setPosition(head.getPosition() - head.getVelocity());
        corpo.front().setRotation(head);
    }
}

void Snake::draw(sf::RenderTarget& target) {
    for (auto& it : corpo)
        it.draw(target);
    head.draw(target);
}

void Snake::aumentarCorpo() {
    corpo.emplace_back(SnakeBody(corpo.back().getPosition(), false));
    corpo.back().setRotation(corpo[corpo.size() - 2]);
}

bool Snake::morreu() const {
    for (const auto& it : corpo) {
        if (head.colidiuCom(it) && head.acabouDeMover())
            return true;
    }
    return false;
}

bool Snake::comeu(const GameObject& apple) const {
    return head.colidiuCom(apple);
}

const std::vector<SnakeBody>& Snake::getCorpo() const {
    return corpo;
}