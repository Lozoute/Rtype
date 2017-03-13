#include "Explosion.hpp"


Explosion::Explosion(int posX, int posY, ObjectType ot, MobType)
{
  Loader loader;

  /*if (ot == OT_MisAlly || ot == OT_MisFoe)
  _sprite = loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Explode1);
  else if (mb == MT_LittleShip || mb == MT_BrownArmor || mb == MT_Butterfly || mb == MT_GreenArmor)
  _sprite = loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Explode2);
  else if (mb == MT_RedArmor || mb == MT_MecaTurret || mb == MT_MecaCrab || mb == MT_Centiped)
  _sprite = loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Explode3);
  else if (mb == MT_RedArmor || mb == MT_MecaTurret || mb == MT_MecaCrab || mb == MT_Centiped)
  _sprite = loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Explode4);
  else if (mb == MT_Crab || mb == MT_ShipMob || mb == MT_Tentacle)
  _sprite = loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::FatExplode);*/


  _posX = posX;
  _posY = posY;
  _done = false;
  frame = 0;
  mode = 0;

  if (ot == OT_MisAlly)
    _posX = _posX - 50;
  else
    _posX = _posX + 50;
  _sprite = loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Explode4);
  _sprite->setTextureRect(_sprite->getPosX(), _sprite->getPosY(), _sprite->getWidth(), _sprite->getHeight());
  _sprite->setPosition(_posX, _posY);
}

Explosion::~Explosion()
{
}

void Explosion::setMode(int mode)
{
  _sprite->setTextureRect(_sprite->getPosX() + mode * (_sprite->getWidth() + 1),
			  _sprite->getPosY(),
			  _sprite->getWidth(),
			  _sprite->getHeight());
}


void Explosion::draw(sf::RenderWindow &window)
{
  ++frame;
  this->setMode(mode);
  if (frame >= 0 && frame <= 10)
    mode = 0;
  else if (frame >= 0 && frame <= 10)
    mode = 1;
  else if (frame >= 11 && frame <= 20)
    mode = 2;
  else if (frame >= 21 && frame <= 30)
    mode = 3;
  else if (frame >= 31 && frame <= 40)
    mode = 4;
  else if (frame >= 41 && frame <= 50)
    mode = 5;
  else if (frame >= 51 && frame <= 60)
    mode = 6;
  else if (frame >= 61 && frame <= 70)
    mode = 7;
  if (frame >= 70)
    _done = true;
  window.draw(_sprite->getSprite());
}

