#include "ship.hpp"
#include "IRessources.hpp"

ship::ship(const int id, const int pos_x, const int pos_y, const int hp)
  : AObject(GameSprite::Ship1, id, pos_x, pos_y, hp, ObjectType::OT_Player, MobType::MT_LittleShip)
{
  you = false;
  _posX = pos_x;
  _posY = pos_y;
  _id = id;
  _hp = hp;
  _objectType = ObjectType::OT_Player;
  _mobType = MobType::MT_LittleShip;
  shipSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Ship1);
  SpriteMap[0] = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Ship1);
  SpriteMap[1] = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Ship2);
  SpriteMap[2] = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Ship3);
  SpriteMap[3] = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Ship4);

  if (id >= 0 && id <= 3)
    shipSprite = SpriteMap[id];
  FireRate = 300;
  _speed = 20;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Explode4);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::GameBlaster);
  _you = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::You);
  _you->setTextureRect(0, 0, 28, 45);
  _you->getSprite().setScale(sf::Vector2f(0.7f, 0.7f));
  this->setMode(2);
}

ship::~ship()
{ }

int	ship::getMode() const
{
  return (this->mode);
}

void ship::move_down()
{
  if (_Destroyed == true)
    return;
  if (this->mode == 2)
  {
    clock.restart();
    this->setMode(1);
  }
  else if (clock.getElapsedTime().asMilliseconds() >= 500)
    this->setMode(0);
  _posY += _speed;
}

void ship::move_up()
{
  if (_Destroyed == true)
    return;
  if (this->mode == 2)
  {
    clock.restart();
    this->setMode(3);
  }
  else if (clock.getElapsedTime().asMilliseconds() >= 500)
    this->setMode(4);
  _posY -= _speed;
}

void ship::move_forward()
{
  if (_Destroyed == true)
    return;
  _posX += _speed;  
}

void ship::move_backward()
{
  if (_Destroyed == true)
    return;
  _posX -= _speed;
}

void ship::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    DesSprite->getSprite().setScale(1.5, 1.5);
    setModeDes(0);
    _loader.getPtr<int>(LIBNAME, "play_sound", GameSound::ExplodeMecha3);
  }
}

void ship::resetAnim()
{
  this->setMode(2);
}

bool ship::launch_attack()
{
  if (_Destroyed == false && FireClock.getElapsedTime().asMilliseconds() >= FireRate)
  {
    explode->play();
    FireClock.restart();
    return (true);
  }
  return (false);
}

void ship::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

void ship::setModeDes(const int a)
{
  DesSprite->setTextureRect(DesSprite->getPosX() + a * (DesSprite->getWidth() + 1),
			    DesSprite->getPosY(),
			    DesSprite->getWidth(),
			    DesSprite->getHeight());
}

void ship::draw(sf::RenderWindow &window)
{
  static int time = 200;
  static int a = 0;

  a++;
  if (a == 30)
    a = 0;
  if (new_mob == 7)
  {
    _toDelete = true;
    return;
  }
  if (_Destroyed == false)
  {
    if (you == true)
    {
      _you->setPosition(_posX + 6, _posY - 40);
      if ((a >= 0 && a <= 10) || (a >= 20 && a <= 30))
        window.draw(_you->getSprite());
    }
    this->setMode(mode);
    shipSprite->setPosition(_posX, _posY);
    if (safe_time % 3 < 2)
      window.draw(shipSprite->getSprite());
    if (safe_time != 0)
      ++safe_time;
    if (safe_time == 70)
      safe_time = 0;
  }
  if (_Destroyed == true)
  {
    DesSprite->setPosition(_posX, _posY);
    if (DesClock.getElapsedTime().asMilliseconds() > time)
    {
      time += 200;
      ++new_mob;
      setModeDes(new_mob);
    }
   window.draw(DesSprite->getSprite());
  }
}
