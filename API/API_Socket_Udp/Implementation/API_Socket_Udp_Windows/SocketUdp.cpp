#include <WS2tcpip.h>
#include <iostream>
#include "SocketUdp.hpp"
#include "Address.hpp"
#include "API_Error.hpp"
#include "ScopedLock.hpp"

using namespace API_Socket_Udp_Windows;

SocketUdp::SocketUdp(int port)
{
  SOCKADDR_IN		addr;

  try
  {
    _mutexSend = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
    _mutexReceive = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
  }
  catch (const Error &e)
  {
    throw Error(e.what(), e.who());
  }
  WSAStartup(MAKEWORD(2, 2), &(this->_wsaData));
  _mode = API_Socket_Udp::SERVER;
  memset(&_addrSvr, 0, sizeof(_addrSvr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(static_cast<u_short>(port));
  if ((this->_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    throw Error("socket() failed", "SocketUdp::init");
  if ((bind(this->_sock, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr))) == SOCKET_ERROR)
    throw Error("bind() failed", "SocketUdp::init");
  setBlocking(true);
}

SocketUdp::SocketUdp(const std::string &host, int svrPort, int localPort)
{
  bool	  localHost = host == "127.0.0.1" || host == "localhost";

  try
  {
    _mutexSend = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
    _mutexReceive = &_loader.getInstance<API_Mutex::IMutex>(LIB_MUTEX, "__API_Load__");
  }
  catch (const Error &e)
  {
    throw Error(e.what(), e.who());
  }
  WSAStartup(MAKEWORD(2, 2), &(this->_wsaData));
  _mode = API_Socket_Udp::CLIENT;
  memset(&_addrSvr, 0, sizeof(_addrSvr));
  _addrSvr.sin_family = AF_INET;
  if (!localHost)
    _addrSvr.sin_addr.s_addr = INADDR_ANY;
  else
    inet_pton(AF_INET, host.c_str(), &_addrSvr.sin_addr.s_addr);
  _addrSvr.sin_port = htons(static_cast<u_short>(localPort));
  if ((this->_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    throw Error("socket() failed", "SocketUdp::init");
  if ((bind(this->_sock, reinterpret_cast<SOCKADDR *>(&_addrSvr), sizeof(_addrSvr))) == SOCKET_ERROR)
    throw Error("bind() failed", "SocketUdp::init");
  _addrSvr.sin_port = htons(static_cast<u_short>(svrPort));
  if (!localHost)
    inet_pton(AF_INET, host.c_str(), &_addrSvr.sin_addr.s_addr);
  setBlocking(false);
}

SocketUdp::~SocketUdp()
{
  closesocket(this->_sock);
  WSACleanup();
}

API_Socket_Udp::Mode	SocketUdp::getMode() const
{
  return _mode;
}

std::size_t		SocketUdp::sendTo(void *data, std::size_t dataSize,
					  const std::shared_ptr<const API_Socket_Udp::IAddress> &addrPtr)
{
  ScopedLock		lock(*_mutexSend);
  const Address		*addr = dynamic_cast<const Address *>(addrPtr.get());

  if (_mode != API_Socket_Udp::SERVER)
    throw Error("wrong socket mode", "SocketUdp::sendTo");
  auto len = sendto(_sock, static_cast<const char *>(data), dataSize,
		    sendToFlags, addr->getSockAddr(), addr->getAddrLen());
  if (len == SOCKET_ERROR)
    {
      int error = WSAGetLastError();
      std::cout << "error " << error << std::endl;
      throw Error("sendto() failed", "SocketUdp::sendTo");
    }
  return len;
}

std::size_t		SocketUdp::receiveFrom(void *buff, std::size_t buffSize,
					       std::shared_ptr<API_Socket_Udp::IAddress> &addrPtr)
{
  ScopedLock		lock(*_mutexReceive);
  struct sockaddr	addr;
  int			addrLen = sizeof(addr);

  if (_mode != API_Socket_Udp::SERVER)
    throw Error("wrong socket mode", "SocketUdp::receiveFrom");
  auto len = recvfrom(_sock, static_cast<char *>(buff), buffSize, receiveFromFlags, &addr, &addrLen);
  if (len == SOCKET_ERROR)
  {
    int error = WSAGetLastError();
    if (error != WSAEWOULDBLOCK && error != WSAECONNRESET)
    {
      std::cout << "error " << error << std::endl;
      throw Error("recvfrom() failed", "SocketUdp::receiveFrom");
    }
    return 0;
  }
  if (addrPtr.use_count() == 0)
    addrPtr = std::shared_ptr<API_Socket_Udp::IAddress>(new Address(addr, addrLen));
  else
    dynamic_cast<Address *>(addrPtr.get())->update(addr, addrLen);
  return len;
}

std::size_t		SocketUdp::send(const void *data, std::size_t dataSize)
{
  ScopedLock		lock(*_mutexSend);

  if (_mode != API_Socket_Udp::CLIENT)
    throw Error("wrong socket mode", "SocketUdp::send");
  auto len = sendto(_sock, static_cast<const char *>(data), dataSize,
		    sendToFlags, reinterpret_cast<const SOCKADDR *>(&_addrSvr), sizeof(_addrSvr));
  if (len == SOCKET_ERROR){
    std::cout << GetLastError() << std::endl;
    throw Error("sendto failed", "SocketUdp::send");
  }
  return len;
}

std::size_t		SocketUdp::receive(void *buff, std::size_t buffSize)
{
  ScopedLock		lock(*_mutexReceive);
  struct sockaddr	addr;
  sockaddr_in		*addr_in;
  int			size = sizeof(addr);
  int			len;

  if (_mode != API_Socket_Udp::CLIENT)
    throw Error("wrong socket mode", "SocketUdp::receive");
  do
  {
    len = recvfrom(_sock, static_cast<char *>(buff), buffSize,
		   receiveFromFlags, reinterpret_cast<SOCKADDR *>(&addr), &size);
    addr_in = reinterpret_cast<sockaddr_in *>(&addr);
  } while (len != SOCKET_ERROR
	   && (addr_in->sin_addr.S_un.S_addr != _addrSvr.sin_addr.S_un.S_addr
	   || addr_in->sin_port != _addrSvr.sin_port));
  if (len == SOCKET_ERROR)
  {
    int error = WSAGetLastError();
    if (error != WSAEWOULDBLOCK && error != WSAECONNRESET)
    {
      std::cout << "error " << error << std::endl;
      throw Error("recvfrom() failed", "SocketUdp::receive");
    }
    return 0;
  }
  return len;
}

void		SocketUdp::setBlocking(bool mode)
{
  DWORD	nonBlock = mode ? 0 : 1;

  if (ioctlsocket(this->_sock, FIONBIO, &nonBlock) == -1)
    throw Error("ioctlsocket() failed", "SocketUdp::setBlocking");
}

extern "C"EXPORT API_Socket_Udp::ISocket *socket_server(int port)
{
  return (new API_Socket_Udp_Windows::SocketUdp(port));
}

extern "C" EXPORT API_Socket_Udp::ISocket *socket_client(const std::string *host, int svrPort, int localPort)
{
  return (new API_Socket_Udp_Windows::SocketUdp(*host, svrPort, localPort));
}
