#ifndef DRAWMAP_HPP_
#define DRAWMAP_HPP_

#include <SFML/Graphics.hpp>

class DrawMap
{
  sf::VertexArray _quad;
  sf::Texture  _texture;
  int	       _counter;
public:
  DrawMap(const std::string &path);
  ~DrawMap();
  void	addObject(int, int, int, int, int, int);
  
  sf::VertexArray &getArray() {return _quad;}
  sf::Texture *getTexture() {return &_texture;}
  void	clear(size_t size);
};

#endif
