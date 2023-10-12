﻿#include "GameState.h"

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

	vector<Enemy> ListEnemy;
	
	// declare list weapon
	vector<Bullet> ListBullet;
	player.weapon[USP].type = USP;
	player.weapon[AK_47].type = AK_47;
	player.weapon[MP5].type = MP5;
	player.weapon[USP].init();
	player.weapon[AK_47].init();
	player.weapon[MP5].init();


	int curWeapon = 0;
	int countDistance = 0;

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
				if (e.key.keysym.sym == SDLK_a) 
					player.moveKey[LEFT] = true;

				else if (e.key.keysym.sym == SDLK_d)
					player.moveKey[RIGHT] = true;

				else if (e.key.keysym.sym == SDLK_w) 
					player.moveKey[UP] = true;
				
				else if (e.key.keysym.sym == SDLK_s) 
					player.moveKey[DOWN] = true;

				else if (e.key.keysym.sym == SDLK_LSHIFT)
					player.moveKey[SLOW] = true;

				else if (e.key.keysym.sym == SDLK_SPACE)
					player.moveKey[FAST] = true;
			}

			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_a)
					player.moveKey[LEFT] = false;		

				else if (e.key.keysym.sym == SDLK_d)
					player.moveKey[RIGHT] = false;			
				
				else if (e.key.keysym.sym == SDLK_w)
					player.moveKey[UP] = false;				
				
				else if (e.key.keysym.sym == SDLK_s)
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
			
			// kiểm tra sự kiện lăn chuột
			if (e.type == SDL_MOUSEWHEEL) {
				int scrollDirection = e.wheel.y;
				if (scrollDirection > 0) {
						curWeapon++;
					if (curWeapon > 2)
						curWeapon = 0;
				}
				else if (scrollDirection < 0) {
						curWeapon--;
					if (curWeapon < 0)
						curWeapon = 2;
					
				}
			}
			
		}


		// process
		collesion();
		for (int i = 0; i < ListBullet.size(); i++)
		{
			for (int j = 0; j < ListEnemy.size(); j++)
			{
				if (ListEnemy[j].hp <= 0)
					ListEnemy[j].active = 0;

				
				if (checkCollesion(ListBullet[i].r, ListEnemy[j].r))
				{
					ListBullet[i].active = 0;
					ListEnemy[j].hp -= player.weapon[curWeapon].damage;
				}

			}
		}
		//move
		player.move();

		//acttack
	// Kiểm tra nếu chuột đang được giữ
		if (holdMouse)
		{
			// Lấy thời gian hiện tại tính bằng mili giây
			Uint32 current_time = SDL_GetTicks();

			// Tính thời gian đã trôi qua kể từ lần bắn trước đó
			Uint32 time_since_last_shot = current_time - last_shot_time;

			// Kiểm tra nếu đã đủ thời gian trôi qua từ lần bắn trước đó (200 mili giây)
			if (time_since_last_shot >= 200) {
				// Giảm số lượng đạn còn lại của vũ khí hiện tại
				player.weapon[curWeapon].totalBullets--;

				// Bắn vũ khí bằng cách gọi hàm shoot với các tham số cần thiết
				player.weapon[curWeapon].shoot(renderer, ListBullet, player.r.x, player.r.y, heightWindow, widthWindow);

				// Cập nhật thời gian bắn cuối cùng thành thời gian hiện tại
				last_shot_time = current_time;
			}
		}

		if (ListEnemy.size() <= 10)
		{
			Enemy newEnemy;
			newEnemy.init(renderer);
			newEnemy.spam(heightWindow, widthWindow);
			ListEnemy.push_back(newEnemy);
		}

		SDL_RenderClear(renderer);
		player.draw(renderer);

		//vẽ viên đạn và di chuyển đạn trong danh sách đạn
		for (int i = 0; i < ListBullet.size(); i++)
		{
			ListBullet[i].draw(renderer);
			ListBullet[i].move();
		}
		for (int i = 0; i < ListEnemy.size(); i++)
		{
			ListEnemy[i].setTargetToPlayer(player);
			ListEnemy[i].draw(renderer);
			ListEnemy[i].move();
		}
		SDL_RenderPresent(renderer);

		// xóa viên đạn ra khỏi danh sách nếu như viên đạn không còn hoạt động (active = 0)
		for (int i = 0; i < ListBullet.size(); i++)
			if (!ListBullet[i].active)
				ListBullet.erase(ListBullet.begin() + i);


		// xóa quái ra khỏi danh sách nếu viên đạn chạm quái 
		for (int i = 0; i < ListEnemy.size(); i++)
			if (!ListEnemy[i].active)
				ListEnemy.erase(ListEnemy.begin() + i);
		
	}
}
bool GameState::checkCollesion(SDL_FRect &r1, SDL_FRect &r2)
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