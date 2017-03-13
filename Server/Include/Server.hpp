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
# include "Player.hpp"
# include "GameEngine.hpp"
# include "PlayerShip.hpp"


/// Some Namespace
using namespace					API_Thread;
using namespace					API_Mutex;
using namespace					API_Protocol;


/// Some Variables
const auto					_NbThreadsReceive = 4;


/// Some Forward Declarations
class						Game;


/// Server Class
class						Server
{
public:
  typedef void					(Server::*ThreadF)();

private:
  typedef void					(Server::*CmdF)(const Srtp &);
  Loader					_Loader;
  GameEngine					_GameEngine;
  bool						_IsRunning;

  std::vector<Ptr<IThread<ThreadF, Server *>>>	_ReceiveThreads;

public:
  Server					();
  ~Server					();

  void						Start(const std::string &);
  void						Stop();

private:
  Server					(const Server &);
  Server					&operator=(const Server &);

  void						Receive();
  void						Treat(const Srtp &);
  void						TreatCmdProto(const Srtp &);
  void						TreatCmdClient(const Srtp &);
};

#endif /* !SERVER_HPP_ */
