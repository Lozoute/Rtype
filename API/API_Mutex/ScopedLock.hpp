# ifndef SCOPEDLOCK_HPP_
# define SCOPEDLOCK_HPP_

# include "API_Mutex.hpp"

class ScopedLock
{
private:
  API_Mutex::IMutex      &_mutex;
public:
  ScopedLock(API_Mutex::IMutex &mutex)
    : _mutex(mutex)
  {
    _mutex.lock();
  }
  ScopedLock &operator=(ScopedLock const &) = delete;
  ScopedLock(ScopedLock const &) = delete;
  ~ScopedLock(){
    _mutex.unLock();
  }
};

#endif //!SCOPEDLOCK_HPP_
