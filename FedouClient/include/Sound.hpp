#ifndef SOUND_HPP_
# define SOUND_HPP_

#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "Loader.hpp"
#include "API_Mutex.hpp"
#include "API_Error.hpp"

template <typename T>
using Ptr = std::shared_ptr<T>;

class Sound
{
  Ptr<sf::Sound>   	_sound;
  Ptr<sf::SoundBuffer>	_soundBuffer;
  Ptr<sf::Music>	_music;
  int		       	_type;
 
  Sound() {};
  Sound(const Sound &) {};
  Sound& operator=(const Sound &){ return (*this); };
public:
  Sound(const std::string &file, int);
  ~Sound();
  
  void play();
  void stop();
};
#endif /* !SOUND_HPP_ */
