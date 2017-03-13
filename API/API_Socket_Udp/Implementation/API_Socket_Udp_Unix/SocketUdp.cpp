//
// SocketUdp.cpp for  in /home/sabbah_j/rendu/TEK3/B5-ADVANCED-CPP/rtype/API/API_Socket_Udp/Implementation/API_Socket_Udp_Unix
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jul 15 00:04:18 2015 jordan sabbah
// Last update Fri Jul 24 16:37:38 2015 jordan sabbah
//

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <mutex>
#include "SocketUdp.hpp"
#include "Address.hpp"
#include "API_Error.hpp"
#include "ScopedLock.hpp"

using namespace API_Socket_Udp_Unix;

SocketUdp::SocketUdp(int port)
{
  sockaddr_in		addr;

  // try
  // {
  //   _mutexSend = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
  // 	_mutexReceive = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
  // }
  // catch (const Error &e)
  // {
  //   throw Error(e.what(), e.who());
  // }
  _mode = API_Socket_Udp::SERVER;
  memset(&_addrSvr, 0, sizeof(_addrSvr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if ((this->_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    throw Error("socket() failed", "SocketUdp::init");
  if ((bind(this->_sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr))) == -1)
    throw Error("bind() failed", "SocketUdp::init");
  setBlocking(false);
}

SocketUdp::SocketUdp(const std::string &host, int svrPort, int localPort)
{
  bool	  localHost = host == "127.0.0.1" || host == "localhost";

  // try
  //   {
  //     _mutexSend = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
  // 	  _mutexReceive = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
  //   }
  // catch (const Error &e)
  //   {
  //     throw Error(e.what(), e.who());
  //   }
  _mode = API_Socket_Udp::CLIENT;
  memset(&_addrSvr, 0, sizeof(_addrSvr));
  _addrSvr.sin_family = AF_INET;
  if (!localHost)
    _addrSvr.sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, host.c_str(), &_addrSvr.sin_addr.s_addr);
  _addrSvr.sin_port = htons(localPort);
  if ((this->_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    throw Error("socket() failed", "SocketUdp::init");
  if ((bind(this->_sock, reinterpret_cast<sockaddr *>(&_addrSvr), sizeof(_addrSvr))) == -1)
    throw Error("bind() failed", "SocketUdp::init");
  _addrSvr.sin_port = htons(svrPort);
  if (!localHost)
    inet_pton(AF_INET, host.c_str(), &_addrSvr.sin_addr.s_addr);
  setBlocking(false);
}

SocketUdp::~SocketUdp()
{
  close(_sock);
}

API_Socket_Udp::Mode	SocketUdp::getMode() const
{
  return _mode;
}

std::size_t		SocketUdp::sendTo(void *data, std::size_t dataSize,
					  const std::shared_ptr<const API_Socket_Udp::IAddress> &addrPtr)
{
  //  std::unique_lock <API_Mutex::IMutex>  lock(*_mutexSend, std::defer_lock);
  // if (!lock.try_lock())
  //   return 0;
  ScopedLock	lock(_lockSend);
  Address const	*addr = dynamic_cast<const Address *>(addrPtr.get());

  if (_mode != API_Socket_Udp::SERVER)
    throw Error("wrong socket mode", "SocketUdp::sendTo");
  auto len = sendto(_sock, data, dataSize,
		    sendToFlags, addr->getSockAddr(), addr->getAddrLen());
  if (len == -1)
    {
      int error = errno;
      if (error != EWOULDBLOCK || error != EAGAIN)
	{
	  std::cout << "error = "<< error << std::endl;
	  throw Error("sendto() failed", "SocketUdp::sendTo");
	}
      return 0;
    }
    return len;
}

std::size_t		SocketUdp::receiveFrom(void *buff, std::size_t buffSize,
					       std::shared_ptr<API_Socket_Udp::IAddress> &addrPtr)
{
  // std::unique_lock <API_Mutex::IMutex>  lock(*_mutexReceive, std::defer_lock);
  // if (!lock.try_lock())
  //   return 0;
  ScopedLock		lock(_lockReceive);
  struct sockaddr	addr;
  socklen_t		addrLen = sizeof(addr);

  if (_mode != API_Socket_Udp::SERVER)
    throw Error("wrong socket mode", "SocketUdp::receiveFrom");
  auto len = recvfrom(_sock, buff, buffSize, receiveFromFlags, &addr, &addrLen);
  if (len == -1)
    {
      int error = errno;
      if (error != EWOULDBLOCK || error != EAGAIN)
	throw Error("recvfrom() failed", "SocketUdp::receiveFrom");
      return 0;
    }
  if (addrPtr.use_count() == 0)
    addrPtr = std::shared_ptr<API_Socket_Udp::IAddress>(new Address(addr, static_cast<int>(addrLen)));
  else
    dynamic_cast<Address *>(addrPtr.get())->update(addr, addrLen);
  return len;
}

std::size_t		SocketUdp::send(const void *data, std::size_t dataSize)
{
  ScopedLock		lock(_lockSend);
  //  std::unique_lock <API_Mutex::IMutex>  lock(*_mutexSend, std::defer_lock);
  // if (!lock.try_lock())
  //   return 0;
  if (_mode != API_Socket_Udp::CLIENT)
    throw Error("wrong socket mode", "SocketUdp::send");
  auto len = sendto(_sock, data, dataSize,
		    sendToFlags, reinterpret_cast<const sockaddr *>(&_addrSvr), sizeof(_addrSvr));
  if (len == -1)
    {
      int error = errno;
      if (error != EWOULDBLOCK || error != EAGAIN)
	throw Error("send failed", "SocketUdp::send");
      return 0;
    }
  return len;
}

std::size_t		SocketUdp::receive(void *buff, std::size_t buffSize)
{
  // std::unique_lock <API_Mutex::IMutex>  lock(*_mutexReceive, std::defer_lock);
  // if (!lock.try_lock())
  //   return 0;
  ScopedLock		lock(_lockReceive);
  sockaddr		addr;
  sockaddr_in		*addr_in;
  socklen_t		size = sizeof(addr);
  int			len;

  if (_mode != API_Socket_Udp::CLIENT)
    throw Error("wrong socket mode", "SocketUdp::receive");
  do
    {
      len = recvfrom(_sock, buff, buffSize,
		     receiveFromFlags, reinterpret_cast<sockaddr *>(&addr), &size);
      addr_in = reinterpret_cast<sockaddr_in *>(&addr);
    }
  while (len != -1 && (addr_in->sin_addr.s_addr != _addrSvr.sin_addr.s_addr
		       || addr_in->sin_port != _addrSvr.sin_port));
  if (len == -1)
    {
      int error = errno;
      if (error != EWOULDBLOCK || error != EAGAIN)
	throw Error("recvfrom() failed", "SocketUdp::receive");
      return 0;
    }
  return len;
}

void		SocketUdp::setBlocking(bool mode)
{
  int	nonBlock = mode ? 0 : 1;

  if (ioctl(_sock, FIONBIO, &nonBlock) == -1)
    throw Error("ioctlsocket() failed", "SocketUdp::setBlocking");
}

extern "C" EXPORT API_Socket_Udp::ISocket *socket_server(int port)
{
  return (new API_Socket_Udp_Unix::SocketUdp(port));
}

extern "C" EXPORT API_Socket_Udp::ISocket *socket_client(const std::string *host, int svrPort, int localPort)
{
  return (new API_Socket_Udp_Unix::SocketUdp(*host, svrPort, localPort));
}
