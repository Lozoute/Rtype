#ifndef SRTP_HPP_
# define SRTP_HPP_

# include <iostream>
# include <string>

enum			ObjectType
  {
    OT_Player		= 0,
    OT_Mob		= 1,
    OT_Boss		= 2,
    OT_MisAlly		= 3,
    OT_MisFoe		= 4,
    OT_Bonus		= 5,
  };

enum			MobType
  {
    MT_LittleShip	= 0,
    MT_BrownArmor	= 1,
    MT_Butterfly	= 2,
    MT_GreenArmor	= 3,
    MT_RedArmor		= 4,
    MT_MecaTurret	= 5,
    MT_MecaCrab		= 6,
    MT_Centiped		= 7,
    MT_Crab		= 8,
    MT_ShipMob		= 9,
    MT_Tentacle		= 10,
    MT_None		= 11,
};

enum			BonusType
  {
    BT_HealthPack	= 0,
    BT_DamageBooster	= 1,
    BT_FireRateBooster	= 2,
    BT_None		= 3,
  };

enum			CmdProto
  {
    CMDP_Connect	= 0,
    CMDP_Disconnect	= 1,
    CMDP_None		= 2,
  };

enum			CmdClient
  {
    CMDC_New		= 0,
    CMDC_Delete		= 1,
    CMDC_Attack		= 2,
    CMDC_Update		= 3,
    CMDC_Welcome	= 4,
    CMDC_Stage		= 5,
    CMDC_Score		= 6,
    CMDC_None		= 7,
  };

struct			Srtp
{
  /// Protocol
  int			_idDest;
  CmdProto		_cmdProto;

  /// Client
  CmdClient		_cmdClient;
  ObjectType		_objType;
  MobType		_mobType;
  BonusType		_bonusType;
  int			_idGame;
  int			_idObject;
  int			_idMissile;
  int			_posX;
  int			_posY;
  int			_speedX;
  int			_speedY;
  int			_hp;
  bool			_shield;

			/*
			** Default Constructor
			*/
  Srtp			()
			: _idDest(-1), _cmdProto(CMDP_None), _cmdClient(CMDC_None),
			  _objType(OT_Player), _mobType(MT_None), _bonusType(BT_None),
			  _idGame(-1),
			  _idObject(-1), _idMissile(-1), _posX(-1),
			  _posY(-1), _speedX(-1), _speedY(-1), _hp(-1), _shield(false) {}

			/*
			** Complete Constructor, When You Want To Initialize Every Fields
			*/
  Srtp			(int idDest, CmdProto cmdP, CmdClient cmdC,
			 ObjectType oT, MobType mT, BonusType bT, int idG, int idO,
			 int idM, int posX, int posY, int sX, int sY, int hP, bool shield)
			: _idDest(idDest), _cmdProto(cmdP), _cmdClient(cmdC),
			  _objType(oT), _mobType(mT), _bonusType(bT), _idGame(idG),
			  _idObject(idO), _idMissile(idM), _posX(posX),
			  _posY(posY), _speedX(sX), _speedY(sY), _hp(hP),
			  _shield(shield) {}

			/*
			** Protocol Oriented Constructor,
			** When You Don't Care About Client Fields
			*/
  Srtp			(int idD, CmdProto cmdP)
			: _idDest(idD), _cmdProto(cmdP), _cmdClient(CMDC_None),
			  _objType(OT_Player), _mobType(MT_None), _bonusType(BT_None),
			  _idGame(-1),
			  _idObject(-1), _idMissile(-1), _posX(-1),
			  _posY(-1), _speedX(-1), _speedY(-1), _hp(-1), _shield(false) {}

			/*
			**Copy Constructor, When You're A Copy-Cat
			*/
  Srtp			(const Srtp &O)
			: _idDest(O._idDest), _cmdProto(O._cmdProto), _cmdClient(O._cmdClient),
			  _objType(O._objType), _mobType(O._mobType), _bonusType(O._bonusType),
			  _idGame(O._idGame),
			  _idObject(O._idObject), _idMissile(O._idMissile), _posX(O._posX),
			  _posY(O._posY), _speedX(O._speedX), _speedY(O._speedY),
			  _hp(O._hp), _shield(O._shield) {}
};

#endif /* !SRTP_HPP_ */
