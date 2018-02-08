#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "game.h"
#include <string>

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
    }
    this->_window = SDL_CreateWindow("SDL KATA", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (this->_window == NULL)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
    _renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(_renderer, 0, 255, 255, 255);
    graphics.setRenderer(_renderer);
    Sprite playerSprite(graphics.getTexture("/home/davinci/Development/c/sdlkata/MyChar.pbm"), 312, 320, 32, 32);
    _ammoTexture = graphics.getTexture("/home/davinci/Development/c/sdlkata/ammo.bmp");
    Sprite tSprite(_ammoTexture, 10, 15, 16, 16);
    int randNum = (rand() % 660) + 1;
    _player.setSprite(playerSprite);
    _background = graphics.getTexture("/home/davinci/Development/c/sdlkata/SpaceBG.bmp");
    _bombTexture = graphics.getTexture("/home/davinci/Development/c/sdlkata/frame01.bmp");
    _fruitTexture = graphics.getTexture("/home/davinci/Development/c/sdlkata/fruit.bmp");
    _expTexture = graphics.getTexture("/home/davinci/Development/c/sdlkata/explosion.bmp");
    initGame();
    gameLoop();
}

Game::~Game() {}

void Game::initGame()
{
    gameTime = 0;
    gamePoint = 0;
    gameState = true;
    gameOver = false;
    initBombs();
    initFruits();
    gameStartTime = SDL_GetTicks();
}
void Game::gameLoop()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
    gameStartTime = SDL_GetTicks();
    while (true)
    {
        frameStart = SDL_GetTicks();
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            SDL_Keycode key = event.key.keysym.sym;
            if (event.type == SDL_KEYDOWN)
            {
                if (key == SDLK_ESCAPE)
                    break;
                if (key == SDLK_SPACE)
                    gameState = !gameState;
                if (key == SDLK_f)
                    continue;
                if (key == SDLK_r)
                    if (gameOver)
                    {
                        gameOver = false;
                        initGame();
                    }
            }
            else if (event.type == SDL_KEYUP)
            {
            }
            else if (event.type == SDL_QUIT)
            {
                break;
            }
        }
        update();
        if (gameState && !gameOver)
        {
            if (keystates[SDL_SCANCODE_A])
            {
                this->_player.moveLeft();
            }
            else if (keystates[SDL_SCANCODE_D])
            {
                this->_player.moveRight();
            }
            else
            {
                this->_player.stopAnimate();
            }
            frameTime = SDL_GetTicks() - frameStart;
            gameTime = SDL_GetTicks() - gameStartTime;
            if (gameTime >= 1000)
            {
                int a = gameTime;
                if (gameTime >= 10000)
                {
                    while (a >= 99)
                    {
                        a /= 10;
                    }
                }
                else
                {
                    while (a > 9)
                    {
                        a /= 10;
                    }
                }
            }
            if (frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }
}
void Game::draw()
{
}

void Game::initBombs()
{
    for (int i = 0; i < 10; i++)
    {
        int randNum = (rand() % 660) + 1;
        Bomb bomb;
        Sprite bombSprite(_bombTexture, randNum, 0, 20, 20);
        bomb.setSprite(bombSprite);
        _bombs[i] = bomb;
        bombsPositions[i] = bomb._sprite._sRect.x;
    }
}

void Game::initFruits()
{
    for (int i = 0; i < 3; i++)
    {
        int randNum = (rand() % 660) + 1;
        Fruit _fruit;
        Sprite fruitSprite(_fruitTexture, randNum, 0, 32, 32);
        _fruit.setSprite(fruitSprite);
        if (i == 1)
        {
            _fruit.setSource(2 * 64, 64);
        }
        else if (i == 2)
        {
            _fruit.setSource(64, 3 * 64);
        }
        _fruits[i] = _fruit;
    }
}

void Game::expAnimate(SDL_Rect r)
{
    int sourceX = 0, sourceY = 0;
    SDL_Rect source = {sourceX, sourceY, 320, 230};
    Sprite expSprite(_expTexture, r.x, r.y, 60, 60);
    for (int i = 0; i < 5; i++)
    {
        for (int k = 0; k < 6; k++)
        {
            sourceX = k * 320;
            sourceY = i * 230;
        }
    }
    expSprite.draw(graphics, &source);
}

void Game::update()
{
    graphics.clear();
    graphics.draw(_background, NULL, NULL);

    this->_player.draw(graphics);
    for (int i = 0; i < 10; i++)
    {
        _bombs[i].draw(graphics);
        if (gameState && !gameOver)
            _bombs[i].update(_bombs, i);
        if (i < 3)
        {
            _fruits[i].draw(graphics);
            if (gameState && !gameOver)
            {
                _fruits[i].update();
                if (this->_player._sprite.checkCollision(_fruits[i]._sprite._sRect))
                {
                    gamePoint += 10;
                    _fruits[i].spawnPoint();
                    printf("Game Point: %d\n", gamePoint);
                }
            }
        }
        if (gameState && !gameOver)
        {
            if (this->_player._sprite.checkCollision(_bombs[i]._sprite._sRect))
            {
                printf("Game Over!\n");
                gameOver = true;
                gameOverTime = SDL_GetTicks();
                frame = 0;
            }
        }
    }
    if (gameState && !gameOver)
    {
        this->_player.update();
    }
    if (gameOver)
    {
        int thisTime = SDL_GetTicks() - gameOverTime;
        Sprite expSprite(_expTexture, _player._sprite._sRect.x - 10, _player._sprite._sRect.y - 10, 60, 60);
        SDL_Rect source = {frame * 320, 230 * 3, 320, 230};
        expSprite.draw(graphics, &source);
        if (thisTime > 60 && frame < 4)
        {
            gameOverTime = SDL_GetTicks();
            frame++;
        }
    }
    graphics.flip();
}
