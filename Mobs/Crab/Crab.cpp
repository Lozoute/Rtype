#include "Crab.hpp"

Crab::Crab(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::Crab, id, pos_x, pos_y, hp, object, MobType::MT_Crab)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", BlueExplode);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeAlien2);
  setMode(12);
}

Crab::~Crab()
{
}

void Crab::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	Crab::getMode() const
{
  return (this->mode);
}

void Crab::move_down()
{
  if (_Destroyed == true)
    return;
  if (this->mode == 12)
  {
    clock.restart();
    this->setMode(11);
  }
  else if (clock.getElapsedTime().asMilliseconds() >= 400)
    this->setMode(10);
}

void Crab::move_up()
{
  if (_Destroyed == true)
    return;
  if (this->mode == 12)
  {
    clock.restart();
    this->setMode(13);
  }
  else if (clock.getElapsedTime().asMilliseconds() >= 400)
    this->setMode(14);
}

void Crab::move_forward()
{
  if (_Destroyed == true)
    return;
}

void Crab::move_backward()
{
  if (_Destroyed == true)
    return;
}

void Crab::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    DesSprite->getSprite().setScale(1.5, 1.5);
    explode->play();
  }
}

void Crab::setModeDes(const int a)
{
  DesSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

void Crab::resetAnim()
{
  this->setMode(12);
}

void Crab::draw(sf::RenderWindow &window)
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
  EXPORT IObject *get_Crab(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class Crab(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_Crab;
  }
}
