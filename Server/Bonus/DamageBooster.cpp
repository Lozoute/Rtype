#include "DamageBooster.hpp"
#include "Game.hpp"

///
/// CTOR ETC
///
DamageBooster::DamageBooster	(int Id, Game *G, int Gain)
  : AObject(OT_Bonus, Id, std::rand() % __SizeX,
	    __WallSize + (std::rand() % (__SizeY - (__WallSize * 2) - 28)),
	    46, 28, 0, 0, 1, 0, G,
	    MT_None, nullptr, BT_DamageBooster),
    _Gain(Gain)
{}

DamageBooster::DamageBooster	(const DamageBooster &O)
					: AObject(O), _Gain(O._Gain)
{}

DamageBooster&			DamageBooster::operator=(const DamageBooster &)
{
  return (*this);
}

DamageBooster::~DamageBooster	()
{}

///
/// ACTIONS
//
void				DamageBooster::Affect(PlayerShip &Obj)
{
  Obj.BoostDamages(_Gain);
  _IdTaker = Obj.GetId();
  this->Kill();
}
