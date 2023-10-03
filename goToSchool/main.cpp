#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "GameState.h"


int main(int argc, char *argv[])
{
	GameState gameMain;
	gameMain.init();
	gameMain.gameLoop();
	gameMain.freeAll();
	return 0;
}