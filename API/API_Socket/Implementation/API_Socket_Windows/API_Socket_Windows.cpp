# include "API_Socket_Windows.hpp"

using namespace API_Socket_Windows;
//
// Constructors...
//

Socket::Socket()
	: _read(false), _write(false)
{
	WSAStartup(MAKEWORD(2, 2), &(this->_wsaData));
}

Socket::Socket(SOCKET sock)
	: _sock(sock), _read(false), _write(false)
{
	this->_mode = API_Socket::CLIENT;
	WSAStartup(MAKEWORD(2, 2), &(this->_wsaData));
}

Socket::Socket(const Socket &other)
	: _sock(other._sock), _read(false), _write(false), _mode(other._mode)
{
	WSAStartup(MAKEWORD(2, 2), &(this->_wsaData));
}

Socket &Socket::operator=(const Socket &other)
{
	if (&other != this)
	{
		this->_sock = other._sock;
		this->_read = other._read;
		this->_write = other._write;
	}
	return (*this);
}

Socket::~Socket()
{
	closesocket(this->_sock);
	WSACleanup();
}

//
// INIT
//
void	Socket::Init(int port)
{
	SOCKADDR_IN		addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if ((this->_sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		throw API_Socket::Error("socket() failed", "Socket::Init");
	if ((bind(this->_sock, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr))) == SOCKET_ERROR)
		throw API_Socket::Error("Bind() fail", "Socket::init()");
	if ((listen(this->_sock, SOMAXCONN)) == SOCKET_ERROR)
		throw API_Socket::Error("listen() fail", "Socket::init()");
	this->_mode = API_Socket::SERVER;
}

void	Socket::Init(int port, const std::string &host)
{
	sockaddr_in		addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_port = htons(port);
	if ((this->_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		throw API_Socket::Error("Socket() fail", "Socket::Init()");
	if ((connect(this->_sock, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr))) == SOCKET_ERROR)
		throw API_Socket::Error("Connect() fail", "Socket::init()");
	this->_mode = API_Socket::CLIENT;
}

//
// BASIC FUNCTIONS
//
std::shared_ptr<API_Socket::ISocket>		Socket::Accept()
{
	SOCKET					New_client;

	if ((New_client = accept(this->_sock, NULL, NULL)) == INVALID_SOCKET)
		throw API_Socket::Error("accept() fail", "Socket_Server::accept()");
	return (std::shared_ptr<API_Socket::ISocket>(new API_Socket_Windows::Socket(New_client)));
}

std::size_t			Socket::Send(const void *data, std::size_t size)
{
	int		res;

	if ((res = send(this->_sock, static_cast<const char *>(data), size, 0)) == SOCKET_ERROR)
		return (0);
	return (res);
}

std::size_t			Socket::Receive(void *data, std::size_t size)
{
	int		res;

	if ((res = recv(this->_sock, static_cast<char *>(data), size, 0)) == SOCKET_ERROR)
		return (0);
	return (res);
}

//
// GETTERS
//

bool Socket::IsReadable() const
{
	return (this->_read);
}

bool Socket::IsWritable() const
{
	return (this->_write);
}

API_Socket::Mode	Socket::GetMode() const
{
	return (this->_mode);
}

//
// POLL
//

/* Functor !! */
template<typename T>
struct OnYourKnees
{
	std::shared_ptr<T> operator ()(std::shared_ptr<API_Socket::ISocket> value) const
	{ 
		return std::dynamic_pointer_cast<T>(value); 
	} 
};

int	Socket::Poll(std::vector<std::shared_ptr<API_Socket::ISocket>> &BeadTAB, std::vector<std::shared_ptr<API_Socket::ISocket>> &BriteTAB)
{
	std::vector<std::shared_ptr<Socket>>			ReadTAB(BeadTAB.size());
	std::vector<std::shared_ptr<Socket>>			WriteTAB(BriteTAB.size());
	std::vector<std::shared_ptr<Socket>>::iterator it;
	int								Res;
	int								MaxFd = 0;
	fd_set							ReadSET;
	fd_set							WriteSET;
	struct timeval					Tv = { 2, 0 };

	std::transform(BeadTAB.begin(), BeadTAB.end(), ReadTAB.begin(), OnYourKnees<Socket>());
	std::transform(BriteTAB.begin(), BriteTAB.end(), WriteTAB.begin(), OnYourKnees<Socket>());

	FD_ZERO(&ReadSET);
	FD_ZERO(&WriteSET);
	for (it = ReadTAB.begin(); it != ReadTAB.end(); ++it)
		FD_SET((*it)->_sock, &ReadSET);
	for (it = WriteTAB.begin(); it != WriteTAB.end(); ++it)
		FD_SET((*it)->_sock, &WriteSET);
	if ((Res = select(MaxFd, &ReadSET, &WriteSET, NULL, &Tv)) == SOCKET_ERROR)
		throw API_Socket::Error("Select Failed", "Socket::Poll");
	for (it = ReadTAB.begin(); it != ReadTAB.end(); ++it)
	{
		if (FD_ISSET((*it)->_sock, &ReadSET))
			(*it)->_read = true;
		else
			(*it)->_read = false;
	}
	for (it = WriteTAB.begin(); it != WriteTAB.end(); ++it)
	{
		if (FD_ISSET((*it)->_sock, &WriteSET))
			(*it)->_write = true;
		else
			(*it)->_write = false;
	}
	return (Res);
}

//
// API GENERATION
//
extern "C" __declspec(dllexport) API_Socket::ISocket *__API_Load__(void)
{
	return (new API_Socket_Windows::Socket);
}