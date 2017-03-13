#ifndef CRAB_HPP_
# define CRAB_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"

class Game;
class Player;

class Crab : public AObject
{
private:
  bool			_Visible;
  const std::vector<Ptr<Player>> &_Players;
  int			_FireRate;

  Crab		&operator=(const Crab &);
  Crab		(const Crab &);

public:
  Crab		(int, int, int, Game *, const std::vector<Ptr<Player>> &);
  ~Crab		();

  void			EnterGame();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);

};

#endif /* !CRAB_HPP_ */
