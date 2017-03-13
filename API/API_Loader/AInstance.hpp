//
// AInstance.hpp for  in /home/sabbah_j/rendu/TEK2/B4-SystemeUnix/PSU_2014_zappy/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Wed Jun 10 01:36:13 2015 jordan sabbah
// Last update Sun Jun 21 14:59:48 2015 jordan sabbah
//

#ifndef AINSTANCE_HPP_
# define AINSTANCE_HPP_

class AInstance {
public:
  AInstance(){}
  virtual ~AInstance(){}
  virtual void *get_instance() = 0;
  template<typename T>
  T &get_inst(){
    T *value = static_cast<T *>(get_instance());
    return (*value);
  }
  template<typename T>
  T *get_ptr(){
    T *value = static_cast<T *>(get_instance());
    return value;
  }
};

#endif // !AINSTANCE_HPP_
