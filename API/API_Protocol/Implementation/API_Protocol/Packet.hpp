#ifndef PACKET_HPP_
# define PACKET_HPP_

# include "Header.hpp"
# include "Srtp.hpp"
# include "SrtpLight.hpp"

struct	      Packet
{
  Header      header;
  SrtpLight   srtpL;
  Packet()
    : header(), srtpL()
  {}
};

#endif // !PACKET_HPP_
