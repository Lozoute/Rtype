#ifndef WINDOW_HPP_
# define WINDOW_HPP_


# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include <iostream>
# include <sstream>
# include <string>
# include <memory>
# include <array>
# include <atomic>
# include "ship.hpp"
# include "GameEngine.hpp"
# include "Background.hpp"
# include "Menu.hpp"
# include "PauseMenu.hpp"
# include "Sound.hpp"
# include "MenuJoin.hpp"
# include "Loader.hpp"
# include "API_Thread.hpp"
# include "API_Mutex.hpp"
# include "API_Protocol.hpp"


using	namespace API_Thread;
using	namespace API_Mutex;

class	Window
{
  enum	Joystick
  {
    A = 0,
    B = 1,
    X = 2,
    Y = 3,
    LB = 4,
    RB = 5,
    SELECT = 6,
    START = 7,
    LEFT_STICK = 8,
    RIGHT_STICK = 9
  };
  enum	WindowState
  {
    MenuMain,
    Join,
    Game,
    Pause
  };
  enum	KeyState
  {
    Pressed,
    Released
  };
  using keyFunction = void (Window::*)(KeyState);
  using TrdFc = void (Window::*)();

  std::map<sf::Keyboard::Key, keyFunction>    _event;
  std::map<sf::Keyboard::Key, keyFunction>    _eventJoin;
  std::map<unsigned int, keyFunction>	      _joystick;

  GameEngine				      *_game;
  sf::RenderWindow			      _window;
  Background				      _background;
  unsigned int				      width;
  unsigned int				      height;
  MainMenu				      main_menu;
  MenuJoin				      join_menu;
  PauseMenu				      pause_menu;
  WindowState				      _state;
  std::string				      _ip;
  int					      _port;
  Loader				      _Loader;
  std::array<IThread<TrdFc, Window *> *, 8 >  _threads;
  std::shared_ptr<IMutex>		      _Mtx;
  std::shared_ptr<API_Protocol::IProtocol>    proto;
  ISound				      *_selectMenu;
  ISound				      *_connectMenu;
  std::atomic<int>			      _Running;

public:
  Window();
  Window(const Window &) = delete;
  Window				      &operator=(const Window &) = delete;
  ~Window();

  void					      event_loop_game();
  void					      catch_loop_game();
  int					      event_MainMenu();
  int					      event_JoinMenu();

  //Event Function
  void					      key_up(KeyState);
  void					      key_down(KeyState);
  void					      key_left(KeyState);
  void					      key_right(KeyState);
  void					      key_tab(KeyState);
  void					      key_space(KeyState);
  void					      key_enter(KeyState);
  void					      key_escape(KeyState);
  void					      key_p(KeyState);
  void					      key_nothing(KeyState);
  void					      key_a(KeyState);
  void					      key_0(KeyState);
  void					      key_1(KeyState);
  void					      key_2(KeyState);
  void					      key_3(KeyState);
  void					      key_4(KeyState);
  void					      key_5(KeyState);
  void					      key_6(KeyState);
  void					      key_7(KeyState);
  void					      key_8(KeyState);
  void					      key_9(KeyState);
  void					      key_Period(KeyState);
  void					      key_BackSpace(KeyState);
};
# if defined(WIN32) || defined (_WIN32)
# define LIB_PROTO	"../API/DLLs/lib_API_Protocol.dll"
# define LIB_RES	"../API/DLLs/lib_API_Ressources.dll"
# else
# define LIB_PROTO	"../API/SOs/lib_API_Protocol.so"
# define LIB_RES	"../API/SOs/lib_API_Ressources.so"
# endif

#endif /* !WINDOW_HPP_ */
