# include "API_Socket_Unix.hpp"

using namespace API_Socket_Unix;


//
// Constructors...
//
Socket::Socket				()
	: _read(false), _write(false)
{}

Socket::Socket				(int sock)
	: _sock(sock), _read(false), _write(false)
{
	this->_mode = API_Socket::CLIENT;
}

Socket::Socket				(const Socket &other)
	: _sock(other._sock), _read(false), _write(false), _mode(other._mode)
{}

Socket &				Socket::operator=(const Socket &other)
{
	if (&other != this)
	{
		this->_sock = other._sock;
		this->_read = other._read;
		this->_write = other._write;
		this->_mode = other._mode;
	}
	return (*this);
}

Socket::~Socket				()
{
	close(this->_sock);
}


//
// INIT
//
void					Socket::Init(int port)
{
  struct sockaddr_in			addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(port);
  if ((this->_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    throw API_Socket::Error("socket() failed", "Socket::Init");
  if ((bind(this->_sock, reinterpret_cast<const struct sockaddr *>(&addr), sizeof(addr))) == -1)
    throw API_Socket::Error("Bind() fail", "Socket::init()");
  if ((listen(this->_sock, SOMAXCONN)) == -1)
    throw API_Socket::Error("listen() fail", "Socket::init()");
  this->_mode = API_Socket::SERVER;
}

void					Socket::Init(int port, const std::string &host)
{
  struct sockaddr_in			addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(host.c_str());
  addr.sin_port = htons(port);
  if ((this->_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    throw API_Socket::Error("Socket() fail", "Socket::Init()");
  if ((connect(this->_sock, reinterpret_cast<const struct sockaddr *>(&addr), sizeof(addr))) == -1)
    throw API_Socket::Error("Connect() fail", "Socket::init()");
  this->_mode = API_Socket::CLIENT;
}


//
// BASIC FUNCTIONS
//
std::shared_ptr<API_Socket::ISocket>	Socket::Accept()
{
  int					New_client;
  socklen_t				len;
  struct sockaddr_in			addr;

  if ((New_client = accept(this->_sock, reinterpret_cast<struct sockaddr *>(&addr), &len)) == -1)
    throw API_Socket::Error("accept() fail", "Socket_Server::accept()");
  return (std::shared_ptr<API_Socket::ISocket>(new API_Socket_Unix::Socket(New_client)));

}

std::size_t				Socket::Send(const void *data, std::size_t size)
{
  int					res;

  if ((res = send(this->_sock, data, size, 0)) == -1)
    return (0);
  return (res);
}

std::size_t			Socket::Receive(void *data, std::size_t size)
{
  int				res;

  if ((res = recv(this->_sock, data, size, 0)) == -1)
    return (0);
  return (res);
}


//
// GETTERS
//
bool				Socket::IsReadable() const
{
  return (this->_read);
}

bool				Socket::IsWritable() const
{
  return (this->_write);
}

API_Socket::Mode		Socket::GetMode() const
{
  return (this->_mode);
}


//
// POLL
//
void				Socket::Bigger(int *MaxFd,
					       const std::vector<std::shared_ptr<Socket>> &ReadTAB,
					       const std::vector<std::shared_ptr<Socket>> &WriteTAB) const
{
  std::vector<std::shared_ptr<Socket>>::const_iterator it;

  for (it = ReadTAB.begin(); it != ReadTAB.end(); ++it)
    if (*MaxFd < (*it)->_sock)
      *MaxFd = (*it)->_sock;
  for (it = WriteTAB.begin(); it != WriteTAB.end(); ++it)
    if (*MaxFd < (*it)->_sock)
      *MaxFd = (*it)->_sock;
}


/* Functor ! */
template<typename T>
struct OnYourKnees
{
	std::shared_ptr<T> operator ()(std::shared_ptr<API_Socket::ISocket> value) const
	{
		return std::dynamic_pointer_cast<T>(value);
	}
};


int				Socket::Poll(std::vector<std::shared_ptr<ISocket>> &BeadTAB,
					     std::vector<std::shared_ptr<ISocket>> &BriteTAB)
{
	std::vector<std::shared_ptr<Socket>>		ReadTAB(BeadTAB.size());
	std::vector<std::shared_ptr<Socket>>		WriteTAB(BriteTAB.size());
	std::vector<std::shared_ptr<Socket>>::iterator it;
	int						Res;
	int						MaxFd = 0;
	fd_set						ReadSET;
	fd_set						WriteSET;
	struct timeval					Tv = {2, 0};

	std::transform(BeadTAB.begin(), BeadTAB.end(), ReadTAB.begin(), OnYourKnees<Socket>());
	std::transform(BriteTAB.begin(), BriteTAB.end(), WriteTAB.begin(), OnYourKnees<Socket>());

	this->Bigger(&MaxFd, ReadTAB, WriteTAB);
	FD_ZERO(&ReadSET);
	FD_ZERO(&WriteSET);
	for (it = ReadTAB.begin(); it != ReadTAB.end(); ++it)
		FD_SET((*it)->_sock, &ReadSET);
	for (it = WriteTAB.begin(); it != WriteTAB.end(); ++it)
		FD_SET((*it)->_sock, &WriteSET);
	if ((Res = select(++MaxFd, &ReadSET, &WriteSET, NULL, &Tv)) == -1)
		throw API_Socket::Error("Select Failed", "Socket::Poll");
	for (it = ReadTAB.begin(); it != ReadTAB.end(); ++it)
	{
	  if (FD_ISSET(static_cast<std::shared_ptr<Socket>>((*it))->_sock, &ReadSET))
	    (*it)->_read = true;
	  else
	    (*it)->_read = false;
	}
	for (it = WriteTAB.begin(); it != WriteTAB.end(); ++it)
	{
	  if (FD_ISSET(static_cast<std::shared_ptr<Socket>>((*it))->_sock, &WriteSET))
	    (*it)->_write = true;
	  else
	    (*it)->_write = false;
	}
	return (Res);
}


//
// API GENERATION
//
extern "C"			API_Socket::ISocket *__API_Load__(void)
{
  return (new API_Socket_Unix::Socket);
}
