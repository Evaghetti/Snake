#include "PlayState.h"

#include  "FrameWork/Manager.h"
#include "RankState.h"

#include <SFML/Window/Event.hpp>

#include <algorithm>
#include <fstream>

PlayState::PlayState(sf::RenderWindow& window) 
: 

GameState(window), 
player(SnakeBody({640.f / 2.f - 8.f, 480.f / 2 - 8.f})),
fundo(sf::Quads, 6000)

{
    for (int i = 0; i < 5; i++)
        apples.emplace_back(Apple());

    float row = 0.f;
    for (unsigned i = 0; i < fundo.getVertexCount(); i += 4) {
        
        fundo[i].position = sf::Vector2f(float(((i / 4) * 16) % 656), row * 16.f);
        fundo[i + 1].position = sf::Vector2f(float(((i / 4) * 16) % 656) + 16.f + 16.f, row * 16.f);
        fundo[i + 2].position = sf::Vector2f(float(((i / 4) * 16) % 656) + 16.f + 16.f, row * 16.f + 16.f);
        fundo[i + 3].position = sf::Vector2f(float(((i / 4) * 16) % 656), row * 16.f + 16.f);

        fundo[i].texCoords = sf::Vector2f(0.f, 0.f);
        fundo[i + 1].texCoords = sf::Vector2f(16.f, 0.f);
        fundo[i + 2].texCoords = sf::Vector2f(16.f, 16.f);
        fundo[i + 3].texCoords = sf::Vector2f(0.f, 16.f);

        if (((i / 4) * 16) % 656 == 0 && i > 0)
            row++;
    }
    texturaFundo = TextureManager::carregar("Images/grama.png");
}

void PlayState::handleInput() {
    sf::Event e;

    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed)
            window.close();
    }
}

void PlayState::update() {
    const float deltaTime = getDeltaTime();

    player.update(deltaTime);
    for (auto it = apples.begin(); it != apples.end(); it++) {
        Apple& apple = *it;

        if (player.comeu(apple)) {
            player.aumentarCorpo();

            const auto& corpo = player.getCorpo();
            int cont = 0;
            do {
                apple.respawn();
            } while(player.comeu(apple) || std::any_of(corpo.begin(), corpo.end(), [&](auto a) {
                return a.colidiuCom(apple) && ++cont < 640 * 480;
            }));

            if (cont == 640 * 480) {
                apples.erase(it);
                it--;                
            }
        }
    }
}

void PlayState::draw() {
    window.clear();

    window.draw(fundo, texturaFundo.get());
    player.draw(window);
    for (auto& it : apples)
        it.draw(window);

    window.display();
}

bool PlayState::works() const {
    return GameState::works() && !player.morreu();
}

std::unique_ptr<GameState> PlayState::wichChange() const {
    std::ofstream arquivo("data", std::ios::binary | std::ios::app);

    unsigned tamanho = player.getCorpo().size() + 1;

    arquivo.write(reinterpret_cast<char*>(&tamanho), sizeof(unsigned));
    arquivo.close();

    return std::make_unique<RankState>(window);
}