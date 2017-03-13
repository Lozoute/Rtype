#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include <SFML/Graphics.hpp>
# include <iostream>
# include <string>
# include "Srtp.hpp"

class RessourcesV2;

class Object
{
protected:  
  int                   _id;
  int			_posX;
  int			_posY;
  int			_width;
  int			_height;
  int			_speedX;
  int			_speedY;
  int			_hp;
  bool			_alive;
  ObjectType		_objectType;
  MobType		_mobType;
  int			_posMisX;
  int			_posMisY;
  int		        _ownerId;
  BonusType		_bonusType;
  int			_dmgs;
  bool			_shield;
  int			_shieldCount;
public:
  Object ();
  Object (int id, int posx, int posy, int width, int height, int speedx, int speedy ,int hp, bool alive, ObjectType ot, MobType mt, BonusType bt = BT_None, bool shield = false);
  Object (const Object &O);
  Object&		operator=(const Object &);
  ~Object	();

  int			getId()		const { return(_id);}
  int			getPosX()	const { return(_posX);}
  int			getPosY()	const { return(_posY);}
  int			getWidth()	const { return(_width);}
  int			getHeight()	const { return(_height);}
  int			getSpeedX()	const { return(_speedX);}
  int			getSpeedY()	const { return(_speedY);}
  int			getHp()		const { return(_hp);}
  bool			isAlive()	const { return(_alive);}
  int			getObjectType()	const { return(_objectType);}
  MobType		getMobType()	const { return(_mobType);}
  BonusType		getBonusType()	const { return(_bonusType);}
  int			getDmgs()	const { return(_dmgs);}

  void			kill();
  void			setId(int);
  void			setPosX(int);
  void			setPosY(int);
  void			setSpeedX(int);
  void			setSpeedY(int);
  void			setHp(int);
  void			setOwnerId(int);
  void			setBonusType(BonusType);
  void			setDmgs(int);

  void			update(); 
  void			draw(RessourcesV2 &);
  void			toggleShield(bool);
};

#endif /* !OBJECT_HPP_ */
