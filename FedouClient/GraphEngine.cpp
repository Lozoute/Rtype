#include <SFML/Graphics.hpp>
#include <chrono>
#include "GraphEngine.hpp"
#include "Object.hpp"
#include "NetworkThread.hpp"
#include "Explosion.hpp"

GraphEngine::GraphEngine(sf::RenderWindow *wind)
  : _maxId(-1), _bufferCounter(0),
    _window(wind), _idGame(-1), _idShip(-1)
{
  vectorUpSize(2000, _objects);
  vectorUpSize(2000, _buffer);
  _mtx = _loader.getSmartPtr<IMutex>(__LibMutex, __LoadSym);
  _mtxShip = _loader.getSmartPtr<IMutex>(__LibMutex, __LoadSym);
  _mtxExpl = _loader.getSmartPtr<IMutex>(__LibMutex, __LoadSym);
  _shipSrtp._cmdClient = CMDC_Update;
  _shipSrtp._idMissile = -1;
  _shipSrtp._hp = -1;
  _shipSrtp._shield = -1;
  _shipSrtp._speedX = 0;
  _shipSrtp._speedY = 0;
  _res.playSound(0);
  _fireRate = 10;
  _actualFire = 0;
}

GraphEngine::~GraphEngine()
{
}

void	GraphEngine::updateAndDraw()
{
  int i = 0;

  _bg.draw(_window);
  while (i < _maxId)
    {
      if ((_objects[i].get())->isAlive())
	{
	  (_objects[i].get())->update();
	  (_objects[i].get())->draw(_res);
	}
      i++;
    }
}

void	GraphEngine::vectorUpSize(int amount, std::vector<Ptr<Object> > &vect)
{
  int i = 0;
  Object *newObject;
  
  while (i < amount)
    {
      newObject = new Object();
      vect.push_back(Ptr<Object>(newObject));
      i++;
    }
}

bool    GraphEngine::run()
{
  auto Start = std::chrono::high_resolution_clock::now();
  if (_window->isOpen())
    {
      if (!handleKeys())
	return (false);
      _window->clear(sf::Color::Black);
      updateAndDraw();
      addBuffer();
      _res.draw(*_window, _objects.size(), _explosions.size());
      drawExplosions();
      drawHearts();
      sendShipDatas();
      _window->display();
      auto End = std::chrono::high_resolution_clock::now();
      if (End - Start < __FPS)
	std::this_thread::sleep_for(__FPS - (End - Start));
      return (true);
    }
  else
    return (false);
}

void	GraphEngine::sendShipDatas()
{
  Object *sheep;

  _mtxShip->lock();
  if (_idGame != -1 && _idShip != -1)
    {
      sheep = (_objects[_idShip].get());
      if (!(sheep->isAlive()))
	_res.drawDead(*_window);
      if (sheep->getObjectType() == OT_Player)
	{
	  _shipSrtp._objType = OT_Player;
	  _shipSrtp._mobType = MT_None;
	  _shipSrtp._idGame = _idGame;
	  _shipSrtp._idObject = _idShip;
	  _shipSrtp._posX = _shipSrtp._speedX + sheep->getPosX();
	  sheep->setPosX(_shipSrtp._posX);
	  _shipSrtp._posY = _shipSrtp._speedY + sheep->getPosY();
	  sheep->setPosY(_shipSrtp._posY);
	}
      if (_shipSrtp._cmdClient == CMDC_Attack)
	{
	  _actualFire ++;
	  if (_actualFire >= _fireRate)
	    {
	      _actualFire = 0;
	      SendPacket(_shipSrtp);
	    }
	  _shipSrtp._cmdClient = CMDC_Update;
	  SendPacket(_shipSrtp);
	  _shipSrtp._cmdClient = CMDC_Attack;
	}
      else
	SendPacket(_shipSrtp);
    }
  _mtxShip->unLock();
}

bool    GraphEngine::handleKeys()
{
  sf::Event e;
  
  while (_window->pollEvent(e))
    {
      if (e.type == sf::Event::Closed || 
	  (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape))
	{
	  _window->close();
	  return (false);
	}
      else if (e.type == sf::Event::KeyPressed)
	press(e.key.code);
      else if (e.type == sf::Event::KeyReleased)
	release(e.key.code);
    }
  return (true);
}

void	GraphEngine::press(sf::Keyboard::Key &k)
{
  if (k == sf::Keyboard::Left)
    _shipSrtp._speedX -= __ShipSpeed;
  else if (k == sf::Keyboard::Right)
    _shipSrtp._speedX += __ShipSpeed;
  else if (k == sf::Keyboard::Up)
    _shipSrtp._speedY -= __ShipSpeed;
  else if (k == sf::Keyboard::Down)
    _shipSrtp._speedY += __ShipSpeed;
  else if (k == sf::Keyboard::Space)
    _shipSrtp._cmdClient = CMDC_Attack;
  regulateSpeed();
}

void	GraphEngine::release(sf::Keyboard::Key &k)
{
  if (k == sf::Keyboard::Left)
    _shipSrtp._speedX += __ShipSpeed;
  else if (k == sf::Keyboard::Right)
    _shipSrtp._speedX -= __ShipSpeed;
  else if (k == sf::Keyboard::Up)
    _shipSrtp._speedY += __ShipSpeed;
  else if (k == sf::Keyboard::Down)
    _shipSrtp._speedY -= __ShipSpeed;
  else if (k == sf::Keyboard::Space)
    _shipSrtp._cmdClient = CMDC_Update;
  regulateSpeed();
}

void	GraphEngine::regulateSpeed()
{
  if (_shipSrtp._speedY < -__ShipSpeed)
    _shipSrtp._speedY = -__ShipSpeed;
  else if (_shipSrtp._speedY > __ShipSpeed)
    _shipSrtp._speedY = __ShipSpeed;
  if (_shipSrtp._speedX < -__ShipSpeed)
    _shipSrtp._speedX = -__ShipSpeed;
  else if (_shipSrtp._speedX > __ShipSpeed)
    _shipSrtp._speedX = __ShipSpeed;
}


void	GraphEngine::addBuffer()
{
  int i = 0;
  int id;

  _mtx->lock();
  while (i < _bufferCounter)
    {
      id = (_buffer[i].get())->getId();
      while (id >= static_cast<int>(_objects.size()))
	vectorUpSize(2000, _objects);
      *(_objects[id]) = *((_buffer[i].get()));
      if ((_buffer[i].get())->getId() == _maxId && (_buffer[i].get())->isAlive() == false)
	_maxId--;
      else if ((_buffer[i].get())->getId() > _maxId)
	_maxId = (_buffer[i].get())->getId();
      i++;
    }
  _bufferCounter = 0;
  _mtx->unLock();
}

void	GraphEngine::addToBuffer(Object &obj)
{
  _mtx->lock();
  while (_bufferCounter >= static_cast<int>(_buffer.size()))
    vectorUpSize(2000, _buffer);
  *(_buffer[_bufferCounter].get()) = obj;
  _bufferCounter++;
  _mtx->unLock();
}


void	GraphEngine::receivePacket(const Srtp &p)
{
  Object o(p._idObject, p._posX, p._posY, 0, 0, p._speedX,
	   p._speedY, p._hp, true, p._objType, p._mobType, p._bonusType);

  o.toggleShield(p._shield);
  if (p._cmdClient == CMDC_Welcome && _idGame == -1)
    {
      _mtxShip->lock();
      _idGame = p._idGame;
      _idShip = p._idObject;
      _mtxShip->unLock();
    }
  if (p._cmdClient == CMDC_Delete || p._hp <= 0)
    {
      o.kill();
      if (p._objType != OT_Bonus)
	addExplosion(p._objType, p._mobType, p._posX, p._posY);
    }
  if (p._objType == OT_MisAlly || p._objType == OT_MisFoe)
    {
      if (p._cmdClient == CMDC_New)
	playBlaster(p._objType);
      o.setId(p._idMissile);
      o.setOwnerId(p._idObject);
    }
  if (p._objType == OT_Bonus)
    manageBonus(p, o);
  if (p._cmdClient != CMDC_Stage && !(p._cmdClient == CMDC_Update && p._objType == OT_Bonus))
    addToBuffer(o);
}

bool  GraphEngine::checkAlive(int idobj, CmdClient cmd)
{
  _mtxShip->lock();
  if (_idShip != -1 && idobj == _idShip && cmd == CMDC_Delete)
      return (false);
  _mtxShip->unLock();
  return (true);
 
}

void  GraphEngine::manageBonus(const Srtp &p, Object &o)
{
  if (p._cmdClient == CMDC_Update)
    {
      if (p._bonusType == BT_FireRateBooster)
	{
	  _mtxShip->lock();
	    if (p._idObject == _idShip)
	      _fireRate = p._speedX;
	  _mtxShip->unLock();
	}
      else if (p._bonusType == BT_DamageBooster)
	{
	  o.setDmgs(p._speedX);
	}
    }
  o.setSpeedX(0);
  o.setSpeedY(0);
}

void  GraphEngine::playBlaster(ObjectType ot)
{
  if (ot == OT_MisAlly)
    _res.playSound(1);
  else
    _res.playSound(2);
    
}

void  GraphEngine::drawExplosions()
{
  std::vector<Ptr<Explosion> >::iterator it;

  _mtxExpl->lock();
  for (it = _explosions.begin(); it != _explosions.end();)
    {
      _res.drawFx(((*it).get())->getPosX(), ((*it).get())->getPosY(), 0, ((*it).get())->getFrame()); 
      ((*it).get())->explode();
      if (((*it).get())->getFrame() == -1)
	it = _explosions.erase(it);
      
      else
	it++;
    }
  _mtxExpl->unLock();
}

void  GraphEngine::addExplosion(ObjectType ot, MobType mt, int x, int y)
{
  int size;

  if (ot == OT_MisAlly || ot == OT_MisFoe)
    size = 1;
  else if (mt == MT_Tentacle)
    size = 6;
  else
    size = 3;

  _mtxExpl->lock();
  _explosions.push_back(Ptr<Explosion> (new Explosion(x, y, size)));
  _mtxExpl->unLock();
}

void  GraphEngine::drawHearts()
{
  int hp = 0;
  int i = 0;
  _mtxShip->lock();
  if (_idShip != -1)
    hp = (_objects[_idShip].get())->getHp();
  _mtxShip->unLock();
  while(i < hp)
    {
      _res.draw(OT_Bonus, MT_None, BT_HealthPack, 0, 20 + i * 23, 120, 0, 0);
      i++;
    }
}
