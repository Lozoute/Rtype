#include "BrownArmor.hpp"

BrownArmor::BrownArmor(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::BrownArmor, id, pos_x, pos_y, hp, object, MobType::MT_BrownArmor)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", BlueExplode);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeAlien2);
  setMode(1);
}

BrownArmor::~BrownArmor()
{
}

void BrownArmor::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	BrownArmor::getMode() const
{
  return (this->mode);
}

void BrownArmor::move_down()
{
  if (_Destroyed == true)
    return;
}

void BrownArmor::move_up()
{
  if (_Destroyed == true)
    return;
  this->setMode(2);
}

void BrownArmor::move_forward()
{
  if (_Destroyed == true)
    return;
}

void BrownArmor::move_backward()
{
  if (_Destroyed == true)
    return;
}


void BrownArmor::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    DesSprite->setScale(1.5, 1.5);
    explode->play();
  }
}

void BrownArmor::setModeDes(int a)
{
  DesSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
					shipSprite->getPosY(),
					shipSprite->getWidth(),
					shipSprite->getHeight());
}

void BrownArmor::resetAnim()
{
  this->setMode(1);
}

void BrownArmor::draw(sf::RenderWindow &window)
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
  EXPORT IObject *get_BrownArmor(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class BrownArmor(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_BrownArmor;
  }
}
