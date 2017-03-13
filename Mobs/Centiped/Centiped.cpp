#include "Centiped.hpp"

Centiped::Centiped(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::Centiped, id, pos_x, pos_y, hp, object, MobType::MT_Centiped)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", BlueExplode);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeAlien1);
  setMode(2);
}

Centiped::~Centiped()
{
}

void Centiped::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	Centiped::getMode() const
{
  return (this->mode);
}

void Centiped::move_down()
{
  if (_Destroyed == true)
    return;
  if (this->mode == 2)
  {
    clock.restart();
    this->setMode(3);
  }
  else if (clock.getElapsedTime().asMilliseconds() >= 400)
    this->setMode(4);
}

void Centiped::move_up()
{
  if (_Destroyed == true)
    return;
  if (this->mode == 2)
  {
    clock.restart();
    this->setMode(1);
  }
  else if (clock.getElapsedTime().asMilliseconds() >= 400)
    this->setMode(0);
}

void Centiped::move_forward()
{
  if (_Destroyed == true)
    return;
}

void Centiped::move_backward()
{
  if (_Destroyed == true)
    return;
}

void Centiped::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void Centiped::setModeDes(const int a)
{
  DesSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

void Centiped::resetAnim()
{
  this->setMode(2);
}

void Centiped::draw(sf::RenderWindow &window)
{
  static int time = 200;

  if (new_mob == 7)
  {
    _toDelete = true;
    return;
  }
  if (_Destroyed == false)
  {
    this->setMode(mode);
    shipSprite->setPosition(_posX, _posY);
    if (safe_time % 6 < 2)
      window.draw(shipSprite->getSprite());
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

extern "C" {
  EXPORT IObject *get_Centiped(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class Centiped(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_Centiped;
  }
}
