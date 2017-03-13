#include "MecaCrab.hpp"
#include "Player.hpp"

///
/// CTOR ETC
///
MecaCrab::MecaCrab		(int Id, int PosX, int PosY, Game *G, const std::vector<Ptr<Player>> &players)
				: AObject(OT_Mob, Id, PosX, PosY, 32, 31, 0, 0,
					  40, 20, G, MT_MecaCrab), _Visible(false),
				  _Players(players),  _FireRate(0)
{}

MecaCrab::MecaCrab		(const MecaCrab &O)
  : AObject(O), _Visible(O._Visible), _Players(O._Players)
{}

MecaCrab			&MecaCrab::operator=(const MecaCrab &)
{
  return (*this);
}

MecaCrab::~MecaCrab()
{}

///
/// ACTIONS
///
void				MecaCrab::EnterGame()
{
  _PosX -= 6;
  if (_PosX < __SizeX / 2)
    _Visible = true;
}

bool				MecaCrab::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_Visible)
    this->EnterGame();
  else
    {
      if (_Shield > 0)
	_Shield--;
      if (_FireRate > 0)
	_FireRate--;
      else
	Attack();
      _Game->CheckCollisions(this, Them, 0, 0);
      return (true);
    }
  return (false);
}

void				MecaCrab::Attack()
{
  for (int i = 0; i < 3; ++i)
    {
      if (_Players[i]->IsAlive())
	{
	  _TargetX = _Players[i]->GetShip()->GetPosX() - _PosX;
	  _TargetY = _Players[i]->GetShip()->GetPosY() - _PosY;
	  _TargetX *= 60;
	  _TargetY *= 60;
	  _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX,
				     _PosY, _TargetX, _TargetY, _Game, this, MT_MecaCrab,
				     16, 13, 1, _Game->GetNbPlayers()));
	}
      _FireRate = 2;
    }
}

void				MecaCrab::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(60);
    }
}
