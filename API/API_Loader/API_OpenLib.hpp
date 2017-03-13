//
// API_OpenLib.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 15:49:57 2015 jordan sabbah
// Last update Wed Jun 10 00:06:13 2015 jordan sabbah
//

#ifndef API_OPENLIB_HPP
# define API_OPENLIB_HPP

#include <string>
#include "API_Error.hpp"

class IOpenLib{
public:
  virtual ~IOpenLib(){}
  virtual bool			is_sym(std::string const &) const = 0;
  virtual void			*&get_sym(std::string const &) = 0;
  virtual void			push_sym(std::string const &) = 0;
  virtual std::string const	&get_name() const = 0;
};

# if  defined(_WIN32) || defined(WIN32)
#  include "OpenLib_Windows.hpp"
# elif defined(linux) || defined(__unix__)
#  include "OpenLib_Unix.hpp"
# endif

#endif // !API_OPENLIB_HPP
