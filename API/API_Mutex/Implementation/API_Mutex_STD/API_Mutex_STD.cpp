#include "API_Mutex_STD.hpp"

using namespace API_Mutex_STD;

//
// CTOR, DTOR ETC
//

Mutex::Mutex				()
{}

Mutex::~Mutex				()
{}

//
// MUTEX MANIPULATIONS
//
bool					Mutex::lock()
{
  _Mutex.lock();
  return (true);
}

bool					Mutex::tryLock()
{
  return (_Mutex.try_lock());
}

bool					Mutex::try_lock()
{
  return (_Mutex.try_lock());
}

bool					Mutex::unLock()
{
  _Mutex.unlock();
  return (true);
}

bool					Mutex::unlock()
{
  _Mutex.unlock();
  return (true);
}

//
// API LOADING
//
extern "C" EXPORT API_Mutex::IMutex	*__API_Load__()
{
  return (new API_Mutex_STD::Mutex);
}
