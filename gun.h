#ifndef GUN_H
#define GUN_H

#include "graphics.h"
#include <SDL2/SDL.h>
#include "sprite.h"

class Gun
{
public:
  Gun();
  void fire(Graphics graphics, SDL_Rect playerRect);
  void update();
  void addAmmo(int ammo);
  void setSprite(Sprite _sprite);
  int getAmmo();
  bool onFire;
  Sprite _sprite;

private:
  int ammoNumber;
};
#endif