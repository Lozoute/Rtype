#ifndef SOCKETUDP_HPP_
# define SOCKETUDP_HPP_

# include "API_Socket_Udp.hpp"
# include "API_Mutex.hpp"
# include "Loader.hpp"

namespace API_Socket_Udp_Windows
{
    class SocketUdp : public API_Socket_Udp::ISocket
    {
    private:
	WSADATA				_wsaData;
	SOCKET				_sock;
	SOCKADDR_IN			_addrSvr;
	API_Socket_Udp::Mode		_mode;
	Loader				_loader;
	API_Mutex::IMutex		*_mutexSend;
	API_Mutex::IMutex		*_mutexReceive;
      void				setBlocking(bool mode);

	static const int		receiveFromFlags = 0;
	static const int		sendToFlags = 0;

    public:
	virtual ~SocketUdp();

	virtual API_Socket_Udp::Mode	getMode() const;

	// server
	SocketUdp::SocketUdp(int port);
	virtual std::size_t		sendTo(void *data, std::size_t dataSize,
	    const std::shared_ptr<const API_Socket_Udp::IAddress> &addrPtr);
	virtual std::size_t		receiveFrom(void *buff, std::size_t buffSize,
	    std::shared_ptr<API_Socket_Udp::IAddress> &addrPtr);

	// client
	SocketUdp::SocketUdp(const std::string &host, int svrPort, int localPort);
	virtual	std::size_t		send(const void *data, std::size_t dataSize);
	virtual	std::size_t		receive(void *buff, std::size_t buffSize);

	SocketUdp(const SocketUdp &other)				    = delete;
	SocketUdp			&operator=(const SocketUdp &other)  = delete;
    };
}

#endif // !SOCKETUDP_HPP_
