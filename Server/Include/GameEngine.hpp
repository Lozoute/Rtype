#ifndef GAMEENGINE_HPP_
# define GAMEENGINE_HPP_

# include <iostream>
# include <string>
# include <vector>
# include <memory>
# include "Game.hpp"
# include "Player.hpp"

const auto			__NbGamesStart = 20;

/// Some Forward Declarations
class				Game;
class				Server;
class				AObject;
class				Player;

class GameEngine
{
private:
  std::vector<Ptr<Player>>	_Players;
  std::vector<Ptr<Game>>	_Games;

  GameEngine			(const GameEngine &);
  GameEngine			&operator=(const GameEngine &);

public:
  GameEngine			();
  ~GameEngine			();

  int				GenGameId();

  void				OpenGame(const Srtp &);

  void				Join(const Srtp &);
  void				Quit(const Srtp &);
  void				Treat(const Srtp &);
};

#endif /* !GAMEENGINE_HPP_ */
