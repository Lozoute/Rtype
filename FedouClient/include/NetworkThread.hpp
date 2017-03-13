#ifndef SERVER_HPP_
# define SERVER_HPP_

# include <iostream>
# include <string>
# include <vector>
# include <queue>
# include <memory>
# include <chrono>
# include <sstream>
# include "API_Error.hpp"
# include "Loader.hpp"
# include "API_Thread.hpp"
# include "API_Mutex.hpp"
# include "API_Protocol.hpp"
# include "Srtp.hpp"
# include "GraphEngine.hpp"

# if defined(WIN32) || defined (_WIN32)
# define LIB_PROTO      "../API/DLLs/lib_API_Protocol.dll"
# else
# define LIB_PROTO      "../API/SOs/lib_API_Protocol.so"
# endif

API_Protocol::IProtocol *GetProto(API_Protocol::IProtocol *Obj = nullptr);

/* Well I Find std::shared_ptr Too Long */
template <typename T>
using Ptr = std::shared_ptr<T>;


/// Some Namespace
using namespace					API_Thread;
using namespace					API_Mutex;
using namespace					API_Protocol;


/// Some Variables
const auto					_NbThreadsReceive = 1;

class GraphEngine;

/// NetworkThread Class
class						NetworkThread
{
public:
  typedef void					(NetworkThread::*ThreadF)();

private:
  typedef void					(NetworkThread::*CmdF)(const Srtp &);
  Loader					_Loader;
  GraphEngine					*_graphEngine;
  bool						_IsRunning;
  Ptr<IThread<ThreadF, NetworkThread *>>        _Th;
  std::vector<Ptr<IThread<ThreadF, NetworkThread *>>>	_ReceiveThreads;

public:
  NetworkThread					(GraphEngine *);
  ~NetworkThread					();

  void						Start(const std::string &, std::string);
  void						Stop();

private:
  NetworkThread					(const NetworkThread &);
  NetworkThread					&operator=(const NetworkThread &);

  void						Receive();
};

void				SendPacket(const Srtp &P);

#endif /* !SERVER_HPP_ */
