#include <utility>
#include "Ressources.hpp"

Res::Ressources *Res::Ressources::_res = nullptr;

Res::Ressources::Ressources()
{
  int	i = 0;
  Sprite::Info spriteInfo[52] = {
    Sprite::Info("../Ressources/Sprite/bonus.png", 0, 0, 46, 28),
    Sprite::Info("../Ressources/Sprite/bonus.png", 0, 29, 46, 28),
    Sprite::Info("../Ressources/Sprite/bonus.png", 0, 58, 46, 28),
    Sprite::Info("../Ressources/Sprite/Ship.png", 0, 0, 32, 16),
    Sprite::Info("../Ressources/Sprite/Ship.png", 0, 17, 32, 16),
    Sprite::Info("../Ressources/Sprite/Ship.png", 0, 34, 32, 16),
    Sprite::Info("../Ressources/Sprite/Ship.png", 0, 51, 32, 16),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 0, 21, 24),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 58, 32, 32),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 115, 27, 23),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 139, 56, 56),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 244, 60, 47),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 346, 30, 26),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 437, 32, 31),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 643, 62, 54),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 918, 32, 28),
    Sprite::Info("../Ressources/Sprite/enemy.png", 0, 947, 32, 22),
    Sprite::Info("../Ressources/SpriteV3/Tentacle.png", 0, 0, 140, 262),
    Sprite::Info("../Ressources/Sprite/projectiles_ally.png", 0, 31, 48, 13),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 30, 0, 29, 10),
    Sprite::Info("../Ressources/Sprite/Projectiles_Empire2.png", 0, 11, 17, 16),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 29, 15, 11),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 42, 16, 13),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 17, 87, 16, 13),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 66, 230, 32, 29),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 294, 31, 32),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 327, 32, 29),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 358, 12, 12),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 370, 12, 10),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 381, 7, 6),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 389, 31, 30),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 0, 455, 31, 30),
    Sprite::Info("../Ressources/Sprite/projectiles_enemy.png", 49, 520, 48, 4),
    Sprite::Info("../Ressources/Sprite/explosion.png", 0, 0, 32, 32),
    Sprite::Info("../Ressources/Sprite/explosion.png", 0, 33, 32, 29),
    Sprite::Info("../Ressources/Sprite/explosion.png", 0, 63, 32, 30),
    Sprite::Info("../Ressources/Sprite/explosion.png", 0, 94, 32, 32),
    Sprite::Info("../Ressources/Sprite/explosion.png", 0, 127, 32, 32),
    Sprite::Info("../Ressources/Sprite/explosion.png", 0, 160, 64, 64),
    Sprite::Info("../Ressources/Sprite/HUD.png", 0, 0, 780, 400),
    Sprite::Info("../Ressources/Sprite/HealthPoint1.png", 0, 0, 644, 33),
    Sprite::Info("../Ressources/Sprite/dead.png", 0, 0, 354, 172),
    Sprite::Info("../Ressources/Sprite/you.png", 0, 0, 28, 45),
    Sprite::Info("../Ressources/Sprite/nextStage.png", 0, 0, 700, 168),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance.png", 0, 0, 65, 14),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance.png", 0, 15, 65, 14),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance.png", 0, 30, 65, 14),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance.png", 0, 45, 65, 14),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance2.png", 0, 60, 80, 16),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance2.png", 0, 77, 80, 16),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance2.png", 0, 94, 80, 16),
    Sprite::Info("../Ressources/Sprite/Projectile_Alliance2.png", 0, 110, 80, 16),
  };

  char const *soundName[] = {
    "../Ressources/SoundEffect/Menu_Soundtrack.wav",
    "../Ressources/SoundEffect/Kavinsky.ogg",
    "../Ressources/SoundEffect/Menu_Selection.wav",
    "../Ressources/SoundEffect/Menu_Accept.wav",
    "../Ressources/SoundEffect/Shields_Up_Weapon_Online.wav",
    "../Ressources/SoundEffect/Game_Laser.wav",
    "../Ressources/SoundEffect/Game_Blaster.wav",
    "../Ressources/SoundEffect/Explosion/Game_Alien1.wav",
    "../Ressources/SoundEffect/Explosion/Game_Alien2.wav",
    "../Ressources/SoundEffect/Explosion/Game_Explod1.wav",
    "../Ressources/SoundEffect/Explosion/Game_Explod2.WAV",
    "../Ressources/SoundEffect/Explosion/Game_Explod3.WAV",
    "../Ressources/SoundEffect/Explosion/Game_Explod4.wav"
  };

  for (auto it = _sprites.begin(); it != _sprites.end(); ++it)
    it->init(spriteInfo[i++]);

  i = 0;
  for (auto it = _sounds.begin(); it != _sounds.end(); ++it)
    it->init(soundName[i++]);

  _width = 1920;
  _height = 1080;
  _sprites[HudText].getSprite().setScale(1.2f, 1.2f);
  _sprites[Hp].getSprite().setScale(1.2f, 1.2f);

  _sounds[MenuMusic].getSound()->setLoop(true);
  _sounds[GameMusic].getSound()->setLoop(true);
  for (auto it = _sounds.begin() + 2; it != _sounds.end(); ++it)
    it->getSound()->setLoop(false);
  _font.loadFromFile("../Ressources/font/hemi_head_bd_it.ttf");
  _sounds[ExplodeAlien1].getSound()->setVolume(40);
  _sounds[ExplodeAlien2].getSound()->setVolume(40);
  _sounds[ExplodeMecha1].getSound()->setVolume(40);
  _sounds[ExplodeMecha2].getSound()->setVolume(40);
  _sounds[ExplodeMecha3].getSound()->setVolume(40);
  _sounds[ExplodeMecha4].getSound()->setVolume(40);
}

Res::Ressources::~Ressources()
{}

void		Res::Ressources::setVolumeMusic(const float volume)
{
  _sounds[MenuMusic].getSound()->setVolume(volume);
  _sounds[GameMusic].getSound()->setVolume(volume);
}

void		Res::Ressources::setVolumeEffect(const float volume)
{
  for (auto it = _sounds.begin() + 2; it != _sounds.end(); ++it)
    it->getSound()->setVolume(volume);
}


void		Res::Ressources::playBackgroundMusic(e_Music music)
{
  if (music == MENU && !_sounds[MenuMusic].isPlaying())
  {
    _sounds[GameMusic].stop();
    _sounds[MenuMusic].play();
  }
  else if (music == GAME && !_sounds[GameMusic].isPlaying())
  {
    _sounds[MenuMusic].stop();
    _sounds[GameMusic].play();
  }
}

ISprite *Res::Ressources::get_sprite(GameSprite id){
  if (id >= 0 && id < 52)
    return (&_res->_sprites[id]);
  return nullptr;
}
ISound *Res::Ressources::get_sound(GameSound id){
  if (id >= 0 && id < 13)
    return (&_res->_sounds[id]);
  return nullptr;
}

Res::Ressources *Res::Ressources::get_res(){
  return  ((_res) ? _res : (_res = new Res::Ressources));
}

extern "C" {
  EXPORT ISprite *get_sprite(GameSprite id){
    if (id >= 0 && id < 52)
      return (&Res::Ressources::get_res()->_sprites[id]);
    return nullptr;
  }
  EXPORT  ISound *get_sound(GameSound id){
    if (id >= 0 && id < 13)
      return (&Res::Ressources::get_res()->_sounds[id]);
    return nullptr;
  }
  EXPORT IRessources *get_ressources(){
    return Res::Ressources::get_res();
  }
  EXPORT sf::Font *get_font(){
    return &(Res::Ressources::get_res()->_font);
  }
  EXPORT  int *play_sound(GameSound id){
    if (id >= 0 && id < 13)
      Res::Ressources::get_res()->_sounds[id].play();
    return nullptr;
  }
}
