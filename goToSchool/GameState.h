#pragma once
#include "Player.h"
#include "bullet.h"
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

