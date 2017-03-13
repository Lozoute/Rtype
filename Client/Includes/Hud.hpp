#ifndef HUD_HPP_
# define HUD_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "ISprite.hpp"

class CleverHud
{
private:
  bool		_isTabPressed;
  bool		_isDead;
  bool		_nextStage;
  ISprite	*_hudText;
  ISprite	*_hpSprite;
  ISprite	*_stageSprite;
  int		_hpPlayer;

  int		_blue_Score;
  int		_pink_Score;
  int	    	_green_Score;
  int		_red_Score;
  sf::Font      _font;
  sf::Text      _player[4];
  ISprite	*_Dead;

  void		draw_ctrl(sf::RenderWindow &);
  void		triScore();

public:
  CleverHud();
  ~CleverHud();
  CleverHud(const CleverHud &) = delete;
  CleverHud& operator=(const CleverHud &) = delete;

  void		draw(sf::RenderWindow &);

  void		setTabPressed(bool);
  void		setScore(const int blue, const int pink, const int green, const int red);
  void		setIsDead(bool);
  void		setPlayerHp(int entry);
  void		setNextStage(int entry);
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

#endif /* !HUD_HPP_ */