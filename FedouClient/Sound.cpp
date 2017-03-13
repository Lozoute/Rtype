#include "Sound.hpp"

Sound::Sound(const std::string &file, int type)
{
  _type = type;
  if (_type == 0)
    {
      _sound = Ptr<sf::Sound>(new sf::Sound);
      _soundBuffer = Ptr<sf::SoundBuffer>(new sf::SoundBuffer);
      (_soundBuffer.get())->loadFromFile(file);
      (_sound.get())->setBuffer(*(_soundBuffer.get()));
    }
  else
    {
      _music = Ptr<sf::Music>(new sf::Music);
      (_music.get())->openFromFile(file);
      (_music.get())->setLoop(true);
      
    }
}

Sound::~Sound()
{
}

void	Sound::play()
{
  if (_type == 0)
    (_sound.get())->play();
  else
    (_music.get())->play();
    
}

void	Sound::stop()
{
  if (_type == 0)
    return;
  else
    (_music.get())->stop();
  
}
