#include "LogFile.hpp"
#include <fstream>
#include <string>

LogFile::LogFile()
{
  std::ifstream	  log(".conf");
  std::string	  buffer;
  std::size_t	  pos;

  if (!log.is_open()){
    _host = "127.0.0.1";
    _port = "4242";
    return;
  }
  std::getline(log, buffer);
  if (log.fail())
  {
    _host = "127.0.0.1";
    _port = "4242";
    return;
  }
  if ((pos = buffer.find("host = ")) != std::string::npos)
  {
    find_host(buffer);
    std::getline(log, buffer);
  }
  else
    _host = "127.0.0.1";
  if (log.fail()){
    _port = "4242";
    log.close();
    return;
  }
  find_port(buffer);
  log.close();
}

LogFile::~LogFile(){
  std::ofstream	  log(".conf");

  log << "host = " << _host << std::endl;
  log << "port = " << _port << std::endl;
  log.close();
}

void	  LogFile::find_host(std::string const &str){
  std::size_t	  pos;

  if ((pos = str.find_first_not_of("0123456789.", sizeof("host = "))) == std::string::npos){
    _host = str.substr(sizeof("host = ") - 1);
    return;
  }
    _host = str.substr(sizeof("host = ") - 1, pos - sizeof("host = "));
}

void	  LogFile::find_port(std::string const &str){
  std::size_t	  pos;

  if ((pos = str.find_first_not_of("0123456789", sizeof("port = "))) == std::string::npos){
    _port = str.substr(sizeof("port = ") - 1);
    return;
  }
    _port = str.substr(sizeof("port = ") - 1, pos - sizeof("port = "));
}

std::string const &LogFile::get_port() const{
  return _port;
}

std::string const &LogFile::get_host() const{
  return _host;
}

void  LogFile::set_port(std::string const &port){
  _port = port;
}

void  LogFile::set_host(std::string const &host){
  _host = host;
}

void  LogFile::set_port(int port){
  _port = std::to_string(port);
}