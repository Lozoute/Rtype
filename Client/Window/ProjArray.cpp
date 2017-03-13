#include "ProjArray.hpp"

ProjArray::ProjArray(ISprite *sprite, const int id_sender)
{
  _texture = sprite;
  _quad.setPrimitiveType(sf::Quads);
  _id = id_sender;
}

ProjArray::ProjArray(const ProjArray &other)
{
  _texture = other._texture;
  _quad = other._quad;
  _side = other._side;
  _posTexX = other._posTexX;
  _posTexY = other._posTexY;
  _height = other._height;
  _width = other._width;
  tab = other.tab;
  _id = other._id;
}

ProjArray::ProjArray(ISprite *texture, const side s)
{
  _texture = texture;
  _quad.setPrimitiveType(sf::Quads);
  _side = s;
  _height = _texture->getHeight();
  _width = _texture->getWidth();
  _posTexX = _texture->getPosX();
  _posTexY = _texture->getPosY();
}

ProjArray::~ProjArray()
{
}

std::vector<std::pair<ProjArray::ptr, std::shared_ptr<IMutex>>>			&ProjArray::getTab()
{
  return (this->tab);
}

ISprite	*ProjArray::getSprite() const
{
  return (_texture);
}
void ProjArray::draw(sf::RenderWindow &window)
{
  if (tab.empty())
    return;
  _quad.clear();
  _quad.resize(tab.size() * 4);
  unsigned int a = 0;
  for (auto it = tab.begin(); it != tab.end(); ++it)
  {
    //it->second->lock();
    if (it->first == nullptr)
    {
      it->second->unLock();
      return;
    }
    _quad[a].position = sf::Vector2f(it->first->getPosX() + 0, it->first->getPosY() + 0);
    _quad[a].texCoords = sf::Vector2f(0 + _posTexX, 0 + _posTexY);
    a++;
    _quad[a].position = sf::Vector2f(it->first->getPosX() + _width, it->first->getPosY() + 0);
    _quad[a].texCoords = sf::Vector2f(_texture->getWidth() + _posTexX, 0 + _posTexY);
    a++;
    _quad[a].position = sf::Vector2f(it->first->getPosX() + _width, it->first->getPosY() + _height);
    _quad[a].texCoords = sf::Vector2f(_texture->getWidth() + _posTexX, _texture->getHeight() + _posTexY);
    a++;
    _quad[a].position = sf::Vector2f(it->first->getPosX() + 0, it->first->getPosY() + _height);
    _quad[a].texCoords = sf::Vector2f(0 + _posTexX, _texture->getHeight() + _posTexY);
    a++;
    //it->second->unLock();
  }
  window.draw(_quad, &_texture->getTexture());
  tab.clear();
}