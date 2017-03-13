#include "LittleShip.hpp"

LittleShip::LittleShip(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::LittleShip, id, pos_x, pos_y, hp, object, MobType::MT_LittleShip)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", Explode1);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeMecha2);
  setMode(2);
}

LittleShip::~LittleShip()
{
}

void LittleShip::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}


int	LittleShip::getMode() const
{
  return (this->mode);
}

void LittleShip::move_down()
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
  _posY += _speed;
}

void LittleShip::move_up()
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
  _posY -= _speed;
}

void LittleShip::move_forward()
{
  if (_Destroyed == true)
    return;
  _posX += _speed;
}

void LittleShip::move_backward()
{
  if (_Destroyed == true)
    return;
  _posX -= _speed;
}

void LittleShip::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void LittleShip::setModeDes(const int a)
{
  DesSprite->setTextureRect(DesSprite->getPosX() + a * (DesSprite->getWidth() + 1),
			    DesSprite->getPosY(),
			    DesSprite->getWidth(),
			    DesSprite->getHeight());
}

void LittleShip::resetAnim()
{
  this->setMode(2);
}

void LittleShip::draw(sf::RenderWindow &window)
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
    //window.draw(DesSprite->getSprite());
  }
}

extern "C" {
  EXPORT IObject *get_LittleShip(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class LittleShip(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_LittleShip;
  }
}
