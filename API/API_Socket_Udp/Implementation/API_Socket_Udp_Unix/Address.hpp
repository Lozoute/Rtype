//
// Address.hpp for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jul 15 00:07:05 2015 jordan sabbah
// Last update Thu Jul 16 15:01:53 2015 florian hellegouarch
//

#ifndef ADDRESS_UNIX_HPP_
# define ADDRESS_UNIX_HPP_

# include <sys/socket.h>
# include <netinet/in.h>
# include <string>
# include "API_Socket_Udp.hpp"

namespace API_Socket_Udp_Unix
{
  class Address : public API_Socket_Udp::IAddress
  {
  private:
    sockaddr			_address;
    int				_addrLen;
    std::string			_str;

    void			updateString();

  public:
    Address(sockaddr const &val, int len);
    virtual ~Address();

    virtual const std::string	&toString() const;
    virtual int			getPort() const;

    const sockaddr		*getSockAddr() const;
    int				getAddrLen() const;

    void			update(sockaddr const &val, int len);
  };
}

#endif // !ADDRESS_UNIX_HPP_
