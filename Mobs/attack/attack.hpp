#ifndef ATTACK_HPP_
# define ATTACK_HPP_

#include <SFML/Graphics.hpp>
#include "AObject.hpp"

class attack : public AObject
{
private:
  int			_speedX;
  int			_speedY;
  long long int		_baseX;
  long long int		_baseY;
  int			_sender;

public:
  attack(const attack &);
  attack(const int, const int, const int);
  attack(const int pos_x, const int pos_y, const int id, const ObjectType obj, const MobType mb, int, int, int);
  ~attack();
  attack		&operator=(const attack &) = delete;
  void			move_forward();
  void			move_backward();

  void			hit();

  void			setMode(int) {};
  void			move_down() {};
  void			move_up() {};
  void			getDestroyed() {};
  void			resetAnim() {};
  bool			launch_attack() { return (false); };
  void			draw(sf::RenderWindow &) {};

  void			updateMove();
};


#endif /* !ATTACK_HPP_ */
