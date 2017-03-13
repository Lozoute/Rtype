#ifndef EXPLOSION_HPP_
# define EXPLOSION_HPP_

#include "IRessources.hpp"
#include "Srtp.hpp"
#include "Loader.hpp"


# if defined(WIN32) || defined (_WIN32)
//  Microsoft
# define LIBNAME  "../API/DLLs/lib_API_Ressources.dll"
# elif defined(linux) || defined (__unix__)
//  UNIX
# define LIBNAME  "../API/SOs/lib_API_Ressources.so"
# else
//  unknown
# define LIBNAME  ""
# pragma warning Unknown dynamic link import/export semantics.
# endif

class Explosion
{
  ISprite *_sprite;
  int _posX;
  int _posY;
  bool _done;
  int frame;
  int mode;

public:
  Explosion(int , int, ObjectType, MobType);
  Explosion(const Explosion &) = delete;
  Explosion &operator=(const Explosion &) = delete;
  ~Explosion();

  void draw(sf::RenderWindow &);
  void setMode(int);
  bool getDone() const{ return _done; };
};

#endif // !EXPLOSION_HPP_
