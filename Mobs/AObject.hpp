#ifndef AOBJECT_HPP_
# define AOBJECT_HPP_

# include "IObject.hpp"
# include "ISprite.hpp"
# include "IRessources.hpp"
# include "Loader.hpp"

class attack;
class ISprite;

class AObject : public IObject
{
protected:
  Loader			_loader;
  ISprite			*shipSprite;
  int				_id;
  int				_posX;
  int				_posY;
  int				_hp;
  ObjectType			_objectType;
  MobType			_mobType;
  int				_speed;
  bool				_Destroyed;
  bool				_toDelete;
  int				safe_time;
  int				new_mob;
  int				sender;
  bool				_boost;

public:
  AObject(){}
  AObject(const AObject &) = delete;
  AObject &operator=(const AObject &) = delete;
  AObject(GameSprite sprite,
	  const int id,
	  const int pos_x,
	  const int pos_y,
	  const int hp,
	  const ObjectType object,
	  const MobType mob)
  {
    try
    {
      shipSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", sprite);
    }
    catch (Error e)
    {
      throw Error("couldn't find lib Ressources", "AObject(GameSprite, int ..)");
    }
    _id = id;
    _posX = pos_x;
    _posY = pos_y;
    _hp = hp;
    _speed = 1;
    _objectType = object;
    _mobType = mob;
    _Destroyed = false;
    _toDelete = false;
    safe_time = 0;
    new_mob = 0;
    _boost = false;
  };

  AObject(const int id,
	  const int pos_x,
	  const int pos_y,
	  const int hp,
	  const ObjectType object,
	  const MobType mob)
  {
    shipSprite = nullptr;
    _id = id;
    _posX = pos_x;
    _posY = pos_y;
    _hp = hp;
    _speed = 1;
    _objectType = object;
    _mobType = mob;
    _Destroyed = false;
    _toDelete = false;
    safe_time = 0;
    new_mob = 0;
    _boost = false;
  };
  virtual ~AObject() {};

  virtual void setMode(int) = 0;
  virtual void move_down() = 0;
  virtual void move_up() = 0;
  virtual void move_forward() = 0;
  virtual void move_backward() = 0;
  virtual void getDestroyed() = 0;
  virtual void resetAnim() = 0;
  virtual void draw(sf::RenderWindow &) = 0;

  void setSpeed(int entry) { _speed = entry; };
  void setId(int entry)  { _id = entry; };
  void setHp(int entry)  { _hp = entry; };
  void setPosX(int entry) { _posX = entry; };
  void setPosY(int entry) { _posY = entry; };
  void addSafeTime() { safe_time = (safe_time + 1) % 30; };
  void setSender(int entry) { sender = entry; };
  void setBoost(int entry){ _boost = entry; };
  bool getBoost() const { return _boost; };

  void takeDamage(const int val)
  {
    if (val == 0)
    {
      safe_time = 0;
    }
    else
    {
      safe_time += val;
      if (safe_time == 30)
	safe_time = 0;
    }
  };

  int getId() const { return (_id); };
  int getHp() const { return (_hp); };
  bool getDelete() const { return (_toDelete); };
  void setDelete()  { _toDelete = true; };
  void setDestroy()  { _Destroyed = true; };
  int getPosX() const { return (_posX); };
  int getPosY() const { return (_posY); };
  int getSender() const { return (sender); };
  int getWidth() const
  {
    if (shipSprite)
      return (shipSprite->getWidth());
    return (0);
  };
  int getHeight() const
  {
    if (shipSprite)
      return (shipSprite->getHeight());
    return (0);
  };
  int getSafeTime() const { return (safe_time); };
  bool isAlive() { return (_hp != 0); };
  ObjectType getObjectType() const { return (_objectType); };
  MobType getMobType() const { return (_mobType); };
  IObject   *operator()(Srtp  &packet, bool attack){
    packet._idObject = _id;
    packet._posX = _posX;
    packet._posY = _posY;
    packet._hp = _hp;
    packet._mobType = _mobType;
    packet._idGame = 0;
    packet._objType = _objectType;
    packet._cmdClient = attack ? CMDC_Attack : CMDC_Update;
    return this;
  }
};

#endif /* !AOBJECT_HPP_ */
