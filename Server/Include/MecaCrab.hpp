#ifndef MECACRAB_HPP_
# define MECACRAB_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"

class Game;
class Player;

class MecaCrab : public AObject
{
private:
  bool			_Visible;
  const std::vector<Ptr<Player>> &_Players;
  int			_FireRate;
  int			_TargetX;
  int			_TargetY;

  MecaCrab		&operator=(const MecaCrab &);
  MecaCrab		(const MecaCrab &);

public:
  MecaCrab		(int, int, int, Game *, const std::vector<Ptr<Player>> &);
  ~MecaCrab		();

  void			EnterGame();
  void			aimPlayer();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);

  void			teleportAndFire();
};

#endif /* !MECACRAB_HPP_ */
