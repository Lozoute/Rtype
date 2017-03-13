#include "Sprite.hpp"

Sprite::Sprite(const std::string &file, const int pos_x, const int pos_y, const int width, const int height)
{
  _Texture = Ptr<sf::Texture>(new sf::Texture);
  _Sprite = Ptr<sf::Sprite>(new sf::Sprite);
  if (!((_Texture.get())->loadFromFile(file)))
    std::cout << "Error loading texture from " << file << std::endl;
  (_Texture.get())->setSmooth(true);
  (_Sprite.get())->setTexture(*this->_Texture);
  _posX = pos_x;
  _posY = pos_y;
  _width = width;
  _height = height;
}

Sprite::~Sprite()
{
}

sf::Sprite&	Sprite::getSprite() const
{
  return (*(_Sprite.get()));
}

sf::Texture&	Sprite::getTexture() const
{
  return (*(_Texture.get()));
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
