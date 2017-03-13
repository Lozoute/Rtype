#ifndef GREENARMOR_HPP_
# define GREENARMOR_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"

class Game;
class Player;

class GreenArmor : public AObject
{
private:
  bool			_Visible;
  const std::vector<Ptr<Player>> &_Players;
  int			_Target;
  int			_FireRate;

  GreenArmor		&operator=(const GreenArmor &);
  GreenArmor		(const GreenArmor &);

public:
  GreenArmor		(int, int, int, Game *, const std::vector<Ptr<Player>> &);
  ~GreenArmor		();

  void			EnterGame();
  void			aimPlayer();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);
};


#endif /* !AOBJECT_HPP_ */
