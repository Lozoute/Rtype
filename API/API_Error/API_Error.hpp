//
// Error.hpp for  in /home/sabbah_j/rendu/TEK2/B5-AdvancedCPP/rtype
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jun  6 23:44:50 2015 jordan sabbah
// Last update Sun Jun  7 12:58:52 2015 jordan sabbah
//

#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <stdexcept>
# include <string>

class Error : public std::exception {
private:
  std::string const	_what;
  std::string const	_who;

public:
	Error(){}
	Error(Error const &){}
	Error(std::string const &what, std::string const &who) : _what(what), _who(who) {}
	Error			&operator=(Error const &){ return *this; }
	~Error() throw(){}
	virtual const char	*what() const throw(){ return _what.c_str(); }
	const char		*who() const throw(){ return _who.c_str(); }
	std::string		toString() const { return _what + " in " + _who; }
};

#endif // !ERROR_HPP_
