#ifndef TENTACLE_HPP_
# define TENTACLE_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class Tentacle : public AObject
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
  Tentacle() = delete;
  Tentacle(const int, const int, const int, const int, const ObjectType);
  Tentacle(const Tentacle &) = delete;
  Tentacle		&operator=(const Tentacle &) = delete;
  ~Tentacle();

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

#endif /* !TENTACLE_HPP_ */
