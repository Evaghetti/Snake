#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "FrameWork/GameState.h"
#include "Snake.h"
#include "Apple.h"

class PlayState : public GameState {
public:
    PlayState(sf::RenderWindow* window);

    void handleInput() override;
    void update() override;
    void draw() override;

    bool works() const override;
    std::unique_ptr<GameState> wichChange() const override;
private:
    Snake player;
    std::vector<Apple> apples;
};

#endif