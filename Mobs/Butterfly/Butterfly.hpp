#ifndef BUTTERFLY_HPP_
# define BUTTERFLY_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class Butterfly : public AObject
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
  Butterfly() = delete;
  Butterfly(const int, const int, const int, const int, const ObjectType);
  Butterfly(const Butterfly &) = delete;
  Butterfly		&operator=(const Butterfly &) = delete;
  ~Butterfly();

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

#endif /* !BUTTERFLY_HPP_ */
