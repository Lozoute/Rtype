#ifndef VERTEX_ARRAY_HPP_
# define VERTEX_ARRAY_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Loader.hpp"
#include "ISprite.hpp"
#include "IObject.hpp"
#include "API_Mutex.hpp"

using namespace API_Mutex;

enum side
{
  ALLY,
  ENEMY
};

class ProjArray
{
  using ptr = std::shared_ptr < IObject >;
public:
  ISprite				  		*_texture;
  sf::VertexArray					_quad;
  side				  		_side;
  int						_posTexX;
  int						_posTexY;
  int						_height;
  int						_width;
  std::vector<std::pair<ptr, std::shared_ptr<IMutex>>>				tab;
  int						_id;

  ProjArray() = delete;
  ProjArray& operator=(const ProjArray &) = delete;
public:
  ProjArray(const ProjArray &);
  ProjArray(ISprite *sprite, const int id_sender);
  ProjArray(ISprite *texture, side s);
  ~ProjArray();

  void draw(sf::RenderWindow &);
  void setScale(const int, const int);
  ISprite	*getSprite() const;
  std::vector<std::pair<ptr, std::shared_ptr<IMutex>>>		&getTab();
  int	getId() const { return _id; };
};

#endif /* !VERTEX_ARRAY_HPP_ */
