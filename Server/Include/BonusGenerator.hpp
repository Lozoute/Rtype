#ifndef BONUSGENERATOR_HPP_
# define BONUSGENERATOR_HPP_

# include <iostream>
# include <string>
# include <vector>
# include "AObject.hpp"

class				Game;

class				BonusGenerator
{
private:
  typedef void			(BonusGenerator::*GenF)();
  std::vector<GenF>		_Functions;
  Game				&_Game;
  std::vector<Ptr<AObject>>	&_Bonus;

  BonusGenerator		(const BonusGenerator &);
  BonusGenerator&		operator=(const BonusGenerator &);

public:
  BonusGenerator		(Game &, std::vector<Ptr<AObject>> &);
  ~BonusGenerator		();

  void				Generate(long long int Frames, int Stage);

  void				GenHealthPack();
  void				GenFireRateBooster();
  void				GenDamageBooster();
};

#endif /* !BONUSGENERATOR_HPP_ */
