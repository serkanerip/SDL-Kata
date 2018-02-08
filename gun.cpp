#include <SDL2/SDL.h>
#include "gun.h"
#include "sprite.h"
Gun::Gun() : ammoNumber(0)
{
    onFire = false;
}

void Gun::fire(Graphics graphics, SDL_Rect playerRect)
{
    if (ammoNumber >= 1)
    {
        SDL_Rect source = {0, 0, 16, 16};
        if (!onFire)
        {
            this->_sprite._sRect.x = playerRect.x + (playerRect.w / 2) - 2;
            this->_sprite._sRect.y = playerRect.y;
        }
        this->_sprite.draw(graphics, &source);
        onFire = true;
        ammoNumber--;
    }
}

void Gun::update()
{
    if (this->_sprite._sRect.y < 0)
    {
        onFire = false;
    }
    this->_sprite._sRect.y -= 15;
}

int Gun::getAmmo()
{
    return this->ammoNumber;
}

void Gun::addAmmo(int ammo)
{
    this->ammoNumber = ammo;
}

void Gun::setSprite(Sprite _sprite)
{
    this->_sprite = _sprite;
}