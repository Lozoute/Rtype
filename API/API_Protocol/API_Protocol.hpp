#ifndef API_PROTOCOL_HPP_
# define API_PROTOCOL_HPP_

# include <cstdlib>
# include <string>
# include <memory>
# include <iostream>
# include "Srtp.hpp"

namespace API_Protocol
{
    class IProtocol
    {
    public:
	// /!\ to prevent errors, any exception in this API must be caught before destroying the loader
	virtual ~IProtocol() {};

	virtual void	send(const Srtp &data) = 0;
	virtual bool	receive(Srtp &data) = 0; // return true if data was received
    };

# if defined(WIN32) || defined (_WIN32)
    //  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# define LIB_SOCKET	"../API/DLLs/lib_API_Socket_Udp_Windows"
# elif defined(linux) || defined (__unix__)
    //  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# define LIB_SOCKET	"../API/SOs/lib_API_Socket_Udp_Unix.so"
# else
    //  do nothing and hope for the best?
# define EXPORT
# define IMPORT
# pragma warning Unknown dynamic link import/export semantics.
# endif
} // !namespace API_Protocol

// ISocket *protocol_server(const std::string &host, int svrPort, int localPort = 0)
// ISocket *protocol_client(int port)

#endif // !API_PROTOCOL_HPP_
