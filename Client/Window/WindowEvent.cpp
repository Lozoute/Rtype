#include "Window.hpp"

void	Window::key_up(KeyState stateKey)
{
  if (_state == WindowState::MenuMain)
    this->main_menu.move_up();
  else if (_state == WindowState::Game)
  {
    if (stateKey == KeyState::Pressed)
    {
	_game->getShip().move_up();
	Srtp packet;
	_game->getShip()(packet, false);
	packet._idGame = _game->getIdGame();
	proto->send(packet);
    }
    else if (stateKey == KeyState::Released)
    {
      _game->getShip().setMode(2);
    }
  }
  else if (_state == WindowState::Pause && stateKey == KeyState::Released)
  {
    pause_menu.move_up();
  }
  else if (_state == WindowState::Join)
  {
    join_menu.move_up();
  }
}

void	Window::key_down(KeyState stateKey)
{
  if (_state == WindowState::MenuMain)
    this->main_menu.move_down();
  else if (_state == WindowState::Game)
  {
    if (stateKey == KeyState::Pressed)
    {
      _game->getShip().move_down();
      Srtp packet;
      _game->getShip()(packet, false);
      packet._idGame = _game->getIdGame();
      proto->send(packet);
    }
    else
    {
      _game->getShip().setMode(2);
    }
  }
  else if (_state == WindowState::Pause && stateKey == KeyState::Released)
  {
    pause_menu.move_down();
  }
  else if (_state == WindowState::Join)
  {
    join_menu.move_down();
  }
}

void	Window::key_left(KeyState stateKey)
{
  if (_state == WindowState::MenuMain)
    return;
  else if (_state == WindowState::Game)
  {
    if (stateKey == KeyState::Pressed)
    {
      _game->getShip().move_backward();
      Srtp packet;
      _game->getShip()(packet, false);
      packet._idGame = _game->getIdGame();
      proto->send(packet);
    }
  }
  else if (_state == WindowState::Pause && stateKey == KeyState::Released &&
	   (pause_menu.get_item() == 1 || pause_menu.get_item() == 2))
  {
    pause_menu.setVolume(static_cast<typeVolume>(pause_menu.get_item()), -5);
  }
}

void	Window::key_right(KeyState stateKey)
{
  if (_state == WindowState::MenuMain)
    this->main_menu.move_down();
  else if (_state == WindowState::Game)
  {
    if (stateKey == KeyState::Pressed)
    {
      _game->getShip().move_forward();
      Srtp packet;
      _game->getShip()(packet, false);
      packet._idGame = _game->getIdGame();
      proto->send(packet);
    }
  }
  else if (_state == WindowState::Pause && stateKey == KeyState::Released &&
	   (pause_menu.get_item() == 1 || pause_menu.get_item() == 2))
  {
    pause_menu.setVolume(static_cast<typeVolume>(pause_menu.get_item()), 5);
  }
}

void	Window::key_tab(KeyState stateKey)
{
  if (_state == WindowState::MenuMain)
    this->main_menu.move_down();
  else if (_state == WindowState::Game)
  {
    if (stateKey == KeyState::Pressed)
    {
      Srtp packet;
      packet._cmdClient = CMDC_Score;
      packet._idGame = _game->getIdGame();
      proto->send(packet);
      _game->setTab(true);
    }
    else
      _game->setTab(false);
  }
}

void	Window::key_space(KeyState stateKey)
{
  if (_state == WindowState::MenuMain)
    this->main_menu.move_down();
  else if (_state == WindowState::Game)
  {
    if (stateKey == KeyState::Pressed)
    {
      //if (_game->getShip().launch_attack() == true)
      //{
      _game->getShip().launch_attack();
      Srtp packet;
      _game->getShip()(packet, true);
      packet._idGame = _game->getIdGame();
      proto->send(packet);
      //}
    }
  }
}

void	Window::key_enter(KeyState stateKey)
{
  if (_state == WindowState::Pause && stateKey == KeyState::Released)
  {
    if (pause_menu.get_item() == 0)
    {
      key_p(KeyState::Released);
    }
  }
}

void	Window::key_escape(KeyState stateKey)
{

  if (_state == WindowState::MenuMain || _state == WindowState::Join)
    _window.close();
  else if (_state == WindowState::Game)
     _window.close();
  else if (_state == WindowState::Pause)
    key_p(stateKey);

}

void	Window::key_p(KeyState stateKey)
{
  if (_state == WindowState::Game && stateKey == KeyState::Released)
  {
    _state = WindowState::Pause;
    _selectMenu->play();
    pause_menu.setPause(!pause_menu.isPaused());
  }
  else if (_state == WindowState::Pause && stateKey == KeyState::Released)
  {
    _state = WindowState::Game;
    _selectMenu->play();
    pause_menu.setPause(!pause_menu.isPaused());
  }
}

void	Window::key_nothing(KeyState)
{
  return;
}

void	Window::key_a(KeyState)
{
  static int a = 0;
  if (_state == WindowState::Game && a == 0)
  {
    a = 1;
    _game->getShip().getDestroyed();
  }
}

void	Window::key_0(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('0');
  }
}

void	Window::key_1(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('1');
  }
}

void	Window::key_2(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('2');
  }
}

void	Window::key_3(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('3');
  }
}

void	Window::key_4(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('4');
  }
}

void	Window::key_5(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('5');
  }
}

void	Window::key_6(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('6');
  }
}

void	Window::key_7(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('7');
  }
}

void	Window::key_8(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('8');
  }
}

void	Window::key_9(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('9');
  }
}

void	Window::key_Period(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo('.');
  }
}

void	Window::key_BackSpace(KeyState stateKey)
{
  if (_state == WindowState::Join && stateKey == KeyState::Released)
  {
    join_menu.writeinfo(-1);
  }
}
