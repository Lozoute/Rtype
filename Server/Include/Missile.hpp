#ifndef MISSILE_HPP_
# define MISSILE_HPP_

# include <iostream>
# include <string>
# include <memory>
# include <map>
# include "AObject.hpp"

class Game;
class Player;

class Missile : public AObject
{
private:
  Player		*_Player;
  long long int		_BaseX;
  long long int		_BaseY;

  Missile		(const Missile &);
  Missile		&operator=(const Missile &);

public:
  Missile		(int, Player *, int, int, int, int, Game *, AObject *,
			 MobType, int, int, int, int);
  ~Missile		();

  Player		*GetPlayer()	const;
  void			SetPlayer(Player *);

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);
};


#endif /* !AOBJECT_HPP_ */
