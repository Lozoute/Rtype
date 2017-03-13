#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <iostream>
# include <string>
# include <memory>
# include "Game.hpp"
# include "PlayerShip.hpp"


/// Forward Declarations
class			Game;
class			PlayerShip;


/// Player Class
class			Player
{
private:
  int			_Id;
  int			_ShipId;
  Ptr<PlayerShip>	_Ship;
  Game			*_Game;
  int			_GameId;
  bool			_Connected;

  Player		(const Player&);
  Player		&operator=(const Player &);

public:
  Player		(Ptr<PlayerShip> &, Game *);
  ~Player		();

  int			GetId()		const;
  PlayerShip		*GetShip()	const;
  Ptr<PlayerShip>	&GetAObject();
  int			GetShipId()	const;
  Game			*GetGame()	const;
  int			GetGameId()	const;
  bool			IsAlive()	const;
  bool			IsConnected()	const;
  int			GetScore()	const;

  void			Kill();
  void			Resurect();
  void			Connect(int);
  void			Disconnect();

  void			SendSituation();
};

#endif /* !PLAYER_HPP_ */
