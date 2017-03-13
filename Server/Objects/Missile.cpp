#include "Missile.hpp"
#include "Game.hpp"
#include "Player.hpp"

///
/// CTOR ETC
///
Missile::Missile	(int Id, Player *Pl, int PosX, int PosY, int SpeedX,
			 int SpeedY, Game *Game, AObject *Owner, MobType mt,
			 int W, int H, int Hp, int Dmgs)
			: AObject((Pl ? OT_MisAlly : OT_MisFoe), Id, PosX, PosY,
				  W, H, SpeedX, SpeedY, Hp, Dmgs, Game, mt, Owner),
			  _Player(Pl), _BaseX(PosX * 1000), _BaseY(PosY * 1000)
{}

Missile::Missile	(const Missile &O)
			  : AObject(O), _Player(O._Player), _BaseX(O._BaseX),
			    _BaseY(O._BaseY)
{}

Missile			&Missile::operator=(const Missile &)
{
  return (*this);
}

Missile::~Missile	()
{}

///
/// GETTERS
///
Player			*Missile::GetPlayer() const
{
  return (_Player);
}

///
/// SETTERS
///
void			Missile::SetPlayer(Player *Pl)
{
  _Player = Pl;
}

///
/// ACTIONS
///
bool			Missile::Update(std::vector<Ptr<AObject>> &Them)
{
  _BaseX += _SpeedX;
  _BaseY += _SpeedY;
  _Game->CheckCollisions(this, Them, (_BaseX / 1000) - _PosX, (_BaseY / 1000) - _PosY);
  _PosX = _BaseX / 1000;
  _PosY = _BaseY / 1000;
  if (_Shield > 0)
    _Shield--;
  if (_PosX < 0 || _PosY < 0 || _PosX >= __SizeX || _PosY >= __SizeY)
    this->Kill();
  return (true);
}

void			Missile::Attack()
{}

void			Missile::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(1);
    }
}
