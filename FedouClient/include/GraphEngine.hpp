#ifndef GRAPHENGINE_HPP
#define GRAPHENGINE_HPP

#include <chrono>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Loader.hpp"
#include "API_Mutex.hpp"
#include "API_Error.hpp"
#include "Srtp.hpp"
#include "Background.hpp"
#include "RessourcesV2.hpp"
#include "Explosion.hpp"

const auto      __ShipSpeed = 18;
const auto      __FPS = std::chrono::microseconds(33333);
const auto      __LibMutex = "../API/SOs/lib_API_Mutex_STD.so";
const auto      __LoadSym = "__API_Load__";

using namespace API_Mutex;

template <typename T>
using Ptr = std::shared_ptr<T>;

class Object;

class GraphEngine
{
  int _maxId;
  std::vector<Ptr<Object> > _objects;
  std::vector<Ptr<Object> > _buffer;
  std::vector<Ptr<Explosion> > _explosions;
  int			_bufferCounter;
  sf::RenderWindow *    _window;
  int			_idGame;
  int			_idShip;
  Loader		_loader;
  Ptr<IMutex>		_mtx;
  Ptr<IMutex>		_mtxShip;
  Ptr<IMutex>		_mtxExpl;
  Background            _bg;
  Srtp			_shipSrtp;
  RessourcesV2          _res;
  int			_fireRate;
  int			_actualFire;
public:
  GraphEngine(sf::RenderWindow *wind);
  ~GraphEngine();

  void	updateAndDraw();
  void	vectorUpSize(int amount, std::vector<Ptr<Object> > &vect);
  bool  run();
  void  sendShipDatas();
  bool  handleKeys();
  void	press(sf::Keyboard::Key &);
  void	release(sf::Keyboard::Key & );
  void  regulateSpeed();
  void	addBuffer();
  void	playBlaster(ObjectType);
  void	addToBuffer(Object &obj);
  void  receivePacket(const Srtp &P);
  void  manageBonus(const Srtp &P, Object &o);
  void  drawExplosions();
  void  addExplosion(ObjectType, MobType, int, int);
  void	drawHearts();
  bool  checkAlive(int, CmdClient);
};

#endif
