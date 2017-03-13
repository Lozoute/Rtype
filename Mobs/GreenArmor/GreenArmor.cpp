#include "GreenArmor.hpp"

GreenArmor::GreenArmor(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::GreenArmor, id, pos_x, pos_y, hp, object, MobType::MT_GreenArmor)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", Explode4);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeMecha4);
  setMode(1);
}

GreenArmor::~GreenArmor()
{
}

void GreenArmor::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	GreenArmor::getMode() const
{
  return (this->mode);
}

void GreenArmor::move_down()
{
  if (_Destroyed == true)
    return;
  this->setMode(0);
  _posY += _speed;
}

void GreenArmor::move_up()
{
  if (_Destroyed == true)
    return;
  this->setMode(2);
  _posY -= _speed;
}

void GreenArmor::move_forward()
{
  if (_Destroyed == true)
    return;
  _posX += _speed;
}

void GreenArmor::move_backward()
{
  if (_Destroyed == true)
    return;
  _posX -= _speed;
}

void GreenArmor::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void GreenArmor::setModeDes(const int a)
{
  DesSprite->setTextureRect(DesSprite->getPosX() + a * (DesSprite->getWidth() + 1),
			    DesSprite->getPosY(),
			    DesSprite->getWidth(),
			    DesSprite->getHeight());
 }

void GreenArmor::resetAnim()
{
  this->setMode(1);
}

void GreenArmor::draw(sf::RenderWindow &window)
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
  EXPORT IObject *get_GreenArmor(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class GreenArmor(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_GreenArmor;
  }
}

