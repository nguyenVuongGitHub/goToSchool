#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "bullet.h"
#include <vector>
using namespace std;
class GameState
{
public:
	GameState();
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	

	short heightWindow;
	short widthWindow;
	int mouseX;
	int mouseY;
	bool holdMouse;
	bool isGameRunning;
	
	void init();
	void gameLoop();
	void collesion();
	bool checkCollesion(SDL_Rect &r1, SDL_Rect &r2);
	void freeAll();
	
};

