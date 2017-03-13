#ifndef MOBGENERATOR_HPP_
# define MOBGENERATOR_HPP_

# include <vector>
# include "AObject.hpp"

class					Game;
class					Player;

class					MobGenerator
{
private:
  typedef void				(MobGenerator::*StageF)();
  int					_ActualStage;
  bool					_BossPhase;
  long long int				_Seconds;
  int					_Fps;
  int					_Frames;
  Game					*_Game;
  std::vector<StageF>			_StageVect;
  const std::vector<Ptr<Player>>	&_Players;

public:
  MobGenerator				(Game *, const std::vector<Ptr<Player>> &);
  ~MobGenerator				();

  bool Generate				(int);

private:
  void Stage1				();
  void StageRedArmor			();
  void Stage3				();

  void SummonGreenArmor			();
  void SummonShipMob			();
  void SummonLittleShip			();
  void SummonTentacle			();
  void SummonRedArmor			();
  void SummonCentiped			();
  void SummonMecaCrab			();
  void SummonCrab			();
  void SummonButterfly			();
  void SummonSuperMeca			();
};

#endif /* !MOBGENERATOR_HPP_ */
