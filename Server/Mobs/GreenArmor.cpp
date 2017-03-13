#include "GreenArmor.hpp"
#include "Player.hpp"

///
/// CTOR ETC
///
GreenArmor::GreenArmor		(int Id, int PosX, int PosY, Game *G, const std::vector<Ptr<Player>> &players)
				: AObject(OT_Mob, Id, PosX, PosY, 56, 56, -4, 0,
					  1, 1, G, MT_GreenArmor), _Visible(false),
				  _Players(players), _Target(-1), _FireRate(0)
{}

GreenArmor::GreenArmor		(const GreenArmor &O)
  : AObject(O), _Visible(O._Visible), _Players(O._Players)
{}

GreenArmor			&GreenArmor::operator=(const GreenArmor &)
{
  return (*this);
}

GreenArmor::~GreenArmor()
{}

///
/// ACTIONS
///
void				GreenArmor::EnterGame()
{
  _PosX += _SpeedX;
  if (_PosX + _Width < __SizeX)
    _Visible = true;
}

bool				GreenArmor::Update(std::vector<Ptr<AObject>> &Them)
{
  if (!_Visible)
    this->EnterGame();
  else
    {
      aimPlayer();
      if (_Shield > 0)
	_Shield--;
      if (_FireRate > 0)
	_FireRate--;
      _Game->CheckCollisions(this, Them, _SpeedX, _SpeedY);
      _PosX += _SpeedX;
      _PosY += _SpeedY;
      if (_PosX < (0 - _Width))
	this->Kill();
      return (true);
    }
  return (false);
}

void				GreenArmor::aimPlayer()
{
  AObject			*sheep;
  int				sheepY;

  if (_Target == -1)
    _Target = std::rand() % 4;
  sheep = _Players[_Target]->GetShip();
  sheepY = _Target;
  while (!(sheep->IsAlive()) || !(_Players[_Target]->IsConnected()))
    {
      _Target = (_Target + 1) % 4;
      if (_Target == sheepY)
	{
	  _SpeedY = 0;
	  return;
	}
      sheep = _Players[_Target]->GetShip();
    }
  sheepY = sheep->GetPosY();
  if ((_PosY >= sheepY && _PosY <= sheepY + sheep->GetHeight())
      || (_PosY + _Height >= sheepY && _PosY + _Height <= sheepY + sheep->GetHeight())
      || sheep->GetPosX() > _PosX)
    {
      _SpeedY = 0;
      if (sheep->GetPosX() < _PosX)
	this->Attack();
    }
  else if (sheepY < _PosY)
    _SpeedY = -4;
  else if (sheepY > _PosY)
    _SpeedY = 4;
}

void				GreenArmor::Attack()
{
  if (_FireRate <= 0)
    {
      _SpeedY = 0;
      _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX - 1,
				 _PosY, -40000, 0, _Game, this, MT_GreenArmor,
				 48, 4, 1, 1));
      _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX - 1,
				 _PosY + (_Height / 2), -40000, 0, _Game, this, MT_GreenArmor,
				 48, 4, 1, 1));
      _Game->AddBuff(new Missile(_Game->GenerateId(), nullptr, _PosX - 1,
				 _PosY + _Height, -40000, 0, _Game, this, MT_GreenArmor,
				 48, 4, 1, 1));
      _FireRate = 15;
    }
}

void				GreenArmor::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      this->SetShield(1);
    }
}
