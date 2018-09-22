#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f& position, const sf::FloatRect& hitbox, const sf::Vector2f& offset) {
	this->position = position;
	this->hitbox = hitbox;
	this->offsetFromOriginHitbox = offset;
}

void GameObject::update(const float deltaTime) {
	hitbox.left = position.x + offsetFromOriginHitbox.x;
	hitbox.top  = position.y + offsetFromOriginHitbox.y;
}

bool GameObject::colidiuCom(const GameObject& outro) const {
	return this->hitbox.intersects(outro.hitbox);
}

void GameObject::write(std::ostream& stream) const {
	throw std::runtime_error("Write não implementado");
}

void GameObject::read(std::istream& stream) {
	throw std::runtime_error("Read não implementado");
}
