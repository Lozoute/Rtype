#include "Object.hpp"
#include "RessourcesV2.hpp"
#include "Sprite.hpp"
#include "Srtp.hpp"

Object::Object ()
  : _id(-1), _posX(0), _posY(0), _width(0), _height(0), _speedX(0),
    _speedY(0), _hp(0), _alive(0), _objectType(OT_Boss), _mobType(MT_None), 
    _posMisX(-1), _posMisY(-1), _bonusType(BT_None), _dmgs(1), _shield(false), _shieldCount(0)
{
  _ownerId = 0;
}


Object::Object (int id, int posx, int posy, int width, int height, int speedx, int speedy,
		int hp, bool alive, ObjectType ot, MobType mt, BonusType bt, bool shield)
  : _id(id), _posX(posx), _posY(posy), _width(width), _height(height), _speedX(speedx),
    _speedY(speedy), _hp(hp), _alive(alive), _objectType(ot), _mobType(mt),
    _posMisX(-1), _posMisY(-1), _bonusType(bt), _dmgs(1), _shield(shield), _shieldCount(0)
{
  _ownerId = 0;
}

Object::Object(const Object &o)
  : _id(o._id), _posX(o._posX), _posY(o._posY), _width(o._width), _height(o._height),
    _speedX(o._speedX), _speedY(o._speedY), _hp(o._hp), _alive(o._alive),
    _objectType(o._objectType), _mobType(o._mobType),
    _posMisX(-1), _posMisY(-1), _ownerId(o._ownerId), _bonusType(o._bonusType), _dmgs(o._dmgs)
  , _shield(o._shield), _shieldCount(o._shieldCount)
{
}

Object	 &Object::operator=(const Object &O)
{
  if (this != &O)
    {
      _id = O._id;
      _posX = O._posX;
      _posY = O._posY;
      _width = O._width;
      _height = O._height;
      _speedX = O._speedX;
      _speedY = O._speedY;
      _hp = O._hp;
      _alive = O._alive;
      _objectType = O._objectType;
      _mobType = O._mobType;
      _posMisX = -1;
      _posMisY = -1;
      _ownerId = O._ownerId;
      _bonusType = O._bonusType;
      _dmgs = O._dmgs;
      _shield = O._shield;
      _shieldCount = O._shieldCount;
    }
  return (*this);
}

Object::~Object()
{
}

void			Object::toggleShield(bool lele)
{
  _shield = lele;
}

void			Object::kill()
{
  _alive = false;
}

void			Object::setId(int i)
{
  _id = i;
}

void			Object::setPosX(int i)
{
  _posX = i;
}

void			Object::setPosY(int i)
{
  _posY = i;
}

void			Object::setSpeedX(int i)
{
  _speedX = i;
}

void			Object::setSpeedY(int i)
{
  _speedY = i;
}

void			Object::setHp(int i)
{
  _hp = i;
}

void			Object::setOwnerId(int id)
{
  _ownerId = id;
}

void			Object::setBonusType(BonusType bt)
{
  _bonusType = bt;
}

void			Object::setDmgs(int dmgs)
{
  _dmgs = dmgs;
}

void			Object::update()
{
  if ((_objectType == OT_MisFoe || _objectType == OT_MisAlly)
      && _posMisX == -1 && _posMisY == -1)
    {
      _posMisX = _posX * 1000;
      _posMisY = _posY * 1000;
    }
  if (_posMisX != -1 && _posMisY != -1)
    {
      _posMisX += _speedX;
      _posMisY += _speedY;
      _posX = _posMisX / 1000;
      _posY = _posMisY / 1000;
    }
  else
    {
      _posX += _speedX;
      _posY += _speedY;
    }
  _shieldCount = (_shieldCount + 1) % 2;
}

void			Object::draw(RessourcesV2 &res)
{
  if (!_shield)
    res.draw(_objectType, _mobType, _bonusType, _id, _posX, _posY, _speedY, _dmgs);
  else if (_shieldCount % 2 == 1 && _shield)
    res.draw(_objectType, _mobType, _bonusType, _id, _posX, _posY, _speedY, _dmgs);
}


