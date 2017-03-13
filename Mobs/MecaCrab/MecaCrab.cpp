#include "MecaCrab.hpp"

MecaCrab::MecaCrab(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::MecaCrab, id, pos_x, pos_y, hp, object, MobType::MT_MecaCrab)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", Explode4);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeMecha4);
  setMode(2);
}

MecaCrab::~MecaCrab()
{
}

void MecaCrab::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	MecaCrab::getMode() const
{
  return (this->mode);
}

void MecaCrab::move_down()
{
  if (_Destroyed == true)
    return;
    this->setMode(3);
}

void MecaCrab::move_up()
{
  if (_Destroyed == true)
    return;
    this->setMode(1);
}

void MecaCrab::move_forward()
{
  if (_Destroyed == true)
    return;
}

void MecaCrab::move_backward()
{
  if (_Destroyed == true)
    return;
}

void MecaCrab::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void MecaCrab::setModeDes(const int a)
{
  DesSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

void MecaCrab::resetAnim()
{
  this->setMode(2);
}

void MecaCrab::draw(sf::RenderWindow &window)
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
    if (safe_time % 3 < 2)
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
  EXPORT IObject *get_MecaCrab(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class MecaCrab(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_MecaCrab;
  }
}
