#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <SFML/Audio/Sound.hpp>

#include <string>
#include <memory>

class SoundEffect {
public:
  SoundEffect() = default;
  SoundEffect(std::string caminho, bool stoppable = false);

  void play();
  void stop();
private:
  bool stoppable;
  std::shared_ptr<sf::SoundBuffer> buffer;
  sf::Sound sound;
};

#endif
