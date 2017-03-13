#ifndef API_MUTEX_HPP_
# define API_MUTEX_HPP_

# include <iostream>
# include <string>
# include "API_Error.hpp"

namespace API_Mutex
{
  class IMutex
  {
  public:
    virtual ~IMutex			() {}

    virtual bool			lock() = 0;
    virtual bool			tryLock() = 0;
    virtual bool			try_lock() = 0;
    virtual bool			unLock() = 0;
    virtual bool			unlock() = 0;
  }; /* !class IMutex */

# if defined(WIN32) || defined (_WIN32)
  //  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# elif defined(linux) || defined (__unix__)
  //  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# else
  //  do nothing and hope for the best?
# define EXPORT
# define IMPORT
# pragma warning Unknown dynamic link import/export semantics.
# endif
}

#endif /* !API_MUTEX_HPP_ */
