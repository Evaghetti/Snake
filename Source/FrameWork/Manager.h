#ifndef MANAGER_H
#define MANAGER_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <iostream>

template <typename T>
class Manager {
	public:
		static std::shared_ptr<T> carregar(const std::string& chave) {
			auto recurso = recursos.find(chave);

			if (recurso != recursos.end())
				return recurso->second;
			else {
				std::shared_ptr<T> temp = std::make_shared<T>();
				temp->loadFromFile(chave);

				recursos.insert({ chave, temp });
				return temp;
			}
		}
		static void liberar() {
			for (auto it = recursos.begin(); it != recursos.end();) {
				if (it->second.unique())
					it = recursos.erase(it);
				else
					it++;
			}
		}
	private:
		static std::unordered_map<std::string, std::shared_ptr<T>> recursos;
};

template <typename T>
std::unordered_map<std::string, std::shared_ptr<T>> Manager<T>::recursos;

typedef Manager<sf::Texture> TextureManager;
typedef Manager<sf::Font> FontManager;
typedef Manager<sf::SoundBuffer> SoundBufferManager;

#endif
