#include "MenuJoin.hpp"
#include "Loader.hpp"

MenuJoin::MenuJoin(float width, float height)
  : MENU_ITEM(4)
{
  this->_backgroundText = new sf::Texture;
  this->_backgroundText2 = new sf::Texture;
  this->_backgroundSprite = new sf::Sprite;
  this->_circle = new sf::Sprite;
  if (!this->_backgroundText->loadFromFile("../Ressources/Sprite/MenuJoin.png"))
    std::cerr << "Could not load join background" << std::endl;

  this->_backgroundText->setRepeated(true);
  this->_backgroundText->setSmooth(true);
  this->_backgroundSprite->setTexture(*this->_backgroundText);
  this->_backgroundSprite->setPosition(0, 0);
  this->_backgroundSprite->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width * 2, sf::VideoMode::getDesktopMode().height));

  if (!this->_backgroundText2->loadFromFile("../Ressources/Sprite/MenuJoinCircle.png"))
    std::cerr << "Could not load MenuJoinCircle" << std::endl;
  this->_backgroundText2->setRepeated(false);
  this->_backgroundText2->setSmooth(false);
  this->_circle->setTexture(*this->_backgroundText2);
  this->_circle->setPosition(780, 254);
  this->_circle->setTextureRect(sf::IntRect(0, 0, 407, 408));

  this->Item_Selected = 0;
  if (!font.loadFromFile("../Ressources/font/hemi_head_bd_it.ttf"))
    std::cerr << "Could not load font" << std::endl;

  item[0].setFont(font);
  item[0].setColor(sf::Color::Red);
  item[0].setString(_log.get_host());
  item[0].setPosition(sf::Vector2f(static_cast<float>(width / 5.439), static_cast<float>(height / 3.176)));

  item[1].setFont(font);
  item[1].setColor(sf::Color::White);
  item[1].setString(_log.get_port());
  item[1].setPosition(sf::Vector2f(static_cast<float>(width / 5.439), static_cast<float>(height / 2.494)));

  item[2].setFont(font);
  item[2].setColor(sf::Color::White);
  item[2].setString("Connect");
  item[2].setPosition(sf::Vector2f(static_cast<float>(width / 4.637), static_cast<float>(height / 1.894)));

  item[3].setFont(font);
  item[3].setColor(sf::Color::White);
  item[3].setString("Return to Menu");
  item[3].setPosition(sf::Vector2f(static_cast<float>(width / 4.848), static_cast<float>(height / 1.529)));

  _info_ok = true;
  Loader  loader;
  _soundSelect = loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::MenuSelect);
  _soundAccept = loader.getPtr<ISound>(LIBNAME, "get_sound", GameSound::MenuAccept);
}

MenuJoin::~MenuJoin()
{
  delete this->_backgroundText;
  delete this->_backgroundText2;
  delete this->_backgroundSprite;
  delete this->_circle;;
}

void MenuJoin::draw(sf::RenderWindow &window) const
{
  static int i = 0;
  static int time = 50;

  window.draw(*_backgroundSprite);
  for (int i = 0; i < MENU_ITEM; i++)
  {
    window.draw(item[i]);
  }
  if (_clock.getElapsedTime().asMilliseconds() > time)
  {
    time += 50;
    i = (i + 1) % 2;
    if (i == 1)
    {
      window.draw(*_circle);
      time = 50;
    }
  }
  if (_info_ok == false)
  {
    static sf::Text text("Bad port or\nIP address ...", font);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
    text.setPosition(115, 910);
    window.draw(text);
  }
}

void MenuJoin::move_up()
{
  _soundSelect->play();
  item[Item_Selected].setColor(sf::Color::White);
  this->Item_Selected--;
  if (this->Item_Selected < 0)
    this->Item_Selected = MENU_ITEM - 1;
  item[Item_Selected].setColor(sf::Color::Red);
}

void MenuJoin::move_down()
{
  _soundSelect->play();
  item[Item_Selected].setColor(sf::Color::White);
  this->Item_Selected++;
  if (this->Item_Selected >= MENU_ITEM)
    this->Item_Selected = 0;
  item[Item_Selected].setColor(sf::Color::Red);
}

bool MenuJoin::checkDotIP(const int count_nb, const int count_dot, const int i, const std::string &res) const
{
  if ((count_nb == 0) || (count_dot == 3) || (count_nb == 3 &&
    (res[i - 3] > '2' ||
    (res[i - 3] == '2' && res[i - 2] > '5') ||
    (res[i - 3] == '2' && res[i - 2] == '5' && res[i - 1] > '5'))))
    return (false);
  return (true);
}

std::string MenuJoin::get_ip()
{
  std::string res = item[0].getString();
  size_t i = 0;
  int count_dot = 0;
  int count_nb = 0;
  bool is_ok = true;

  while (i < res.size() && is_ok == true)
  {
    if (res[i] == '.')
    {
      is_ok = checkDotIP(count_nb, count_dot, i, res);
      count_dot += 1;
      count_nb = 0;
    }
    else if (count_nb == 3)
      is_ok = false;
    else
      count_nb++;
    ++i;
  }

  if (is_ok == false || (count_dot != 3) || (is_ok == true && count_nb == 3 &&
    (res[i - 3] > '2' ||
    (res[i - 3] == '2' && res[i - 2] > '5') ||
    (res[i - 3] == '2' && res[i - 2] == '5' && res[i - 1] > '5'))))
  {
    res.assign("");
  }
  else
    _log.set_host(res);
  return (res);
}

int MenuJoin::get_port()
{
  std::string res = item[1].getString();
  if ((res.size() == e_size_info::SIZE_PORT) &&
      ((res[0] > '6') ||
      (res[0] == '6' && res[1] > '5') ||
      (res[0] == '6' && res[1] == '5' && res[2] > '5') ||
      (res[0] == '6' && res[1] == '5' && res[2] == '5' && res[3] > '3') ||
      (res[0] == '6' && res[1] == '5' && res[2] == '5' && res[3] == '3' && res[4] > '5')))
  {
    return (-1);
  }
  _log.set_port(res);
  std::stringstream ss;
  int val;
  ss << res;
  ss >> val;
  return (val);
}

 int	 MenuJoin::get_item() const
 {
   _soundAccept->play();
   return (this->Item_Selected);
 }

 void MenuJoin::writeinfo(const char c)
 {
   if (Item_Selected < 2)
   {
     size_t maxSize;
     if (Item_Selected == 0)
       maxSize = e_size_info::SIZE_IP;
     else
       maxSize = e_size_info::SIZE_PORT;
     size_t size = item[Item_Selected].getString().getSize();
     if (size > 0 && c == -1)
     {
       std::string str = item[Item_Selected].getString();
       str.pop_back();
       item[Item_Selected].setString(str);
     }
     else if (c != -1 && size < maxSize)
     {
       item[Item_Selected].setString(item[Item_Selected].getString() + c);
     }
   }
 }

 void MenuJoin::reset_itemSelect()
 {
   item[Item_Selected].setColor(sf::Color::White);
   Item_Selected = 0;
   item[Item_Selected].setColor(sf::Color::Red);
 }

bool MenuJoin::getInfoOk() const
{
  return (_info_ok);
}

void MenuJoin::setInfoOk(const bool val)
{
  _info_ok = val;
}
