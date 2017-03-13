#include <chrono>
#include "RessourcesV2.hpp"
#include "DrawMap.hpp"
#include "Sound.hpp"

RessourcesV2::RessourcesV2()
{
  /*_drawMaps[OT_Player] = Ptr<DrawMap>(new DrawMap("./Sprite_V3/allies.png"));
  _drawMaps[OT_Mob] = Ptr<DrawMap>(new DrawMap("./Sprite_V3/mobs.png"));
  _drawMaps[OT_Boss] = Ptr<DrawMap>(new DrawMap("./Sprite_V3/bosses.png"));
  _drawMaps[OT_MisAlly] = Ptr<DrawMap>(new DrawMap("./Sprite_V3/misAllies.png"));
  _drawMaps[OT_MisFoe] = Ptr<DrawMap>(new DrawMap("./Sprite_V3/misFoes.png"));
  _drawMaps[OT_Bonus] = Ptr<DrawMap>(new DrawMap("./Sprite_V3/bonuses.png"));
  _fxDrawMap = Ptr<DrawMap>(new DrawMap("./Sprite_V3/fx.png"));*/

  _drawMaps[OT_Player] = Ptr<DrawMap>(new DrawMap("./Sprite_V2/Ally.png"));
  _drawMaps[OT_Mob] = Ptr<DrawMap>(new DrawMap("./Sprite_V2/Empire.png"));
  _drawMaps[OT_Boss] = Ptr<DrawMap>(new DrawMap("./Sprite_V2/Tentacle.png"));
  _drawMaps[OT_MisAlly] = Ptr<DrawMap>(new DrawMap("./Sprite_V2/Projectile_Alliance.png"));
  _drawMaps[OT_MisFoe] = Ptr<DrawMap>(new DrawMap("./Sprite_V2/EnemyProjectiles.png"));
  _drawMaps[OT_Bonus] = Ptr<DrawMap>(new DrawMap("./Sprite_V2/bonus.png"));
  _fxDrawMap = Ptr<DrawMap>(new DrawMap("./Sprite_V2/explosion.png"));
  _statDrawMap = Ptr<DrawMap>(new DrawMap("./Sprite_V2/dead.png"));

  _allyDatas[0] = FourInt(0, 0, 32, 16);

  _mobDatas[MT_GreenArmor] = FourInt(0, 82, 56, 56);
  _mobDatas[MT_LittleShip] = FourInt(0, 0, 21, 24);
  _mobDatas[MT_BrownArmor] = FourInt(0, 25, 32, 22);
  _mobDatas[MT_Butterfly] = FourInt(0, 0, 32, 22);
  _mobDatas[MT_MecaTurret] = FourInt(0, 0, 32, 22);
  _mobDatas[MT_MecaCrab] = FourInt(0, 187, 32, 31);
  _mobDatas[MT_Centiped] = FourInt(0, 219, 62, 54);
  _mobDatas[MT_Crab] = FourInt(0, 274, 32, 28);
  _mobDatas[MT_RedArmor] = FourInt(0, 139, 60, 47);
  _mobDatas[MT_ShipMob] = FourInt(0, 303, 32, 22);
  _mobDatas[MT_None] = FourInt(0, 0, 0, 0);

  _bossDatas[MT_Tentacle] = FourInt(0, 0, 139, 262);


  _misAllyDatas[0] = FourInt(0, 0, 65, 14);
  _misAllyDatas[1] = FourInt(0, 60, 80, 16);

  _misMobDatas[MT_LittleShip] = FourInt(0, 11, 32, 14);
  _misMobDatas[MT_Centiped] = FourInt(0, 48, 16, 13);
  _misMobDatas[MT_GreenArmor] = FourInt(0, 26, 48, 4);
  _misMobDatas[MT_RedArmor] = FourInt(0, 30, 63, 16); 
  _misMobDatas[MT_ShipMob] = FourInt(0, 0, 29, 10);
  _misMobDatas[MT_Tentacle] = FourInt(0, 62, 36, 33);
  _misMobDatas[MT_MecaCrab] = FourInt(0, 48, 16, 13);

  _fxDatas[0] = FourInt(0, 160, 64, 64);

  _bonusDatas[BT_HealthPack] = FourInt(0, 87, 46, 28); 
  _bonusDatas[BT_None] = FourInt(0, 0, 46, 28); 
  _bonusDatas[BT_FireRateBooster] = FourInt(0, 29, 46, 28);
  _bonusDatas[BT_DamageBooster] = FourInt(0, 58, 46, 28);

  _sound[0] = Ptr<Sound>(new Sound("../Ressources/SoundEffect/Kavinsky.ogg", 1));
  _sound[1] = Ptr<Sound>(new Sound("../Ressources/SoundEffect/Game_Blaster.wav", 0));
  _sound[2] = Ptr<Sound>(new Sound("../Ressources/SoundEffect/Game_Laser.wav", 0));
  _sound[3] = Ptr<Sound>(new Sound("../Ressources/SoundEffect/Explosion/Game_Explod1.wav", 0));
}

RessourcesV2::~RessourcesV2()
{
}


void	RessourcesV2::playSound(int a)
{
  (_sound[a].get())->play();
}

void	RessourcesV2::stopSound(int a)
{
  (_sound[a].get())->stop();
}

void	RessourcesV2::draw(ObjectType ot, MobType mt, BonusType bt, int id, int x, int y, int speedY, int dmgs)
{
  FourInt coords(0, 0, 0, 0);
  int player = 0;
  int pose = 0;
  
  if (ot == OT_Player)
    player = id;
  if (ot == OT_Mob || ot == OT_Player)
    {
      if (speedY > 0)
        pose = 2;
      else if (speedY < 0)
	pose = 0;
      else
	pose = 1;
    }
  if (ot == OT_Player)
    coords = _allyDatas[0];
  else if (ot == OT_Mob)
    coords  = _mobDatas[mt];
  else if (ot == OT_Boss && mt == MT_Tentacle)
    coords  = _bossDatas[mt];
  else if (ot == OT_Boss)
    coords = _mobDatas[mt];
  else if (ot == OT_MisAlly)
    {
      if (dmgs >= 2)
	coords  = _misAllyDatas[1];
      else
	coords  = _misAllyDatas[0];
    }
  else if (ot == OT_MisFoe)
    coords  = _misMobDatas[mt];
  else if (ot == OT_Bonus)
    coords  = _bonusDatas[bt];
  (_drawMaps[ot].get())->addObject(x, y,
				   coords.a + (pose * coords.c + pose * 1),
				   coords.b + (player * coords.d + player * 1),
				   coords.c, coords.d);
}

void RessourcesV2::drawFx(int x, int y, int type, int frame)
{
  FourInt lele = _fxDatas[type];

  (_fxDrawMap.get())->addObject(x, y,
				lele.a + (frame * (lele.d + 1)), 
				lele.b,
				lele.c,
				lele.d);
}

void RessourcesV2::draw(sf::RenderWindow &rw, size_t sizeObj, size_t sizeExpl)
{
  rw.draw((_drawMaps[OT_Player].get())->getArray(), (_drawMaps[OT_Player].get())->getTexture());
  (_drawMaps[OT_Player].get())->clear(sizeObj);
  
  rw.draw((_drawMaps[OT_Mob].get())->getArray(), (_drawMaps[OT_Mob].get())->getTexture());
  (_drawMaps[OT_Mob].get())->clear(sizeObj);
  
  rw.draw((_drawMaps[OT_Boss].get())->getArray(), (_drawMaps[OT_Boss].get())->getTexture());
  (_drawMaps[OT_Boss].get())->clear(sizeObj);
  
  rw.draw((_drawMaps[OT_MisAlly].get())->getArray(), (_drawMaps[OT_MisAlly].get())->getTexture());
  (_drawMaps[OT_MisAlly].get())->clear(sizeObj);
  
  rw.draw((_drawMaps[OT_MisFoe].get())->getArray(), (_drawMaps[OT_MisFoe].get())->getTexture());
  (_drawMaps[OT_MisFoe].get())->clear(sizeObj);
  
  rw.draw((_drawMaps[OT_Bonus].get())->getArray(), (_drawMaps[OT_Bonus].get())->getTexture());
  (_drawMaps[OT_Bonus].get())->clear(sizeObj);
  
  rw.draw((_fxDrawMap.get())->getArray(), (_fxDrawMap.get())->getTexture());
  (_fxDrawMap.get())->clear(sizeExpl + 20);
}

void	RessourcesV2::drawDead(sf::RenderWindow &rw)
{
  (_statDrawMap.get())->addObject(813, 80,
				   0,
				   0,
				   354, 172);
  rw.draw((_statDrawMap.get())->getArray(), (_statDrawMap.get())->getTexture());
  (_statDrawMap.get())->clear(1);
}
