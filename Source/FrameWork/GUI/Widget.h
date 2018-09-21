#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

class Widget {
	public:
		Widget(const sf::Vector2f& position);

		virtual void draw(sf::RenderTarget& target) = 0;
		virtual void update() = 0;

		virtual void handleInput();
		virtual void handleMouse(const sf::Vector2f& mousePos);
	protected:
		sf::Vector2f position;
};
