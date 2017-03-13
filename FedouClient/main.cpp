#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "GraphEngine.hpp"
#include "NetworkThread.hpp"

int main()
{
  sf::RenderWindow *gameWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "R-tipe", sf::Style::Fullscreen);
  GraphEngine g_en(gameWindow);
  NetworkThread nt(&g_en);
  std::string ip = "127.0.0.1";
  std::string port = "4242";

  nt.Start(port, ip);
  while (g_en.run());
  nt.Stop();
  delete (gameWindow);
  return (0);
}
