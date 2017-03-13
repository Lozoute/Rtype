#include <iostream>
#include "DrawMap.hpp"

DrawMap::DrawMap(const std::string &path)
{
  _counter = 0;
  _texture.loadFromFile(path);
  _quad.setPrimitiveType(sf::Quads);
  _quad.resize(2000 * 4);
}

DrawMap::~DrawMap()
{
}

void	DrawMap::addObject(int x, int y, int textX, int textY, int width, int height)
{
  _quad[_counter + 0].position = sf::Vector2f(x, y);
  _quad[_counter + 1].position = sf::Vector2f(x + width, y);
  _quad[_counter + 2].position = sf::Vector2f(x + width, y + height);
  _quad[_counter + 3].position = sf::Vector2f(x, y + height);

  _quad[_counter + 0].texCoords = sf::Vector2f(textX, textY);
  _quad[_counter + 1].texCoords = sf::Vector2f(textX + width, textY);
  _quad[_counter + 2].texCoords = sf::Vector2f(textX + width, textY + height);
  _quad[_counter + 3].texCoords = sf::Vector2f(textX, textY + height);
  
  _counter += 4;
}

void DrawMap::clear(size_t size)
{
  _quad.clear();
  _quad.resize(size * 4);
  _counter = 0;
}
