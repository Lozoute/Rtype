#ifndef BACKGROUND_HPP_
# define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

class Background
{
  sf::Texture		        *_BackText;
  sf::Sprite		        *_BackSprite;
  sf::Texture		        *_BackObjText;
  sf::Sprite		        *_BackObjSprite;
  sf::Sprite			*_BackObjSprite2;
  int			  	pos_x;
  int				width;
  int				pos_back;
  int				width_back;

  Background(const Background &) = delete;
  Background& operator=(const Background &) = delete;
public:
  Background();
  ~Background();

  void draw(sf::RenderWindow *);

};

#endif /* !BACKGROUND_HPP_ */
