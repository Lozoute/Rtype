#ifndef API_CONDVARSTD_HPP_
# define API_CONDVARSTD_HPP_

# include "API_CondVar.hpp"
# include <condition_variable>

class CondVar : public ICondVar
{
private:
  std::condition_variable_any	_Cv;
  using Lock = std::unique_lock<API_Mutex::IMutex>;
public:
  CondVar			();
  CondVar			(const CondVar &) = delete;
  CondVar			&operator=(const CondVar &) = delete;
  virtual ~CondVar		();

  virtual void			wait(API_Mutex::IMutex *);
  virtual void			wait(API_Mutex::IMutex &);
  virtual void			wait(std::shared_ptr<API_Mutex::IMutex> &);
  virtual void			notifyAll();
  virtual void			notifyOne();
};

#endif /* !API_CONDVARSTD_HPP_ */
