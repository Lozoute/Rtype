#ifndef LOGFILE_HPP_
# define LOGFILE_HPP_

# include <string>

class LogFile{
private:
  std::string	    _host;
  std::string	    _port;
  void		    find_host(std::string const &);
  void		    find_port(std::string const &);
public:
  LogFile();
  ~LogFile();
  LogFile(LogFile const &) = delete;
  LogFile	    &operator=(LogFile const &) = delete;
  std::string const &get_host() const;
  std::string const &get_port() const;
  void		    set_host(std::string const &);
  void		    set_port(std::string const &);
  void		    set_port(int);
};

#endif // !LOGFILE_HPP_