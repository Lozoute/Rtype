#include "AObject.hpp"
#include "Game.hpp"

///
/// GETTERS
///
ObjectType		AObject::GetType()	const
{
  return (_ObjType);
}

MobType			AObject::GetMobType()	const
{
  return (_MobType);
}

int			AObject::GetId()	const
{
  return (_Id);
}

int			AObject::GetPosX()	const
{
  return (_PosX);
}

int			AObject::GetPosY()	const
{
  return (_PosY);
}

int			AObject::GetWidth()	const
{
  return (_Width);
}

int			AObject::GetHeight()	const
{
  return (_Height);
}

int			AObject::GetSpeedX()	const
{
  return (_SpeedX);
}

int			AObject::GetSpeedY()	const
{
  return (_SpeedY);
}

int			AObject::GetDmgs()	const
{
  return (_Dmgs);
}

int			AObject::GetShield()	const
{
  return (_Shield);
}

int			AObject::GetHp()	const
{
  return (_Hp);
}

AObject			*AObject::GetOwner()	const
{
  return (_Owner);
}

int			AObject::GetOwnerId()	const
{
  return (_OwnerId);
}

bool			AObject::IsAlive()	const
{
  return (_Alive);
}

int			AObject::GetScore()	const
{
  return (_Score);
}

BonusType		AObject::GetBonusType()	const
{
  return (_BonusType);
}

int			AObject::GetIdTaker()	const
{
  return (_IdTaker);
}

///
/// SETTERS
///
void			AObject::Kill()
{
  _Alive = false;
  this->NotifyAll(CMDC_Delete);
  _PosX = -1;
  _PosY = -1;
}

void			AObject::SetPosX(int X)
{
  _PosX = X;
}

void			AObject::SetPosY(int Y)
{
  _PosY = Y;
}

void			AObject::Move(int X, int Y)
{
  _PosX = X;
  _PosY = Y;
}

void			AObject::SetSpeedX(int SpeedX)
{
  _SpeedX = SpeedX;
}

void			AObject::SetSpeedY(int SpeedY)
{
  _SpeedY = SpeedY;
}

void			AObject::SetHp(int Hp)
{
  _Hp = Hp;
  if (_Hp <= 0)
    this->Kill();
}

void			AObject::SetShield(int Shield)
{
  _Shield = Shield;
}

void			AObject::SetDmgs(int Dmgs)
{
  if (Dmgs >= 0)
    _Dmgs = Dmgs;
}

void			AObject::SetOwner(AObject *Owner)
{
  _Owner = Owner;
}

///
/// MISC
///
void			AObject::Collide(AObject *Other)
{
  if (Other)
    {
      if (_ObjType == OT_MisAlly && Other->GetType() == OT_Mob)
	this->GetOwner()->AddScore(Other->GetMobType());
      else if (_ObjType != OT_Mob && Other->GetType() == OT_MisAlly)
	Other->GetOwner()->AddScore(_MobType);
      this->TakeDmgs(Other->GetDmgs());
      Other->TakeDmgs(this->GetDmgs());
    }
}

void			AObject::AddScore(MobType Mt)
{
  if (Mt == MT_GreenArmor)
    _Score += 10;
  else if (Mt == MT_ShipMob)
    _Score += 15;
  else if (Mt == MT_LittleShip)
    _Score += 50;
  else if (Mt == MT_Tentacle)
    _Score += 10;
  else if (Mt == MT_RedArmor)
    _Score += 15;
}

void			AObject::NotifyAll(CmdClient C) const
{
  Srtp			P;

  P._cmdProto = CMDP_None;
  P._cmdClient = C;
  if (_Game)
    {
      _Game->FillPacketFromObject(this, P);
      _Game->SendToGame(P);
    }
}

void			AObject::NotifyAllButMe(CmdClient C, int Id) const
{
  Srtp			P;

  P._cmdProto = CMDP_None;
  P._cmdClient = C;
  if (_Game)
    {
      _Game->FillPacketFromObject(this, P);
      _Game->SendToGame(P, Id);
    }
}
