#ifndef HEALTHPACK_HPP_
# define HEALTHPACK_HPP_

# include <iostream>
# include <string>
# include "AObject.hpp"

class			Game;

class HealthPack	: public AObject
{
private:
  int			_Gain;

public:
  HealthPack		(int, Game *, int);
  HealthPack		(const HealthPack &);
  HealthPack&		operator=(const HealthPack &);
  virtual ~HealthPack	();

  virtual void		Affect(PlayerShip &);
};

#endif /* !HEALTHPACK_HPP_ */
