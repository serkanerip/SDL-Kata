#include <SDL2/SDL.h>
#include "graphics.h"
#include <iostream>

Graphics::Graphics() {}
Graphics::~Graphics() {}

SDL_Texture *Graphics::getTexture(const std::string filePath)
{
    SDL_Surface *bmp = SDL_LoadBMP(filePath.c_str());
    if (bmp == NULL)
    {
        SDL_DestroyRenderer(this->_renderer);
        std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(this->_renderer, bmp);
    SDL_FreeSurface(bmp);
    return tex;
}
void Graphics::draw(SDL_Texture *texture, const SDL_Rect *sourceRect, const SDL_Rect *destRect)
{
    SDL_RenderCopy(this->_renderer, texture, sourceRect, destRect);
}

void Graphics::clear()
{
    SDL_RenderClear(this->_renderer);
}

void Graphics::flip()
{
    SDL_RenderPresent(this->_renderer);
}

void Graphics::setRenderer(SDL_Renderer *ren)
{
    this->_renderer = ren;
}