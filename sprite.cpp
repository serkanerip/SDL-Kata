#include <SDL2/SDL.h>
#include "sprite.h"
#include <SDL2/SDL.h>

Sprite::Sprite(){};
Sprite::Sprite(SDL_Texture *texture, int x, int y, int w, int h)
{
    this->_sTexture = texture;
    this->_sRect.x = x;
    this->_sRect.y = y;
    this->_sRect.w = w;
    this->_sRect.h = h;
}
Sprite::~Sprite() {}
void Sprite::draw(Graphics graphics, const SDL_Rect *source)
{
    graphics.draw(this->_sTexture, source, &_sRect);
}
void Sprite::update() {}
bool Sprite::checkCollision(SDL_Rect Rect1)
{
    int r1Bottom = Rect1.y + Rect1.h;
    int r2Bottom = _sRect.y + _sRect.h;
    int r1Left = Rect1.x;
    int r2Left = _sRect.x;
    int r1Right = Rect1.x + Rect1.w;
    int r2Right = _sRect.x + _sRect.w;
    return (!((r1Bottom < _sRect.y) ||
              (Rect1.y > r2Bottom) ||
              (r1Left > r2Right) ||
              (r1Right < r2Left)));
}