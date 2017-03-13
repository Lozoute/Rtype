#ifndef RESSOURCES_HPP_
# define RESSOURCES_HPP_

# include "Sprite.hpp"
# include "Sound.hpp"

enum e_Music {
	MENU,
	GAME
};

namespace Res
{
	class Ressources
	{

		Ressources(const Ressources &){};
		Ressources& operator=(const Ressources &){ return (*this); };
	public:
		Ressources();
		~Ressources();

		//Menu BackGround
		Sprite		*_JoinBackGround;
		Sprite		*_JoinCircle;

		int _width;
		int _height;
		int _game;

		// ADD TO DLL PROJECT
		Sprite		*_HealthPack;
		Sprite		*_DamageBooster;
		Sprite		*_FireRateBooster;
		// ADD TO DLL PROJECT

		// Ship
		Sprite		*_Ship1;
		Sprite		*_Ship2;
		Sprite		*_Ship3;
		Sprite		*_Ship4;

		// Normal MOB
		Sprite		*_LittleShip;
		Sprite		*_BrownArmor;
		Sprite		*_Butterfly;
		Sprite		*_GreenArmor;
		Sprite		*_RedArmor;
		Sprite		*_MecaTurret;
		Sprite		*_MecaCrab;
		Sprite		*_Centiped;
		Sprite		*_Crab;
		Sprite		*_ShipMob;
		// Elite MOB
		Sprite		*_Tentacle;

		// Projectiles Ally
		Sprite		*_FireSprite;
		// Projectiles Enemy
		Sprite		*_LittleBlueBlaster;
		Sprite		*_FatBlueBlaster;
		Sprite		*_RedMissile;
		Sprite		*_GreenMissile;
		Sprite		*_Caterpillar;
		Sprite		*_GreenEgg;
		Sprite		*_Jellyfish;
		Sprite		*_Bubble;
		Sprite		*_Caca;
		Sprite		*_BlueBullet;
		Sprite		*_Orange;
		Sprite		*_LittleYellowBlaster;
		Sprite		*_FatYellowBlaster;
		Sprite		*_RedLaser;


		// Explosions
		Sprite		*_BlueExplode;
		Sprite		*_Explode1;
		Sprite		*_Explode2;
		Sprite		*_Explode3;
		Sprite		*_Explode4;
		Sprite		*_FatExplode;

		Sprite		*_hudText;
		Sprite		*_hp;

		Sound		*_menuMusic;
		Sound		*_menuSelect;
		Sound		*_menuAccept;
		Sound		*_menuConnect;
		Sound		*_gameMusic;
		Sound		*_gameLaser;
		Sound		*_gameBlaster;
		Sound		*_explodeAlien1;
		Sound		*_explodeAlien2;
		Sound		*_explodeMecha1;
		Sound		*_explodeMecha2;
		Sound		*_explodeMecha3;
		Sound		*_explodeMecha4;


		sf::Font	*_font;

		void		setVolumeMusic(const float volume);
		void		setVolumeEffect(const float volume);
		void		playBackgroundMusic(const e_Music&);
	};
	Ressources *getRessources(Ressources *res = NULL);
}

#endif /* !RESSOURCES_HPP_ */