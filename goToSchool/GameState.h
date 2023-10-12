#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "FlatVector.h"
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
	
	bool playerCollisionDetect(Player &p, Player &obj);
	
	void init();
	void gameLoop();
	void freeAll();
	
};

