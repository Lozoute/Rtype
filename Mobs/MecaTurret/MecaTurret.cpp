#include "MecaTurret.hpp"

MecaTurret::MecaTurret(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::MecaTurret, id, pos_x, pos_y, hp, object, MobType::MT_MecaTurret)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", Explode3);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeMecha3);
  setMode(1);
}

MecaTurret::~MecaTurret()
{
}

void MecaTurret::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	MecaTurret::getMode() const
{
  return (this->mode);
}

void MecaTurret::move_down()
{
  if (_Destroyed == true)
    return;
  this->setMode(0);
}

void MecaTurret::move_up()
{
  if (_Destroyed == true)
    return;
  this->setMode(2);
}

void MecaTurret::move_forward()
{
  if (_Destroyed == true)
    return;
}

void MecaTurret::move_backward()
{
  if (_Destroyed == true)
    return;
}

void MecaTurret::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void MecaTurret::setModeDes(const int a)
{
  DesSprite->setTextureRect(DesSprite->getPosX() + a * (DesSprite->getWidth() + 1),
			    DesSprite->getPosY(),
			    DesSprite->getWidth(),
			    DesSprite->getHeight());
}

void MecaTurret::resetAnim()
{
  this->setMode(1);
}

void MecaTurret::draw(sf::RenderWindow &window)
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
  EXPORT IObject *get_MecaTurret(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class MecaTurret(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_MecaTurret;
  }
}
