#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "graphics.h"

class Sprite
{
public:
  Sprite();
  Sprite(SDL_Texture *texture, int x, int y, int w, int h);
  ~Sprite();
  void draw(Graphics graphics, const SDL_Rect *source);
  void update();
  bool checkCollision(SDL_Rect r2);
  SDL_Rect _sRect;
  SDL_Texture *_sTexture;

private:
};

#endif