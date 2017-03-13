#include "RedArmor.hpp"
#include "Game.hpp"
#include "Missile.hpp"

///
/// CTOR ETC
///
RedArmor::RedArmor		(int id, int x, int y, int phase, Game *game,
				 const std::vector<Ptr<Player>> &Pl)
				: AObject(OT_Boss, id, x, y, 60, 47, 0, 0,
					  8 - phase, 5, game, MT_RedArmor),
				  _timer(60), _dir(0), _speed(1 + phase), _visible(false),
				  _Players(Pl)
{
  _phase = phase + 3;
  _timer = 80 / _speed;
  SetShield(60);
}

RedArmor::~RedArmor		()
{}

///
/// UPDATE & CIE
///
void				RedArmor::EnterGame()
{
  _PosX -= _speed;
  if (_PosX  < __SizeX - ( (_Width * (_phase + 1)) + (10 * _phase)))
    _visible = true;
}

bool				RedArmor::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_visible)
    {
      this->EnterGame();
      return (false);
    }
  if (_Shield > 0)
    _Shield--;
  if (_timer > 0)
    _timer--;
  else
    this->Attack();
  if (_dir == 0)
    {
      _Game->CheckCollisions(this, Them, 0, - _speed);
      _PosY = _PosY - _speed;
    }
  else
    {
      _Game->CheckCollisions(this, Them, 0, _speed);
      _PosY = _PosY + _speed;
    }
  if (_PosY <= __WallSize)
    _dir = 1;
  else if (_PosY >= __SizeY - __WallSize - _Height)
    _dir = 0;
  return (true);
}

void				RedArmor::Attack()
{
  int				Target = std::rand() % 4;
  AObject			*Pl = _Players[Target]->GetShip();
  int				Secu = Target;
  int				_TargetX;
  int				_TargetY;

  while (!Pl->IsAlive())
    {
      Pl = _Players[(++Target) % 4]->GetShip();
      if (Target == Secu)
	return;
    }
  _TargetX = Pl->GetPosX() - _PosX;
  _TargetY = Pl->GetPosY() - _PosY;
  _TargetX *= 10;
  _TargetY *= 10;
  _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX, _PosY,
			     _TargetX, _TargetY, _Game, this, MT_RedArmor,
			     17, 16, 50, 20));
  _timer = (60 / _speed);
}

void				RedArmor::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      if (_phase < 5)
	_Game->AddBuff(new RedArmor(_Game->GenerateId(), _PosX, _PosY, _phase + 1, _Game, _Players));
      this->SetHp(_Hp - Dmg);
      this->SetShield(1);
    }
}
