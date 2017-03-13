#ifndef PROTOCOLCLIENT_HPP_
# define PROTOCOLCLIENT_HPP_

# include "AProtocol.hpp"

namespace API_Protocol
{
  class ProtocolClient : public AProtocol
  {
  private:
    static const double	      checkReceiveTime;
    static const double	      checkSendTime;

    TimePoint		      lastReceive;
    TimePoint		      lastSend;

    uint16_t		      idPacket;
    uint16_t		      idAck;
    AckQueue		      ackQueue;

    bool		      checkReceive(Srtp &srtp);
    void		      checkSend();
    void		      ping();

    bool		      checkOrder(Header const &);
    void		      removeOrders(int);
    bool		      isWrapAround(uint16_t) const;

  public:
    ProtocolClient(int port, std::string const &hostName);
    virtual ~ProtocolClient();

    virtual void	      send(const Srtp &data);
    virtual bool	      receive(Srtp &data);
  };
}

#endif // !PROTOCOLCLIENT_HPP_