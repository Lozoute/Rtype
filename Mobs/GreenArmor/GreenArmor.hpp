#ifndef GREENARMOR_HPP_
# define GREENARMOR_HPP_

#include <SFML/System/Clock.hpp>
#include "Ressources.hpp"
#include "AObject.hpp"

class GreenArmor : public AObject
{
private:
  ISprite	  *DesSprite;
  ISound	  *explode;
  int		  mode;
  sf::Clock	  clock;
  sf::Clock	  FireClock;
  int		  FireRate;
  sf::Clock	  DesClock;

public:
  GreenArmor() = delete;
  GreenArmor(const GreenArmor &) = delete;
  GreenArmor& operator=(const GreenArmor &) = delete;
  GreenArmor(const int, const int, const int, const int, const ObjectType);
  ~GreenArmor();

  void		  setMode(int);
  void	    	  setModeDes(const int);
  int		  getMode() const;
  void		  move_down();
  void		  move_up();
  void		  move_forward();
  void		  move_backward();
  void		  getDestroyed();
  void		  resetAnim();

  void		  draw(sf::RenderWindow &);
};

#endif /* !GREENARMOR_HPP_ */
