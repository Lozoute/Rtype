#ifndef FIRERATEBOOSTER_HPP_
# define FIRERATEBOOSTER_HPP_

# include <iostream>
# include <string>
# include "AObject.hpp"

class				Game;

class FireRateBooster		: public AObject
{
private:
  int				_Gain;

public:
  FireRateBooster		(int, Game *, int);
  FireRateBooster		(const FireRateBooster &);
  FireRateBooster&		operator=(const FireRateBooster &);
  virtual ~FireRateBooster	();

  virtual void			Affect(PlayerShip &);
};

#endif /* !FIRERATEBOOSTER_HPP_ */
