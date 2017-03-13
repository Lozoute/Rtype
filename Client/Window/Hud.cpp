#include "Hud.hpp"
#include "Loader.hpp"
#include "IRessources.hpp"

CleverHud::CleverHud()
{
  Loader  _loader;
  _isDead = false;
  _nextStage = false;
  _Dead = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", Dead);
  _Dead->setPosition(1920 / 2 - _Dead->getWidth() / 2, 0);
  _isTabPressed = false;
  _hudText = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", HudText);
  _hudText->getSprite().setPosition(sf::Vector2f(1920.0f / 4.0f, 1080.0f / 4.0f));
  _hpSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::Hp);
  _hpSprite->setPosition(1920 / 20, 1080 / 100);
  _stageSprite = _loader.getPtr<ISprite>(LIBNAME, "get_sprite", GameSprite::NextStage);
  _stageSprite->getSprite().setPosition(sf::Vector2f(1920.0f / 2 - _stageSprite->getWidth() / 2, 1080.0f / 2 -_stageSprite->getHeight() / 2));


  _blue_Score = 0;
  _pink_Score = 0;
  _green_Score = 0;
  _red_Score = 0;

  if (!_font.loadFromFile("../Ressources/font/hemi_head_bd_it.ttf"))
    std::cerr << "Could not load font" << std::endl;

  std::stringstream ss;

  std::string value;
  _player[0].setFont(_font);
  ss << _blue_Score;
  ss >> value;
  _player[0].setColor(sf::Color::Blue);
  _player[0].setString(value);
  _player[0].setPosition(sf::Vector2f(static_cast<float>(1920 / 4 + 500 * 1.2), 1080 / 4 + 125));

  ss.clear();

  _player[1].setFont(_font);
  ss << _pink_Score;
  ss >> value;
  _player[1].setColor(sf::Color::Magenta);
  _player[1].setString(value);
  _player[1].setPosition(sf::Vector2f(static_cast<float>(1920 / 4 + 500 * 1.2), 1080 / 4 + 200));

  ss.clear();

  _player[2].setFont(_font);
  ss << _green_Score;
  ss >> value;
  _player[2].setColor(sf::Color::Green);
  _player[2].setString(value);
  _player[2].setPosition(sf::Vector2f(static_cast<float>(1920 / 4 + 500 * 1.2), 1080 / 4 + 275));

  ss.clear();

  _player[3].setFont(_font);
  ss << _red_Score;
  ss >> value;
  _player[3].setColor(sf::Color::Red);
  _player[3].setString(value);
  _player[3].setPosition(sf::Vector2f(static_cast<float>(1920 / 4 + 500 * 1.2), 1080 / 4 + 350));
}

CleverHud::~CleverHud()
{
}

void CleverHud::draw(sf::RenderWindow &window)
{
  static int a = 0;

  if (_nextStage == true)
  {
    a++;
    window.draw(_stageSprite->getSprite());
    if (a >= 90)
    {
      a = 0;
      _nextStage = false;
    }
  }
  _hpSprite->setTextureRect(0,
			    _hpPlayer * _hpSprite->getHeight(),
			    _hpSprite->getWidth(),
			    _hpSprite->getHeight());
  window.draw(_hpSprite->getSprite());
  if (_isDead == true)
    window.draw(_Dead->getSprite());
  if (_isTabPressed)
    draw_ctrl(window);
}

void CleverHud::draw_ctrl(sf::RenderWindow &window)
{
  window.draw(_hudText->getSprite());
  for (int i = 0; i <= 3; ++i)
    window.draw(_player[i]);
}

void CleverHud::setTabPressed(bool entry)
{
  _isTabPressed = entry;
}

void CleverHud::setScore(const int blue, const int pink, const int green, const int red)
{
  _blue_Score = blue;
  _pink_Score = pink;
  _green_Score = green;
  _red_Score = red;

  std::stringstream ss;
  std::string value;
  ss << _blue_Score;
  ss >> value;
  _player[0].setString(value);
  ss.clear();

  ss << _pink_Score;
  ss >> value;
  _player[1].setString(value);
  ss.clear();

  ss << _green_Score;
  ss >> value;
  _player[2].setString(value);
  ss.clear();

  ss << _red_Score;
  ss >> value;
  _player[3].setString(value);
  ss.clear();
}

void CleverHud::setIsDead(bool entry)
{
  _isDead = entry;
}

void CleverHud::setPlayerHp(int entry)
{
  _hpPlayer = entry;
}

void CleverHud::setNextStage(int entry)
{
  _nextStage = entry;
}
