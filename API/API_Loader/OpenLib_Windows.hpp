//
// OpenLib_Windows.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 16:38:36 2015 jordan sabbah
// Last update Wed Jun 10 00:06:38 2015 jordan sabbah
//

#ifndef OPENLIB_WINDOWS_HPP
# define OPENLIB_WINDOWS_HPP

# include <string>
# include <utility>
# include <list>
# include <Windows.h>
# include <Winbase.h>
# include "API_OpenLib.hpp"

class OpenLib : public IOpenLib{
private:
    typedef std::pair<std::string const, void *> pair;
    std::list<pair>		_syms;
    std::string const		_name;
    HMODULE			_libHandle;
public:
    OpenLib(std::string const &name) : _name(name), _libHandle(NULL)
    {
	if (!(_libHandle = LoadLibraryA((name.c_str()))))
	    throw Error("Windows LoadLibrary failed", "OpenLib(std::string const &)");
    }

    virtual ~OpenLib(){
	if (!FreeLibrary(_libHandle))
	    throw Error("FreeLibrary", "Loader Windows");
    }

    OpenLib(OpenLib const &){
	throw Error("should not call this function", "OpenLib(OpenLib const &)");
    }

    OpenLib &operator=(OpenLib const &){}

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

	if (!(tmp_handler = GetProcAddress(_libHandle, name.c_str())))
	    throw Error("Windows GetProcAddress failed", "void push_sym(std::string const &)");
	_syms.push_back(pair(name, tmp_handler));
    }

    virtual std::string const	&get_name() const{
	return _name;
    }

};

# endif // !OPENLIB_WINDOWS_HPP
