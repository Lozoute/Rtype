#ifndef ISPRITE_HPP_
# define ISPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ISprite{
public:
  virtual ~ISprite(){}
  virtual sf::Sprite		&getSprite() = 0;
  virtual sf::Texture		&getTexture() = 0;
  virtual int			getWidth() const = 0;
  virtual int			getHeight() const = 0;
  virtual int			getPosX() const = 0;
  virtual int			getPosY() const = 0;
  virtual void			setTextureRect(int, int, int, int) = 0;
  virtual void			setScale(float, float) = 0;
  virtual void			setPosition(int, int) = 0;
};

# endif // !ISPRITE_HPP_
