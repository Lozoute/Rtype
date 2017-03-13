//
// OpenLib_Unix.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 15:58:52 2015 jordan sabbah
// Last update Fri Jul 17 00:49:35 2015 jordan sabbah
//

#ifndef OPENLIB_UNIX_HPP
# define OPENLIB_UNIX_HPP

# include <string>
# include <utility>
# include <list>
# include <dlfcn.h>
# include "API_OpenLib.hpp"

class OpenLib : public IOpenLib{
private:
  typedef std::pair<std::string const, void *> pair;
  std::list<pair>		_syms;
  std::string const		_name;
  void				*_libHandle;
public:
  OpenLib(std::string const &name)  : _name(name), _libHandle(NULL)
{
  dlerror();
  if (!(_libHandle = dlopen(name.c_str(), RTLD_LAZY)))
    throw Error(dlerror(), "OpenLib(std::string const &)");
}

  virtual ~OpenLib(){
  dlclose(_libHandle);
}

  OpenLib(OpenLib const &){
	throw Error("should not have called this function", "OpenLib(OpenLib const &)");
}

  OpenLib &operator=(OpenLib const &){
	throw Error("should not have called this function", "OpenLib(OpenLib const &)");
}

  virtual bool			is_sym(std::string const &name) const{
  for (std::list<pair>::const_iterator it = _syms.begin(); it != _syms.end(); ++it){
    if (it->first == name)
      return true;
  }
  return false;
}

  virtual void			*&get_sym(std::string const &name){
    std::list<pair>::iterator it;
  for (it = _syms.begin(); it != _syms.end(); ++it){
    if (it->first == name)
      return (it->second);
  }
  push_sym(name);
  return _syms.back().second;
}

  virtual void			push_sym(std::string const &name){
  void	*tmp_handler = NULL;

  tmp_handler = dlsym(_libHandle, name.c_str());
  if (!tmp_handler)
    throw Error("dlsym failed", "void push_sym(std::string const &)");
  _syms.push_back(pair(name, tmp_handler));
}

  virtual std::string const	&get_name() const{
  return _name;
}

};

#endif // !OPENLIB_UNIX_HPP
