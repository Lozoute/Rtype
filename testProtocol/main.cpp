#include <memory>
#include <iostream>
#include <thread>
#include <array>
#include "Loader.hpp"
#include "API_Protocol.hpp"
#include "API_Error.hpp"

# if defined(WIN32) || defined (_WIN32)
# define LIB_PROTO	"../API/DLLs/lib_API_Protocol.dll"
# else
# define LIB_PROTO	"../API/SOs/lib_API_Protocol.so"
# endif

std::ostream					&operator<<(std::ostream &os, const Srtp &srtp)
{
  static const std::array<std::string, 4>	ObjectType = { "Player", "Mob", "Boss", "Missile" };
  static const std::array<std::string, 11>	MobType = { "LittleShip", "BrownArmor", "Butterfly", "GreenArmor",
    "RedArmor", "MecaTurret", "MecaCrab", "Centiped", "Crab", "ShipMob", "Tentacle" };
  static const std::array<std::string, 3>	Proto = { "Connect", "Disconnect", "None" };
  static const std::array<std::string, 4>	Client = { "New", "Delete", "Attack", "Update" };

  if (srtp._cmdClient < Client.size() && srtp._cmdClient >= 0)
    os << "cmdClient: " << Client[srtp._cmdClient] << ' ';
  if (srtp._cmdProto < Proto.size() && srtp._cmdProto >= 0)
    os << "cmdProto: " << Proto[srtp._cmdProto] << ' ';
  if (srtp._mobType < MobType.size() && srtp._mobType >= 0)
    os << "mobType: " << MobType[srtp._mobType] << ' ';
  if (srtp._objType < ObjectType.size() && srtp._objType >= 0)
    os << "objectType: " << ObjectType[srtp._objType];
  return os;
}

void						testServer(Loader &loader)
{
  Srtp    srtp;
  std::shared_ptr<API_Protocol::IProtocol>	proto = loader.getSmartPtr<API_Protocol::IProtocol>(LIB_PROTO,
												    "protocol_server", 4242);
  int nbImp = 0;

  std::cout << "server" << std::endl;
  int i = 1;
  while (i)
  {
    if (proto->receive(srtp))
    {
      i++;
      // std::cout << "SENDING IMPORTANT MESSAGE " << ++nbImp << std::endl;
      srtp._cmdClient = static_cast<CmdClient>(i % 4);
      srtp._mobType = static_cast<MobType>(i % 11);
      srtp._objType = static_cast<ObjectType>(i % 4);
      std::cout << "sending " << srtp << std::endl;
      proto->send(srtp);
      srtp._cmdClient = CMDC_Attack;
    }
    /*else
    {
      if (proto->receive(srtp))
	std::cout << srtp << ' ' << i++ << std::endl;
      // proto->send(srtp);
    }*/
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
}

void						testClient(Loader &loader)
{
  Srtp    srtp;
  std::string	host = "127.0.0.1";
  std::shared_ptr<API_Protocol::IProtocol>	proto = loader.getSmartPtr<API_Protocol::IProtocol>(LIB_PROTO, "protocol_client",
												    4242, &host);

  std::cout << "client" << std::endl;
  srtp._cmdClient = CMDC_New;
  srtp._cmdProto = CMDP_Connect;
  std::cout << srtp << std::endl;
  int nbImp = 0;

  for (int i = 0; i < 25; i++)
  {
    proto->send(srtp);
    std::cout << "message sent" << std::endl;
    while (proto->receive(srtp))
    {
      std::cout << "send loop: " << srtp << std::endl;
      if (srtp._cmdClient == CMDC_Delete)
	nbImp++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  while (srtp._cmdProto != CMDP_Disconnect)
  {
    if (proto->receive(srtp))
    {
      std::cout << "received loop: " << srtp << std::endl;
      if (srtp._cmdClient == CMDC_Delete)
	nbImp++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  std::cout << "received " << nbImp << " importants messages" << std::endl;
}

int						main()
{
  Loader					loader;

  try
  {
    std::cout << "test server/client s/c" << std::endl;
    char c;
    while ((c = std::cin.get()) != 's' && c != 'c');
    while (std::cin.get() != '\n');
    if (c == 's')
      testServer(loader);
    else
      testClient(loader);
  }
  catch (const Error &e)
  {
    std::cerr << "error: " << e.toString() << std::endl;
  }
  std::cout << "test ok" << std::endl;
  while (std::cin.get() != '\n');
  return 0;
}
