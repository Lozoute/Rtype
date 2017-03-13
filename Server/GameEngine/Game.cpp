#include <cstdlib>
#include "Game.hpp"
#include "AObject.hpp"
#include "ShipMob.hpp"
#include "PlayerShip.hpp"
#include "GreenArmor.hpp"
#include "LittleShip.hpp"
#include "Tentacle.hpp"
#include "MobGenerator.hpp"
#include "BonusGenerator.hpp"

///
/// CTOR ETC
///
Game::Game			(int Id, std::vector<Ptr<Player>> &Plyrs)
				  : _Id(Id), _MaxId(__MaxPlayers), _Stage(0), _Frames(0),
				  _IsRunning(false), _Slots(__MaxPlayers)
{
  for (unsigned int i = 0; i < __MaxPlayers; ++i)
    {
      Ptr<PlayerShip>		Sheep(new PlayerShip(i, -1, -1, this));
      Ptr<Player>		Pl(new Player(Sheep, this));

      Sheep->SetPlayer(Pl.get());
      Plyrs.push_back(Pl);
      _Players.push_back(Pl);
    }
  _CmdsProto.push_back(&Game::CMDProtoConnect);
  _CmdsProto.push_back(&Game::CMDProtoDisconnect);
  _CmdsClient.push_back(&Game::CMDClientNew);
  _CmdsClient.push_back(&Game::CMDClientDelete);
  _CmdsClient.push_back(&Game::CMDClientAttack);
  _CmdsClient.push_back(&Game::CMDClientUpdate);
  _CmdsClient.push_back(&Game::CMDClientWelcome);
  _CmdsClient.push_back(&Game::CMDClientStage);
  _CmdsClient.push_back(&Game::CMDClientScore);
  _MobGen.reset(new MobGenerator(this, _Players));
  _BonusGen.reset(new BonusGenerator(*this, _Bonus));
  _Starter = _Loader.getSmartPtr<IMutex>(__LibMutex, __LoadSym);
  _Mtx = _Loader.getSmartPtr<IMutex>(__LibMutex, __LoadSym);
  _CondVar = _Loader.getSmartPtr<ICondVar>(__LibCondVar, __LoadCondVar);
  _Thread.reset(new Thread<ThreadF, Game *>);
  if (!_Thread->init(&Game::Update, this))
    throw Error("Unable To Init Thread", "Game::Game()");
}

Game::Game			(const Game &)
{}

Game				&Game::operator=(const Game &)
{
  return (*this);
}

Game::~Game			()
{}

///
/// BASICS GETTERS
///
int				Game::GetId() const
{
  return (_Id);
}

int				Game::GetNbAllies() const
{
  return (_Allies.size());
}

int				Game::GetNbFoes() const
{
  return (_Foes.size());
}

///
/// NB PLAYERS
///
bool				Game::IsFull() const
{
  return (_Slots <= 0);
}

int				Game::GetNbPlayers() const
{
  return (__MaxPlayers - _Slots);
}

///
/// WAILCAUME
///
void				Game::Welcome(Ptr<Player> &Pl)
{
  Srtp				P;

  if (!Pl.get())
    return;
  P._idDest = Pl->GetId();
  P._cmdProto = CMDP_None;
  P._cmdClient = CMDC_Welcome;
  this->FillPacketFromObject(Pl->GetShip(), P);
  SendPacket(P);
  P._cmdClient = CMDC_New;
  this->FillPacketAndSend(_Allies, P);
  this->FillPacketAndSend(_Foes, P);
  Pl->GetShip()->NotifyBonusBase();
}

void				Game::FillPacketAndSend(std::vector<Ptr<AObject>> &Objs, Srtp &P)
{
  for (std::vector<Ptr<AObject>>::iterator It = Objs.begin(); It != Objs.end(); ++It)
    {
      this->FillPacketFromObject((*It).get(), P);
      SendPacket(P);
    }
}

void				Game::FillPacketFromObject(const AObject *Obj, Srtp &P)
{
  if (!Obj)
    return;
  P._objType = Obj->GetType();
  P._mobType = Obj->GetMobType();
  P._idGame = _Id;
  P._idObject = Obj->GetId();
  P._idMissile = -1;
  P._posX = Obj->GetPosX();
  P._posY = Obj->GetPosY();
  if (Obj->GetType() == OT_MisAlly || Obj->GetType() == OT_MisFoe)
    {
      P._idObject = Obj->GetOwnerId();
      P._idMissile = Obj->GetId();
    }
  else if (Obj->GetType() == OT_Bonus)
    P._idMissile = Obj->GetIdTaker();
  P._speedX = Obj->GetSpeedX();
  P._speedY = Obj->GetSpeedY();
  P._hp = Obj->GetHp();
  P._shield = (Obj->GetShield() > 0);
  P._bonusType = Obj->GetBonusType();
}

///
/// START & CLOSE
///
void				Game::Start()
{
  _IsRunning = true;
  _CondVar->notifyOne();
}

void				Game::Close()
{
  _IsRunning = false;
  _Slots = __MaxPlayers;
  _Allies.clear();
  _Foes.clear();
  _Bonus.clear();
  _Buff.clear();
  _AvailableId.clear();
  _Stage = 0;
  _MaxId = __MaxPlayers;
  for (std::vector<Ptr<Player>>::iterator It = _Players.begin(); It != _Players.end(); ++It)
    (*It)->Disconnect();
  _MobGen.reset(new MobGenerator(this, _Players));
  _BonusGen.reset(new BonusGenerator(*this, _Bonus));
}

bool				Game::EveryoneDead() const
{
  for (std::vector<Ptr<Player>>::const_iterator It = _Players.begin(); It != _Players.end(); ++It)
    if ((*It)->IsAlive())
      return (false);
  return (true);
}

///
/// UPDATING GAME
///
void				Game::Update()
{
  while (1)
    {
      _CondVar->wait(_Starter);
      while (_IsRunning)
	{
	  auto Start = std::chrono::high_resolution_clock::now();
	  _Frames++;
	  this->GenMobAndCo();
	  this->UpdateSide(_Allies, _Foes);
	  this->UpdateSide(_Foes, _Allies);
	  _Foes.insert(_Foes.end(), _Buff.begin(), _Buff.end());
	  _Buff.clear();
	  this->TreatPackets();
	  if (this->EveryoneDead())
	    this->Close();
	  auto End = std::chrono::high_resolution_clock::now();
	  if (End - Start < __FPS && _IsRunning)
	    std::this_thread::sleep_for(__FPS - (End - Start));
	}
    }
}

void				Game::UpdateSide(std::vector<Ptr<AObject>> &Us,
						 std::vector<Ptr<AObject>> &Them)
{
  for (std::vector<Ptr<AObject>>::iterator It = Us.begin(); It != Us.end(); )
    {
      (*It)->Update(Them);
      if (!(*It)->IsAlive() || (*It)->GetHp() <= 0)
	{
	  if ((*It)->GetId() == _MaxId -1)
	    _MaxId--;
	  else
	    _AvailableId.push_back((*It)->GetId());
	  It = Us.erase(It);
	}
      else
	{
	  if ((*It)->GetType() == OT_Mob || (*It)->GetType() == OT_Boss)
	    (*It)->NotifyAll(CMDC_Update);
	  ++It;
	}
    }
}

///
/// COLLISIONS
///
bool				Game::CheckCollisions(AObject *Init,
						      std::vector<Ptr<AObject>> &Objs,
						      int a, int b)
{
  if (Init && Init->GetShield() <= 0)
    {
      for (std::vector<Ptr<AObject>>::iterator It = Objs.begin(); It != Objs.end(); ++It)
	{
	  if (Init != (*It).get() && (*It)->GetShield() <= 0 &&
	      !(Init->GetType() == OT_MisAlly && (*It)->GetType() == OT_Bonus))
	    if (CheckHitbox(Init, (*It).get(), a + 1, b + 1))
	      return (true);
	}
    }
  return (false);
}

void				Game::CheckBonus(PlayerShip *Init, int a, int b)
{
  if (Init)
    {
      for (std::vector<Ptr<AObject>>::iterator It = _Bonus.begin(); It != _Bonus.end(); ++It)
	{
	  if (Init != (*It).get() && CheckHitbox(Init, (*It).get(), a + 1, b + 1))
	    {
	      (*It)->Affect(*Init);
	      _Bonus.erase(It);
	      break;
	    }
	}
    }
}

bool				Game::CheckHitbox(AObject *A, AObject *B, int speedX, int speedY)
{
  std::pair<int, int>		aStart(A->GetPosX() - 1, A->GetPosY() - 1);
  std::pair<int, int>		aEnd(A->GetPosX() - 1 + A->GetWidth(), A->GetPosY() - 1 + A->GetHeight());
  std::pair<int, int>		bStart(B->GetPosX(), B->GetPosY());
  std::pair<int, int>		bEnd(B->GetPosX() + B->GetWidth(), B->GetPosY() + B->GetHeight());
  bool				widthCollide = false;
  bool				heightCollide = false;

  if (A->GetWidth() <= 0 || A->GetHeight() <= 0 || B->GetWidth() <= 0 || B->GetHeight() <= 0)
    return (false);
  AddSpeed(aStart, aEnd, speedX, speedY);
  widthCollide = false;
  heightCollide = false;
  if ((bStart.first >= aStart.first && bStart.first <= aEnd.first)
      || (bEnd.first >= aStart.first && bEnd.first <= aEnd.first))
    widthCollide = true;
  if ((bStart.second >= aStart.second && bStart.second <= aEnd.second)
      || (bEnd.second >= aStart.second && bEnd.second <= aEnd.second))
    heightCollide = true;
  if (widthCollide && heightCollide)
    {
      A->Collide(B);
      return (true);
    }
  return (false);
}

void				Game::AddSpeed(std::pair<int, int> &a,
					       std::pair<int, int> &b,
					       int speedX, int speedY)
{
  if (speedX == 0 && speedY == 0)
    return;
  if (speedX == 0)
    b.second += speedY;
  else if (speedY == 0)
    b.first += speedX;
  else
    {
      a.first += speedX;
      a.second += speedY;
      b.first += speedX;
      b.second += speedY;
    }
}

///
/// ID GENERATING
///
int				Game::GenerateId()
{
  int                           Id;

  if (_AvailableId.size())
    {
      Id = _AvailableId.back();
      _AvailableId.pop_back();
    }
  else
    {
      Id = _MaxId;
      ++_MaxId;
    }
  return (Id);
}

///
/// COORD GENERATING
///
void				Game::GenRdmCoord(int *X, int *Y, bool Ally, int Tol)
{
  if (!Ally)
    *X = (__SizeX / __Zone * 2) + (std::rand() % (__SizeX - (__SizeX / __Zone * 2)));
  else
    *X = std::rand() % (__SizeX / __Zone);
  *Y = __WallSize + (std::rand() % (__SizeY - (__WallSize * 2) - 16));
  if (this->GetAtCoord(*X, *Y) && Tol)
    this->GenRdmCoord(X, Y, Ally, Tol - 1);
}

void				Game::GenRdmCoord(int *X, int *Y, int Tol)
{
  *X = std::rand() % __SizeX;
  *Y = __WallSize + (std::rand() % (__SizeY - (__WallSize * 2) - 16));
  if (this->GetAtCoord(*X, *Y) && Tol)
    this->GenRdmCoord(X, Y, Tol - 1);
}

///
/// MOBS & BONUS ETC GENERATION
///
void				Game::GenMobAndCo()
{
  if (_MobGen->Generate(_Stage) == true && _Foes.size() == 0)
    {
      Srtp			P;

      P._cmdProto = CMDP_None;
      P._cmdClient = CMDC_Stage;
      P._idGame = _Id;
      this->SendToGame(P);
      _Stage++;
    }
  _BonusGen->Generate(_Frames, _Stage);
}

///
/// GET AT COORD
///
AObject				*Game::GetAtCoord(int X, int Y) const
{
  for (std::vector<Ptr<AObject>>::const_iterator It = _Allies.begin(); It != _Allies.end(); ++It)
    if ((*It)->GetPosX() == X && (*It)->GetPosY() == Y)
      return ((*It).get());
  for (std::vector<Ptr<AObject>>::const_iterator It = _Foes.begin(); It != _Foes.end(); ++It)
    if ((*It)->GetPosX() == X && (*It)->GetPosY() == Y)
      return ((*It).get());
  return (nullptr);
}

///
/// ADDING NEW AOBJECT
///
void				Game::AddFoe(AObject *Obj)
{
  if (Obj)
    _Foes.emplace_back(Obj);
}

void				Game::AddAlly(AObject *Obj)
{
  if (Obj)
    _Allies.emplace_back(Obj);
}

void				Game::AddFoe(Ptr<AObject> &Obj)
{
  if (Obj.get())
    _Foes.emplace_back(Obj);
}

void				Game::AddAlly(Ptr<AObject> &Obj)
{
  if (Obj.get())
    _Allies.emplace_back(Obj);
}

void				Game::AddPacket(const Srtp &P)
{
  _Mtx->lock();
  _Packets.push_back(P);
  _Mtx->unLock();
}

void				Game::AddBuff(Ptr<AObject> &Obj)
{
  if (Obj.get())
    _Buff.emplace_back(Obj);
}

void				Game::AddBuff(AObject *Obj)
{
  if (Obj)
    _Buff.emplace_back(Obj);
}

///
/// TREAT PACKETS
///
void				Game::TreatPackets()
{
  _Mtx->lock();
  for (std::vector<Srtp>::iterator It = _Packets.begin(); It != _Packets.end(); ++It)
    {
      if ((*It)._cmdProto != CMDP_None)
	this->TreatPacketProto(*It);
      else
	this->TreatPacketClient(*It);
    }
  _Packets.clear();
  _Mtx->unLock();
}

void				Game::TreatPacketProto(const Srtp &P)
{
  if (P._cmdProto >= 0 && P._cmdProto < CMDP_None)
    (this->*(_CmdsProto[P._cmdProto]))(P);
}

void				Game::TreatPacketClient(const Srtp &P)
{
  if (P._cmdClient >= 0 && P._cmdClient < CMDC_None)
    (this->*(_CmdsClient[P._cmdClient]))(P);
}

/// SEND TO EVERYONE IN GAME
///
void				Game::SendToGame(Srtp &P) const
{
  for (std::vector<Ptr<Player>>::const_iterator It = _Players.begin(); It != _Players.end(); ++It)
    {
      if ((*It)->IsConnected() && (*It)->GetId() != -1)
	{
	  P._idDest = (*It)->GetId();
	  SendPacket(P);
	}
    }
}

void				Game::SendToGame(Srtp &P, int Id) const
{
  for (std::vector<Ptr<Player>>::const_iterator It = _Players.begin(); It != _Players.end(); ++It)
    {
      if ((*It)->IsConnected() && (*It)->GetId() != Id && (*It)->GetId() != -1)
	{
	  P._idDest = (*It)->GetId();
	  SendPacket(P);
	}
    }
}
