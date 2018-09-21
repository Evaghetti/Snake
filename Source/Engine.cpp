#include "Engine.h"
#include "FrameWork/Manager.h"
#include <SFML/Graphics/Image.hpp>

Engine::Engine(const std::string& nome, int largura, int altura)
	: window(sf::VideoMode(largura, altura), nome, sf::Style::Close | sf::Style::Titlebar)
{
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	run();
}

void Engine::run() {
	while (window.isOpen() && gameState) {
		while (gameState->works()) {
			gameState->handleInput();
			gameState->update();
			gameState->draw();
		}

		gameState = gameState->wichChange();

		TextureManager::liberar();
		FontManager::liberar();
		SoundBufferManager::liberar();
	}
}
