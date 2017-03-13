#include <Ws2tcpip.h>
#include <sstream>
#include "Address.hpp"
#include "API_Error.hpp"

using namespace API_Socket_Udp_Windows;

Address::Address(const struct sockaddr &val, int len)
    : _addrLen(len)
{
    memcpy(&_address, &val, len);
    updateString();
}


Address::~Address(){}

void		Address::updateString()
{
    char	buff[46];

    if (_address.sa_family == AF_INET)
    {
	sockaddr_in	address;

	memcpy(&address, &_address, sizeof(address));
	if (!InetNtopA(_address.sa_family, static_cast<PVOID>(&address.sin_addr), buff, 46))
	    throw Error("InetNtopA() failed", "Address::toString");
    }
    else
    {
	sockaddr_in6	address;

	memcpy(&address, &_address, sizeof(address));
	if (!InetNtopA(_address.sa_family, static_cast<PVOID>(&address.sin6_addr), buff, 46))
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

const SOCKADDR		*Address::getSockAddr() const
{
    return reinterpret_cast<const SOCKADDR *>(&_address);
}

int			Address::getAddrLen() const
{
    return _addrLen;
}

void			Address::update(const struct sockaddr &val, int len)
{
    memcpy(&_address, &val, len);
    updateString();
}
