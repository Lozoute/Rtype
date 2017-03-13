#ifndef BACKGROUND_HPP_
# define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "Loader.hpp"
#include "API_Mutex.hpp"
#include "API_Error.hpp"
#include "Srtp.hpp"
#include "Background.hpp"

template <typename T>
using Ptr = std::shared_ptr<T>;

class Background
{
  Ptr<sf::Texture>		_BackText;
  Ptr<sf::Sprite>		_BackSprite;
  Ptr<sf::Texture>		_BackObjText;
  Ptr<sf::Sprite>		_BackObjSprite;
  Ptr<sf::Sprite>		_BackObjSprite2;
  int				pos_x;
  int				width;
  int				pos_back;
  int				width_back;

	Background(const Background &){};
	  Background& operator=(const Background &){return (*this);};
public:
	Background();
	~Background();

	void draw(sf::RenderWindow *);

};

#endif /* !BACKGROUND_HPP_ */
