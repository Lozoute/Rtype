#ifndef API_THREAD_HPP
# define API_THREAD_HPP

# include "API_Error.hpp"

namespace API_Thread
{
  template <typename Func, typename... Arg>
  class IThread
  {
  public:
    virtual ~IThread() {}

    virtual bool init(Func, Arg...) = 0;
    virtual bool stop() = 0;
    virtual bool join() = 0;
  }; /* !class IThread */

} /* !namespace API_Thread */

# include "Implementation/API_Thread_STD/API_Thread_STD.hpp"

#endif /* !API_THREAD_HPP */
