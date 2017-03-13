#include "Background.hpp"

Background::Background()
{
	pos_back = 0;
	pos_x = 0;
	width = (sf::VideoMode::getDesktopMode().width) * -1;
	_BackText = Ptr<sf::Texture>(new sf::Texture);
	_BackSprite = Ptr<sf::Sprite>(new sf::Sprite);
	_BackObjText = Ptr<sf::Texture>(new sf::Texture);
	_BackObjSprite = Ptr<sf::Sprite>(new sf::Sprite);
	_BackObjSprite2 = Ptr<sf::Sprite>(new sf::Sprite);
	_BackText->loadFromFile("../Ressources/Sprite/Game_Background_7680x2160.png");
	width_back = -1 * _BackText->getSize().x;

	(_BackText.get())->setRepeated(true);
	(_BackText.get())->setSmooth(true);
	(_BackSprite.get())->setTexture(*_BackText);
	(_BackSprite.get())->setPosition(static_cast<float>(0), static_cast<float>(0));
	(_BackSprite.get())->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width * 3, sf::VideoMode::getDesktopMode().height));
	//(_BackSprite.get())->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));

	(_BackObjText.get())->loadFromFile("../Ressources/Sprite/side_wall.png");
	(_BackObjText.get())->setRepeated(true);
	(_BackObjText.get())->setSmooth(true);
	(_BackObjSprite.get())->setTexture(*_BackObjText);
	(_BackObjSprite.get())->setPosition(static_cast<float>(pos_x), static_cast<float>(0));
	(_BackObjSprite.get())->setScale(static_cast<float>(2.11), static_cast<float>(2));
	//(_BackObjSprite.get())->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width * 2, 50));
	(_BackObjSprite.get())->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, 50));

	(_BackObjSprite2.get())->setTexture(*_BackObjText);
	(_BackObjSprite2.get())->setPosition(static_cast<float>(pos_x), static_cast<float>(sf::VideoMode::getDesktopMode().height - 100));
	(_BackObjSprite2.get())->setScale(static_cast<float>(2.11), static_cast<float>(2));
	(_BackObjSprite2.get())->setTextureRect(sf::IntRect(0, 0, sf::VideoMode::getDesktopMode().width, 50));
}

Background::~Background()
{
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

  (_BackSprite.get())->setPosition(static_cast<float>(pos_back / 4), static_cast<float>(0));
  (_BackObjSprite2.get())->setPosition(static_cast<float>(pos_x), static_cast<float>(sf::VideoMode::getDesktopMode().height - 100));
  (_BackObjSprite.get())->setPosition(static_cast<float>(pos_x), static_cast<float>(0));
  window->draw(*(_BackSprite.get()));
  window->draw(*(_BackObjSprite.get()));
  window->draw(*(_BackObjSprite2.get()));
}
