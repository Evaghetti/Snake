#ifndef RANKSTATE_H
#define RANKSTATE_H

#include "FrameWork/GameState.h"
#include "FrameWork/GUI/Widget.h"

#include <vector>
#include <memory>

class RankState : public GameState {
public:
    RankState(sf::RenderWindow& window, bool adcionar = false, int pontos = 0);

    void handleInput() override;
    void update() override;
    void draw() override;

    bool works() const override;
    std::unique_ptr<GameState> wichChange() const override;
private:
    std::string lerArquivo() const;
    void escrerArquivo(const std::string& nome) const;
private:
    std::vector<std::unique_ptr<Widget>> gui;

    sf::VertexArray fundo;
    std::shared_ptr<sf::Texture> texturaFundo;
    const int pontosPraAdd;
    bool adcionando;
};

#endif // RANKSTATE_H