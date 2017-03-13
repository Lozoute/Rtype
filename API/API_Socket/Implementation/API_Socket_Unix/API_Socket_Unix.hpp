#ifndef API_SOCKET_UNIX_HPP_
# define API_SOCKET_WINDOWS_HPP_

# include <algorithm>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <arpa/inet.h>
# include "API_Socket.hpp"

namespace API_Socket_Unix
{
  class Socket : public API_Socket::ISocket
  {
    int						_sock;
    bool					_read;
    bool					_write;
    API_Socket::Mode				_mode;


    void					Bigger(int *, const std::vector<std::shared_ptr<Socket>> &,
						       const std::vector<std::shared_ptr<Socket>> &) const;

  public:
    Socket					();
    Socket					(int);
    Socket					(const Socket &);
    Socket &					operator=(const Socket &);
    virtual ~Socket				();

    virtual void				Init(int);
    virtual void				Init(int, const std::string &);
    virtual std::shared_ptr<ISocket>		Accept();

    virtual std::size_t				Send(const void *, std::size_t);
    virtual std::size_t				Receive(void *, std::size_t);

    virtual int					Poll(std::vector<std::shared_ptr<ISocket>> &,
						     std::vector<std::shared_ptr<ISocket>> &);

    virtual bool				IsReadable() const;
    virtual bool				IsWritable() const;

    virtual API_Socket::Mode			GetMode() const;

  };
};

# endif /* !API_SOCKET_UNIX_HPP_ */
