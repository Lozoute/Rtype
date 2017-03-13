#ifndef TENTACLE_HPP_
# define TENTACLE_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Game.hpp"
# include "LittleShip.hpp"

class Game;

class Tentacle : public AObject
{
  std::size_t		_Frames;
  bool			_Visible;
  int			_BulletX;
  int			_BulletY;
  int			_Dir;

  Tentacle		(const Tentacle &);
  Tentacle		&operator=(const Tentacle &);

public:
  Tentacle		(int, int, int, Game *);
  ~Tentacle		();

  void			EnterGame();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);

  void			RotateAndFire();
  void			PhaseOne();
  void			PhaseTwo();
  void			PhaseThree();
  void			PhaseFour();
};

#endif /* !TENTACLE_HPP_ */
