#ifndef LITTLESHIP_HPP_
# define LITTLESHIP_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"
class Game;

class LittleShip : public AObject
{
private:
  bool			_Visible;
  int			_Frames;

  LittleShip		(const LittleShip &);
  LittleShip		&operator=(const LittleShip &);

public:
  LittleShip		(int, int, int, Game *);
  ~LittleShip		();

  void			EnterGame();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);
};

#endif /* !AOBJECT_HPP_ */
