#ifndef GAME_HPP_
# define GAME_HPP_

# include <vector>
# include <cstring>
# include <cstdlib>
# include <atomic>
# include "AObject.hpp"
# include "Player.hpp"
# include "Loader.hpp"
# include "API_Thread.hpp"
# include "API_Mutex.hpp"
# include "Implementation/API_Mutex_STD/API_CondVar_STD.hpp"
# include "API_CondVar.hpp"
# include "API_Error.hpp"
# include "MobGenerator.hpp"

/// We're Lazy
using namespace			API_Mutex;
using namespace			API_Thread;

/// Forward Declarations
class				Player;
class				PlayerShip;
class				MobGenerator;
class				AObject;
class				BonusGenerator;

/// Variables
const auto			__MaxPlayers = 4;
const auto			__WallSize = 100;
const auto			__SizeX = 1920;
const auto			__SizeY = 1080;
const auto			__Zone = 4;

/// Game Class
class				Game
{
public:
  typedef void			(Game::*ThreadF)();
  typedef void			(Game::*CmdF)(const Srtp &);

private:
  int				_Id;
  int				_MaxId;
  int				_Stage;
  long long int			_Frames;
  std::atomic<bool>		_IsRunning;
  std::atomic<int>		_Slots;
  Ptr<MobGenerator>		_MobGen;
  Ptr<BonusGenerator>		_BonusGen;
  Loader			_Loader;

  std::vector<int>		_AvailableId;
  std::vector<Ptr<AObject>>	_Allies;
  std::vector<Ptr<AObject>>	_Foes;
  std::vector<Ptr<AObject>>	_Bonus;
  std::vector<Ptr<AObject>>	_Buff;
  std::vector<Ptr<Player>>	_Players;

  std::vector<Srtp>		_Packets;
  Ptr<IThread<ThreadF, Game *>>	_Thread;

  Ptr<ICondVar>			_CondVar;
  Ptr<IMutex>			_Starter;
  Ptr<IMutex>			_Mtx;

  std::vector<CmdF>		_CmdsClient;
  std::vector<CmdF>		_CmdsProto;

  Game				(const Game &);
  Game				&operator=(const Game &);

public:
  Game				(int, std::vector<Ptr<Player>> &);
  ~Game				();

  int				GetId()		const;
  int				GetNbAllies()	const;
  int				GetNbFoes()	const;

  bool				IsFull()	const;
  int				GetNbPlayers()	const;

  void				Welcome(Ptr<Player> &);
  void				FillPacketAndSend(std::vector<Ptr<AObject>> &, Srtp &);
  void				FillPacketFromObject(const AObject *, Srtp &);

  void				Close();
  void				Start();
  bool				EveryoneDead() const;

  int				GenerateId();
  void				GenRdmCoord(int *, int *, bool, int);
  void				GenRdmCoord(int *, int *, int);
  void				GenMobAndCo();

  AObject			*GetAtCoord(int, int) const;

  void				Update();
  void				UpdateSide(std::vector<Ptr<AObject>> &, std::vector<Ptr<AObject>> &);
  bool				CheckCollisions(AObject *, std::vector<Ptr<AObject> > &
						, int, int);
  void				CheckBonus(PlayerShip *, int, int);
  bool				CheckHitbox(AObject *, AObject *, int, int);
  void				AddSpeed(std::pair<int, int> &, std::pair<int, int> &, int, int);

  void				AddFoe(AObject *);
  void				AddAlly(AObject *);
  void				AddFoe(Ptr<AObject> &);
  void				AddAlly(Ptr<AObject> &);
  void				AddBuff(Ptr<AObject> &);
  void				AddBuff(AObject *);
  void				AddPacket(const Srtp &);

  void				TreatPackets();
  void				TreatPacketProto(const Srtp &);
  void				TreatPacketClient(const Srtp &);

  void				CMDProtoConnect(const Srtp &);
  void				CMDProtoDisconnect(const Srtp &);
  void				CMDClientNew(const Srtp &);
  void				CMDClientDelete(const Srtp &);
  void				CMDClientAttack(const Srtp &);
  void				CMDClientUpdate(const Srtp &);
  void				CMDClientWelcome(const Srtp &);
  void				CMDClientStage(const Srtp &);
  void				CMDClientScore(const Srtp &);

  void				SendToGame(Srtp &) const;
  void				SendToGame(Srtp &,int) const;

};

#endif /* !GAME_HPP_ */
