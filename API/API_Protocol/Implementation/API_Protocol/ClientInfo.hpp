#ifndef CLIENTINFO_HPP_
# define CLIENTINFO_HPP_

# include <memory>
# include <chrono>
# include <list>
# include "API_Socket_Udp.hpp"
# include "Packet.hpp"
# include "AckQueue.hpp"

class						    ClientInfo
{
public:
  typedef std::shared_ptr<API_Socket_Udp::IAddress> AddrPtr;
  typedef std::shared_ptr<API_Socket_Udp::ISocket>  SocketPtr;
  typedef std::chrono::system_clock::time_point	    TimePoint;

private:
  static const double				    timeout;
  AddrPtr					    _addr;
  TimePoint					    _lastTime;
  std::list<Packet>				    _importantPackets;

  uint16_t					    _idPacket;
  uint16_t					    _idAck;
  AckQueue					    _ackQueue;

public:
  ClientInfo(AddrPtr &addr);
  ~ClientInfo();

  const AddrPtr					    &getAddr() const;
  bool						    isTimeout() const;
  void						    updateTime();

  void						    updateHeader(Header &);
  void						    addImportant(const Packet &);
  bool						    checkOrder(Header const &, SocketPtr &);
  void						    removeOrders(int, SocketPtr &, Header const &);
  bool						    isWrapAround(uint16_t) const;
  bool						    isWrapAround(uint16_t, uint16_t) const;

  ClientInfo() = delete;
  ClientInfo	operator=(const ClientInfo &other) = delete;
};

#endif // !CLIENTINFO_HPP_