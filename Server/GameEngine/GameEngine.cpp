#include "GameEngine.hpp"

///
/// CTOR, DTOR ETC
///
GameEngine::GameEngine		()
{
  for (unsigned int i = 0; i < __NbGamesStart; ++i)
    _Games.push_back(Ptr<Game>(new Game(i, _Players)));
}

GameEngine::GameEngine		(const GameEngine &)
{}

GameEngine			&GameEngine::operator=(const GameEngine &)
{
  return (*this);
}

GameEngine::~GameEngine		()
{}

///
/// OPEN A GAME
///
void				GameEngine::OpenGame(const Srtp &)
{}

///
/// JOIN A GAME
///
void				GameEngine::Join(const Srtp &P)
{
  for (std::vector<Ptr<Game>>::iterator It = _Games.begin(); It != _Games.end(); ++It)
    if (!(*It)->IsFull())
      {
	(*It)->AddPacket(P);
	if ((*It)->GetNbPlayers() == 0)
	  (*It)->Start();
	return;
      }
  this->OpenGame(P);
}

///
/// QUIT A GAME
///
void				GameEngine::Quit(const Srtp &P)
{
  for (std::vector<Ptr<Player>>::iterator It = _Players.begin(); It != _Players.end(); ++It)
    if ((*It)->GetId() == P._idDest)
      {
	(*It)->GetGame()->AddPacket(P);
	break;
      }
}

///
/// TREAT CMD CLIENT
///
void				GameEngine::Treat(const Srtp &P)
{
  if (P._idGame >= 0 && P._idGame < static_cast<int>(_Games.size()))
    _Games[P._idGame]->AddPacket(P);
}
