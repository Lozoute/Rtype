#ifndef REDARMOR_HPP_
# define REDARMOR_HPP_

# include <iostream>
# include <string>
# include <memory>
# include <vector>
# include "AObject.hpp"

class Player;

class RedArmor : public AObject
{
private:
  int		_timer;
  int		_dir;
  int		_speed;
  int           _phase;
  bool		_visible;
  const std::vector<Ptr<Player>> &_Players;

  RedArmor	&operator=(const RedArmor &) { return *this; }

public:
  RedArmor	(int, int, int, int, Game *, const std::vector<Ptr<Player>> &);
  ~RedArmor	();

  void		EnterGame();

  virtual bool	Update(std::vector<Ptr<AObject>> &);
  virtual void	Attack();
  virtual void	TakeDmgs(int);

};

#endif /* !AOBJECT_HPP_ */
