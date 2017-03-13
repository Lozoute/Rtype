#ifndef SOUND_HPP_
# define SOUND_HPP_

#include <iostream>
#include <string>
#include "ISound.hpp"

class Sound : public ISound
{
private:
  sf::Music	    _Audio;
  bool		    _isPlaying;

public:
  Sound(){}
  Sound(const std::string &file);
  ~Sound();
  Sound(const Sound &) = delete;
  Sound		&operator=(const Sound &) = delete;
  
  void		init(std::string const &);
  sf::Music	*getSound();
  void		play();
  void		stop();
  bool		isPlaying() const;
};

#endif /* !SOUND_HPP_ */
