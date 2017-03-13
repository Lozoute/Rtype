#include <iostream>
#include <string>
#include "API_CondVar_STD.hpp"
#include "API_Mutex_STD.hpp"
#include "API_Error.hpp"

//
// CTOR, DTOR ETC
//
CondVar::CondVar		()
{}

CondVar::~CondVar()
{}

//
// CONDVAR MANIPULATIONS
//
void				CondVar::wait(API_Mutex::IMutex *mutex)
{
  Lock				lock(*mutex);
  _Cv.wait(lock);
}


void				CondVar::wait(API_Mutex::IMutex &mutex)
{
  Lock				lock(mutex);
  _Cv.wait(lock);
}

void				CondVar::wait(std::shared_ptr<API_Mutex::IMutex> &mutex)
{
  API_Mutex::IMutex		*ptr = mutex.get();
  Lock				lock(*ptr);
  _Cv.wait(lock);
}

void				CondVar::notifyAll()
{
  _Cv.notify_all();
}

void				CondVar::notifyOne()
{
  _Cv.notify_one();
}

//
// API LOADING
//
extern "C" EXPORT ICondVar	*get_CondVar()
{
  return (new CondVar);
}
