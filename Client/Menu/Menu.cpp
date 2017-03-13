#include "Menu.hpp"

MainMenu::MainMenu(float width, float height)
  : MENU_ITEM(2)
{
  if (!this->_backgroundText.loadFromFile("../Ressources/Sprite/menu_background_title.png"))
    std::cerr << "Could not load background" << std::endl;

  this->_backgroundText.setRepeated(true);
  this->_backgroundText.setSmooth(true);
  this->_backgroundSprite.setTexture(this->_backgroundText);
  this->_backgroundSprite.setPosition(0, 0);
  this->_backgroundSprite.setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width * 2, sf::VideoMode::getDesktopMode().height));

  this->Item_Selected = 0;
  if (!font.loadFromFile("../Ressources/font/hemi_head_bd_it.ttf"))
    std::cerr << "Could not load font" << std::endl;

  item[0].setFont(font);
  item[0].setColor(sf::Color::Red);
  item[0].setString("Online Game");
  item[0].setPosition(sf::Vector2f(width / 1.75f, height / MENU_ITEM * 0.75f));

  item[1].setFont(font);
  item[1].setColor(sf::Color::White);
  item[1].setString("Exit");
  item[1].setPosition(sf::Vector2f(width / 1.75f, height / MENU_ITEM * 0.9f));

  _soundSelect = loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::MenuSelect);
  _soundAccept = loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::MenuAccept);
}

MainMenu::~MainMenu()
{
}

void MainMenu::draw(sf::RenderWindow &window) const
{
  window.draw(_backgroundSprite);
  for (int i = 0; i < MENU_ITEM; i++)
  {
    window.draw(item[i]);
  }
}

void MainMenu::move_up()
{
  _soundSelect->play();
  item[Item_Selected].setColor(sf::Color::White);
  this->Item_Selected--;
  if (this->Item_Selected < 0)
    this->Item_Selected = MENU_ITEM - 1;
  item[Item_Selected].setColor(sf::Color::Red);
}

void MainMenu::move_down()
{
  _soundSelect->play();
  item[Item_Selected].setColor(sf::Color::White);
  this->Item_Selected++;
  if (this->Item_Selected >= MENU_ITEM)
    this->Item_Selected = 0;
  item[Item_Selected].setColor(sf::Color::Red);
}

int	 MainMenu::get_item() const
{
  _soundAccept->play();
  return (this->Item_Selected);
}
