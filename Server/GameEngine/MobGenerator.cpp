#include "MobGenerator.hpp"
#include "Game.hpp"
#include "AObject.hpp"
#include "ShipMob.hpp"
#include "PlayerShip.hpp"
#include "GreenArmor.hpp"
#include "LittleShip.hpp"
#include "Tentacle.hpp"
#include "RedArmor.hpp"
#include "Centiped.hpp"
#include "MecaCrab.hpp"
#include "Crab.hpp"

///
/// CTOR ETC
///
MobGenerator::MobGenerator	(Game *g, const std::vector<Ptr<Player>> &players)
				: _ActualStage(0), _BossPhase(false),
				  _Seconds(0), _Fps(30), _Frames(0), _Game(g),
				  _Players(players)
{
  _StageVect.push_back(&MobGenerator::Stage1);
  _StageVect.push_back(&MobGenerator::StageRedArmor);
  _StageVect.push_back(&MobGenerator::Stage3);
}

MobGenerator::~MobGenerator	()
{}

///
/// UPDATE
///
bool				MobGenerator::Generate(int Stage)
{
  _Frames++;
  if (_Frames == _Fps)
    {
      _Frames = 0;
      _Seconds++;
    }
  if (Stage != _ActualStage)
    {
      _ActualStage = Stage;
      _Frames = 0;
      _Seconds = 0;
      _BossPhase = false;
    }
  if (Stage >= 0 && Stage < static_cast<int>(_StageVect.size()))
    (this->*(_StageVect[Stage]))();
  return (_BossPhase);
}

///
/// STAGES
///
void				MobGenerator::Stage1()
{
  if (_Seconds < 20)
    SummonGreenArmor();
  else if (_Seconds < 40)
    {
      SummonGreenArmor();
      SummonShipMob();
    }
  else if (_Seconds < 60)
    SummonLittleShip();
  else if (_BossPhase == false)
    {
      _BossPhase = true;
      SummonTentacle();
    }
}

void				MobGenerator::StageRedArmor()
{
  if (_Seconds > 5  && _BossPhase == false)
    {
      _BossPhase = true;
      SummonRedArmor();
    }
}

void				MobGenerator::Stage3()
{
  if (_Seconds > 5)
    {
      if (_Seconds < 20)
	SummonCentiped();
      else if (_Seconds < 60)
	{
	  SummonCentiped();
	  SummonMecaCrab();
	}
      else if (_Seconds < 80)
	{
	  SummonGreenArmor();
	  SummonShipMob();
	  SummonLittleShip();
	}
      else if (_Seconds < 120)
	{
	  SummonCentiped();
	  SummonCrab();
	  SummonButterfly();
	}
      else if (_BossPhase == false)
	{
	  _BossPhase = true;
	  SummonSuperMeca();
	}
    }
}

///
/// SUMMONING
///
void				MobGenerator::SummonGreenArmor()
{
  if ((_Frames == 1 && _Seconds % 2 == 0) || (_Seconds > 15 && _Seconds < 20 && _Frames % 15 == 0))
    _Game->AddFoe(new GreenArmor(_Game->GenerateId(), __SizeX + 56,
				 __WallSize + (std::rand() % (__SizeY - (2 * __WallSize) - 56)),
				 _Game, _Players));
}

void				MobGenerator::SummonShipMob()
{
  if (_Frames == 1 && _Seconds % 2 == 0)
    _Game->AddFoe(new ShipMob(_Game->GenerateId(), __SizeX + 32,
			      __WallSize + (std::rand() % (__SizeY - (2 * __WallSize) - 22)),
			      _Game));
}

void				MobGenerator::SummonLittleShip()
{
  if ((_Frames == 1 && _Seconds % 2 == 0) || (_Seconds > 55 && _Seconds < 60 && _Frames % 8 == 0))
    _Game->AddFoe(new LittleShip(_Game->GenerateId(), __SizeX + 21,
				 __WallSize + 20 + (std::rand() % (__SizeY - (2 * __WallSize) - 44)),
				 _Game));
}

void				MobGenerator::SummonTentacle()
{
  _Game->AddFoe(new Tentacle(_Game->GenerateId(),
			     __SizeX + 139,
			     __WallSize + (std::rand() % (__SizeY - (2 * __WallSize) - 262)),
			     _Game));
}

void				MobGenerator::SummonRedArmor()
{
  _Game->AddFoe(new RedArmor(_Game->GenerateId(), __SizeX + 60,
			     __WallSize + (std::rand() % (__SizeY - (2 * __WallSize) - 47)),
			     1, _Game, _Players));
}

void				MobGenerator::SummonCentiped()
{
  if ((_Frames == 15 && _Seconds % 5 == 0))
    _Game->AddFoe(new Centiped(_Game->GenerateId(), __SizeX + 62,
			       __WallSize + (std::rand() % (__SizeY - (2 * __WallSize) - 54)),
			       _Game, _Players));
}

void				MobGenerator::SummonMecaCrab()
{
  if (_Frames == 1 && _Seconds == 50)
    _Game->AddFoe(new MecaCrab(_Game->GenerateId(), __SizeX + 40,
			       __SizeY / 2,
			       _Game, _Players));
}

void				MobGenerator::SummonCrab()
{
  if (_Frames == 1 && (_Seconds == 85 || _Seconds == 95 || _Seconds == 105 || _Seconds == 115))
  _Game->AddFoe(new Crab(_Game->GenerateId(), __SizeX + 34,
			 __WallSize + (std::rand() % (__SizeY - (2 * __WallSize) - 32)),
			 _Game, _Players));
}

void				MobGenerator::SummonButterfly()
{}

void				MobGenerator::SummonSuperMeca()
{}
