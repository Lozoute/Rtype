#ifndef PAUSEMENU_HPP_
# define PAUSEMENU_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "IRessources.hpp"
#include "ISound.hpp"
#include "Loader.hpp"

enum typeVolume
{
  MUSIC = 1,
  EFFECT = 2
};

class PauseMenu
{
  const int	MENU_ITEM;
  int	       	Item_Selected;
  sf::Font	font;
  sf::Text	item[3];
  float		vol_music;
  float		vol_effect;
  bool		_paused;

  Loader	loader;
  ISound	*_soundSelect;
  ISound	*_soundAccept;
  IRessources	*_res;

  PauseMenu(const PauseMenu &) = delete;
  PauseMenu &operator=(const PauseMenu &) = delete;
public:
  PauseMenu();
  ~PauseMenu();

  void draw(sf::RenderWindow &window) const;
  void move_up();
  void move_down();
  int get_item() const;
  bool isPaused() const;
  void setVolume(const typeVolume &type, const float volume);
  void setVolumeMusic(const float volume);
  void setVolumeEffect(const float volume);
  void setPause(bool paused);
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

#endif /* !PAUSEMENU_HPP_ */
