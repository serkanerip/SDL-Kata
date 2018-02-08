#ifndef FRUIT_H
#define FRUIT_H

#include "graphics.h"
#include "sprite.h"

class Fruit{
public:
    Fruit();
    void update();
    void draw(Graphics graphics);
    void spawnPoint();
    void setSprite(Sprite _sprite);
    void setSource(int sourceX, int sourceY);
    Sprite _sprite;
private:
    int fallSpeed;
    int sourceX, sourceY;
};

#endif