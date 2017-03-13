#ifndef BONUS_HPP_
# define BONUS_HPP_

#include "AObject.hpp"
#include "IRessources.hpp"

class Bonus : public AObject
{
  BonusType	_type;

  Bonus(const Bonus &) = delete;
  Bonus &operator=(const Bonus &) = delete;
public:
  Bonus(const BonusType type, const int id, const int pos_x, const int pos_y);
  ~Bonus();

  void setMode(int){};
  void move_down(){};
  void move_up(){};
  void move_forward(){};
  void move_backward(){};
  void getDestroyed(){};
  void resetAnim(){};
  void draw(sf::RenderWindow &);
};

#endif /* !BONUS_HPP_ */