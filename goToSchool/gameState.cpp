#include "GameState.h"

GameState::GameState() :

	heightWindow(0),
	widthWindow(0),
	mouseX(0),
	mouseY(0),
	window(NULL),
	renderer(NULL),
	isGameRunning(0)
	
{}

void GameState::init()
{
	heightWindow = 1080;
	widthWindow = 1920;
	mouseX = 0;
	mouseY = 0;
	isGameRunning = 1;
	window = SDL_CreateWindow("game test", 0, 0, widthWindow, heightWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);
}
void GameState::gameLoop()
{
	// object
	Player player;
	player.init(renderer);

	//

	// Khai báo biến cho việc kiểm soát tốc độ vòng lặp
	/*const int targetFPS = 60;
	const int frameDelay = 1000 / targetFPS;
	Uint32 frameStart;
	int frameTime;*/
	
	SDL_Event e;
	while (isGameRunning)
	{
		// tắt con trỏ chuột
		SDL_ShowCursor(SDL_DISABLE);

		//frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				isGameRunning = 0;
			}
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				isGameRunning = 0;
			}

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_LEFT) 
					player.moveKey[LEFT] = true;

				else if (e.key.keysym.sym == SDLK_RIGHT)
					player.moveKey[RIGHT] = true;

				else if (e.key.keysym.sym == SDLK_UP) 
					player.moveKey[UP] = true;
				
				else if (e.key.keysym.sym == SDLK_DOWN) 
					player.moveKey[DOWN] = true;
				else if (e.key.keysym.sym == SDLK_LSHIFT)
					player.moveKey[SLOW] = true;
				else if (e.key.keysym.sym == SDLK_SPACE)
					player.moveKey[FAST] = true;
			}

			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_LEFT) 
					player.moveKey[LEFT] = false;
				
				else if (e.key.keysym.sym == SDLK_RIGHT) 
					player.moveKey[RIGHT] = false;
				
				else if (e.key.keysym.sym == SDLK_UP) 
					player.moveKey[UP] = false;
				
				else if (e.key.keysym.sym == SDLK_DOWN) 
					player.moveKey[DOWN] = false;
				else if (e.key.keysym.sym == SDLK_LSHIFT)
					player.moveKey[SLOW] = false;
				else if (e.key.keysym.sym == SDLK_SPACE)
					player.moveKey[FAST] = false;
			}
		}


		// process
		collesion();
		//move
		player.move();

		// Render và cập nhật trạng thái của trò chơi tại đây
		/*frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}*/


		SDL_RenderClear(renderer);
		player.draw(renderer);
		SDL_RenderPresent(renderer);
	}
}
bool GameState::checkCollesion(SDL_Rect &r1, SDL_Rect &r2)
{
	return (r1.x + r1.w >= r2.x && r2.x + r2.w >= r1.x
		&& r1.y + r1.h >= r2.y && r2.y + r2.h >= r1.y);
}
void GameState::collesion()
{

}
void GameState::freeAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}