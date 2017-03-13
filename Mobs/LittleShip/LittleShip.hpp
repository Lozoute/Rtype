#ifndef LITTLESHIP_HPP_
# define LITTLESHIP_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class LittleShip : public AObject
{
private:
  ISprite	  *DesSprite;
  ISound	  *explode;
  int		  mode;
  sf::Clock	  clock;
  sf::Clock	  FireClock;
  int	       	  FireRate;
  sf::Clock	  DesClock;
public:
  LittleShip() = delete;
  LittleShip(const LittleShip &) = delete;
  LittleShip	  &operator=(const LittleShip &) = delete;
  LittleShip(const int, const int, const int, const int, const ObjectType);
  ~LittleShip();

  void		  setMode(int a);
  void		  setModeDes(const int a);
  int		  getMode() const;
  void		  move_down();
  void		  move_up();
  void		  move_forward();
  void		  move_backward();
  void		  getDestroyed();
  void		  resetAnim();

  void		  draw(sf::RenderWindow &);
};

#endif /* !LITTLESHIP_HPP_ */
