#include "Centiped.hpp"
#include "Player.hpp"

///
/// CTOR ETC
///
Centiped::Centiped		(int Id, int PosX, int PosY, Game *G, const std::vector<Ptr<Player>> &players)
				: AObject(OT_Mob, Id, PosX, PosY, 62, 54, 0, 0,
					  G->GetNbPlayers(), 1, G, MT_Centiped), _Visible(false),
				  _Players(players),  _FireRate(0)
{}

Centiped::Centiped		(const Centiped &O)
  : AObject(O), _Visible(O._Visible), _Players(O._Players)
{}

Centiped			&Centiped::operator=(const Centiped &)
{
  return (*this);
}

Centiped::~Centiped()
{}

///
/// ACTIONS
///
void				Centiped::EnterGame()
{
    _Visible = true;
}

bool				Centiped::Update(std::vector<Ptr<AObject>> &Them)
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
	teleportAndFire();
      if (_FireRate % 10 == 0)
	Attack();
      _Game->CheckCollisions(this, Them, 0, 0);
      return (true);
    }
  return (false);
}

void				Centiped::teleportAndFire()
{
  _PosX = std::rand() % __SizeX;
  _PosY = __WallSize + (std::rand() % (__SizeY - (__WallSize * 2) - _Width));
  _FireRate = 80;
}

void				Centiped::Attack()
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
  _TargetX = Pl->GetPosX() - _PosX;
  _TargetY = Pl->GetPosY() - _PosY;
  _TargetX *= 50;
  _TargetY *= 50;
  _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX,
			     _PosY, _TargetX, _TargetY, _Game, this, MT_Centiped,
			     16, 13, 1, _Game->GetNbPlayers()));
}

void				Centiped::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(1);
    }
}
