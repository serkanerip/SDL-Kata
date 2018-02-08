all: 
	g++ sdl.cpp game.cpp bomb.cpp player.cpp sprite.cpp graphics.cpp fruit.cpp gun.cpp -lSDL2 -w -o game