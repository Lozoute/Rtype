//
// main.cpp for  in /home/ssj/rendu/rtype/API/API_Loader
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Sat Jul 18 14:17:04 2015 jordan sabbah
// Last update Sat Jul 18 14:32:29 2015 jordan sabbah
//

#include "Loader.hpp"
#include "API_Protocol.hpp"
#include <stdlib.h>

int	main(int, char **)
{
  Loader		  loader;
  API_Protocol::IProtocol *prot = loader.getPtr<API_Protocol::IProtocol>("../API/SOs/lib_API_Protocol.so", "protocol_server", 4242);
  delete prot;
  return 1;
}
