//
// SpinLock.hpp for  in /home/sabbah_j/rendu/TEK3/rtype/API/API_Mutex
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Fri Jul 24 02:57:51 2015 jordan sabbah
// Last update Fri Jul 24 12:21:21 2015 jordan sabbah
//

#ifndef SPINLOCK_HPP_
# define SPINLOCK_HPP_

# include "API_Mutex.hpp"
# include <atomic>

class SpinLock : public API_Mutex::IMutex{
private:
  std::atomic_flag	_lock = ATOMIC_FLAG_INIT;
public:
  SpinLock(){}
  ~SpinLock(){}
  SpinLock(SpinLock const &) = delete;
  SpinLock &operator=(SpinLock const &) = delete;
  bool	lock(){
    while (_lock.test_and_set(std::memory_order_acquire));
    return true;
  }
  bool	unlock(){
    _lock.clear(std::memory_order_release);
    return true;
  }
  bool	try_lock(){
    return !_lock.test_and_set(std::memory_order_acquire);
  }
  bool	unLock(){
    _lock.clear(std::memory_order_release);
    return true;
  }
  bool	tryLock(){
    return !_lock.test_and_set(std::memory_order_acquire);
  }
};

# endif // !SPINLOCK_HPP_
