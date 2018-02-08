#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    SDL_Texture *getTexture(const std::string filePath);
    void draw(SDL_Texture *texture, const SDL_Rect *sourceRect, const SDL_Rect *destRect);
    void flip();
    void clear();
    void setRenderer(SDL_Renderer *ren);

  private:
    SDL_Renderer *_renderer;
};
#endif