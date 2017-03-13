#include "GameEngine.hpp"
#include "IRessources.hpp"

GameEngine::GameEngine()
  : _obj(1000, std::pair<ptr, std::shared_ptr<IMutex>>(nullptr, _Loader.getSmartPtr<IMutex>(LIB_MUTEX, "__API_Load__")))
{
  _idMax = 0;
  _idGame = 0;

  this->_fct.push_back(&GameEngine::executeNew);
  this->_fct.push_back(&GameEngine::executeDelete);
  this->_fct.push_back(&GameEngine::executeAttack);
  this->_fct.push_back(&GameEngine::executeUpdate);
  this->_fct.push_back(&GameEngine::executeWelcome);
  this->_fct.push_back(&GameEngine::executeStage);
  this->_fct.push_back(&GameEngine::executeScore);
  this->_fct.push_back(&GameEngine::executeNone);

  this->_mob.push_back(&GameEngine::new_LittleShip);
  this->_mob.push_back(&GameEngine::new_BrownArmor);
  this->_mob.push_back(&GameEngine::new_Butterfly);
  this->_mob.push_back(&GameEngine::new_GreenArmor);
  this->_mob.push_back(&GameEngine::new_RedArmor);
  this->_mob.push_back(&GameEngine::new_MecaTurret);
  this->_mob.push_back(&GameEngine::new_MecaCrab);
  this->_mob.push_back(&GameEngine::new_Centiped);
  this->_mob.push_back(&GameEngine::new_Crab);
  this->_mob.push_back(&GameEngine::new_ShipMob);
  this->_mob.push_back(&GameEngine::new_Tentacle);
  this->_mob.push_back(&GameEngine::new_Ship);

  IRessources * res = _Loader.getPtr<IRessources>(LIB_RES, "get_ressources");

  this->_prj.emplace_back(res->get_sprite(LittleYellowBlaster), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(FatYellowBlaster), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(Caca), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(RedLaser), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(FatBlueBlaster), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(RedMissile), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(GreenMissile), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(Caterpillar), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(Orange), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(LittleBlueBlaster), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(Bubble), side::ENEMY);
  this->_prj.emplace_back(res->get_sprite(FireSprite), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FireBlue), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FirePink), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FireGreen), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FireRed), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FatFireBlue), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FatFirePink), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FatFireGreen), side::ALLY);
  this->_prj.emplace_back(res->get_sprite(FatFireRed), side::ALLY);

  my_ship = std::shared_ptr<ship>(new ship(0, 200, 200, 3));
}

GameEngine::~GameEngine()
{
}

void	GameEngine::update(sf::RenderWindow &window)
{
  int id = 0;

  /*for (auto it = _exp.begin(); it != _exp.end(); ++it)
  {
    (*it)->draw(window);
    if ((*it)->getDone() == true)
      it = _exp.erase(it);
  }*/

  for (auto it = _obj.begin(); id <= _idMax && it != _obj.end(); ++it, ++id)
  {
    (*it).second->lock();
    if ((*it).first != nullptr && (*it).first->getObjectType() != OT_MisAlly && (*it).first->getObjectType() != OT_MisFoe)
    {
      (*it).first->draw(window);
      if ((*it).first->getDelete() == true && id > 3)
	(*it).first = nullptr;
    }
    else if ((*it).first != nullptr && ((*it).first->getObjectType() == OT_MisAlly || (*it).first->getObjectType() == OT_MisFoe))
    {
      (*it).first->getObjectType() == OT_MisAlly ? (*it).first->move_forward() : (*it).first->move_backward();
      if ((*it).first->getObjectType() == OT_MisAlly)
      {
	if ((*it).first->getSender() == 0)
	{
	  if ((*it).first->getBoost() == false)
	   _prj[12].getTab().push_back(*it);
	  else if ((*it).first->getBoost() == true)
	    _prj[16].getTab().push_back(*it);
	}
	else if ((*it).first->getSender() == 1)
	{
	  if ((*it).first->getBoost() == false)
	    _prj[13].getTab().push_back(*it);
	  else if ((*it).first->getBoost() == true)
	    _prj[17].getTab().push_back(*it);
	}
	else if ((*it).first->getSender() == 2)
	{
	  if ((*it).first->getBoost() == false)
	    _prj[14].getTab().push_back(*it);
	  else if ((*it).first->getBoost() == true)
	    _prj[18].getTab().push_back(*it);
	}
	else if ((*it).first->getSender() == 3)
	{
	  if ((*it).first->getBoost() == false)
	    _prj[15].getTab().push_back(*it);
	  else if ((*it).first->getBoost() == true)
	    _prj[19].getTab().push_back(*it);
	}
      }
      else
	_prj[(*it).first->getMobType()].getTab().push_back(*it);
    }
    (*it).second->unLock();
  }

  for (auto it = _prj.begin(); it != _prj.end(); ++it)
    it->draw(window);

  _gameHud.draw(window);
}

void	GameEngine::setTab(const bool entry)
{
  _gameHud.setTabPressed(entry);
}

void	GameEngine::setMode(int mode)
{
  _mode = mode;
}

//
// Function command
//
void	GameEngine::executeCmd(const Srtp &cmd)
{
  // std::cout << "-------TREATING PACKET-------" << std::endl; 
  // std::cout << "Id dest : " << cmd._idDest << std::endl;
  // std::cout << "Cmd Proto : " << cmd._cmdProto << std::endl;
  // std::cout << "Cmd Client : " << cmd._cmdClient << std::endl;
  // std::cout << "Object Type : " << cmd._objType << std::endl;
  // std::cout << "Mob Type : " << cmd._mobType << std::endl;
  // std::cout << "Id Game : " << cmd._idGame << std::endl;
  // std::cout << "Id Object : " << cmd._idObject << std::endl;
  // std::cout << "Id Missile : " << cmd._idMissile << std::endl;
  // std::cout << "Pos X : " << cmd._posX << std::endl;
  // std::cout << "Pos Y : " << cmd._posY << std::endl;
  // std::cout << "Speed X : " << cmd._speedX << std::endl;
  // std::cout << "Speed Y : " << cmd._speedY << std::endl;
  // std::cout << "Hp : " << cmd._hp << std::endl;
  // std::cout << "Shield : " << cmd._shield << std::endl;
  // std::cout << "-------TREATING PACKET-------" << std::endl;
  /*if ((cmd._objType >= 0 && cmd._objType <= 2) &&
    (cmd._idObject < 0 || cmd._idObject > 999))
    return;
  else if (cmd._objType > 2 && (cmd._idMissile < 0 || cmd._idMissile > 999))
    return;*/
  cmdFunction fct = _fct[cmd._cmdClient];
  (this->*fct)(cmd);
  // std::cout << "-------DONE TREATING PACKET-------" << std::endl;
}

void	GameEngine::executeNew(const Srtp &cmd)
{
  //std::cout << "New " << cmd._idObject << " " << cmd._idMissile << std::endl;
  if (cmd._objType == OT_Mob || cmd._objType == OT_Boss || cmd._objType == OT_Player)
    {
      //std::cout << " Mob" << std::endl;
      if (_idMax < cmd._idObject)
	_idMax = cmd._idObject;
      _obj[cmd._idObject].second->lock();
      _obj[cmd._idObject].first = (this->*_mob[cmd._mobType])(cmd._idObject, cmd._posX, cmd._posY, cmd._hp, cmd._objType);
      _obj[cmd._idObject].second->unLock();
    }
  else if (cmd._objType == OT_MisAlly || cmd._objType == OT_MisFoe)
    {
      //std::cout << " Missile" << std::endl;
      if (_idMax < cmd._idMissile)
	_idMax = cmd._idMissile;
      _obj[cmd._idMissile].second->lock();
      _obj[cmd._idMissile].first = _Loader.getSmartPtr<IObject>(LIB_ATTACK, "get_attack",
							   cmd._posX, cmd._posY, cmd._idMissile,
							   cmd._objType, cmd._mobType, cmd._speedX, cmd._speedY, cmd._idObject);
      if (_obj[cmd._idObject].first != nullptr)
	_obj[cmd._idMissile].first->setBoost(_obj[cmd._idObject].first->getBoost());
      _obj[cmd._idMissile].second->unLock();
    }
  else if (cmd._objType == OT_Bonus)
    {
      if (_idMax < cmd._idObject)
	_idMax = cmd._idObject;
      _obj[cmd._idObject].second->lock();
      _obj[cmd._idObject].first = _Loader.getSmartPtr<IObject>(LIB_BONUS, "get_bonus", cmd._bonusType, cmd._idObject, cmd._posX, cmd._posY);
      _obj[cmd._idObject].second->unLock();
    }
}

void	GameEngine::executeDelete(const Srtp &cmd)
{
  //std::cout << "Delete ";
  if (cmd._objType == OT_Mob || cmd._objType == OT_Boss || cmd._objType == OT_Player)
  {
    //std::cout << "Mob " << std::endl;
    if (_idMax == cmd._idObject)
      --_idMax;
    _obj[cmd._idObject].second->lock();
    if (_obj[cmd._idObject].first == nullptr)
    {
      _obj[cmd._idObject].second->unLock();
      return;
    }
    if (cmd._idObject == my_ship->getId())
      _gameHud.setPlayerHp(cmd._hp);
    //_exp.push_back(std::shared_ptr<Explosion>(new Explosion(cmd._posX, cmd._posY, cmd._objType, cmd._mobType)));
    _obj[cmd._idObject].first->getDestroyed();
    _obj[cmd._idObject].second->unLock();
  }
  else if (cmd._objType == OT_MisAlly || cmd._objType == OT_MisFoe)
  {
    //std::cout << "Missile " << cmd._idMissile  << std::endl;
    if (_idMax == cmd._idMissile)
      --_idMax;
    _obj[cmd._idMissile].second->lock();
    if (_obj[cmd._idMissile].first == nullptr)
    {
      _obj[cmd._idMissile].second->unLock();
      return;
    }
    //_exp.push_back(std::shared_ptr<Explosion>(new Explosion(cmd._posX, cmd._posY, cmd._objType, cmd._mobType)));
    //delete _obj[cmd._idMissile].first;
    _obj[cmd._idMissile].first = nullptr;
    _obj[cmd._idMissile].second->unLock();
  }
  else if (cmd._objType == OT_Bonus)
  {
    if (_idMax == cmd._idObject)
      --_idMax;
    _obj[cmd._idObject].second->lock();
    if (_obj[cmd._idObject].first == nullptr)
    {
      _obj[cmd._idObject].second->unLock();
      return;
    }
    //delete _obj[cmd._idObject].first;
    _obj[cmd._idObject].first = nullptr;
    _obj[cmd._idObject].second->unLock();
  }
}

void	GameEngine::executeAttack(const Srtp &)
{
  //std::cout << "Attack" << std::endl;
}

void	GameEngine::executeUpdate(const Srtp &cmd)
{
  //std::cout << "Update" << std::endl;
  if (cmd._objType == OT_Mob || cmd._objType == OT_Boss || cmd._objType == OT_Player)
  {
    //std::cout << "Update Lock inc" << std::endl;
    _obj[cmd._idObject].second->lock();
    if (_obj[cmd._idObject].first == nullptr)
    {
      _obj[cmd._idObject].second->unLock();
      return;
    }
      if (_obj[cmd._idObject].first->getPosY() < cmd._posY)
	_obj[cmd._idObject].first->move_up();
      else if (_obj[cmd._idObject].first->getPosY() > cmd._posY)
	_obj[cmd._idObject].first->move_down();
      else
	_obj[cmd._idObject].first->resetAnim();
      cmd._shield == true ? _obj[cmd._idObject].first->takeDamage(1) : _obj[cmd._idObject].first->takeDamage(0);
      if (_obj[cmd._idObject].first->getHp() != cmd._hp)
        _obj[cmd._idObject].first->setHp(cmd._hp);
      if (_obj[cmd._idObject].first->getId() == my_ship->getId())
      {
	_gameHud.setPlayerHp(cmd._hp);
	if (cmd._hp <= 0)
  	_gameHud.setIsDead(true);
      }
      _obj[cmd._idObject].first->setPosX(cmd._posX);
      _obj[cmd._idObject].first->setPosY(cmd._posY);
      _obj[cmd._idObject].second->unLock();
  }
  else if (cmd._objType == OT_Bonus)
  {
    if (cmd._bonusType == BT_DamageBooster)
    {
      _obj[cmd._idObject].second->lock();
      if (_obj[cmd._idObject].first == nullptr)
      {
	_obj[cmd._idObject].second->unLock();
	return;
      }
      if (cmd._speedX > 1)
	_obj[cmd._idObject].first->setBoost(true);
      else if(cmd._speedX == 1)
	_obj[cmd._idObject].first->setBoost(false);
      _obj[cmd._idObject].second->unLock();
    }
  }
  //std::cout << "End Update" << std::endl;
}

void	GameEngine::executeWelcome(const Srtp &cmd)
{
  //std::cout << "Welcome" << std::endl;
  my_ship = std::shared_ptr<ship>(new ship(cmd._idObject, cmd._posX, cmd._posY, cmd._hp));
  _obj[cmd._idObject].first = my_ship;
  _gameHud.setPlayerHp(cmd._hp);
  my_ship->setYou(true);
  _idGame = cmd._idGame;
}

void GameEngine::executeStage(const Srtp &)
{
  //std::cout << "Stage" << std::endl;
  _gameHud.setNextStage(true);
}

void GameEngine::executeScore(const Srtp &cmd)
{
  //std::cout << "Score" << std::endl;
  if (cmd._cmdClient == CMDC_Score)
    _gameHud.setScore(cmd._posX, cmd._posY, cmd._speedX, cmd._speedY);
}


void GameEngine::executeNone(const Srtp &)
{
  //std::cout << "None" << std::endl;
}


ship &GameEngine::getShip() const
{
  return (*my_ship);
}

int GameEngine::getIdGame() const
{
  return (_idGame);
}

GameEngine::ptr GameEngine::new_LittleShip(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_LITTLESHIP, "get_LittleShip", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_BrownArmor(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_BROWNARMOR, "get_BrownArmor", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_Butterfly(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_BUTTERFLY, "get_Butterfly", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_GreenArmor(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_GREENARMOR, "get_GreenArmor", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_RedArmor(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_REDARMOR, "get_RedArmor", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_MecaTurret(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_MECATURRET, "get_MecaTurret", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_MecaCrab(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_MECACRAB, "get_MecaCrab", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_Centiped(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_CENTIPED, "get_Centiped", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_Crab(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_CRAB, "get_Crab", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_ShipMob(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_SHIPMOB, "get_ShipMob", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_Tentacle(const int idObject, const int posX, const int posY, const int hp, ObjectType objType){
  return _Loader.getSmartPtr<IObject>(LIB_TENTACLE, "get_Tentacle", idObject, posX, posY, hp, objType);
}

GameEngine::ptr GameEngine::new_Ship(const int idObject, const int posX, const int posY, const int hp, ObjectType){
  return std::shared_ptr<IObject>(new ship(idObject, posX, posY, hp));
}
