#include "Server.hpp"

///
/// CTOR, DTOR ETC
///
Server::Server			(const Server &)
{}

Server				&Server::operator=(const Server &)
{
  return (*this);
}

Server::Server			()
				: _IsRunning(true)
{}

Server::~Server			()
{}

///
/// Initialization & Stop
///
void				Server::Start(const std::string &Port)
{
  std::stringstream		S;
  int				P;

  S << Port;
  S >> P;
  GetProto(_Loader.getPtr<IProtocol>(__LibProto, __LoadProto, P));
  for (unsigned int i = 0; i < _NbThreadsReceive; ++i)
    {
      Ptr<IThread<ThreadF, Server *>> Th(new Thread<ThreadF, Server *>);
      _ReceiveThreads.push_back(Th);
      if (!Th->init(&Server::Receive, this))
	throw Error("Unable To Init Thread", "Server::Start()");
      Th->join();
    }
}

void				Server::Stop()
{
  _IsRunning = false;
}

///
/// Threaded Receiving From API Protocol
///
void				Server::Receive()
{
  IProtocol			*Proto;
  Srtp				NewPacket;
  bool				Smth = false;

  if ((Proto = GetProto()))
    {
      while (1)
	{
	  while (!(Smth = Proto->receive(NewPacket)));
	  if (Smth)
	    this->Treat(NewPacket);
	}
    }
}

void				Server::Treat(const Srtp &P)
{
  if (P._cmdProto != CMDP_None)
    this->TreatCmdProto(P);
  else
    this->TreatCmdClient(P);
}

void				Server::TreatCmdProto(const Srtp &P)
{
  if (P._cmdProto == CMDP_Connect)
    _GameEngine.Join(P);
  else if (P._cmdProto == CMDP_Disconnect)
    _GameEngine.Quit(P);
}

void				Server::TreatCmdClient(const Srtp &P)
{
  _GameEngine.Treat(P);
}

///
/// WRAPPER
///
IProtocol			*GetProto(IProtocol *Obj)
{
  static IProtocol		*_Proto = nullptr;

  if (Obj)
    _Proto = Obj;
  return (_Proto);
}

void				SendPacket(const Srtp &P)
{
  IProtocol			*Proto;

  if ((Proto = GetProto()))
    {
      Proto->send(P);
    }
}
