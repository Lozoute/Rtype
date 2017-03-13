#ifndef ACKQUEUE_HPP_
# define ACKQUEUE_HPP_

#include <stdint.h>

struct	    AckQueue
{
  int32_t   _queue;

  AckQueue(){
    _queue = 0;
  }

  inline void	    shift(int nb){
    nb = (nb > 32) ? 32 : nb;
    if (nb)
    {
      _queue <<= 1;
      _queue++;
      _queue <<= nb - 1;
    }
  }

  inline bool	    operator[](int nb) const{
    return (_queue & (1 << nb));
  }

  inline void	    operator()(int nb){
    _queue |= 1 << nb;
  }

  inline AckQueue   &operator=(AckQueue const &other){
    _queue = other._queue;
    return *this;
  }
};

#endif // !ACKQUEUE_HPP_