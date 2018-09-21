#include "GameObject.h"

void GameObject::write(std::ostream& stream) const {
	throw std::runtime_error("Write não implementado");
}

void GameObject::read(std::istream& stream) {
	throw std::runtime_error("Read não implementado");
}
