#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <memory>

class Widget {
public:
	Widget(std::unique_ptr<sf::Shape> formato, bool ativo = true);

	virtual void draw(sf::RenderTarget& target);

	virtual void update(const float deltaTime = 0.f) = 0;
	virtual void update(const sf::Keyboard::Key keyPressed);
	virtual void update(const sf::Vector2f& mousePosition);

	void setAtivo();
	void setAtivo(bool ativo);

	bool taAtivo() const;

	virtual bool podeSerUsado() const;
    virtual bool foiUsado() const;
protected:
	std::unique_ptr<sf::Shape> formato;
private:
	bool ativo;
};
