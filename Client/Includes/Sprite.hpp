#ifndef SPRITE_HPP_
# define SPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class Sprite
{
	sf::Texture		*_Texture;
	sf::Sprite		*_Sprite;
	int				_posX;
	int				_posY;
	int				_width;
	int				_height;

	Sprite() {};
	Sprite(const Sprite &) {};
	Sprite& operator=(const Sprite &){ return (*this); };
public:
	Sprite(const std::string &file, const int, const int, const int, const int);
	~Sprite();

	sf::Sprite&		getSprite() const;
	sf::Texture&	getTexture() const;
	int				getWidth() const;
	int				getHeight() const;
	int				getPosX() const;
	int				getPosY() const;
};
#endif /* !SPRITE_HPP_ */
