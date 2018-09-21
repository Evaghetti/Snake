#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include <memory>
#include <chrono>
#include <string>

class GameState {
	public:
		GameState(sf::RenderWindow* window);
		virtual ~GameState();

		virtual void handleInput() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;

		float getDeltaTime();
		virtual bool works() const = 0;
		virtual std::unique_ptr<GameState> wichChange() const = 0;

	private:
		std::chrono::steady_clock::time_point timePoint;
	protected:
		sf::RenderWindow* window;
};

#endif
