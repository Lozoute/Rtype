#ifndef PLAYERSHIP_HPP_
# define PLAYERSHIP_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "AObject.hpp"
# include "Missile.hpp"
# include "Player.hpp"

/// We're Lazy
using namespace		API_Mutex;

/// Forward Declarations
class			Player;
class			Game;

/// Variables
const auto		__FireRate = 8;
const auto		__Damages = 1;

/// PlayerShip Class
class			PlayerShip : public AObject
{
private:
  Player		*_Player;
  int			_FireRate;
  int			_Timer;
  int			_BoostFireRate;
  int			_BoostDamages;
  int			_Damages;

  PlayerShip		(const PlayerShip &);
  PlayerShip		&operator=(const PlayerShip &);

public:
  PlayerShip		(int, int, int, Game *);
  ~PlayerShip		();

  Player		*GetPlayer()	const;
  void			SetPlayer(Player *);
  int			GetPlayerId() const;
  void			Resurect();
  void			Reset();

  virtual bool		Update(std::vector<Ptr<AObject>> &);
  virtual void		Attack();
  virtual void		TakeDmgs(int);

  void			DecrBoost();
  void			BoostFireRate(int);
  void			BoostDamages(int);

  void			NotifyBonus(BonusType, int);
  void			NotifyBonusBase();
};

#endif /* !AOBJECT_HPP_ */
