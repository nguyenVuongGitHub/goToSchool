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
				
			}
		}
		//add a block
		SDL_Rect block = { 100, 100, 100 ,100 };

		//move
		collisionDetect(player.r, block);
		player.move();


		// Render và cập nhật trạng thái của trò chơi tại đây
		/*frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}*/


		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, player.t, NULL, &block);

		player.draw(renderer);
		SDL_RenderPresent(renderer);
	}
}

void GameState::collisionDetect(SDL_Rect& obj1, SDL_Rect& obj2)
{
		if (obj1.x + obj1.w >= obj2.x + 10 && obj1.x <= obj2.x + obj2.w - 10)
		{
			if (obj1.y + obj1.h > obj2.y && obj1.y < obj2.y) //On brick
			{
				obj1.y = obj2.y - obj1.h;
			}
			if (obj1.y < obj2.y + obj2.h && obj1.y > obj2.y) //Brick above
			{
				obj1.y = obj2.y + obj2.h;
			}
		}
		if (obj1.y + obj1.h > obj2.y + 6 && obj1.y < obj2.y + obj2.h * 39 / 40)
		{
			if (obj1.x + obj1.w > obj2.x && obj1.x < obj2.x)
			{
				obj1.x = obj2.x - obj1.w; //edge left
			}
			else if (obj1.x < obj2.x + obj2.w && obj1.x + obj1.w> obj2.x + obj2.w)
			{
				obj1.x = obj2.x + obj2.w; //edge right
			}
			else if (obj1.x + obj1.w >= obj2.x && obj1.x + obj1.w <= obj2.x + obj2.w) //Inside
			{
				if (obj1.x + obj1.w < obj2.x + obj2.w / 2)
				{
					obj1.x = obj2.x - obj1.w;
				}
				else
				{
					obj1.x = obj2.x + obj2.w;
				}
			}
		}
}

void GameState::freeAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}