#include "GameState.h"


int main(int argc, char *argv[])
{
	 GameState gameMain;
	 gameMain.initData();
	 gameMain.menuMain();
	 gameMain.freeAll();
	return 0;
}