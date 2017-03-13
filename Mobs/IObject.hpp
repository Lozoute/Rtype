#ifndef IOBJECT_HPP_
# define IOBJECT_HPP_

# include <SFML/Graphics.hpp>
# include "Srtp.hpp"

class IObject{
public:
  using cmdd = IObject *(*)(const int, const int, const int, const int, ObjectType);
  virtual ~IObject(){}
  virtual void	      setMode(int) = 0;
  virtual void	      move_down() = 0;
  virtual void	      move_up() = 0;
  virtual void	      move_forward() = 0;
  virtual void	      move_backward() = 0;
  virtual void	      getDestroyed() = 0;
  virtual void	      resetAnim() = 0;
  virtual void	      draw(sf::RenderWindow &) = 0;

  virtual void setBoost(int) = 0;
  virtual bool getBoost() const = 0;
  virtual void	      setSpeed(int) = 0;
  virtual void	      setId(int) = 0;
  virtual void	      setHp(int) = 0;
  virtual void	      setPosX(int) = 0;
  virtual void	      setPosY(int) = 0;
  virtual void	      addSafeTime() = 0;

  virtual void	      takeDamage(const int val) = 0;

  virtual int	      getSender() const = 0;
  virtual int	      getId() const = 0;
  virtual int	      getHp() const = 0;
  virtual bool	      getDelete() const = 0;
  virtual void	      setDelete() = 0;
  virtual void	      setDestroy() = 0;
  virtual int	      getPosX() const = 0;
  virtual int	      getPosY() const = 0;
  virtual int	      getWidth() const = 0;
  virtual int	      getHeight() const = 0;
  virtual int	      getSafeTime() const = 0;
  virtual bool	      isAlive() = 0;
  virtual ObjectType  getObjectType() const  = 0;
  virtual MobType     getMobType() const = 0;
  virtual IObject     *operator()(Srtp  &packet, bool attack) = 0;
};

# if defined(WIN32) || defined (_WIN32)
//  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# define LIBNAME  "../API/DLLs/lib_API_Ressources.dll"
# elif defined(linux) || defined (__unix__)
//  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# define LIBNAME  "../API/SOs/lib_API_Ressources.so"
# else
//  unknown
# define EXPORT
# define IMPORT
# define LIBNAME  ""
# pragma warning Unknown dynamic link import/export semantics.
# endif

# endif // !IOBJECT_HPP_
