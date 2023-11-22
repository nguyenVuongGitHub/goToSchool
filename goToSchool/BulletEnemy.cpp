#include "BulletEnemy.h"

void BulletEnemy::setTargetToPlayer(Player& player)
{
	dx = player.f_rect.x - f_rect.x;
	dy = player.f_rect.y - f_rect.y;
	angle = atan2(dy, dx);
}

void BulletEnemy::init(SDL_Renderer* renderer, Player& player, string path, float xEnemy, float yEnemy, int typeEnemy)
{
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	active = 1;
	speed = 5;
	distance = 600;
	if (type == 0)
	{
		f_rect.x = xEnemy - 200 - 500 - 250 - 50;
		f_rect.y = yEnemy + 120;
		f_rect.w = 500*5;
		f_rect.h = 25*5;
		vertices.push_back({ f_rect.x + f_rect.w / 2, f_rect.y });
		vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
		vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
		vertices.push_back({ f_rect.x + f_rect.w / 2, f_rect.y + f_rect.h });

		static std::random_device rd;
		static std::mt19937 gen(rd());

		if (player.f_rect.x >= xEnemy) {
			if (f_rect.y >= player.f_rect.y) {
				std::uniform_real_distribution<float> disX(270, 360);
				angleFlip = disX(gen); // Góc ngẫu nhiên trong khoảng [270, 360]
			}
			else {
				std::uniform_real_distribution<float> disX(0, 90);
				angleFlip = disX(gen); // Góc ngẫu nhiên trong khoảng [0, 90]
			}
		}
		else {
			if (f_rect.y < player.f_rect.y) {
				std::uniform_real_distribution<float> disX(90, 180);
				angleFlip = disX(gen); // Góc ngẫu nhiên trong khoảng [90, 180]
			}
			else {
				std::uniform_real_distribution<float> disX(180, 270);
				angleFlip = disX(gen); // Góc ngẫu nhiên trong khoảng [180, 270]
			}
		}
		
		/*angleFlip = atan2(abs(f_rect.y - player.f_rect.y),abs(player.f_rect.x - xEnemy));
		angleFlip = angleFlip * 180 / M_PI;*/

	}
	else {
		if (typeEnemy == 1)
		{
			f_rect.x = xEnemy + 32/2;
			f_rect.y = yEnemy + 32/2;
			f_rect.w = 30;
			f_rect.h = 36;
		}
		if (typeEnemy == 3)
		{
			f_rect.x = xEnemy + 96/2;
			f_rect.y = yEnemy + 96/2;
			f_rect.w = 60;
			f_rect.h = 72;
		}
		vertices.push_back({ f_rect.x, f_rect.y });
		vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
		vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
		vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
	}


}

void BulletEnemy::update(Player &player, float xenemy, float yenemy)
{
	frameLaze += 0.259784;
	if (frameLaze >= 14)
	{
		frameLaze = 0;
		if(type == 0)
			active = false;
	}
	setTargetToPlayer(player);

	if (type == 0)
	{
		if (distance <= 0)
		{
			active = 0;
		}
		if (active)
		{
			distance -= speed;
			vertices[0] = { f_rect.x + f_rect.w / 2, f_rect.y };
			vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
			vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
			vertices[3] = { f_rect.x + f_rect.w / 2, f_rect.y + f_rect.h };

			//Tranforming position from rotation
			vertices[0] = vertices[0].ClockwiseTransform( { f_rect.x + f_rect.w / 2,f_rect.y + f_rect.h / 2 } , angleFlip);
			vertices[1] = vertices[1].ClockwiseTransform( { f_rect.x + f_rect.w / 2,f_rect.y + f_rect.h / 2 } , angleFlip);
			vertices[2] = vertices[2].ClockwiseTransform( { f_rect.x + f_rect.w / 2,f_rect.y + f_rect.h / 2 } , angleFlip);
			vertices[3] = vertices[3].ClockwiseTransform( { f_rect.x + f_rect.w / 2,f_rect.y + f_rect.h / 2 } , angleFlip);
		}
	}
	if(type == 1)
		move(player.f_rect.x,player.f_rect.w);
}

void BulletEnemy::render(SDL_Renderer* renderer, float scrollX, float scrollY)
{

	srcRect = { (int)frameLaze * 500, 0, 500, 25 };
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	if (type == 0)
	{
		point = { 0,0 };
		SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, angleFlip, NULL, flip);
	}
	else if(type == 1){

		SDL_RenderCopyExF(renderer, texture, NULL, &tmp, 0, NULL, flip);
	}
}

