#ifndef SRTPLIGHT_HPP_
# define SRTPLIGHT_HPP_

struct			SrtpLight
{
  uint16_t		_object : 3;
  uint16_t		_mob : 4;
  uint16_t		_bonus : 3;
  uint16_t		_client : 3;
  uint16_t		_shield : 1;
  // _shield(1bit), CmdClient(3bits)
  // ObjectType(3bits), Mobtype(4bits)
  // BonusType(3bits)
  uint16_t		_posX;
  uint16_t		_posY;
  int16_t		_hp;
  int			_idGame;
  int			_idObject;
  int			_idMissile;
  int			_speedX;
  int			_speedY;

  SrtpLight()
    :  _object(0), _mob(0), _bonus(0),
       _client(0), _shield(0),
       _posX(0), _posY(0), _hp(0),
       _idGame(0), _idObject(0),
       _idMissile(0), _speedX(0),
       _speedY(0)
  {}

  SrtpLight(Srtp const &srtp)
  {
    _shield = srtp._shield;
    _client = srtp._cmdClient;
    _mob = srtp._mobType;
    _object = srtp._objType;
    _idGame = srtp._idGame;
    _idObject = srtp._idObject;
    _idMissile = srtp._idMissile;
    _posX = srtp._posX;
    _posY = srtp._posY;
    _hp = srtp._hp;
    _speedX = srtp._speedX;
    _speedY = srtp._speedY;
    _bonus = srtp._bonusType;
  }

  SrtpLight		&operator()(Srtp const &srtp)
  {
    _shield = srtp._shield;
    _client = srtp._cmdClient;
    _mob = srtp._mobType;
    _object = srtp._objType;
    _idGame = srtp._idGame;
    _idObject = srtp._idObject;
    _idMissile = srtp._idMissile;
    _posX = srtp._posX;
    _posY = srtp._posY;
    _hp = srtp._hp;
    _speedX = srtp._speedX;
    _speedY = srtp._speedY;
    _bonus = srtp._bonusType;
    return *this;
  }

  void			getSrtp(Srtp &srtp) const
  {
    srtp._shield = _shield;
    srtp._cmdClient = static_cast<CmdClient>(_client);
    srtp._mobType = static_cast<MobType>(_mob);
    srtp._objType = static_cast<ObjectType>(_object);
    srtp._bonusType = static_cast<BonusType>(_bonus);
    srtp._idGame = _idGame;
    srtp._idObject = _idObject;
    srtp._idMissile = _idMissile;
    srtp._posX = _posX;
    srtp._posY = _posY;
    srtp._hp = _hp;
    srtp._speedX = _speedX;
    srtp._speedY = _speedY;
  }
};

#endif // !SRTPLIGHT_HPP_
