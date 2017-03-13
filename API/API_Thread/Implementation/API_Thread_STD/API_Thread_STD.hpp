#ifndef API_THREAD_STD_HPP
# define API_THREAD_STD_HPP

# include <iostream>
# include <string>
# include <thread>
# include "API_Thread.hpp"

template <typename Func, typename... Arg>
class Thread : public API_Thread::IThread<Func, Arg...>
{
private:
  std::thread				*_thread;

  Thread(const Thread &) {}
  Thread &operator=(const Thread &) { return *this; }

public:
  Thread() : _thread(nullptr) {}

  virtual ~Thread() {}

  virtual bool init(Func f, Arg... arg)
  {
    if (this->_thread != nullptr)
      this->stop();
    this->_thread = new std::thread(f, arg...);
    return (this->_thread != nullptr);
  }
  virtual bool stop()
  {
    if (_thread == nullptr)
      return (false);
    _thread->detach();
    delete (_thread);
    _thread = nullptr;
    return (true);
    }
  virtual bool join()
  {
    if (_thread == nullptr)
      return (false);
    this->_thread->join();
    return (true);
  }
};

#endif /* !API_THREAD_STD_HPP */
