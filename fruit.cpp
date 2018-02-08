#include <SDL2/SDL.h>
#include "fruit.h"
#include <stdlib.h>

Fruit::Fruit(){
    fallSpeed = 2.5;
    sourceX = 0;
    sourceY = 0;

}

void Fruit::update(){
    if (this->_sprite._sRect.y > 460)
    {
        spawnPoint();
        this->_sprite._sRect.y = 0;
    }
    this->_sprite._sRect.y += fallSpeed;
}

void Fruit::spawnPoint()
{
    int randNum = (rand() % 660) + 1;
    this->_sprite._sRect.x = randNum;
    this->_sprite._sRect.y = 0;
}

void Fruit::draw(Graphics graphics){
    SDL_Rect source = {sourceX, sourceY, 64, 64};
    this->_sprite.draw(graphics, &source);
}

void Fruit::setSprite(Sprite _sprite)
{
    this->_sprite = _sprite;
}

void Fruit::setSource(int x, int y)
{
    this->sourceX = x;
    this->sourceY = y;
}
