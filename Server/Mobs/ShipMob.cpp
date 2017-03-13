#include "ShipMob.hpp"

///
/// CTOR ETC
///
ShipMob::ShipMob		(int Id, int PosX, int PosY, Game *G)
				: AObject(OT_Mob, Id, PosX, PosY, 32, 22, 0, 1,
					  1, 1, G, MT_ShipMob), _Timer(60),
				  _Visible(false), _Coef(std::rand() % 6 + 2)
{}

ShipMob::ShipMob		(const ShipMob &O)
				  : AObject(O), _Timer(O._Timer),
				    _Visible(O._Visible), _Coef(O._Coef)
{}

ShipMob				&ShipMob::operator=(const ShipMob &)
{
  return (*this);
}

ShipMob::~ShipMob		()
{}

///
/// ACTIONS
///
void				ShipMob::EnterGame()
{
  _PosX -= 8;
  if (_PosX + (_Width * _Coef) + (5 * _Coef) < __SizeX)
    _Visible = true;
}

bool				ShipMob::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_Visible)
    this->EnterGame();
  else
    {
      if (_Timer > 0)
	--_Timer;
      else
	this->Attack();
      if (_Shield > 0)
	_Shield--;
      if (_PosY <= __WallSize)
	_SpeedY = 2;
      else if (_PosY + _Height >= __SizeY - __WallSize - 1)
	_SpeedY = -2;
      _Game->CheckCollisions(this, Them, _SpeedX, _SpeedY);
      _PosX += _SpeedX;
      _PosY += _SpeedY;
      return (true);
    }
  return (false);
}

void				ShipMob::Attack()
{
  if (_Game)
    {
      _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX - 1,
				 _PosY, -20000, 0, _Game, this, MT_ShipMob,
				 29, 10, 1, 2));
     _Timer = 30;
    }
}

void				ShipMob::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(__Shield / 4);
    }
}
