#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>

class GameObject {
	public:
		GameObject(const sf::Vector2f& position = sf::Vector2f(), const sf::FloatRect& hitbox = sf::FloatRect(), const sf::Vector2f& offset = sf::Vector2f());

		virtual void draw(sf::RenderTarget& target) = 0;
		virtual void update(const float deltaTime) = 0;

		bool colidiuCom(const GameObject& outro) const;

		friend std::ostream& operator<<(std::ostream& stream, const GameObject& gameObject) {
			gameObject.write(stream);

			return stream;
		}
		friend std::istream& operator>>(std::istream& stream, GameObject& gameObject) {
			gameObject.read(stream);

			return stream;
		}
	protected:
		virtual void write(std::ostream& stream) const;
		virtual void read(std::istream& stream);

		sf::Vector2f position;
	private:
		sf::FloatRect hitbox;
		sf::Vector2f offsetFromOriginHitbox;
};

#endif
