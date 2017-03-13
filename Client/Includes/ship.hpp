#ifndef SHIP_HPP_
# define SHIP_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "AObject.hpp"
#include "ISprite.hpp"

class ship : public AObject
{
private:
  ISprite			*DesSprite;
  ISprite			*_you;
  bool				you;
  ISound			*explode;
  int			  	mode;
  int	       			FireRate;
  sf::Clock			FireClock;
  sf::Clock			clock;
  std::vector<attack *>  	projectile;
  sf::Clock			DesClock;
  std::map<int, ISprite *>	SpriteMap;
public:
  ship() = delete;
  ship(const ship &) = delete;
  ship& operator=(const ship &) = delete;
  ship(const int, const int, const int, const int);
  virtual ~ship();

  void				setMode(int a);
  void				setModeDes(const int a);
  int				getMode() const;
  void				move_down();
  void				move_up();
  void				move_forward();
  void				move_backward();
  void				getDestroyed();
  void				resetAnim();
  bool				launch_attack();
  void				draw(sf::RenderWindow &);

  void				setYou(bool entry) { you = entry; };
  void				setFireRate(int entry) { FireRate = entry; };
};

#endif /* !SHIP_HPP_ */
