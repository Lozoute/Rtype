#include "Window.hpp"
#include "IRessources.hpp"
#include "ISound.hpp"


Window::Window()
  : _window(sf::VideoMode::getDesktopMode(), "R-Type", sf::Style::Fullscreen),
  main_menu(static_cast<float>(sf::VideoMode::getDesktopMode().width),
  static_cast<float>(sf::VideoMode::getDesktopMode().height)),
  join_menu(static_cast<float>(sf::VideoMode::getDesktopMode().width),
  static_cast<float>(sf::VideoMode::getDesktopMode().height)),
  pause_menu()
{
  for (auto it = _threads.begin(); it != _threads.end(); ++it)
    (*it) = new Thread < TrdFc, Window * > ;
  this->_event[sf::Keyboard::Up] = &Window::key_up;
  this->_event[sf::Keyboard::Down] = &Window::key_down;
  this->_event[sf::Keyboard::Left] = &Window::key_left;
  this->_event[sf::Keyboard::Right] = &Window::key_right;
  this->_event[sf::Keyboard::Tab] = &Window::key_tab;
  this->_event[sf::Keyboard::Space] = &Window::key_space;
  this->_event[sf::Keyboard::Return] = &Window::key_enter;
  this->_event[sf::Keyboard::Escape] = &Window::key_escape;
  this->_event[sf::Keyboard::P] = &Window::key_p;
  this->_event[sf::Keyboard::A] = &Window::key_a;
  this->_event[sf::Keyboard::Period] = &Window::key_Period;
  this->_event[sf::Keyboard::BackSpace] = &Window::key_BackSpace;
  this->_event[sf::Keyboard::Num0] = &Window::key_0;
  this->_event[sf::Keyboard::Num1] = &Window::key_1;
  this->_event[sf::Keyboard::Num2] = &Window::key_2;
  this->_event[sf::Keyboard::Num3] = &Window::key_3;
  this->_event[sf::Keyboard::Num4] = &Window::key_4;
  this->_event[sf::Keyboard::Num5] = &Window::key_5;
  this->_event[sf::Keyboard::Num6] = &Window::key_6;
  this->_event[sf::Keyboard::Num7] = &Window::key_7;
  this->_event[sf::Keyboard::Num8] = &Window::key_8;
  this->_event[sf::Keyboard::Num9] = &Window::key_9;

  this->_joystick[Joystick::A] = &Window::key_space;
  this->_joystick[Joystick::B] = &Window::key_nothing;
  this->_joystick[Joystick::X] = &Window::key_nothing;
  this->_joystick[Joystick::Y] = &Window::key_nothing;
  this->_joystick[Joystick::LB] = &Window::key_nothing;
  this->_joystick[Joystick::RB] = &Window::key_nothing;
  this->_joystick[Joystick::SELECT] = &Window::key_nothing;
  this->_joystick[Joystick::START] = &Window::key_nothing;
  this->_joystick[Joystick::LEFT_STICK] = &Window::key_nothing;
  this->_joystick[Joystick::RIGHT_STICK] = &Window::key_nothing;

  _state = WindowState::MenuMain;
  this->width = sf::VideoMode::getDesktopMode().width;
  this->height = sf::VideoMode::getDesktopMode().height;
  this->_window.setFramerateLimit(30);
  this->_window.setMouseCursorVisible(false);
  _connectMenu = _Loader.getPtr<ISound>(LIB_RES, "get_sound", MenuConnect);
  _selectMenu = _Loader.getPtr<ISound>(LIB_RES, "get_sound", MenuSelect);
  _Running = 1;
}

Window::~Window()
{
  for (auto it = _threads.begin(); it != _threads.end(); ++it)
    (*it)->join();
}

void	Window::event_loop_game()
{
  _state = WindowState::Game;
  _game = new GameEngine();
  _game->setMode(0);
  pause_menu.setPause(false);

  // FOR FPS
  sf::Clock clock;
  // FOR FPS


  for (auto it = _threads.begin(); it != _threads.end(); ++it)
    (*it)->init(&Window::catch_loop_game, this);
  while (this->_window.isOpen())
  {
    for (auto it = _event.begin();
      it != _event.end();
      ++it)
    {
      if (sf::Keyboard::isKeyPressed(it->first))
      {
	keyFunction fct = it->second;
	(this->*fct)(KeyState::Pressed);
      }
    }

    for (auto it = _joystick.begin();
      it != _joystick.end();
      ++it)
    {
      if (sf::Joystick::isButtonPressed(0, it->first))
      {
	keyFunction fct = it->second;
	(this->*fct)(KeyState::Pressed);

      }
    }

    sf::Event event;
    while (this->_window.pollEvent(event))
    {
      if (event.type == sf::Event::KeyReleased)
      {
	for (auto it = _event.begin();
	  it != _event.end();
	  ++it)
	{
	  if (event.key.code == it->first)
	  {
	    keyFunction fct = it->second;
	    (this->*fct)(KeyState::Released);
	  }
	}
      }
      if (event.type == sf::Event::Closed)
	this->_window.close();
    }


    // This is where we draw everyhing
    this->_window.clear();

    _background.draw(&_window);
    _game->update(_window);

    if (pause_menu.isPaused())
      pause_menu.draw(_window);

    //FPS
    sf::Time time = clock.getElapsedTime();

    clock.restart().asSeconds();
    sf::Text	text;
    std::ostringstream ss;
    ss << static_cast<int>(1.0f / time.asSeconds());
    text.setColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setFont(*_Loader.getPtr<sf::Font>(LIB_RES, "get_font"));
    text.setStyle(sf::Text::Bold);
    text.setString(ss.str());
    text.setPosition(sf::Vector2f(0, 0));
    _window.draw(text);
    //FPS

    this->_window.display();
  }
}

void Window::catch_loop_game()
{
  Srtp packet;

  try
    {
      while (_Running && this->_window.isOpen())
	{
	  while (proto->receive(packet))
	    _game->executeCmd(packet);
	}
    }
  catch (std::exception const &)
    {
      _Running = 0;
      return;
    }
}

int	Window::event_MainMenu()
{
  _state = WindowState::MenuMain;
  while (this->_window.isOpen())
  {
    sf::Event event;
    while (this->_window.pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
      {
	for (auto it = _event.begin();
	  it != _event.end();
	  ++it)
	{
	  if (event.key.code == it->first)
	  {
	    keyFunction fct = it->second;
	    (this->*fct)(KeyState::Released);
	  }
	}
	if (event.key.code == sf::Keyboard::Return)
	{
	  if (this->main_menu.get_item() == 3)
	    this->_window.close();
	  return (this->main_menu.get_item());
	}
      }
    }

    _window.clear();
    this->main_menu.draw(this->_window);
    _window.display();
  }
  return (0);
}

int		Window::event_JoinMenu()
{
  _state = WindowState::Join;
  while (this->_window.isOpen())
  {
    sf::Event event;
    while (this->_window.pollEvent(event))
    {
      if (event.type == sf::Event::KeyPressed)
      {
	for (auto it = _event.begin();
	  it != _event.end();
	  ++it)
	{
	  if (event.key.code == it->first)
	  {
	    keyFunction fct = it->second;
	    (this->*fct)(KeyState::Released);
	  }
	}
	if (event.key.code == sf::Keyboard::Return)
	{
	  if (this->join_menu.get_item() == 2)
	  {
	    if ((_ip = join_menu.get_ip()) == "")
	      join_menu.setInfoOk(false);
	    else if ((_port = join_menu.get_port()) == -1)
	      join_menu.setInfoOk(false);
	    else
	    {
	      join_menu.setInfoOk(true);

	      _connectMenu->play();
	      proto = _Loader.getSmartPtr<API_Protocol::IProtocol>(LIB_PROTO, "protocol_client", _port, &_ip);
	      return (4);
	    }
	    this->join_menu.reset_itemSelect();
	  }
	  if (this->join_menu.get_item() == 3)
	  {
	    int val = this->join_menu.get_item();
	    this->join_menu.reset_itemSelect();
	    return (val);
	  }
	}
      }
    }

    _window.clear();
    this->join_menu.draw(this->_window);
    _window.display();
  }
  return (0);
}
