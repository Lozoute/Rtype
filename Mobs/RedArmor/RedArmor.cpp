#include "RedArmor.hpp"

RedArmor::RedArmor(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type)
  : AObject(GameSprite::RedArmor, id, pos_x, pos_y, hp, type, MobType::MT_RedArmor)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", FatExplode);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeMecha4);
  setMode(0);
}

RedArmor::~RedArmor()
{
}

void RedArmor::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	RedArmor::getMode() const
{
  return (this->mode);
}

void RedArmor::move_down()
{
  if (_Destroyed == true)
    return;
  this->setMode(2);
  _posY += _speed;
}

void RedArmor::move_up()
{
  if (_Destroyed == true)
    return;
  this->setMode(1);
  _posY -= _speed;
}

void RedArmor::move_forward()
{
  if (_Destroyed == true)
    return;
  _posX += _speed;
}

void RedArmor::move_backward()
{
  if (_Destroyed == true)
    return;
  if (_posX - _speed > 0)
    _posX -= _speed;
  shipSprite->setPosition(_posX, _posY);
}


void RedArmor::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesSprite->setScale(2, 2);
    DesSprite->setPosition(_posX, _posY);
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void RedArmor::setModeDes(const int a)
{
  DesSprite->setTextureRect(DesSprite->getPosX() + a * (DesSprite->getWidth() + 1),
			    DesSprite->getPosY(),
			    DesSprite->getWidth(),
			    DesSprite->getHeight());
}

void RedArmor::resetAnim()
{
  this->setMode(0);
}

void RedArmor::draw(sf::RenderWindow &window)
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
  EXPORT IObject *get_RedArmor(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class RedArmor(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_RedArmor;
  }
}
