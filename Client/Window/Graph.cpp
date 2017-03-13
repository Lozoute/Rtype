#include "Graph.hpp"
#include "Loader.hpp"

Graph::Graph()
{
  try
  {
    _res = loader.getPtr<IRessources>(LIB_RES, "get_ressources");
  }
  catch (Error const &)
  {
    throw Error("error Graph Ctor", "Graph()");
  }
}

Graph::~Graph()
{
  delete _res;
}

void Graph::launch()
{
  int a;

  _res->playBackgroundMusic(e_Music::MENU);
  a = this->_window.event_MainMenu();

  if (a == 0)
  {
    if ((a = this->_window.event_JoinMenu()) == 3)
      this->launch();
    else if (a == 4)
    {
      _res->playBackgroundMusic(e_Music::GAME);
      this->_window.event_loop_game();
    }
  }
  else if (a == 1)
  {
    return;
  }
  else
    this->launch();
}
