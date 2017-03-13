#include "Tentacle.hpp"

///
/// CTOR ETC
///
Tentacle::Tentacle		(int Id, int PosX, int PosY, Game *G)
				: AObject(OT_Boss, Id, PosX, PosY, 139, 262, 0, 1,
					  90, 10, G, MT_Tentacle),
				  _Frames(0), _Visible(false), _BulletX(-1000),
				  _BulletY(0), _Dir(0)
{}

Tentacle::Tentacle		(const Tentacle &O)
				: AObject(O), _Frames(O._Frames),
				  _Visible(O._Visible), _BulletX(O._BulletX),
				  _BulletY(O._BulletY), _Dir(O._Dir)
{}

Tentacle			&Tentacle::operator=(const Tentacle &)
{
  return (*this);
}

Tentacle::~Tentacle()
{}

///
/// ACTIONS
///
void				Tentacle::EnterGame()
{
  _PosX -= 1;
  if (_PosX + _Width < __SizeX)
    _Visible = true;
}

bool				Tentacle::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_Visible)
    this->EnterGame();
  else
    {
      if (_Shield > 0)
	_Shield--;
      ++_Frames;
      this->Attack();
      _Game->CheckCollisions(this, Them, _SpeedX, _SpeedY);
      _PosX += _SpeedX;
      _PosY += _SpeedY;
      if (_PosY <= __WallSize)
	_SpeedY = 1;
      else if (_PosY >= __SizeY - __WallSize - _Height)
	_SpeedY = -1;
      return (true);
    }
  return (false);
}

void				Tentacle::Attack()
{
  if (_Hp > 60)
    this->PhaseOne();
  else if (_Hp > 55)
    this->PhaseTwo();
  else if (_Hp > 20)
    this->PhaseThree();
  else
    this->PhaseFour();
}

void				Tentacle::RotateAndFire()
{
  if (!_Game)
    return;
  _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX - 1,
			    (_PosY + (_Height / 2)) % __SizeY,
			    _BulletX * 15, _BulletY * 15, _Game, this, MT_Tentacle,
			    32, 29, 100, 5));

  if (_Dir == 0)
    {
      _BulletY -= 100;
      if (_BulletY <= -900)
	{
	  _BulletY = -1000;
	  _Dir = 1;
	}
      if (_BulletY < 0)
	_BulletX += 100;
      else
	_BulletX -= 100;
    }
  else
    {
      _BulletY += 100;
      if (_BulletY >= 900)
	{
	   _BulletY = 1000;
	  _Dir = 0;
	}
      if (_BulletY < 0)
	_BulletX -= 100;
      else
	_BulletX += 100;
    }
}

void				Tentacle::PhaseOne()
{
  if (_Frames % 5 == 0)
    this->RotateAndFire();
}

void				Tentacle::PhaseTwo()
{
  if (_Frames % 6 == 0 && _Game)
    _Game->AddBuff(new LittleShip(_Game->GenerateId(), __SizeX,
				  std::rand() % __SizeY, _Game));
}

void				Tentacle::PhaseThree()
{
  if (_Frames % 5 == 0)
  this->RotateAndFire();
}

void				Tentacle::PhaseFour()
{
  if (_Frames % 4 == 0)
    this->RotateAndFire();
  if (_Frames % 4 == 0 && _Game)
    _Game->AddBuff(new LittleShip(_Game->GenerateId(), __SizeX,
				  std::rand() % __SizeY, _Game));
}

void				Tentacle::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(__Shield / 5);
    }
}
