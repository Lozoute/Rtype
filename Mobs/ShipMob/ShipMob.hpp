#ifndef SHIPMOB_HPP_
# define SHIPMOB_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class ShipMob : public AObject
{
private:
  ISprite		*DesSprite;
  ISound		*explode;
  int			mode;
  sf::Clock		clock;
  sf::Clock		FireClock;
  int	       		FireRate;
  sf::Clock		DesClock;
  sf::Clock		MoveClock;
public:
  ShipMob() = delete;
  ShipMob(const int, const int, const int, const int, const ObjectType);
  ShipMob(const ShipMob &) = delete;
  ShipMob		&operator=(const ShipMob &) = delete;
  ~ShipMob();

  void			setMode(int a);
  void			setModeDes(const int a);
  int			getMode() const;
  void			move_down();
  void			move_up();
  void			move_forward();
  void			move_backward();
  void			getDestroyed();
  void			resetAnim();
  void			draw(sf::RenderWindow &);
};

#endif /* !SHIPMOB_HPP_ */
