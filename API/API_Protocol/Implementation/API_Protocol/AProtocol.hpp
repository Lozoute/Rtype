#ifndef APROTOCOL_HPP_
# define APROTOCOL_HPP_

# include <cstdint>
# include <chrono>
# include "Loader.hpp"
# include "API_Protocol.hpp"
# include "API_Socket_Udp.hpp"
# include "Packet.hpp"

namespace API_Protocol
{
  class AProtocol : public IProtocol
  {
  protected:
    typedef std::chrono::time_point<std::chrono::system_clock> TimePoint;

    Loader					loader;
    std::shared_ptr<API_Socket_Udp::ISocket>	socket;
    bool					checkMagic(Header const &) const;
    bool					checkPing(Header const &) const;
    bool					checkPong(Header const &) const;
  public:
    static const std::string			apiSocketLib;

    AProtocol();
    virtual ~AProtocol() {}

    virtual void				send(const Srtp &data) = 0;
    virtual bool				receive(Srtp &data) = 0;
  };
}

#endif // !APROTOCOL_HPP_