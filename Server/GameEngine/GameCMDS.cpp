#include "Game.hpp"

///
/// CMDS DU PROCTOLOGUE LéL
///
void				Game::CMDProtoConnect(const Srtp &P)
{
  for (std::vector<Ptr<Player>>::iterator It = _Players.begin(); It != _Players.end(); ++It)
    if (!(*It)->IsConnected())
      {
	(*It)->Connect(P._idDest);
	(*It)->GetAObject()->NotifyAllButMe(CMDC_New, P._idDest);
	this->Welcome(*It);
	_Allies.push_back((*It)->GetAObject());
	_Slots--;
	break;
      }
}

void				Game::CMDProtoDisconnect(const Srtp &P)
{
  for (std::vector<Ptr<Player>>::iterator It = _Players.begin(); It != _Players.end(); ++It)
    if ((*It)->GetId() == P._idDest)
      {
	(*It)->Disconnect();
	for (std::vector<Ptr<AObject>>::iterator Jt = _Allies.begin(); Jt != _Allies.end(); ++Jt)
	  if ((*Jt)->GetId() == (*It)->GetShipId())
	    {
	      _Allies.erase(Jt);
	      break;
	    }
	break;
      }
}

///
/// CMDS CLIENT
///
void				Game::CMDClientNew(const Srtp &)
{}

void				Game::CMDClientDelete(const Srtp &)
{}

void				Game::CMDClientAttack(const Srtp &P)
{
  Player			*Pl;

  if (P._idObject >= 0 && P._idObject < __MaxPlayers
      && (Pl = _Players[P._idObject].get()) && Pl->IsConnected())
    {
      if (!Pl->IsAlive())
	Pl->SendSituation();
      else
	Pl->GetAObject()->Attack();
    }
}

void				Game::CMDClientUpdate(const Srtp &P)
{
  Player			*Pl;

  if (P._idObject >= 0 && P._idObject < __MaxPlayers
      && (Pl = _Players[P._idObject].get()) && Pl->IsConnected())
    {
      if (!Pl->IsAlive() || P._posX < 0 || P._posX >= __SizeX ||
	  P._posY < __WallSize || P._posY >= __SizeY - __WallSize)
	Pl->SendSituation();
      else
	{
	  this->CheckBonus(Pl->GetAObject().get(), P._posX - Pl->GetAObject()->GetPosX(),
	  		   P._posY - Pl->GetAObject()->GetPosY());
	  Pl->GetAObject()->Move(P._posX, P._posY);
	  Pl->GetAObject()->NotifyAllButMe(CMDC_Update, Pl->GetId());
	  this->CheckCollisions(Pl->GetAObject().get(), _Foes, 0, 0);
	}
    }
}

void				Game::CMDClientWelcome(const Srtp &)
{}

void				Game::CMDClientStage(const Srtp &)
{}

void				Game::CMDClientScore(const Srtp &P)
{
  Srtp				Pa;

  Pa._cmdProto = CMDP_None;
  Pa._cmdClient = CMDC_Score;
  Pa._idDest = P._idDest;
  Pa._posX = _Players[0]->GetScore();
  Pa._posY = _Players[1]->GetScore();
  Pa._speedX = _Players[2]->GetScore();
  Pa._speedY = _Players[3]->GetScore();
  SendPacket(Pa);
}
