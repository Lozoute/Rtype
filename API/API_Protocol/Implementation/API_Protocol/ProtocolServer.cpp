#include "ProtocolServer.hpp"
#include <cstring>

using namespace API_Protocol;

const double	ProtocolServer::checkReceiveTime = 4;

ProtocolServer::ProtocolServer(int port)
  : AProtocol(), idClient(0)
{
  lastCheckReceive = std::chrono::system_clock::now();
  try
  {
    socket = loader.getSmartPtr<API_Socket_Udp::ISocket>(LIB_SOCKET, "socket_server", port);
  }
  catch (const Error &e)
  {
    throw Error(e.what(), e.who());
  }
}

ProtocolServer::~ProtocolServer()
{ }

void		ProtocolServer::send(const Srtp &data)
{
  Packet	packet;
  bool		prio = (data._cmdClient == CMDC_Delete || data._cmdClient == CMDC_New);

  std::memset(&packet, 0, sizeof(Packet));
  packet.srtpL(data);
  packet.header.magic = MAGIC;
  packet.header.flag = prio ? IS_PRIO : 0;
  packet.header.padding = 0;
  try
  {
    ClientInfo	&client = clients.at(data._idDest);
    client.updateHeader(packet.header);
    if (prio)
      client.addImportant(packet);
    socket->sendTo(&packet, sizeof(Packet), client.getAddr());
  }
  catch (const std::out_of_range &) {}
  {
    // throw Error("id not found", "ProtocolServer::sendServer");
  }
}

bool		ProtocolServer::receive(Srtp &srtp)
{
  Packet	data;
  std::string	addrStr;
  AddrPtr	addrPtr;
  size_t	size;

  if (checkReceive(srtp))
    return true;
  srtp._cmdProto = CMDP_None;
  do
  {
    if ((size = socket->receiveFrom(&data, sizeof(Packet), addrPtr)) >= sizeof(Header))
    {
      if (!checkMagic(data.header))
	continue;
      data.srtpL.getSrtp(srtp);
      addrStr = addrPtr->toString();
      int	  id;
      ClientInfo  *client;
      try
      {
	id = addresses.at(addrStr);
	client = &clients.at(id);
	client->updateTime();
	srtp._cmdProto = CMDP_None;
	srtp._idDest = id;
      }
      catch (const std::out_of_range &)
      {
	id = idClient++;
	std::cout << "new connection(" << id << ") " << addrStr << std::endl;
	addresses.insert(std::pair<std::string, int>(addrStr, id));
	clients.insert(std::pair<int, ClientInfo>(id, ClientInfo(addrPtr)));
	client = &clients.at(id);
	srtp._cmdProto = CMDP_Connect;
	srtp._idDest = id;
	return true;
      }
      if (!client->checkOrder(data.header, socket))
	continue;
      if (size == sizeof(Packet))
	return true;
      if (checkPing(data.header))
	pong(addrPtr, client);
    }
  } while (size);
  return false;
}

bool		ProtocolServer::checkReceive(Srtp &srtp)
{
  std::chrono::duration<double> diff = std::chrono::system_clock::now() - lastCheckReceive;

  if (diff.count() > checkReceiveTime)
  {
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
      if (it->second.isTimeout())
      {
	std::cout << it->second.getAddr()->toString() << " disconnected" << std::endl;
	srtp._idDest = it->first;
	srtp._cmdProto = CMDP_Disconnect;
	addresses.erase(it->second.getAddr()->toString());
	clients.erase(it);
	return true;
      }
    }
    lastCheckReceive = std::chrono::system_clock::now();
  }
  return false;
}


void		ProtocolServer::pong(const AddrPtr &addrPtr, ClientInfo *client)
{
  Header	hd;

  std::memset(&hd, 0, sizeof(Header));
  hd.magic = MAGIC;
  client->updateHeader(hd);
  hd.flag |= IS_PONG;
  socket->sendTo(&hd, sizeof(Header), addrPtr);
}

extern "C" EXPORT IProtocol	*protocol_server(int port)
{
  return (new ProtocolServer(port));
}
