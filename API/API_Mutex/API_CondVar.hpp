#ifndef API_CONDVAR_HPP_
# define API_CONDVAR_HPP_

# include <memory>
# include <mutex>

namespace API_Mutex
{
  class IMutex;
}

class ICondVar
{
public:
  virtual ~ICondVar		() {}

  virtual void			wait(std::shared_ptr<API_Mutex::IMutex> &) = 0;
  virtual void			wait(API_Mutex::IMutex *) = 0;
  virtual void			wait(API_Mutex::IMutex &) = 0;
  virtual void			notifyAll() = 0;
  virtual void			notifyOne() = 0;
};

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

#endif /* !API_CONDVAR_HPP_ */
