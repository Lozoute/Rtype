#ifndef IRESSOURCES_HPP_
# define IRESSOURCES_HPP_

#include "ISprite.hpp"
#include "ISound.hpp"

enum	e_Music {
  MENU,
  GAME
};

enum	GameSprite{
  HealthPack,
  DamageBooster,
  FireRateBooster,
  Ship1,
  Ship2,
  Ship3,
  Ship4,
  LittleShip,
  BrownArmor,
  Butterfly,
  GreenArmor,
  RedArmor,
  MecaTurret,
  MecaCrab,
  Centiped,
  Crab,
  ShipMob,
  Tentacle,
  FireSprite,
  LittleBlueBlaster,
  FatBlueBlaster,
  RedMissile,
  GreenMissile,
  Caterpillar,
  GreenEgg,
  Jellyfish,
  Bubble,
  Caca,
  BlueBullet,
  Orange,
  LittleYellowBlaster,
  FatYellowBlaster,
  RedLaser,
  BlueExplode,
  Explode1,
  Explode2,
  Explode3,
  Explode4,
  FatExplode,
  HudText,
  Hp,
  Dead,
  You,
  NextStage,
  FireBlue,
  FirePink,
  FireGreen,
  FireRed,
  FatFireBlue,
  FatFirePink,
  FatFireGreen,
  FatFireRed
};

enum	GameSound{
  MenuMusic,
  GameMusic,
  MenuSelect,
  MenuAccept,
  MenuConnect,
  GameLaser,
  GameBlaster,
  ExplodeAlien1,
  ExplodeAlien2,
  ExplodeMecha1,
  ExplodeMecha2,
  ExplodeMecha3,
  ExplodeMecha4
};

class IRessources{
public:
  virtual ~IRessources(){}
  virtual void		 setVolumeMusic(const float volume) = 0;
  virtual void		 setVolumeEffect(const float volume) = 0;
  virtual void		 playBackgroundMusic(e_Music) = 0;
  virtual ISprite	*get_sprite(GameSprite) = 0;
  virtual ISound	*get_sound(GameSound) = 0;
};

# endif // !IRESSOURCES_HPP_
