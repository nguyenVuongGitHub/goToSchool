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
	pathImg = "img/arrow.png";
	surface = IMG_Load(pathImg.c_str());
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
	move(player.f_rect.x,player.f_rect.w);
}

