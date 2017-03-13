#include "Explosion.hpp"
#include "RessourcesV2.hpp"
#include "Sprite.hpp"
#include "Srtp.hpp"

Explosion::Explosion ()
  : _posX(0), _posY(0), _size(0), _frame(-1), _maxFrame(0)
{
}


Explosion::Explosion (int x, int y, int size)
  : _posX(x), _posY(y), _size(size), _frame(0), _maxFrame(7)
{
}

Explosion::Explosion(const Explosion &o)
  : _posX(o._posX), _posY(o._posY), _size(o._size), _frame(o._frame)
  , _maxFrame(o._maxFrame)
 
{
}

Explosion	 &Explosion::operator=(const Explosion &O)
{
  if (this != &O)
    {
      _posX = O._posX;
      _posY = O._posY;
      _size = O._size;
      _frame = O._frame;
      _maxFrame = O._maxFrame;
    }
  return (*this);
}

Explosion::~Explosion()
{
}


void	Explosion::explode()
{
  _frame++;
}
