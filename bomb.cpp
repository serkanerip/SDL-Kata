#include <SDL2/SDL.h>

#include "bomb.h"
#include <stdlib.h>

Bomb::Bomb()
{
    fallSpeed = (rand() % 5) + 2;
    spawnPoint();
}

void Bomb::update(Bomb *bombs, int i)
{
    if (this->_sprite._sRect.y > 460)
    {
        spawnPoint();
        for (int k = 0; k < 10; k++)
        {
            if (k == i)
                continue;
            else
            {
                if (this->_sprite.checkCollision(bombs[i]._sprite._sRect))
                {
                    spawnPoint();
                }
            }
        }
        this->_sprite._sRect.y = 0;
        fallSpeed = (rand() % 5) + 2;
    }
    this->_sprite._sRect.y += fallSpeed;
}

void Bomb::spawnPoint()
{
    int randNum = (rand() % 660) + 1;
    this->_sprite._sRect.x = randNum;
    this->_sprite._sRect.y = 0;
}

void Bomb::draw(Graphics graphics)
{
    SDL_Rect source = {0, 0, 512, 512};
    this->_sprite.draw(graphics, &source);
}

void Bomb::setSprite(Sprite _sprite)
{
    this->_sprite = _sprite;
}