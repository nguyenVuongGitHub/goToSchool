﻿#include "Enemy.h"

Enemy::Enemy()
{
	type = 0;
	radius = 0;
}

Enemy::~Enemy()
{
	//Character::~Character();
	/*SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);*/
}

void Enemy::init(SDL_Renderer* renderer,string path)
{
	Character::init(renderer, path);
	f_rect = { -10,-10,30,30 };
	hp = 30;
	speed = 3;
	active = 1;
	radius = 15;

	// 1080 and 1920 is width and height of window
	spawn(1080,1920);

	//center = { f_rect.x + f_rect.w / 2, f_rect.y + f_rect.h / 2 };
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
}
void Enemy::update(Player& player)
{
	setTargetToPlayer(player);
	move();
}

void Enemy::move()
{
	if (active)
	{
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;

		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
}

void Enemy::spawn(int heightWindow, int widthWindow)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(-heightWindow, 2 * heightWindow);
	std::uniform_real_distribution<float> disY(-widthWindow, 2 * widthWindow);

	float x = disX(gen);
	float y = disY(gen);

	f_rect = { x, y, 30, 30 };
}

void Enemy::setTargetToPlayer(Player &player)
{
	dx = player.getRect().x - f_rect.x;
	dy = player.getRect().y - f_rect.y;
	angle = atan2(dy,dx);
}

void Enemy::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_NONE);
}

void Enemy::freeRender(vector<Enemy>& enemyList, int i)
{
	if (!enemyList[i].active)
	{
		enemyList.erase(enemyList.begin() + i);
	}
}
