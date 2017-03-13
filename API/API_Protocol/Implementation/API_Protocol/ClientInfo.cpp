#include "ClientInfo.hpp"
#include "API_Error.hpp"

const double			ClientInfo::timeout = 5;

ClientInfo::ClientInfo(AddrPtr &addr)
  : _addr(addr), _lastTime(std::chrono::system_clock::now()), _idPacket(1), _idAck(0)
{ }

ClientInfo::~ClientInfo()
{ }

const ClientInfo::AddrPtr	&ClientInfo::getAddr() const
{
    return _addr;
}

bool				ClientInfo::isTimeout() const
{
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - _lastTime;
    return diff.count() > timeout;
}

void				ClientInfo::updateHeader(Header &hd)
{
  hd.ack_queue = _ackQueue;
  hd.id_ack = _idAck;
  hd.id_packet = _idPacket++;
}

void				ClientInfo::addImportant(const Packet &p)
{
  _importantPackets.push_back(p);
}

bool				ClientInfo::isWrapAround(uint16_t packet) const{
  if (_idAck > packet)
    return (_idAck - packet > UINT16_MAX / 2);
  return (packet - _idAck > UINT16_MAX / 2);
}


bool				ClientInfo::isWrapAround(uint16_t a, uint16_t b) const
{
  uint16_t			diff = (a > b) ? (a - b) : (b - a);
  return (diff > UINT16_MAX / 2);
}

bool				ClientInfo::checkOrder(Header const &header, SocketPtr &sock){
  if (!isWrapAround(header.id_packet)){
    if ((header.id_packet == _idAck || header.id_packet < _idAck - 33)
	&& !(header.flag & IS_PRIO))
	return false;
    if (header.id_packet > _idAck){
      removeOrders(header.id_packet - _idAck, sock, header);
      _idAck = header.id_packet;
      return true;
    }
    _ackQueue(_idAck - 1 - header.id_packet);
    return (header.flag & IS_PRIO) != 0;
  }
  int ack = _idAck;
  if ((header.id_packet == _idAck || header.id_packet > UINT16_MAX + ack - 33)
      && !(header.flag & IS_PRIO))
      return false;
  if (header.id_packet < _idAck){
    removeOrders(UINT16_MAX - ack + header.id_packet, sock, header);
    _idAck = header.id_packet;
    return true;
  }
  _ackQueue(UINT16_MAX + _idAck - header.id_packet - 1);
  return (header.flag & IS_PRIO) != 0;
}

void				showBits(uint32_t queue)
{
  uint32_t			b = 1;

  while (b)
  {
    std::cout << ((b & queue) != 0);
    b <<= 1;
  }
}

void				ClientInfo::removeOrders(int nb, SocketPtr &sock, Header const &header){
  uint16_t			lastAck = header.id_ack - 32;

  for (auto it = _importantPackets.begin();
       it != _importantPackets.end() && it->header.id_packet - header.id_ack < 32;)
  {
    if ((!isWrapAround(it->header.id_packet, lastAck) && it->header.id_packet < lastAck)
	|| (isWrapAround(it->header.id_packet, lastAck) && it->header.id_packet > lastAck))
    {
      updateHeader(it->header);
      try
      {
	sock->sendTo(&(*it), sizeof(Packet), _addr);
	_importantPackets.push_back(*it);
      }
      catch (const Error &)
      {
      }
      it = _importantPackets.erase(it);
    }
    else if (header.ack_queue[header.id_ack - it->header.id_packet - 1]
	     || it->header.id_packet == header.id_ack)
      it = _importantPackets.erase(it);
    else
      ++it;
  }
  _ackQueue.shift(nb);
}


void				ClientInfo::updateTime()
{
    _lastTime = std::chrono::system_clock::now();
}