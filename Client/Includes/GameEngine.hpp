#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# include <SFML/Graphics.hpp>
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <atomic>
# include "IObject.hpp"
# include "ship.hpp"
# include "ProjArray.hpp"
# include "Hud.hpp"
# include "Srtp.hpp"
# include "API_Mutex.hpp"
# include "Loader.hpp"
# include "Explosion.hpp"

using namespace API_Mutex;

class	GameEngine
{
  using ptr = std::shared_ptr < IObject > ;
  using fcmd = ptr(GameEngine::*)(const int, const int, const int, const int, ObjectType);
  typedef void (GameEngine::*cmdFunction)(const Srtp &);
private:
  Loader	    						      _Loader;
  CleverHud							      _gameHud;
  int								      _mode;
  std::shared_ptr<ship>						      my_ship;
  std::vector<cmdFunction>	  				      _fct;
  std::vector<fcmd>						      _mob;
  std::vector<std::pair<ptr, std::shared_ptr<IMutex>>>		     _obj;
  std::vector<ProjArray>					      _prj;
  std::atomic<int>						      _idMax;
  int								      _idGame;
  std::vector<std::shared_ptr<Explosion>>			      _exp;

  ptr new_LittleShip(const int, const int, const int, const int, ObjectType);
  ptr new_BrownArmor(const int, const int, const int, const int, ObjectType);
  ptr new_Butterfly(const int, const int, const int, const int, ObjectType);
  ptr new_GreenArmor(const int, const int, const int, const int, ObjectType);
  ptr new_RedArmor(const int, const int, const int, const int, ObjectType);
  ptr new_MecaTurret(const int, const int, const int, const int, ObjectType);
  ptr new_MecaCrab(const int, const int, const int, const int, ObjectType);
  ptr new_Centiped(const int, const int, const int, const int, ObjectType);
  ptr new_Crab(const int, const int, const int, const int, ObjectType);
  ptr new_ShipMob(const int, const int, const int, const int, ObjectType);
  ptr new_Tentacle(const int, const int, const int, const int, ObjectType);
  ptr new_Ship(const int, const int, const int, const int, ObjectType);
public:
  GameEngine();
  ~GameEngine();
  GameEngine(const GameEngine &) = delete;
  GameEngine	&operator=(const GameEngine &) = delete;

  void						      update(sf::RenderWindow &);
  void						      setTab(const bool);
  ship						      &getShip() const;

  void						      setMode(int);
  void						      executeCmd(const Srtp &);
  void						      executeNew(const Srtp &);
  void						      executeDelete(const Srtp &);
  void						      executeAttack(const Srtp &);
  void						      executeUpdate(const Srtp &);
  void						      executeWelcome(const Srtp &);
  void						      executeStage(const Srtp &);
  void						      executeScore(const Srtp &);
  void						      executeNone(const Srtp &);

  int						      getIdGame() const;
};

# if defined(WIN32) || defined (_WIN32)
# define LIB_MUTEX	"../API/DLLs/lib_API_Mutex_STD.dll"
# define LIB_RES	"../API/DLLs/lib_API_Ressources.dll"
# define LIB_BROWNARMOR	"../API/DLLs/lib_API_BrownArmor.dll"
# define LIB_BUTTERFLY	"../API/DLLs/lib_API_Butterfly.dll"
# define LIB_CENTIPED	"../API/DLLs/lib_API_Centiped.dll"
# define LIB_CRAB	"../API/DLLs/lib_API_Crab.dll"
# define LIB_GREENARMOR "../API/DLLs/lib_API_GreenArmor.dll"
# define LIB_LITTLESHIP	"../API/DLLs/lib_API_LittleShip.dll"
# define LIB_MECACRAB	"../API/DLLs/lib_API_MecaCrab.dll"
# define LIB_MECATURRET	"../API/DLLs/lib_API_MecaTurret.dll"
# define LIB_REDARMOR	"../API/DLLs/lib_API_RedArmor.dll"
# define LIB_SHIPMOB	"../API/DLLs/lib_API_ShipMob.dll"
# define LIB_TENTACLE	"../API/DLLs/lib_API_Tentacle.dll"
# define LIB_ATTACK	"../API/DLLs/lib_API_attack.dll"
# define LIB_BONUS	"../API/DLLs/lib_API_Bonus.dll"
# else
# define LIB_MUTEX	"../API/SOs/lib_API_Mutex_STD.so"
# define LIB_RES	"../API/SOs/lib_API_Ressources.so"
# define LIB_BROWNARMOR	"../API/SOs/lib_API_BrownArmor.so"
# define LIB_BUTTERFLY	"../API/SOs/lib_API_Butterfly.so"
# define LIB_CENTIPED	"../API/SOs/lib_API_Centiped.so"
# define LIB_CRAB	"../API/SOs/lib_API_Crab.so"
# define LIB_GREENARMOR "../API/SOs/lib_API_GreenArmor.so"
# define LIB_LITTLESHIP	"../API/SOs/lib_API_LittleShip.so"
# define LIB_MECACRAB	"../API/SOs/lib_API_MecaCrab.so"
# define LIB_MECATURRET	"../API/SOs/lib_API_MecaTurret.so"
# define LIB_REDARMOR	"../API/SOs/lib_API_RedArmor.so"
# define LIB_SHIPMOB	"../API/SOs/lib_API_ShipMob.so"
# define LIB_TENTACLE	"../API/SOs/lib_API_Tentacle.so"
# define LIB_ATTACK	"../API/SOs/lib_API_attack.so"
# define LIB_BONUS	"../API/SOs/lib_API_Bonus.so"
# endif

#endif /* !GAMEENGINE_HPP_ */
