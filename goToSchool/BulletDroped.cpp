#include "BulletDropped.h"

void BulletDropped::init(SDL_Renderer* renderer, string pathImg)
{
	ItemDropped::init(renderer, pathImg);
	f_rect = { 0, 0, 15, 15 };
}

void BulletDropped::update(const SDL_FRect& rectPlayer)
{
	ItemDropped::update();
	move(rectPlayer);
}

void BulletDropped::move(const SDL_FRect& rectPlayer)
{
	ItemDropped::moveToPlayer(rectPlayer);
}
