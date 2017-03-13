#include "Sprite.hpp"

Sprite::Sprite(const std::string &file, const int pos_x, const int pos_y, const int width, const int height)
{
	this->_Texture = new sf::Texture;
	this->_Sprite = new sf::Sprite;
	if (!(this->_Texture->loadFromFile(file)))
	  std::cout << "Failed to load" << file << std::endl;
	this->_Texture->setSmooth(true);
	this->_Sprite->setTexture(*this->_Texture);
	_posX = pos_x;
	_posY = pos_y;
	_width = width;
	_height = height;
}

Sprite::~Sprite()
{
	delete _Texture;
	delete _Sprite;
}

sf::Sprite&	Sprite::getSprite() const
{
	return (*this->_Sprite);
}

sf::Texture&	Sprite::getTexture() const
{
	return (*_Texture);
}

int			Sprite::getWidth() const
{
	return _width;
}

int			Sprite::getHeight() const
{
	return _height;
}

int				Sprite::getPosX() const
{
	return (_posX);
}

int				Sprite::getPosY() const
{
	return (_posY);
}
