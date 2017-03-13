#ifndef PROTOCOLSERVER_HPP_
# define PROTOCOLSERVER_HPP_

# include <string>
# include <map>
# include "AProtocol.hpp"
# include "ClientInfo.hpp"

namespace API_Protocol
{
  class ProtocolServer : public AProtocol
  {
  private:
    typedef std::shared_ptr<API_Socket_Udp::IAddress>	AddrPtr;

    static const double					checkReceiveTime;

    std::map<std::string, int>				addresses;
    std::map<int, ClientInfo>				clients;
    int							idClient;

    TimePoint						lastCheckReceive;

    bool						checkReceive(Srtp &srtp);
    void						pong(const AddrPtr &addrPtr, ClientInfo *);

  public:
    ProtocolServer(int port);
    virtual ~ProtocolServer();

    virtual void					send(const Srtp &data);
    virtual bool					receive(Srtp &data);
  };
}

#endif // !PROTOCOLSERVER_HPP_