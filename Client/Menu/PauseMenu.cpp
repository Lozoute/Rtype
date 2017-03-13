#include "PauseMenu.hpp"

PauseMenu::PauseMenu()
  : MENU_ITEM(3)
{
  vol_music = 25;
  vol_effect = 25;


  unsigned int mid_width = sf::VideoMode::getDesktopMode().width / 2;
  unsigned int mid_height = sf::VideoMode::getDesktopMode().height / 2;

  this->Item_Selected = 0;
  if (!font.loadFromFile("../Ressources/font/hemi_head_bd_it.ttf"))
    std::cerr << "Could not load font" << std::endl;

  item[0].setFont(font);
  item[0].setColor(sf::Color::Red);
  item[0].setString("Return to game");
  float x = static_cast<float>(mid_width - 14 * 15 / 2);
  float y = static_cast<float>(mid_height - 50);
  item[0].setPosition(sf::Vector2f(x, y));

  item[1].setFont(font);
  item[1].setColor(sf::Color::White);
  std::string music = "< Music " + std::to_string(static_cast<int>(vol_music)) + " >";
  item[1].setString(music);
  x = static_cast<float>(mid_width - 12 * 15 / 2);
  y = static_cast<float>(mid_height);
  item[1].setPosition(sf::Vector2f(x, y));

  item[2].setFont(font);
  item[2].setColor(sf::Color::White);
  std::string effect = "< Effect " + std::to_string(static_cast<int>(vol_effect)) + " >";
  item[2].setString(effect);
  x = static_cast<float>(mid_width - 12 * 15 / 2);
  y = static_cast<float>(mid_height + 50);
  item[2].setPosition(sf::Vector2f(x, y));

  _paused = false;

  _soundSelect = loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::MenuSelect);
  _soundAccept = loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::MenuAccept);
  _res = loader.getPtr<IRessources>(LIBNAME, "get_ressources");
}

PauseMenu::~PauseMenu()
{

}

void PauseMenu::draw(sf::RenderWindow &window) const
{
  for (int i = 0; i < MENU_ITEM; i++)
  {
    window.draw(item[i]);
  }
}

void PauseMenu::move_up()
{
  _soundSelect->play();
  item[Item_Selected].setColor(sf::Color::White);
  this->Item_Selected--;
  if (this->Item_Selected < 0)
    this->Item_Selected = MENU_ITEM - 1;
  item[Item_Selected].setColor(sf::Color::Red);
}

void PauseMenu::move_down()
{
  _soundSelect->play();
  item[Item_Selected].setColor(sf::Color::White);
  this->Item_Selected++;
  if (this->Item_Selected >= MENU_ITEM)
    this->Item_Selected = 0;
  item[Item_Selected].setColor(sf::Color::Red);
}

int	 PauseMenu::get_item() const
{
  _soundAccept->play();
  return (this->Item_Selected);
}

bool PauseMenu::isPaused() const
{
  return (_paused);
}

void PauseMenu::setVolume(const typeVolume &type, const float volume)
{
  if (type == MUSIC)
    setVolumeMusic(volume);
  else
    setVolumeEffect(volume);
}

void PauseMenu::setVolumeMusic(const float volume)
{
  if (volume > 0)
  {
    if ((vol_music + volume) <= 100)
      vol_music += volume;
  }
  else
  {
    if ((vol_music + volume) >= 0)
      vol_music += volume;
  }
  _res->setVolumeMusic(vol_music);
  std::string music = "< Music " + std::to_string(static_cast<int>(vol_music)) + " >";
  item[1].setString(music);
}

void PauseMenu::setVolumeEffect(const float volume)
{
  if (volume > 0)
  {
    if ((vol_effect + volume) <= 100)
      vol_effect += volume;
  }
  else
  {
    if ((vol_effect + volume) >= 0)
      vol_effect += volume;
  }
  _res->setVolumeEffect(vol_effect);
  std::string effect = "< Effect " + std::to_string(static_cast<int>(vol_effect)) + " >";
  item[2].setString(effect);
}

void PauseMenu::setPause(bool val)
{
  _paused = val;
}
