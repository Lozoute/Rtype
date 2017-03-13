#ifndef SOUND_HPP_
# define SOUND_HPP_

# include <SFML/Audio/Music.hpp>
# include <SFML/Audio.hpp>
# include <SFML/Audio/Sound.hpp>
#include <iostream>
#include <string>

class Sound
{
	sf::Music	*_Audio;
	bool		_isPlaying;

	Sound() {};
	Sound(const Sound &){};
	Sound& operator=(const Sound &){ return (*this); };
public:
	Sound(const std::string &file);
	~Sound();

	sf::Music	*getSound() const;
	void		play();
	void		stop();
	bool		isPlaying() const;
};

#endif /* !SOUND_HPP_ */
