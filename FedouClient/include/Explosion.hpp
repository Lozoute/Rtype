#ifndef EXPLOSION_HPP_
# define EXPLOSION_HPP_

# include <iostream>
# include <string>
# include "Srtp.hpp"

class RessourcesV2;

class Explosion
{
protected:  
  int			_posX;
  int			_posY;
  int			_size;
  int			_frame;
  int			_maxFrame;
public:
  Explosion ();
  Explosion (int x, int y, int size);
  Explosion (const Explosion &O);
  Explosion&		operator=(const Explosion &);
  ~Explosion	();

  int			getPosX()	const { return(_posX);}
  int			getPosY()	const { return(_posY);}
  int			getSize()       const { return(_size);}
  int			getFrame()      const { return(_frame);}
  void			explode();
};

#endif /* !EXPLOSION_HPP_ */
