#ifndef DAMAGEBOOSTER_HPP_
# define DAMAGEBOOSTER_HPP_

# include <iostream>
# include <string>
# include "AObject.hpp"

class				Game;

class DamageBooster		: public AObject
{
private:
  int				_Gain;

public:
  DamageBooster			(int, Game *, int);
  DamageBooster			(const DamageBooster &);
  DamageBooster&		operator=(const DamageBooster &);
  virtual ~DamageBooster	();

  virtual void			Affect(PlayerShip &);
};

#endif /* !DAMAGEBOOSTER_HPP_ */
