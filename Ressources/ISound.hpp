#ifndef ISOUND_HPP_
# define ISOUND_HPP_

# include <SFML/Audio.hpp>

class ISound{
public:
  virtual ~ISound(){}
  virtual  sf::Music	*getSound() = 0;
  virtual void		play() = 0;
  virtual void		stop() = 0;
  virtual bool		isPlaying() const = 0;
};

# endif // !ISOUND_HPP_
