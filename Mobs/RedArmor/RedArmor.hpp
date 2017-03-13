#ifndef REDARMOR_HPP_
# define REDARMOR_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class RedArmor : public AObject
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
  RedArmor() = delete;
  RedArmor(const int, const int, const int, const int, const ObjectType);
  RedArmor(const RedArmor &) = delete;
  RedArmor		&operator=(const RedArmor &) = delete;
  ~RedArmor();

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
#endif /* !REDARMOR_HPP_ */
