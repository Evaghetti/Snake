#include "Animation.h"

#include "Manager.h"

#include <iostream>

Animation::Animation(const std::string& caminho, int largura, int altura, int quantX, int quantY){
	texture = TextureManager::carregar(caminho);

	for (int y = 0; y < altura * quantY; y += altura) {
		for (int x = 0; x < largura * quantX; x += largura)
			frames.emplace_back(sf::IntRect(x, y, largura, altura));
	}

	addInterval("allAnimation", 0, frames.size());

	setInterval("allAnimation");
	setAutoAvance(false);
	setHoldTime(1.f);

	frameAt = 0;
}

void Animation::update(const float deltaTime) {
	if (autoAvance) {
		tempoPassado += deltaTime;

		if (tempoPassado > holdTime) {
			tempoPassado = 0.f;
			avancarSprite();
		}
	}
	else
		avancarSprite();
}

void Animation::avancarSprite() {
	frameAt++;
	if (frameAt == intervals[intervalAt].second)
		frameAt = intervals[intervalAt].first;
}

void Animation::applyTexture(sf::Sprite& sprite) const {
	sprite.setTexture(*texture);
}

void Animation::applyTo(sf::Sprite& sprite, const int index) {
	if (index != -1)
		frameAt = index;
	sprite.setTextureRect(frames[frameAt]);
}

void Animation::setAutoAvance(bool autoAvance) {
	this->autoAvance = autoAvance;
}

void Animation::setHoldTime(float holdTime) {
	if (holdTime == 0.f)
		return;
	this->holdTime = holdTime;
	this->tempoPassado = 0.f;
}

void Animation::addInterval(const std::string& nome, int inicio, int fim) {
	if (intervals.find(nome) == intervals.end())
		intervals.insert({ nome, {inicio, fim} });
	else
		throw std::runtime_error("Intervalo já existe.");
}

void Animation::setInterval(const std::string& nome) {
	if (nome != intervalAt) {
		intervalAt = nome;

		frameAt = intervals[intervalAt].first;
	}
}

void Animation::flipInterval(const std::string& nome) {
	auto intervalo = intervals[nome];
	
	for (auto it = frames.begin() + intervalo.first; it != frames.begin() + intervalo.second; it++) 
		flipRect(*it);
}

void Animation::flipRect(sf::IntRect& rect) const {
	rect = sf::IntRect(rect.left + rect.width, rect.top, -rect.width, rect.height);
}

int Animation::getIndex() const {
	for (unsigned index = 0; index < frames.size(); index++) {
		if (frames[index] == frames[frameAt])
			return index;
	}

	return -1;
}