//
// SocketUdp.hpp for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jul 15 00:04:12 2015 jordan sabbah
// Last update Fri Jul 24 04:19:25 2015 jordan sabbah
//

#ifndef SOCKETUDP_HPP_
# define SOCKETUDP_HPP_

# include "API_Socket_Udp.hpp"
# include "Loader.hpp"
// # include "API_Mutex.hpp"
# include <arpa/inet.h>
# include "SpinLock.hpp"

namespace API_Socket_Udp_Unix
{
  class SocketUdp : public API_Socket_Udp::ISocket
  {
  private:
    int					_sock;
    sockaddr_in				_addrSvr;
    API_Socket_Udp::Mode		_mode;
    Loader				_loader;
    // API_Mutex::IMutex			*_mutexSend;
    // 	API_Mutex::IMutex			*_mutexReceive;
    SpinLock				_lockReceive;
    SpinLock				_lockSend;

    void				setBlocking(bool mode);

    static const int			receiveFromFlags = 0;
    static const int			sendToFlags = 0;

  public:
    virtual ~SocketUdp();

    virtual API_Socket_Udp::Mode	getMode() const;

    // server
    SocketUdp(int port);
    virtual std::size_t			sendTo(void *data, std::size_t dataSize,
				       const std::shared_ptr<const API_Socket_Udp::IAddress> &addrPtr);
    virtual std::size_t			receiveFrom(void *buff, std::size_t buffSize,
						    std::shared_ptr<API_Socket_Udp::IAddress> &addrPtr);

    // client
    SocketUdp(const std::string &host, int svrPort, int localPort);
    virtual std::size_t			send(const void *data, std::size_t dataSize);
    virtual std::size_t			receive(void *buff, std::size_t buffSize);

    SocketUdp(const SocketUdp &other)						= delete;
    SocketUdp				&operator=(const SocketUdp &other)	= delete;
  };
}

#endif // !SOCKETUDP_HPP_
