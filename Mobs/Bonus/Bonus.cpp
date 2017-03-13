#include "Bonus.hpp"

Bonus::Bonus(const BonusType type, const int id, const int pos_x, const int pos_y)
  : AObject(id, pos_x, pos_y, 1, OT_Bonus, MT_None)
{
  _type = type;
  if (type == BT_HealthPack)
    shipSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", HealthPack);
  else if (type == BT_DamageBooster)
    shipSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", DamageBooster);
  else if (type == BT_FireRateBooster)
    shipSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", FireRateBooster);
  shipSprite->setPosition(_posX, _posY);
  shipSprite->setTextureRect(shipSprite->getPosX(), shipSprite->getPosY(), shipSprite->getWidth(), shipSprite->getHeight());
}

Bonus::~Bonus()
{
}

void Bonus::draw(sf::RenderWindow &window)
{
  window.draw(shipSprite->getSprite());
}

extern "C" EXPORT IObject *get_bonus(const BonusType type, const int id, const int pos_x, const int pos_y){
  return (new class Bonus(type, id, pos_x, pos_y));
}
