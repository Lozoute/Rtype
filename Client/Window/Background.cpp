#include "Background.hpp"

Background::Background()
{
	pos_back = 0;
	pos_x = 0;
	width = (sf::VideoMode::getDesktopMode().width) * -1;
	_BackText = new sf::Texture;
	_BackSprite = new sf::Sprite;
	_BackObjText = new sf::Texture;
	_BackObjSprite = new sf::Sprite;
	_BackObjSprite2 = new sf::Sprite;
	_BackText->loadFromFile("../Ressources/Sprite/Game_Background_7680x2160.png");
	width_back = -1 * _BackText->getSize().x;

	_BackText->setRepeated(true);
	_BackText->setSmooth(true);
	_BackSprite->setTexture(*_BackText);
	_BackSprite->setPosition(static_cast<float>(0), static_cast<float>(0));
	_BackSprite->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width * 3, sf::VideoMode::getDesktopMode().height));
	//_BackSprite->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));

	_BackObjText->loadFromFile("../Ressources/Sprite/side_wall.png");
	_BackObjText->setRepeated(true);
	_BackObjText->setSmooth(true);
	_BackObjSprite->setTexture(*_BackObjText);
	_BackObjSprite->setPosition(static_cast<float>(pos_x), static_cast<float>(0));
	_BackObjSprite->setScale(static_cast<float>(2.11), static_cast<float>(2));
	//_BackObjSprite->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width * 2, 50));
	_BackObjSprite->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, 50));

	_BackObjSprite2->setTexture(*_BackObjText);
	_BackObjSprite2->setPosition(static_cast<float>(pos_x), static_cast<float>(sf::VideoMode::getDesktopMode().height - 100));
	_BackObjSprite2->setScale(static_cast<float>(2.11), static_cast<float>(2));
	_BackObjSprite2->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, 50));
}

Background::~Background()
{
	delete _BackSprite;
	delete _BackObjSprite2;
	delete _BackText;
	delete _BackObjSprite;
	delete _BackObjText;
}

void	Background::draw(sf::RenderWindow *window)
{
  if (pos_x <= width)
    pos_x = 0;
  else
    pos_x -= 2;

  if (pos_back / 2  <= width_back)
      pos_back = 0;
  else
    pos_back -= 1;

  _BackSprite->setPosition(static_cast<float>(pos_back / 4), static_cast<float>(0));
  _BackObjSprite2->setPosition(static_cast<float>(pos_x), static_cast<float>(sf::VideoMode::getDesktopMode().height - 100));
  _BackObjSprite->setPosition(static_cast<float>(pos_x), static_cast<float>(0));
  window->draw(*_BackSprite);
  window->draw(*_BackObjSprite);
  window->draw(*_BackObjSprite2);
}
