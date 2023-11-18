#include "BulletEnemy.h"

void BulletEnemy::setTargetToPlayer(Player& player)
{
	dx = player.f_rect.x - f_rect.x;
	dy = player.f_rect.y - f_rect.y;
	angle = atan2(dy, dx);
}

void BulletEnemy::init(SDL_Renderer* renderer, Player& player)
{
	string pathImg;
	pathImg = "img/T_556mm.png";
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	active = 1;
	f_rect = { 0,0,15,15 };
	speed = 5;
	distance = 410;
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
	//setTargetToPlayer(player);
}

void BulletEnemy::update(Player &player)
{
	setTargetToPlayer(player);
	move();
}

//void BulletEnemy::move()
//{
//	if (active)
//	{
//		f_rect.x += cos(angle) * speed;
//		f_rect.y += sin(angle) * speed;
//		vertices[0] = { f_rect.x, f_rect.y };
//		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
//		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
//		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
//	}
//}

