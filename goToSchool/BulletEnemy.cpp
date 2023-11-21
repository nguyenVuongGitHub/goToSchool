#include "BulletEnemy.h"

void BulletEnemy::setTargetToPlayer(Player& player)
{
	dx = player.f_rect.x - f_rect.x;
	dy = player.f_rect.y - f_rect.y;
	angle = atan2(dy, dx);
	
}

void BulletEnemy::init(SDL_Renderer* renderer, Player& player, string path)
{
	surface = IMG_Load(path.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	active = 1;
	f_rect = { 0,0,48,12 };
	speed = 5;
	distance = 410;
	
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
}

void BulletEnemy::update(Player &player)
{
	setTargetToPlayer(player);
	if (type == 0)
	{
		if (distance <= 0)
		{
			active = 0;
		}
		if (active)
		{
			if (f_rect.x > player.f_rect.x + player.f_rect.w / 2)
			{
				flip = SDL_FLIP_HORIZONTAL;
			}
			else
			{
				flip = SDL_FLIP_NONE;
			}
			distance -= speed;
			vertices[0] = { f_rect.x, f_rect.y };
			vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
			vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
			vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
		}
	}
	if(type == 1)
		move(player.f_rect.x,player.f_rect.w);
}

void BulletEnemy::render(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame)
{

	srcRect = { curFrame * 300, 0, 300, 100 };
	
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	if (type == 0)
	{
		SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, 0, NULL, flip);
	}
	else {
		SDL_RenderCopyExF(renderer, texture, NULL, &tmp, 0, NULL, flip);
	}
}

