#include "Crab.hpp"
#include "Player.hpp"

///
/// CTOR ETC
///
Crab::Crab		(int Id, int PosX, int PosY, Game *G, const std::vector<Ptr<Player>> &players)
				: AObject(OT_Mob, Id, PosX, PosY, 32, 32, 0, 0,
					  G->GetNbPlayers() * 40, 99999, G, MT_BrownArmor), _Visible(false),
				  _Players(players),  _FireRate(0)
{}

Crab::Crab		(const Crab &O)
  : AObject(O), _Visible(O._Visible), _Players(O._Players)
{}

Crab			&Crab::operator=(const Crab &)
{
  return (*this);
}

Crab::~Crab()
{}

///
/// ACTIONS
///
void				Crab::EnterGame()
{
  _PosX -= 1;
  if (_PosX + _Width < __SizeX)
    _Visible = true;
}

bool				Crab::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_Visible)
    this->EnterGame();
  else
    {
      _PosX += _SpeedX;
      _PosY += _SpeedY;
      if (_Shield > 0)
	_Shield--;
      Attack();
      _Game->CheckCollisions(this, Them, 0, 0);
      return (true);
    }
  return (false);
}

void				Crab::Attack()
{
  int				Target = std::rand() % 4;
  AObject			*Pl = _Players[Target]->GetShip();
  int				Secu = Target;

  while (!Pl->IsAlive())
    {
      Pl = _Players[(++Target) % 4]->GetShip();
      if (Target == Secu)
	return;
    }
  _SpeedX = (Pl->GetPosX() - _PosX < 0 ? -2 : 2);
  _SpeedY = (Pl->GetPosY() - _PosY < 0 ? -2 : 2);
}

void				Crab::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(1);
    }
}
