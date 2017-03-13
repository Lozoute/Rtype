#include "PlayerShip.hpp"

///
/// CTOR ETC
///
PlayerShip::PlayerShip		(int Id, int PosX, int PosY, Game *G)
				: AObject(OT_Player, Id, PosX, PosY, 32, 16, 0,
					  0, 20, 1, G),
				  _Player(nullptr), _FireRate(__FireRate), _Timer(0),
				  _BoostFireRate(0), _BoostDamages(0), _Damages(__Damages)
{
  _Alive = false;
}

PlayerShip::PlayerShip		(const PlayerShip &O)
				: AObject(O), _Player(O._Player),
				  _FireRate(O._FireRate)
{}

PlayerShip			&PlayerShip::operator=(const PlayerShip &)
{
  return (*this);
}

PlayerShip::~PlayerShip		()
{}

///
/// GETTERS
///
Player				*PlayerShip::GetPlayer() const
{
  return (_Player);
}

int				PlayerShip::GetPlayerId() const
{
  if (_Player)
    return (_Player->GetId());
  return (-1);
}

///
/// SETTERS
///
void				PlayerShip::SetPlayer(Player *Pl)
{
  if (Pl)
    _Player = Pl;
}

void				PlayerShip::Resurect()
{
  if (_Game)
    {
      _Alive = true;
      _Hp = 20;
      _Score = 0;
      _Game->GenRdmCoord(&_PosX, &_PosY, true, __RdmTol);
    }
}

void				PlayerShip::Reset()
{
  _Hp = 20;
  _Score = 0;
  _PosX = 50;
  _PosY = 200;
}

///
/// ACTIONS
///
bool				PlayerShip::Update(std::vector<Ptr<AObject>> &)
{
  if (_Shield > 0)
    {
      _Shield--;
      if (_Shield <= 0)
	this->NotifyAll(CMDC_Update);
    }
  this->DecrBoost();
  if (_Timer > 0)
    _Timer--;
  return (_Shield <= 0);
}

void				PlayerShip::TakeDmgs(int Dmg)
{
  if (Dmg > 0 && _Shield <= 0)
    {
      this->SetHp(_Hp - Dmg);
      if (!_Alive && _Player)
	_Player->Kill();
      else
	{
	  this->SetShield(__Shield);
	  this->NotifyAll(CMDC_Update);
	}
    }
}

void				PlayerShip::Attack()
{
  if (_Game && _Timer <= 0)
    {
      _Game->AddAlly(new Missile(_Game->GenerateId(), _Player, _PosX + 1,
				 _PosY, 30000, 0, _Game, this, MT_None, 48, 13,
				 1, 1));
      _Timer = _FireRate;
    }
}

///
/// BOOST
///
void				PlayerShip::DecrBoost()
{
  if (_BoostFireRate > 0)
    {
      _BoostFireRate--;
      if (_BoostFireRate == 0)
	{
	  _FireRate = __FireRate;
	  this->NotifyBonus(BT_FireRateBooster, __FireRate);
	}
    }
  if (_BoostDamages > 0)
    {
      _BoostDamages--;
      if (_BoostDamages == 0)
	{
	  _Damages = __Damages;
	  this->NotifyBonus(BT_DamageBooster, __Damages);
	}
    }
}

void				PlayerShip::BoostFireRate(int Gain)
{
  _FireRate = Gain;
  _BoostFireRate += 240;
  this->NotifyBonus(BT_FireRateBooster, Gain);
}

void				PlayerShip::BoostDamages(int Gain)
{
  _Damages += Gain;
  _BoostDamages += 360;
  this->NotifyBonus(BT_DamageBooster, _Damages);
}

void				PlayerShip::NotifyBonus(BonusType Type, int Val)
{
  Srtp				P;

  if (!_Player || !_Game)
    return;
  P._cmdProto = CMDP_None;
  P._cmdClient = CMDC_Update;
  P._idDest = _Player->GetId();
  P._objType = OT_Bonus;
  P._mobType = MT_None;
  P._bonusType = Type;
  P._idGame = _Game->GetId();
  P._idObject = _Id;
  P._idMissile = -1;
  P._speedX = Val;
  P._speedY = -1;
  P._posX = -1;
  P._posY = -1;
  P._shield = 0;
  P._hp = 20;
  _Game->SendToGame(P);
}

void				PlayerShip::NotifyBonusBase()
{
  this->NotifyBonus(BT_FireRateBooster, __FireRate);
  this->NotifyBonus(BT_DamageBooster, __Damages);
}
