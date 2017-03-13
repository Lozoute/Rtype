#ifndef API_SOCKET_UDP_HPP_
# define API_SOCKET_UDP_HPP_

# include <stdexcept>
# include <memory>
# include <string>

namespace API_Socket_Udp
{
  enum Mode
    {
      SERVER = 0,
      CLIENT = 1,
    };

  class IAddress
  {
  public:
    virtual ~IAddress() {};

    virtual const std::string	&toString() const = 0;
    virtual int			getPort() const = 0;
  };

  class ISocket
  {
  public:
    virtual ~ISocket() {};

    virtual Mode		getMode() const = 0;

    // server fcts
    virtual std::size_t	sendTo(void *data, std::size_t dataSize,
	const std::shared_ptr<const IAddress> &addrPtr) = 0; // non blocking
    virtual std::size_t	receiveFrom(void *buff, std::size_t buffSize,
	std::shared_ptr<IAddress> &addrPtr) = 0; // non blocking

    // client fcts
    virtual std::size_t	send(const void *data, std::size_t dataSize) = 0; // non blocking
    virtual std::size_t	receive(void *buff, std::size_t buffSize) = 0; // non blocking
  };

# if defined(WIN32) || defined (_WIN32)
    //  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# define LIB_MUTEX  "../API/DLLs/lib_API_Mutex_STD"
# elif defined(linux) || defined (__unix__)
    //  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# define LIB_MUTEX  "../API/SOs/lib_API_Mutex_STD.so"
# else
    //  do nothing and hope for the best?
# define EXPORT
# define IMPORT
# define LIB_MUTEX  "undefined architexture"
# pragma warning Unknown dynamic link import/export semantics.
# endif

} /* !namespace API_Socket_Udp */

//
// DO NOT FORGET TO ADD AN 'extern "c"' FUNCTION IN YOUR IMPLEMENTATION
//

// ISocket *socket_server(const std::string &host, int svrPort, int localPort = 0)
// ISocket *socket_client(int port)

#endif // !API_SOCKET_UDP_HPP_
