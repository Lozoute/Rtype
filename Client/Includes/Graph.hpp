#ifndef GRAPH_HPP_
# define GRAPH_HPP_

#include "Window.hpp"
#include "IRessources.hpp"
#include "Loader.hpp"

class Graph
{
  Window	    _window;
  IRessources	    *_res;
  Loader	    loader;

public:
  Graph();
  Graph(const Graph &) = delete;
  Graph&	operator=(const Graph &) = delete;
  ~Graph();

  void launch();
};

# if defined(WIN32) || defined (_WIN32)
# define LIB_RES	"../API/DLLs/lib_API_Ressources.dll"
# else
# define LIB_RES	"../API/SOs/lib_API_Ressources.so"
# endif


# endif /* !GRAPH_HPP_ */
