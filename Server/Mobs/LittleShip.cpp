#include "LittleShip.hpp"

///
/// CTORS ETC
///
LittleShip::LittleShip		(int Id, int PosX, int PosY, Game *G)
				: AObject(OT_Mob, Id, PosX, PosY, 21, 24, -8,
					  -10, 1, 1, G, MT_LittleShip),
				  _Visible(false), _Frames(0)
{}

LittleShip::LittleShip		(const LittleShip &O)
				: AObject(O), _Visible(O._Visible)
{}

LittleShip			&LittleShip::operator=(const LittleShip &)
{
  return (*this);
}

LittleShip::~LittleShip		()
{}

///
/// ACTIONS
///
void				LittleShip::EnterGame()
{
  _PosX += _SpeedX;
  if (_PosX + _Width < __SizeX)
    _Visible = true;
}

bool				LittleShip::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_Visible)
    this->EnterGame();
  else
    {
      _Frames++;
      if (_Frames % 8 == 0)
	{
	  _SpeedY *= -1;
	  this->Attack();
	}
      _Game->CheckCollisions(this, Them, _SpeedX, _SpeedY);
      _PosX += _SpeedX;
      _PosY += _SpeedY;
      if (_Shield > 0)
	_Shield--;
      if (_PosX < (0 - _Width))
	this->Kill();
      return (true);
    }
  return (false);
}

void				LittleShip::Attack()
{
  if (_Game)
    _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX -1,
			       _PosY, -60000, 0, _Game, this, MT_LittleShip,
			       32, 14, 2, 2));
}

void				LittleShip::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(1);
    }
}
