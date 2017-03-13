#include "Game.hpp"
#include "HealthPack.hpp"
#include "FireRateBooster.hpp"
#include "BonusGenerator.hpp"
#include "DamageBooster.hpp"

///
/// CTOR ETC
///
BonusGenerator::BonusGenerator	(Game &G, std::vector<Ptr<AObject>> &Bonus)
				: _Game(G), _Bonus(Bonus)
{
  _Functions.push_back(&BonusGenerator::GenHealthPack);
  _Functions.push_back(&BonusGenerator::GenFireRateBooster);
  _Functions.push_back(&BonusGenerator::GenDamageBooster);
}

BonusGenerator::~BonusGenerator	()
{}

BonusGenerator::BonusGenerator	(const BonusGenerator &O)
				  : _Game(O._Game), _Bonus(O._Bonus)
{}

BonusGenerator&			BonusGenerator::operator=(const BonusGenerator &)
{
  return (*this);
}

///
/// GEN
///
void				BonusGenerator::Generate(long long int Frames, int Stage)
{
  if (Stage >= static_cast<int>(_Bonus.size()) && Frames % 100 == 0)
    (this->*(_Functions[std::rand() % _Functions.size()]))();
}

///
/// GEN ITEMS
///
void				BonusGenerator::GenHealthPack()
{
  _Bonus.emplace_back(new HealthPack(_Game.GenerateId(), &_Game, 2));
}

void				BonusGenerator::GenFireRateBooster()
{
  _Bonus.emplace_back(new FireRateBooster(_Game.GenerateId(), &_Game, 2));
}

void				BonusGenerator::GenDamageBooster()
{
  _Bonus.emplace_back(new DamageBooster(_Game.GenerateId(), &_Game, 5));
}
