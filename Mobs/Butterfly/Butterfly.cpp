#include "Butterfly.hpp"

Butterfly::Butterfly(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType object)
  : AObject(GameSprite::Butterfly, id, pos_x, pos_y, hp, object, MobType::MT_Butterfly)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", Explode3);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeMecha3);
  setMode(1);
}

Butterfly::~Butterfly()
{
}

void Butterfly::setMode(int a)
{
  this->mode = a;
  shipSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

int	Butterfly::getMode() const
{
  return (this->mode);
}

void Butterfly::move_down()
{
  if (_Destroyed == true)
    return;
  this->setMode(0);
}

void Butterfly::move_up()
{
  if (_Destroyed == true)
    return;
  this->setMode(2);
}

void Butterfly::move_forward()
{
  if (_Destroyed == true)
    return;
}

void Butterfly::move_backward()
{
  if (_Destroyed == true)
    return;
}

void Butterfly::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
    explode->play();
  }
}

void Butterfly::setModeDes(const int a)
{
  DesSprite->setTextureRect(shipSprite->getPosX() + a * (shipSprite->getWidth() + 1),
			     shipSprite->getPosY(),
			     shipSprite->getWidth(),
			     shipSprite->getHeight());
}

void Butterfly::resetAnim()
{
  this->setMode(1);
}

void Butterfly::draw(sf::RenderWindow &window)
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
  EXPORT IObject *get_Butterfly(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class Butterfly(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_Butterfly;
  }
}
