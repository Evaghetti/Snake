#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

class Animation {
public:
	Animation() = default;
	Animation(const std::string& caminho, int largura, int altura, int quantX, int quantY);

	void update(const float deltaTime = 0.f);

	void applyTexture(sf::Sprite& sprite) const;
	void applyTo(sf::Sprite& sprite, int index = -1);

	void flipInterval(const std::string& nome = "allAnimation");

	void addInterval(const std::string& nome, int inicio, int fim);

	void setHoldTime(float holdTime);
	void setAutoAvance(bool autoAvance);
	void setInterval(const std::string& nome = "allAnimation");

	int getIndex() const;
private:
	void avancarSprite();
	void flipRect(sf::IntRect& rect) const;
private:
	std::shared_ptr<sf::Texture> texture;

	std::vector<sf::IntRect> frames;

	std::unordered_map<std::string, std::pair<int, int>> intervals;
	std::string intervalAt;

	bool autoAvance;
	float holdTime, tempoPassado;
	int frameAt;
};

#endif
