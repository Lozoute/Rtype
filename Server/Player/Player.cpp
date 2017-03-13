#include "Player.hpp"

///
/// CTOR, DTOR ETC
///
Player::Player			(Ptr<PlayerShip> &Sheep, Game *G)
				: _Id(-1), _ShipId(Sheep->GetId()), _Ship(Sheep),
				  _Game(G), _GameId(G->GetId()),
				  _Connected(false)
{}

Player::Player			(const Player&)
{}

Player				&Player::operator=(const Player &)
{
  return (*this);
}

Player::~Player			()
{}

///
/// GETTERS
///
int				Player::GetId() const
{
  return (_Id);
}

PlayerShip			*Player::GetShip() const
{
  return (_Ship.get());
}

Ptr<PlayerShip>			&Player::GetAObject()
{
  return (_Ship);
}

int				Player::GetShipId() const
{
  if (_Ship)
    return (_Ship->GetId());
  return (-1);
}

Game				*Player::GetGame() const
{
  return (_Game);
}

bool				Player::IsAlive() const
{
  if (_Ship)
    return (_Ship->IsAlive());
  return (false);
}

bool				Player::IsConnected() const
{
  return (_Connected);
}

int				Player::GetScore() const
{
  if (_Ship)
    return (_Ship->GetScore());
  return (0);
}

///
/// SETTERS
///
void				Player::Kill()
{
  _Ship->Kill();
}

void				Player::Resurect()
{
  _Ship->Resurect();
}

void				Player::Connect(int Id)
{
  _Id = Id;
  _Ship->Resurect();
   _Connected = true;
}

void				Player::Disconnect()
{
  _Id = -1;
  _Ship->Kill();
  _Ship->Reset();
  _Connected = false;
}

///
/// SEND SITUATION
///
void				Player::SendSituation()
{
  if (_Ship.get())
    {
      Srtp			P;

      P._idDest = _Id;
      P._cmdProto = CMDP_None;
      P._cmdClient = CMDC_Update;
      if (_Game)
	{
	  _Game->FillPacketFromObject(_Ship.get(), P);
	  SendPacket(P);
	}
    }
}
