#ifndef HEADER_HPP_
# define HEADER_HPP_

# define MAGIC	    ('R' << 8) + 't'
# define IS_PING    1
# define IS_PONG    (1 << 1)
# define IS_PRIO    (1 << 2)

# include <cstdint>
# include "AckQueue.hpp"

struct		    Header
{
    int16_t	    magic;
    uint16_t	    id_ack;
    uint16_t	    id_packet;
    int8_t	    flag;
    int8_t	    padding;
    AckQueue	    ack_queue;
  Header()
    : magic(0), id_ack(0), id_packet(0),
      flag(0), padding(0)
  {}
};

#endif // !HEADER_HPP_
