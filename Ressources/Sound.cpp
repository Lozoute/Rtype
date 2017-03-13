#include "Sound.hpp"

Sound::Sound(const std::string &file)
{
  if (!_Audio.openFromFile(file))
    std::cerr << "[Error]: Cannot load " << file << " sound effect" << std::endl;
  _Audio.setVolume(25);
  _isPlaying = false;
}

Sound::~Sound()
{
  if (_isPlaying)
  _Audio.stop();
}

void		Sound::init(std::string const &file){
  if (!_Audio.openFromFile(file))
    std::cerr << "[Error]: Cannot load " << file << " sound effect" << std::endl;
  _Audio.setVolume(25);
  _isPlaying = false;
}

sf::Music	*Sound::getSound()
{
  return (&_Audio);
}

void		Sound::play()
{
  _isPlaying = true;
  _Audio.play();
}

void		Sound::stop()
{
  _isPlaying = false;
  _Audio.stop();
}

bool		Sound::isPlaying() const
{
  return (_isPlaying);
}
