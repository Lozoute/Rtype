#include "attack.hpp"

attack::attack(const int pos_x, const int pos_y, const int id)
  : AObject(id, pos_x, pos_y, 1, OT_MisAlly, MT_None)
{
  _baseX = _posX * 1000;
  _baseY = _posY * 1000;
}

attack::attack(const attack &ot)
  : AObject(ot.getId(), ot.getPosX(), ot.getPosY(), ot.getHp(), ot.getObjectType(), ot.getMobType())
{
  _baseX = _posX * 1000;
  _baseY = _posY * 1000;
  _speedX = ot._speedX;
  _speedY = ot._speedY;
}

attack::attack(const int pos_x, const int pos_y, const int id, const ObjectType obj, const MobType mb, int speedX, int speedY, int sender)
  : AObject(id, pos_x, pos_y, 1, obj, mb)
{
  _baseX = _posX * 1000;
  _baseY = _posY * 1000;
  _speedX = speedX;
  _speedY = speedY;
  _sender = sender;
  this->setSender(_sender);
}

attack::~attack()
{
}

void attack::move_forward()
{
  _baseX += _speedX;
  this->_posX = _baseX / 1000;

  _baseY += _speedY;
  this->_posY = _baseY / 1000;
}

void attack::move_backward()
{
  _baseX += _speedX;
  this->_posX = _baseX / 1000;

  _baseY += _speedY;
  this->_posY = _baseY / 1000;
}

void attack::hit()
{
  _posX = -10;
}

extern "C" EXPORT IObject *get_attack(const int pos_x, const int pos_y, const int id, const ObjectType obj, const MobType mb, int speedX, int speedY, int sender){
    return (new class attack(pos_x, pos_y, id, obj, mb, speedX, speedY, sender));
}
