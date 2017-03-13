#ifndef SHIPMOB_HPP_
# define SHIPMOB_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"

class ShipMob : public AObject
{
private:
  int			_Timer;
  bool			_Visible;
  int			_Coef;

  ShipMob		&operator=(const ShipMob &);
  ShipMob		(const ShipMob &);

public:
  ShipMob		(int, int, int, Game *);
  ~ShipMob		();

  void			EnterGame();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);
};

#endif /* !AOBJECT_HPP_ */
