#ifndef SPRITE_HPP_
# define SPRITE_HPP_

#include <iostream>
#include <string>
#include "ISprite.hpp"

class Sprite : public ISprite
{
private:
  sf::Texture			_Texture;
  sf::Sprite			_Sprite;
  int				_posX;
  int				_posY;
  int				_width;
  int				_height;

public:
  Sprite(){}
  Sprite(const std::string &file, const int, const int, const int, const int);
  ~Sprite();
  Sprite(const Sprite &) = delete;
  Sprite			&operator=(const Sprite &) = delete;

  using Info = std::tuple<char const*, int, int, int, int>;
  void				init(Info const &);
  sf::Sprite			&getSprite();
  sf::Texture			&getTexture();
  int				getWidth() const;
  int				getHeight() const;
  int				getPosX() const;
  int				getPosY() const;
  void				setTextureRect(int, int, int, int);
  void				setScale(float, float);
  void				setPosition(int, int);
};
#endif /* !SPRITE_HPP_ */
