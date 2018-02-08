#include <SDL2/SDL.h>
#include "player.h"
#include "graphics.h"
#include "sprite.h"
#include <stdio.h>

Player::Player()
{
    frameX = 0;
    frameY = 16;
    isAnimating = false;
    animateTurn = "none";
}

Player::~Player() {}

void Player::update()
{
    animate();
}

void Player::moveLeft()
{
    if (animateTurn != "left")
    {
        printf("hear!!!!!!!!!!!!!\n");
        animStartTime = SDL_GetTicks();
    }
    this->_sprite._sRect.x += -4;
    animateTurn = "left";
}

void Player::moveRight()
{
    if (animateTurn != "right")
    {
        animStartTime = SDL_GetTicks();
    }
    this->_sprite._sRect.x += +4;
    animateTurn = "right";
}

void Player::animate()
{
    if (animateTurn == "left")
    {
        frameY = 0;
        int thisTime = SDL_GetTicks() - animStartTime;
        if (thisTime > 100)
        {
            frameX += 1;
            printf("frameX:%d\n", frameX);
            if (frameX >= 5)
            {
                frameX = 0;
                animStartTime = SDL_GetTicks();
            }
        }
    }
    else
    {
        frameY = 16;
        int thisTime = SDL_GetTicks() - animStartTime;
        if (thisTime > 100)
        {
            frameX++;
            if (frameX >= 5)
            {
                frameX = 0;
                animStartTime = SDL_GetTicks();
            }
        }
    }
}
void Player::stopAnimate()
{
    animateTurn = "none";
    frameX = 0;
    if (animateTurn == "right")
    {
        frameY = 0;
    }
    else
    {
        frameY = 16;
    }
}

void Player::setSprite(Sprite sprite)
{
    this->_sprite = sprite;
}

void Player::draw(Graphics graphics)
{
    const SDL_Rect source = {frameX * 16, frameY, 16, 16};
    this->_sprite.draw(graphics, &source);
}
