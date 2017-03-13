#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <ctime>
#include "API_Error.hpp"
#include "Server.hpp"

int		main(int argc, char **argv)
{
  Server	S;

  try
    {
      std::srand(std::time(0));
      S.Start((argc > 1 && argv && argv[1] ? argv[2] : "4242"));
    }
  catch (const Error &e)
    {
      std::cerr << "EXCEPTION: " << e.what() << " _in_ " << e.who() << std::endl;
      return (1);
    }
  catch (const std::exception &e)
    {
      std::cerr << "EXCEPTION: " << e.what() << std::endl;
      return (1);
    }
  return (0);
}
