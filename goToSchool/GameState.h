#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
class GameState
{
public:
	GameState();
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	

	short heightWindow;
	short widthWindow;
	short mouseX;
	short mouseY;
	bool isGameRunning;
	
	void collisionDetect(SDL_Rect &obj1, SDL_Rect &obj2);
	void init();
	void gameLoop();
	void freeAll();
	
};

