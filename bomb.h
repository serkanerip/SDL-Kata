#ifndef BOMB_H
#define BOMB_H

#include "sprite.h"

class Bomb
{
public:
  Bomb();
  void update(Bomb *bombs, int i);
  void draw(Graphics graphics);
  void setSprite(Sprite _sprite);
  void spawnPoint();
  Sprite _sprite;

private:
  int fallSpeed;
};
#endif