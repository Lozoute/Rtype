#include "HealthPack.hpp"
#include "Game.hpp"

///
/// CTOR ETC
///
HealthPack::HealthPack	(int Id, Game *G, int Gain)
  : AObject(OT_Bonus, Id, std::rand() % __SizeX,
	    __WallSize + (std::rand() % (__SizeY - (__WallSize * 2) - 28)),
	    46, 28, 0, 0, 1, 0, G,
	    MT_None, nullptr, BT_HealthPack),
    _Gain(Gain)
{}

HealthPack::HealthPack	(const HealthPack &O)
			  : AObject(O), _Gain(O._Gain)
{}

HealthPack&		HealthPack::operator=(const HealthPack &)
{
  return (*this);
}

HealthPack::~HealthPack	()
{}

///
/// ACTIONS
//
void			HealthPack::Affect(PlayerShip &Obj)
{
  Obj.SetHp((Obj.GetHp() + _Gain > 20) ? (20) : (Obj.GetHp() + _Gain));
  if (Obj.GetPlayer())
    Obj.GetPlayer()->SendSituation();
  _IdTaker = Obj.GetId();
  this->Kill();
}
