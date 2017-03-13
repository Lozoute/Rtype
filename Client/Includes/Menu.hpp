#ifndef MENU_HPP_
# define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "IRessources.hpp"
#include "ISound.hpp"
#include "Loader.hpp"

class MainMenu
{
  const int	MENU_ITEM;
  int	       	Item_Selected;
  sf::Texture	_backgroundText;
  sf::Sprite	_backgroundSprite;
  sf::Font	font;
  sf::Text	item[2];
  Loader	loader;
  ISound	*_soundSelect;
  ISound	*_soundAccept;

  MainMenu(const MainMenu &) = delete;
  MainMenu& operator=(const MainMenu &) = delete;
  MainMenu() = delete;
public:
  MainMenu(const float, const float);
  ~MainMenu();

  void		draw(sf::RenderWindow &window) const;
  void		move_up();
  void		move_down();
  int		get_item() const;
};

# if defined(WIN32) || defined (_WIN32)
//  Microsoft
# define LIBNAME  "../API/DLLs/lib_API_Ressources.dll"
# elif defined(linux) || defined (__unix__)
//  UNIX
# define LIBNAME  "../API/SOs/lib_API_Ressources.so"
# else
//  unknown
# define LIBNAME  ""
# pragma warning Unknown dynamic link import/export semantics.
# endif

#endif /* !MENU_HPP_ */
