#ifndef CENTIPED_HPP_
# define CENTIPED_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"

class Game;
class Player;

class Centiped : public AObject
{
private:
  bool			_Visible;
  const std::vector<Ptr<Player>> &_Players;
  int			_FireRate;
  int			_TargetX;
  int			_TargetY;

  Centiped		&operator=(const Centiped &);
  Centiped		(const Centiped &);

public:
  Centiped		(int, int, int, Game *, const std::vector<Ptr<Player>> &);
  ~Centiped		();

  void			EnterGame();
  void			aimPlayer();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);

  void			teleportAndFire();
};

#endif /* !CENTIPED_HPP_ */
