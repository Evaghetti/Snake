#include "GameState.h"

GameState::GameState(sf::RenderWindow& window) : window(window) {
	timePoint = std::chrono::steady_clock::now();
}

bool GameState::works() const {
	return window.isOpen();
}

float GameState::getDeltaTime() {
	auto newTimePoint = std::chrono::steady_clock::now();
	float deltaTime = std::chrono::duration<float>(newTimePoint - timePoint).count();
	timePoint = newTimePoint;

	return deltaTime;
}

std::unique_ptr<GameState> GameState::wichChange() const {
	return nullptr;
}
