#include "NetworkThread.hpp"
#include "Object.hpp"
#include "GraphEngine.hpp"

///
/// CTOR, DTOR ETC
///
NetworkThread::NetworkThread			(const NetworkThread &)
{}

NetworkThread				&NetworkThread::operator=(const NetworkThread &)
{
  return (*this);
}

NetworkThread::NetworkThread			(GraphEngine *graph)
  : _graphEngine(graph), _IsRunning(true)
{}

NetworkThread::~NetworkThread			()
{
}

///
/// Initialization & Stop
///
void				NetworkThread::Start(const std::string &port, std::string ip)
{
  std::stringstream		S;
  int				P;

  S << port;
  S >> P;
  GetProto(_Loader.getPtr<IProtocol>(LIB_PROTO, "protocol_client", P, &ip));
  _Th = Ptr<IThread<ThreadF, NetworkThread *>>(new Thread<ThreadF, NetworkThread *>);
  _ReceiveThreads.push_back(_Th);
  if (!_Th->init(&NetworkThread::Receive, this))
    throw Error("Unable To Init Thread", "NetworkThread::Start()");
}

void				NetworkThread::Stop()
{
  _IsRunning = false;
  _Th->join();
}

///
/// Threaded Receiving From API Protocol
///
void				NetworkThread::Receive()
{
  IProtocol			*Proto;
  Srtp				NewPacket;
  bool				Smth = false;

  if ((Proto = GetProto()))
    {
      while (_IsRunning)
	{
	  while ( _IsRunning && !(Smth = Proto->receive(NewPacket)));
	  if (Smth && _IsRunning)
	    {
   	      _graphEngine->receivePacket(NewPacket);
	    }
	}
    }
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
    Proto->send(P);

}
