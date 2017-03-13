#ifndef API_SOCKET_HPP_
# define API_SOCKET_HPP_

# include <iostream>
# include <string>
# include <stdexcept>
# include <vector>
# include <memory>

namespace API_Socket
{
	typedef enum Mode
	{
		SERVER = 0,
		CLIENT = 1,
	} Mode;

  // Server Interface
class ISocket
  {
  public:


    virtual ~ISocket	() {};

    virtual void				Init(int) = 0;
	virtual void				Init(int, const std::string &) = 0;
	virtual std::shared_ptr<ISocket>		Accept() = 0;

	virtual std::size_t			Send(const void *, std::size_t) = 0;
	virtual std::size_t			Receive(void *, std::size_t) = 0;

	virtual int					Poll(std::vector<std::shared_ptr<ISocket>> &, std::vector<std::shared_ptr<ISocket>> &) = 0;
	virtual bool				IsReadable() const = 0;
	virtual bool				IsWritable() const = 0;

	virtual API_Socket::Mode	GetMode() const = 0;

  }; /* !class ISocket_Server */



  // Socket Exception
  class Error : public std::exception
  {
    std::string const			_what;
    std::string const			_who;

  public:
    Error						() throw() {};
    Error						&operator=(Error const &) throw() {return (*this);};
    Error						(Error const &) throw() {};
    virtual ~Error				() throw() {};

    Error			(std::string const &wa, std::string const &wo) throw()
      : _what(wa), _who(wo) {};

    virtual const char	*what(void) const throw()
    {
      return (_what.c_str());
    }
    const char	*	who(void) const throw()
    {
      return (_who.c_str());
    }
  }; /* ! class Error */

} /* !namespace API_Socket */

//
// DO NOT FORGET TO ADD AN 'extern "c"' FUNCTION IN YOUR IMPLEMENTATION
//

#endif /* !API_SOCKET_HPP_ */
