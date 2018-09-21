#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "FrameWork/GameState.h"
#include "Player.h"

class PlayState : public GameState {
public:
    PlayState(sf::RenderWindow* window);

    void handleInput() override;
    void update() override;
    void draw() override;
private:
    Player player;
};

#endif