#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "FrameWork/GameState.h"

#include "FrameWork/GUI/Button.h"
#include "FrameWork/GUI/TextBox.h"

#include <SFML/Graphics/RenderWindow.hpp>

class MenuState : public GameState {
public:
    MenuState(sf::RenderWindow* window);

    void handleInput() override;
    void update() override;
    void draw() override;

    bool works() const override;
    std::unique_ptr<GameState> wichChange() const override;
private:
    Button teste;
    TextBox teste2;
};

#endif