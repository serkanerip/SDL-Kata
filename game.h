#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "player.h"
#include "bomb.h"
#include "fruit.h"
#include <map>
#include "gun.h"
#include <SDL2/SDL.h>

class Game
{
public:
  Game();
  ~Game();
  void gameLoop();
  void update();
  void draw();
  bool checkCollision(SDL_Rect r1, SDL_Rect r2);
  void initBombs();
  void initFruits();
  void initGame();
  void fireGun();
  void expAnimate(SDL_Rect r);
  bool gameState;
  bool gameOver;
  Graphics graphics;
  Player _player;
  Bomb _bombs[10];
  Fruit _fruits[3];

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  SDL_Texture *_background;
  SDL_Texture *_bombTexture;
  SDL_Texture *_fruitTexture;
  SDL_Texture *_ammoTexture;
  SDL_Texture *_expTexture;
  int posX;
  int bombY;
  int bombsPositions[10];
  int gamePoint;
  int gameTime;
  int gameStartTime;
  bool expStart;
  int frame;
  Uint32 gameOverTime;
};

#endif
