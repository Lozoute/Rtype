#include "FireRateBooster.hpp"
#include "Game.hpp"

///
/// CTOR ETC
///
FireRateBooster::FireRateBooster	(int Id, Game *G, int Gain)
  : AObject(OT_Bonus, Id, std::rand() % __SizeX,
	    __WallSize + (std::rand() % (__SizeY - (__WallSize * 2) - 28)),
	    46, 28, 0, 0, 1, 0, G,
	    MT_None, nullptr, BT_FireRateBooster),
    _Gain(Gain)
{}

FireRateBooster::FireRateBooster	(const FireRateBooster &O)
					: AObject(O), _Gain(O._Gain)
{}

FireRateBooster&			FireRateBooster::operator=(const FireRateBooster &)
{
  return (*this);
}

FireRateBooster::~FireRateBooster	()
{}

///
/// ACTIONS
//
void					FireRateBooster::Affect(PlayerShip &Obj)
{
  Obj.BoostFireRate(_Gain);
  _IdTaker = Obj.GetId();
  this->Kill();
}
