#ifndef RESSOURCES_HPP_
# define RESSOURCES_HPP_

# include "IRessources.hpp"
# include "Sprite.hpp"
# include "Sound.hpp"
# include <vector>
# include <tuple>
# include <array>


namespace Res
{
  class Ressources : public IRessources
  {
  private:
    Ressources();
  public:
    Ressources(const Ressources &) = delete;
    Ressources		  &operator=(const Ressources &) = delete;
    ~Ressources();

    static Ressources	  *_res;
    static Ressources	  *get_res();
    int _width;
    int _height;
    std::array<Sprite, 52> _sprites;
    std::array<Sound, 13>  _sounds;

    sf::Font		  _font;

    void		  setVolumeMusic(const float volume);
    void		  setVolumeEffect(const float volume);
    void		  playBackgroundMusic(e_Music);
    ISprite		  *get_sprite(GameSprite);
    ISound		  *get_sound(GameSound);
  };
}

# if defined(WIN32) || defined (_WIN32)
//  Microsoft
# define EXPORT __declspec(dllexport)
# define IMPORT __declspec(dllimport)
# elif defined(linux) || defined (__unix__)
//  UNIX
# define EXPORT __attribute__((visibility("default")))
# define IMPORT
# else
//  unknown
# define EXPORT
# define IMPORT
# pragma warning Unknown dynamic link import/export semantics.
# endif

#endif /* !RESSOURCES_HPP_ */
