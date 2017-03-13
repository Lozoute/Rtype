#ifndef CENTIPED_HPP_
# define CENTIPED_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class Centiped : public AObject
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
  Centiped() = delete;
  Centiped(const int, const int, const int, const int, const ObjectType);
  Centiped(const Centiped &) = delete;
  Centiped		&operator=(const Centiped &) = delete;
  ~Centiped();

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

#endif /* !CENTIPED_HPP_ */
