#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include "graphics.h"
#include "sprite.h"
#include <string>

class Player
{
public:
  Player();
  ~Player();
  void update();
  void moveLeft();
  void moveRight();
  void setSprite(Sprite sprite);
  void draw(Graphics graphics);
  void animate();
  void animateLeft();
  void animateRight();
  void stopAnimate();
  Sprite _sprite;
  Uint32 animStartTime;

private:
  int x, y, frameX, frameY;
  std::string animateTurn;
  bool isAnimating;
};
#endif