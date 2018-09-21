#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <string>

class GameObject {
	public:
		GameObject() = default;

		virtual void draw(sf::RenderTarget& target) = 0;
		virtual void update(const float deltaTime) = 0;

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
};

#endif
