#ifndef MENUJOIN_HPP_
# define MENUJOIN_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include "IRessources.hpp"
#include "ISound.hpp"
#include "LogFile.hpp"

enum e_size_info {
	SIZE_IP = 15,
	SIZE_PORT = 5
};

class MenuJoin
{
  int		MENU_ITEM;
  int	       	Item_Selected;
  sf::Texture	*_backgroundText;
  sf::Texture	*_backgroundText2;
  sf::Sprite	*_backgroundSprite;
  sf::Sprite	*_circle;
  sf::Clock	_clock;
  bool		_info_ok;
  LogFile	_log;

  sf::Font	font;
  sf::Text	item[4];

  ISound	*_soundSelect;
  ISound	*_soundAccept;

public:
  MenuJoin() = delete;
  MenuJoin(const MenuJoin &) = delete;
  MenuJoin& operator=(const MenuJoin &) = delete;
  MenuJoin(float, float);
  ~MenuJoin();

  void	draw(sf::RenderWindow &window) const;
  void	move_up();
  void	move_down();
  void	writeinfo(const char);
  int	get_item() const;
  bool checkDotIP(const int count_nb, const int count_dot, const int i, const std::string &res) const;
  std::string get_ip();
  int get_port();
  void	reset_itemSelect();

  bool	getInfoOk() const;
  void	setInfoOk(const bool);
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

#endif /* !MENUJOIN_HPP_ */
