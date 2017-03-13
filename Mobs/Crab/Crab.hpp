#ifndef CRAB_HPP_
# define CRAB_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class Crab : public AObject
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
  Crab() = delete;
  Crab(const int, const int, const int, const int, const ObjectType);
  Crab(const Crab &) = delete;
  Crab		&operator=(const Crab &) = delete;
  ~Crab();

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

#endif /* !CRAB_HPP_ */
