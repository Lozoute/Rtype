#include "AProtocol.hpp"
#include <limits>

using namespace API_Protocol;

AProtocol::AProtocol()
{ }

bool  AProtocol::checkMagic(Header const &header) const{
  return header.magic == MAGIC;
}

bool  AProtocol::checkPong(Header const &header) const{
  return (header.flag & IS_PONG) != 0;
}

bool  AProtocol::checkPing(Header const &header) const{
  return static_cast<bool>(header.flag & IS_PING);
}