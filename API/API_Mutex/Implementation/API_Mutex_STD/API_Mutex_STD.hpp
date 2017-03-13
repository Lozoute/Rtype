#ifndef API_MUTEX_STD_HPP_
# define API_MUTEX_STD_HPP_

# include <iostream>
# include <string>
# include <mutex>
# include "API_Mutex.hpp"

class CondVar;

namespace API_Mutex_STD
{
  class Mutex : public API_Mutex::IMutex
  {
  private:
    std::mutex				_Mutex;
  public:
    Mutex				();
    Mutex				(const Mutex &) = delete;
    Mutex				&operator=(const Mutex &) = delete;
    virtual ~Mutex			();

    virtual bool			lock();
    virtual bool			tryLock();
    virtual bool			unLock();
    virtual bool			try_lock();
    virtual bool			unlock();
  };

} /* !namespace API_Mutex_STD */

#endif /* !API_MUTEX_STD_HPP_ */
