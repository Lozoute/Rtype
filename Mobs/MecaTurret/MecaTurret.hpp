#ifndef MECATURRET_HPP_
# define MECATURRET_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class MecaTurret : public AObject
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
  MecaTurret() = delete;
  MecaTurret(const int, const int, const int, const int, const ObjectType);
  MecaTurret(const MecaTurret &) = delete;
  MecaTurret		&operator=(const MecaTurret &) = delete;
  ~MecaTurret();

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

#endif /* !MECATURRET_HPP_ */
