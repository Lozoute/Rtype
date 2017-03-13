//
// Address.cpp for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jul 15 00:07:09 2015 jordan sabbah
// Last update Thu Jul 16 15:04:06 2015 florian hellegouarch
//

#include "Address.hpp"
#include <string.h>
#include <sstream>
#include <arpa/inet.h>
#include "API_Error.hpp"

using namespace API_Socket_Udp_Unix;

Address::Address(const struct sockaddr &val, int len)
  : _addrLen(len)
{
  memcpy(&_address, &val, len);
  updateString();
}


Address::~Address(){}

void			Address::updateString()
{
    char		buff[46];

    if (_address.sa_family == AF_INET)
    {
	sockaddr_in	address;

	memcpy(&address, &_address, sizeof(address));
	if (!inet_ntop(_address.sa_family, &address.sin_addr, buff, 46))
	    throw Error("InetNtopA() failed", "Address::toString");
    }
    else
    {
	sockaddr_in6	address;

	memcpy(&address, &_address, sizeof(address));
	if (!inet_ntop(_address.sa_family, &address.sin6_addr, buff, 46))
	    throw Error("InetNtopA() failed", "Address::toString");
    }
    std::ostringstream oss;
    oss << buff << ':' << getPort();
    _str = oss.str();
}

const std::string	&Address::toString() const
{
  return _str;
}

int			Address::getPort() const
{
  return ntohs(reinterpret_cast<const sockaddr_in *>(&_address)->sin_port);
}

const sockaddr		*Address::getSockAddr() const
{
  return &_address;
}

int			Address::getAddrLen() const
{
  return _addrLen;
}

void			Address::update(sockaddr const &val, int len)
{
  memcpy(&_address, &val, len);
  updateString();
}
