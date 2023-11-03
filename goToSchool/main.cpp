#include "GameState.h"


int main(int argc, char *argv[])
{
	srand(time(0));
	GameState gameMain;
	gameMain.initData();
	gameMain.menuMain();
	gameMain.freeAll();
	return 0;
}