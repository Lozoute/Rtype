#include "Sound.hpp"

Sound::Sound(const std::string &file)
{
	_Audio = new sf::Music;
	if (!_Audio->openFromFile(file))
		std::cerr << "[Error]: Cannot load " << file << " sound effect" << std::endl;
	_Audio->setVolume(25);
	_isPlaying = false;
}

Sound::~Sound()
{
	if (_Audio != NULL)
	{
		_Audio->stop();
		delete _Audio;
	}
}

sf::Music	*Sound::getSound() const
{
	return (_Audio);
}

void		Sound::play()
{
	_isPlaying = true;
	_Audio->play();
}

void		Sound::stop()
{
	_isPlaying = false;
	_Audio->stop();
}

bool		Sound::isPlaying() const
{
	return (_isPlaying);
}
