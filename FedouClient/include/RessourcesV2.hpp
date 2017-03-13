#ifndef RESSOURCESV2_HPP_
# define RESSOURCESV2_HPP_

# include <map>
# include "Srtp.hpp"
# include "Loader.hpp"
# include "API_Mutex.hpp"
# include "API_Error.hpp"
# include "FourInt.hpp"
# include "Sound.hpp"
# include "DrawMap.hpp"


class RessourcesV2
{
private:
  std::map<ObjectType, Ptr<DrawMap> > _drawMaps;
  Ptr<DrawMap> _fxDrawMap;
  Ptr<DrawMap> _statDrawMap;
  std::map<int ,FourInt> _allyDatas;
  std::map<MobType ,FourInt> _mobDatas;
  std::map<MobType ,FourInt> _bossDatas;
  std::map<int ,FourInt> _misAllyDatas;
  std::map<MobType ,FourInt> _misMobDatas;
  std::map<BonusType, FourInt> _bonusDatas;
  std::map<int ,FourInt> _fxDatas;   
  std::map<int, Ptr<Sound> > _sound;
  


  RessourcesV2(const RessourcesV2 &){};
  RessourcesV2& operator=(const RessourcesV2 &){ return (*this); };  
public:
  RessourcesV2();
  ~RessourcesV2();

  void     playSound(int);
  void     stopSound(int);
  void	   draw(ObjectType, MobType, BonusType, int, int, int, int, int);
  void     draw(sf::RenderWindow &rw, size_t, size_t);
  void	   drawFx(int x, int y, int type, int frame);
  void	   drawDead(sf::RenderWindow &rw);
};


#endif /* !RESSOURCESV2_HPP_ */
