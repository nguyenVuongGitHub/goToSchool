#include "GameState.h"

GameState::GameState() :

	heightWindow(0),
	widthWindow(0),
	mouseX(0),
	mouseY(0),
	window(NULL),
	renderer(NULL),
	isGameRunning(0),
	holdMouse(0)
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
	holdMouse = 0;
	IMG_Init(IMG_INIT_PNG);
}
void GameState::gameLoop()
{
	// object
	Player player;
	player.init(renderer);
	vector<Bullet> ListBullet;

	
	//

	// Khai báo biến cho việc kiểm soát tốc độ vòng lặp
	/*const int targetFPS = 60;
	const int frameDelay = 1000 / targetFPS;
	Uint32 frameStart;
	int frameTime;*/
	Uint32 last_shot_time = 0;
	SDL_Event e;
	while (isGameRunning)
	{
		// tắt con trỏ chuột
		//SDL_ShowCursor(SDL_DISABLE);

		//frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				isGameRunning = 0;

			if (e.key.keysym.sym == SDLK_ESCAPE)
				isGameRunning = 0;
			
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
			//bắt sự kiện giữ chuột
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
				holdMouse = true;

			if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LMASK)
				holdMouse = false;
		
		}


		// process
		collesion();
		//move
		player.move();
		//acttack
		if (holdMouse)
		{
			Uint32 current_time = SDL_GetTicks();
			Uint32 time_since_last_shot = current_time - last_shot_time;

			// Kiểm tra xem đã đủ thời gian để bắn đạn tiếp theo chưa
			if (time_since_last_shot >= 50)
			{
				SDL_GetMouseState(&mouseX, &mouseY);
				//khởi tạo viên đạn mới
				Bullet newBullet;
				newBullet.init(renderer, player.r.x, player.r.y, mouseX, mouseY);
				ListBullet.push_back(newBullet);
				// Lưu lại thời gian bắn đạn
				last_shot_time = current_time;
			}
		}


		// Render và cập nhật trạng thái của trò chơi tại đây
		/*frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}*/
		SDL_RenderClear(renderer);
		player.draw(renderer);

		//vẽ viên đạn và di chuyển đạn trong danh sách đạn
		for (int i = 0; i < ListBullet.size(); i++)
		{
			ListBullet[i].draw(renderer);
			ListBullet[i].move(heightWindow,widthWindow);
		}

		SDL_RenderPresent(renderer);

		// xóa viên đạn ra khỏi danh sách nếu như viên đạn không còn hoạt động (active = 0)
		for (int i = 0; i < ListBullet.size(); i++)
			if (!ListBullet[i].active)
				ListBullet.erase(ListBullet.begin() + i);
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