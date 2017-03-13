#include "Ressources.hpp"

Res::Ressources::Ressources()
{
        _width = 1920;
	_height = 1080;
	_game = 0;

	_HealthPack = new Sprite("../Ressources/Sprite/bonus.png", 0, 0, 46, 28);
	_DamageBooster = new Sprite("../Ressources/Sprite/bonus.png", 0, 29, 46, 28);
	_FireRateBooster = new Sprite("../Ressources/Sprite/bonus.png", 0, 58, 46, 28);

	_Ship1 = new Sprite("../Ressources/Sprite/Ship.png", 0, 0, 32, 16);
	_Ship2 = new Sprite("../Ressources/Sprite/Ship.png", 0, 17, 32, 16);
	_Ship3 = new Sprite("../Ressources/Sprite/Ship.png", 0, 34, 32, 16);
	_Ship4 = new Sprite("../Ressources/Sprite/Ship.png", 0, 51, 32, 16);

	_LittleShip = new Sprite("../Ressources/Sprite/enemy.png", 0, 0, 21, 24);
	_BrownArmor = new Sprite("../Ressources/Sprite/enemy.png", 0, 58, 32, 32);
	_Butterfly = new Sprite("../Ressources/Sprite/enemy.png", 0, 115, 27, 23);
	_GreenArmor = new Sprite("../Ressources/Sprite/enemy.png", 0, 139, 56, 56);
	_RedArmor = new Sprite("../Ressources/Sprite/enemy.png", 0, 244, 60, 47);
	_MecaTurret = new Sprite("../Ressources/Sprite/enemy.png", 0, 346, 30, 26);
	_MecaCrab = new Sprite("../Ressources/Sprite/enemy.png", 0, 437, 32, 31);
	_Centiped = new Sprite("../Ressources/Sprite/enemy.png", 0, 643, 62, 54);
	_Crab = new Sprite("../Ressources/Sprite/enemy.png", 0, 918, 32, 28);
	_ShipMob = new Sprite("../Ressources/Sprite/enemy.png", 0, 947, 32, 22);
	//_Tentacle = new Sprite("../Ressources/Sprite/BossTentacle.png", 0, 0, 139, 262);
	_Tentacle = new Sprite("../Ressources/Sprite/Tentacle.png", 0, 0, 140, 262);

	_FireSprite = new Sprite("../Ressources/Sprite/projectiles_ally.png", 0, 31, 48, 13);
	_LittleBlueBlaster = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 30, 0, 29, 10);
	_FatBlueBlaster = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 64, 12, 63, 14);
	_RedMissile = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 29, 15, 11);
	_GreenMissile = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 42, 16, 13);
	_Caterpillar = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 17, 87, 16, 13);
	_GreenEgg = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 66, 230, 32, 29);
	_Jellyfish = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 294, 31, 32);
	_Bubble = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 327, 32, 29);
	_Caca = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 358, 12, 12);
	_BlueBullet = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 370, 12, 10);
	_Orange = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 381, 7, 6);
	_LittleYellowBlaster = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 389, 31, 30);
	_FatYellowBlaster = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 0, 455, 31, 30);
	_RedLaser = new Sprite("../Ressources/Sprite/projectiles_enemy.png", 49, 520, 48, 4);

	_BlueExplode = new Sprite("../Ressources/Sprite/explosion.png", 0, 0, 32, 32);
	_Explode1 = new Sprite("../Ressources/Sprite/explosion.png", 0, 33, 32, 29);
	_Explode2 = new Sprite("../Ressources/Sprite/explosion.png", 0, 63, 32, 30);
	_Explode3 = new Sprite("../Ressources/Sprite/explosion.png", 0, 94, 32, 32);
	_Explode4 = new Sprite("../Ressources/Sprite/explosion.png", 0, 127, 32, 32);
	_FatExplode = new Sprite("../Ressources/Sprite/explosion.png", 0, 160, 64, 64);

	_hudText = new Sprite("../Ressources/Sprite/HUD.png", 0, 0, 780, 400);
	_hudText->getSprite().setScale(1.2, 1.2);
	//_hp = new Sprite("../Ressources/Sprite/HealthPoint.png", 0, 0, 206, 15);
	_hp = new Sprite("../Ressources/Sprite/HealthPoint1.png", 0, 0, 644, 33);
	//_hp->getSprite().setScale(1.2, 1.2);

	_menuMusic = new Sound("../Ressources/SoundEffect/Menu_Soundtrack.wav");
	_menuMusic->getSound()->setLoop(true);
	_menuSelect = new Sound("../Ressources/SoundEffect/Menu_Selection.wav");
	_menuSelect->getSound()->setLoop(false);
	_menuAccept = new Sound("../Ressources/SoundEffect/Menu_Accept.wav");
	_menuAccept->getSound()->setLoop(false);
	_menuConnect = new Sound("../Ressources/SoundEffect/Shields_Up_Weapon_Online.wav");
	_menuConnect->getSound()->setLoop(false);
	//_gameMusic = new Sound("../Ressources/SoundEffect/Game_Soundtrack.wav");
	//_gameMusic = new Sound("../Ressources/SoundEffect/EpicBackgroundMusic.wav");
	_gameMusic = new Sound("../Ressources/SoundEffect/Kavinsky.ogg");
	_gameMusic->getSound()->setLoop(true);


	_gameLaser = new Sound("../Ressources/SoundEffect/Game_Laser.wav");
	_gameLaser->getSound()->setLoop(false);
	_gameBlaster = new Sound("../Ressources/SoundEffect/Game_Blaster.wav");
	_gameBlaster->getSound()->setLoop(false);
	_explodeAlien1 = new Sound("../Ressources/SoundEffect/Explosion/Game_Alien1.wav");
	_explodeAlien1->getSound()->setLoop(false);
	_explodeAlien2 = new Sound("../Ressources/SoundEffect/Explosion/Game_Alien2.wav");
	_explodeAlien2->getSound()->setLoop(false);
	_explodeMecha1 = new Sound("../Ressources/SoundEffect/Explosion/Game_Explod1.wav");
	_explodeMecha1->getSound()->setLoop(false);
	_explodeMecha2 = new Sound("../Ressources/SoundEffect/Explosion/Game_Explod2.WAV");
	_explodeMecha2->getSound()->setLoop(false);
	_explodeMecha3 = new Sound("../Ressources/SoundEffect/Explosion/Game_Explod3.WAV");
	_explodeMecha3->getSound()->setLoop(false);
	_explodeMecha4 = new Sound("../Ressources/SoundEffect/Explosion/Game_Explod4.wav");
	_explodeMecha4->getSound()->setLoop(false);

	_explodeAlien1->getSound()->setVolume(40);
	_explodeAlien2->getSound()->setVolume(40);
	_explodeMecha1->getSound()->setVolume(40);
	_explodeMecha2->getSound()->setVolume(40);
	_explodeMecha3->getSound()->setVolume(40);
	_explodeMecha4->getSound()->setVolume(40);

	_font = new sf::Font;
	_font->loadFromFile("../Ressources/font/hemi_head_bd_it.ttf");
}

Res::Ressources::~Ressources()
{
	delete _Ship1;
	delete _Ship2;
	delete _Ship3;
	delete _Ship4;

	delete _LittleShip;
	delete _BrownArmor;
	delete _Butterfly;
	delete _GreenArmor;
	delete _RedArmor;
	delete _MecaTurret;
	delete _MecaCrab;
	delete _Centiped;
	delete _Crab;
	delete _ShipMob;
	delete _Tentacle;

	delete _FireSprite;
	delete _LittleBlueBlaster;
	delete _FatBlueBlaster;
	delete _RedMissile;
	delete _GreenMissile;
	delete _Caterpillar;
	delete _GreenEgg;
	delete _Jellyfish;
	delete _Bubble;
	delete _Caca;
	delete _BlueBullet;
	delete _Orange;
	delete _LittleYellowBlaster;
	delete _FatYellowBlaster;
	delete _RedLaser;

	delete _BlueExplode;
	delete _Explode1;
	delete _Explode2;
	delete _Explode3;
	delete _Explode4;
	delete _FatExplode;

	delete _hudText;
	delete _hp;

	delete _menuMusic;
	delete _menuSelect;
	delete _menuAccept;
	delete _menuConnect;
	delete _gameMusic;

	delete _gameLaser;
	delete _gameBlaster;
	delete _explodeAlien1;
	delete _explodeAlien2;
	delete _explodeMecha1;
	delete _explodeMecha2;
	delete _explodeMecha3;
	delete _explodeMecha4;

	delete _font;
}

Res::Ressources *Res::getRessources(Res::Ressources *res)
{
	static Res::Ressources *ressource;

	if (res != NULL)
		ressource = res;
	return (ressource);
}

void		Res::Ressources::setVolumeMusic(const float volume)
{
	_menuMusic->getSound()->setVolume(volume);
	_gameMusic->getSound()->setVolume(volume);
}

void		Res::Ressources::setVolumeEffect(const float volume)
{
	_menuSelect->getSound()->setVolume(volume);
	_menuAccept->getSound()->setVolume(volume);
	_menuConnect->getSound()->setVolume(volume);
	_gameLaser->getSound()->setVolume(volume);
	_gameBlaster->getSound()->setVolume(volume);
	_explodeAlien1->getSound()->setVolume(volume);
	_explodeAlien2->getSound()->setVolume(volume);
	_explodeMecha1->getSound()->setVolume(volume);
	_explodeMecha2->getSound()->setVolume(volume);
	_explodeMecha3->getSound()->setVolume(volume);
	_explodeMecha4->getSound()->setVolume(volume);
}


void		Res::Ressources::playBackgroundMusic(const e_Music& music)
{
	if (music == MENU && (_menuMusic->isPlaying() == false))
	{
		_gameMusic->stop();
		_menuMusic->play();
	}
	else if (music == GAME && (_gameMusic->isPlaying() == false))
	{
		_menuMusic->stop();
		_gameMusic->play();
	}
}
