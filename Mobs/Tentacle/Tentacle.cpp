#include "Tentacle.hpp"

Tentacle::Tentacle(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type)
  : AObject(GameSprite::Tentacle, id, pos_x, pos_y, hp, type, MobType::MT_Tentacle)
{
  this->FireRate = 100;
  DesSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", FatExplode);
  explode = _loader.getPtr<ISound>(LIBNAME, "get_sound", ExplodeAlien1);
  setMode(0);
}

Tentacle::~Tentacle()
{
}

void Tentacle::setMode(int a)
{
  this->mode = a;
  if (a >= 35)
    a = 69 - a;
  shipSprite->getSprite().setTextureRect(sf::IntRect(shipSprite->getPosX() + (a / 5) * (shipSprite->getWidth()), shipSprite->getPosY() + (a % 5) * (shipSprite->getHeight() + 1), shipSprite->getWidth(), shipSprite->getHeight()));
}

int	Tentacle::getMode() const
{
  return (this->mode);
}

void Tentacle::move_down()
{
  if (_Destroyed == true)
    return;
  _posY += _speed;
}

void Tentacle::move_up()
{
  if (_Destroyed == true)
    return;
  _posY -= _speed;
}
void Tentacle::move_forward()
{
}

void Tentacle::move_backward()
{
}

void Tentacle::getDestroyed()
{
  if (_Destroyed == false)
  {
    DesSprite->setScale(4, 4);
    DesSprite->setPosition(_posX, _posY);
    DesClock.restart();
    _Destroyed = true;
    setModeDes(0);
  }
}

void Tentacle::setModeDes(const int a)
{
  DesSprite->setTextureRect(DesSprite->getPosX() + a * (DesSprite->getWidth() + 1),
			    DesSprite->getPosY(),
			    DesSprite->getWidth(),
			    DesSprite->getHeight());
}

void Tentacle::resetAnim()
{
}

void Tentacle::draw(sf::RenderWindow &window)
{
  static int time = 200;
  static int time_move = 100;

  if (new_mob == 7)
  {
    _toDelete = true;
    return;
  }
  if (_Destroyed == false)
  {
    if (MoveClock.getElapsedTime().asMilliseconds() > time_move)
    {
      time_move += 100;
      mode++;
      if (mode >= 68)
      {
	mode = 0;
	time_move = 100;
	MoveClock.restart().asMilliseconds();
      }
      setMode(mode);
    }
    shipSprite->setPosition(_posX, _posY);
    if (safe_time % 3 < 2)
      window.draw(shipSprite->getSprite());
  }
  if (_Destroyed == true)
  {
    DesSprite->setPosition(_posX, _posY);
    if (DesClock.getElapsedTime().asMilliseconds() > time)
    {
      if (new_mob % 3 == 0)
	explode->play();
      time += 200;
      ++new_mob;
      setModeDes(new_mob);
    }
    window.draw(DesSprite->getSprite());
  }
}

extern "C" {
  EXPORT IObject *get_Tentacle(const int id, const int pos_x, const int pos_y, const int hp, const ObjectType type){
    return (new class Tentacle(id, pos_x, pos_y, hp, type));
  }
  EXPORT IObject::cmdd get_ctor(){
    return &get_Tentacle;
  }
}
