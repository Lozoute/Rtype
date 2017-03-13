#include "Sprite.hpp"

Sprite::Sprite(const std::string &file, const int pos_x, const int pos_y, const int width, const int height)
{
  _Texture.loadFromFile(file);
  _Texture.setSmooth(true);
  _Sprite.setTexture(_Texture);
  _posX = pos_x;
  _posY = pos_y;
  _width = width;
  _height = height;
}

Sprite::~Sprite()
{
}

void		Sprite::init(Info const &info){
  _Texture.loadFromFile(std::get<0>(info));
  _Texture.setSmooth(true);
  _Sprite.setTexture(_Texture);
  _posX = std::get<1>(info);
  _posY = std::get<2>(info);
  _width = std::get<3>(info);
  _height = std::get<4>(info);
}

sf::Sprite&	Sprite::getSprite()
{
  return (_Sprite);
}

sf::Texture&	Sprite::getTexture()
{
  return (_Texture);
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

void				Sprite::setTextureRect(int left, int top, int width, int height){
  _Sprite.setTextureRect(sf::IntRect(left, top, width, height));
}

void				Sprite::setScale(float x, float y){
  _Sprite.setScale(x, y);
}

void				Sprite::setPosition(int x, int y){
  _Sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
}