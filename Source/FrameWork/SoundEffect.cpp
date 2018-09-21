#include "SoundEffect.h"

#include "Manager.h"

SoundEffect::SoundEffect(std::string caminho, bool stoppable) {
  buffer = SoundBufferManager::carregar(caminho);
  sound.setBuffer(*buffer);

  this->stoppable = stoppable;
}

void SoundEffect::play() {
  if (sound.getStatus() == sf::SoundSource::Stopped || stoppable)
    sound.play();
}

void SoundEffect::stop() {
  sound.stop();
}
