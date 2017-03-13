//
// Instance.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jun  9 15:18:49 2015 jordan sabbah
// Last update Sun Jun 21 15:00:07 2015 jordan sabbah
//

#ifndef INSTANCE_HPP_
# define INSTANCE_HPP_

# include "../API_Error/API_Error.hpp"
# include "AInstance.hpp"

template <typename T>
class Instance : public AInstance{
private:
  T		*_inst;
public:
  Instance(T *ptr){
    _inst = ptr;
  }
  ~Instance(){
    delete _inst;
  }
  Instance(Instance const &){
    throw Error("this function should not have been called", "Instance(Instance const &)");
  }
  Instance operator=(Instance const &){
    throw Error("this function should not have been called", "Instance &operator=(Instance const &)");
  }
  void	*get_instance(){
    return (static_cast<void *>(_inst));
  }
};

#endif // !INSTANCE_HPP_
