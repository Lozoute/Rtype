# include <string>
# include <cstring>
# include "ProtocolClient.hpp"

using namespace API_Protocol;

const double	ProtocolClient::checkReceiveTime = 5;
const double	ProtocolClient::checkSendTime = 0.1;

ProtocolClient::ProtocolClient(int port, std::string const &hostName)
  : AProtocol(), idPacket(1), idAck(0)
{
  lastSend = lastReceive = std::chrono::system_clock::now();
  try
  {
    socket = AProtocol::loader.getSmartPtr<API_Socket_Udp::ISocket>(LIB_SOCKET, "socket_client", &hostName, port, 0);
  }
  catch (const Error &e)
  {
    throw Error(e.what(), e.who());
  }
}

ProtocolClient::~ProtocolClient()
{ }

void		ProtocolClient::send(const Srtp &data)
{
  Packet	packet;

  std::memset(&packet, 0, sizeof(Packet));
  lastSend = std::chrono::system_clock::now();
  packet.srtpL(data);
  packet.header.magic = MAGIC;
  packet.header.id_ack = idAck;
  packet.header.id_packet = idPacket++;
  packet.header.flag = 0;
  packet.header.padding = 0;
  packet.header.ack_queue = ackQueue;
  socket->send(&packet, sizeof(Packet));
}

bool		ProtocolClient::receive(Srtp &srtp)
{
  Packet	data;
  size_t	size;

  std::memset(&data, 0, sizeof(Packet));
  do
  {
    if ((size = socket->receive(&data, sizeof(Packet))) == sizeof(Packet))
    {
      if (!checkMagic(data.header) || !checkOrder(data.header))
	continue;
      data.srtpL.getSrtp(srtp);
      srtp._cmdProto = CMDP_None;
      lastReceive = std::chrono::system_clock::now();
      return true;
    }
    else if (size == sizeof(Header))
    {
      if (!checkMagic(data.header) || !checkOrder(data.header))
	continue;
      if (!checkPong(data.header))
	continue;
      lastReceive = std::chrono::system_clock::now();
    }
    else
      checkReceive(srtp);
  } while (size);
  checkSend();
  return false;
}

bool		ProtocolClient::checkReceive(Srtp &srtp)
{
  std::chrono::duration<double> diff = std::chrono::system_clock::now() - lastReceive;

  if (diff.count() > checkReceiveTime)
  {
    std::cout << "disconnected" << std::endl;
    srtp._cmdProto = CMDP_Disconnect;
    return true;
  }
  return false;
}

void		ProtocolClient::checkSend()
{
  std::chrono::duration<double> diff = std::chrono::system_clock::now() - lastSend;

  if (diff.count() > checkSendTime)
    ping();
}

void		ProtocolClient::ping()
{
  Header	hd;

  std::memset(&hd, 0, sizeof(Header));
  hd.magic = MAGIC;
  hd.ack_queue = ackQueue;
  hd.id_ack = idAck;
  hd.id_packet = idPacket++;
  hd.flag |= IS_PING;
  socket->send(&hd, sizeof(Header));
  lastSend = std::chrono::system_clock::now();
}

bool		ProtocolClient::isWrapAround(uint16_t packet) const{
  if (idAck > packet)
    return (idAck - packet > UINT16_MAX / 2);
  return (packet - idAck > UINT16_MAX / 2);
}

bool		ProtocolClient::checkOrder(Header const &header){
  if (!isWrapAround(header.id_packet)){
    if ((header.id_packet == idAck || header.id_packet < idAck - 33)
	&& !(header.flag & IS_PRIO))
	return false;
    if (header.id_packet > idAck){
      removeOrders(header.id_packet - idAck);
      idAck = header.id_packet;
      return true;
    }
    ackQueue(idAck - 1 - header.id_packet);
    return (header.flag & IS_PRIO);
  }
  int ack = idAck;
  if ((header.id_packet == idAck || header.id_packet > UINT16_MAX + ack - 33)
      && !(header.flag & IS_PRIO))
      return false;
  if (header.id_packet < idAck){
    removeOrders(UINT16_MAX - ack + header.id_packet);
    idAck = header.id_packet;
    return true;
  }
  ackQueue(UINT16_MAX + idAck - header.id_packet - 1);
  return (header.flag & IS_PRIO);
}

void				showBits_(uint32_t queue)
{
  uint32_t			b = 1;

  while (b)
  {
    std::cout << ((b & queue) != 0);
    b <<= 1;
  }
}

inline void	ProtocolClient::removeOrders(int nb){

  ackQueue.shift(nb);
}

extern "C" EXPORT IProtocol	*protocol_client(int port, std::string const *hostName)
{
  return (new ProtocolClient(port, *hostName));
}
