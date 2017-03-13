#ifndef AOBJECT_HPP_
# define AOBJECT_HPP_

# include <iostream>
# include <string>
# include <memory>
# include <chrono>
# include <vector>
# include "API_Protocol.hpp"
# include "API_Mutex.hpp"
# include "Srtp.hpp"

class Game;
class PlayerShip;

/* Well I Find std::shared_ptr Too Long */
template <typename T>
using Ptr = std::shared_ptr<T>;


API_Protocol::IProtocol	*GetProto(API_Protocol::IProtocol *Obj = nullptr);

void			SendPacket(const Srtp &);


const auto		__FPS = std::chrono::microseconds(33333);
const auto		__LoadSym = "__API_Load__";
const auto		__LoadProto = "protocol_server";
const auto		__LoadCondVar = "get_CondVar";
const auto		__Shield = 60;
const auto		__RdmTol = 7;

#if defined(WIN32) || defined(_WIN32)
const auto		__LibMutex = "../API/DLLs/lib_API_Mutex_STD.dll";
const auto		__LibProto = "../API/DLLs/lib_API_Protocol.dll";
const auto		__LibCondVar = "../API/DLLs/lib_API_Mutex_STD.dll";
#else
const auto		__LibMutex = "../API/SOs/lib_API_Mutex_STD.so";
const auto		__LibProto = "../API/SOs/lib_API_Protocol.so";
const auto		__LibCondVar = "../API/SOs/lib_API_Mutex_STD.so";
#endif


class AObject
{
protected:
  ObjectType            _ObjType;
  MobType               _MobType;
  int                   _Id;
  int			_PosX;
  int			_PosY;
  int			_Width;
  int			_Height;
  int			_SpeedX;
  int			_SpeedY;
  int			_Hp;
  bool			_Alive;
  int			_Shield;
  int			_Dmgs;
  Game			*_Game;
  AObject		*_Owner;
  int			_OwnerId;
  int			_Score;
  BonusType		_BonusType;
  int			_IdTaker;

public:
  AObject		(ObjectType T, int Id, int X, int Y, int W, int H,
			 int Sx, int Sy, int Hp, int Dmgs, Game *Game,
			 MobType Mt = MT_None, AObject *Owner = nullptr,
			 BonusType Bt = BT_None)
			: _ObjType(T), _MobType(Mt), _Id(Id), _PosX(X),
			  _PosY(Y), _Width(W), _Height(H), _SpeedX(Sx),
			  _SpeedY(Sy), _Hp(Hp), _Alive(true), _Shield(0),
			  _Dmgs(Dmgs), _Game(Game), _Owner(Owner), _Score(0),
			  _BonusType(Bt), _IdTaker(-1)
			{
			  if (Owner)
			    _OwnerId = Owner->GetId();
			  else
			    _OwnerId = -1;
			  this->NotifyAll(CMDC_New);
			}

  AObject		(const AObject &O)
			: _ObjType(O._ObjType), _MobType(O._MobType),
			  _Id(O._Id), _PosX(O._PosX), _PosY(O._PosY),
			  _Width(O._Width), _Height(O._Height),
			  _SpeedX(O._SpeedX), _SpeedY(O._SpeedY), _Hp(O._Hp),
			  _Alive(O._Alive), _Shield(O._Shield),
			  _Dmgs(O._Dmgs), _Game(O._Game), _Owner(O._Owner),
			  _Score(O._Score), _BonusType(O._BonusType),
			  _IdTaker(O._IdTaker) {}

  AObject&		operator=(const AObject &O)
  {
    if (this != &O)
      {
	_ObjType = O._ObjType;
	_MobType = O._MobType;
	_Id = O._Id;
	_PosX = O._PosX;
	_PosY = O._PosY;
	_Width = O._Width;
	_Height = O ._Height;
	_SpeedX = O._SpeedX;
	_SpeedY = O._SpeedY;
	_Hp = O._Hp;
	_Alive = O._Alive;
	_Shield = O._Shield;
	_Dmgs = O._Dmgs;
	_Game = O._Game;
	_Owner = O._Owner;
	_Score = O._Score;
	_BonusType = O._BonusType;
	_IdTaker = O._IdTaker;
      }
    return (*this);
  }

  virtual ~AObject	() {}

  ObjectType		GetType()	const;
  MobType		GetMobType()	const;
  int			GetId()		const;
  int			GetPosX()	const;
  int			GetPosY()	const;
  int			GetWidth()	const;
  int			GetHeight()	const;
  int			GetSpeedX()	const;
  int			GetSpeedY()	const;
  int			GetDmgs()	const;
  int			GetShield()	const;
  int			GetHp()		const;
  AObject		*GetOwner()	const;
  int			GetOwnerId()	const;
  bool			IsAlive()	const;
  int			GetScore()	const;
  BonusType		GetBonusType()	const;
  int			GetIdTaker()	const;

  void			Kill();
  void			SetPosX(int);
  void			SetPosY(int);
  void			Move(int, int);
  void			SetSpeedX(int);
  void			SetSpeedY(int);
  void			SetHp(int);
  void			SetShield(int);
  void			SetDmgs(int);
  void			SetOwner(AObject *);
  void			Collide(AObject *);
  void			AddScore(MobType);
  void			NotifyAll(CmdClient)		const;
  void			NotifyAllButMe(CmdClient, int)	const;

  virtual void		Attack()				{}
  virtual void		TakeDmgs(int)				{}
  virtual bool		Update(std::vector<Ptr<AObject>> &)	{ return (false); }
  virtual void		Affect(PlayerShip &)			{}
};

#endif /* !AOBJECT_HPP_ */
