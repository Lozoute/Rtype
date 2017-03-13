#ifndef MECACRAB_HPP_
# define MECACRAB_HPP_


#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class MecaCrab : public AObject
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
  MecaCrab() = delete;
  MecaCrab(const int, const int, const int, const int, const ObjectType);
  MecaCrab(const MecaCrab &) = delete;
  MecaCrab		&operator=(const MecaCrab &) = delete;
  ~MecaCrab();

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

#endif /* !MECACRAB_HPP_ */
