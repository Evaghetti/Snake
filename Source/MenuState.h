#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "FrameWork/GameState.h"

#include "FrameWork/GUI/Widget.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>

class MenuState : public GameState {
public:
    MenuState(sf::RenderWindow& window);

    void handleInput() override;
    void update() override;
    void draw() override;

    bool works() const override;
    std::unique_ptr<GameState> wichChange() const override;
private:
    std::vector<std::unique_ptr<Widget>> gui;
};

#endif