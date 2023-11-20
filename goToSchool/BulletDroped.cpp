#include "BulletDropped.h"

void BulletDropped::init(SDL_Renderer* renderer, string pathImg)
{
	ItemDropped::init(renderer, pathImg);
	f_rect = { 0, 0, 32, 32 };
}

void BulletDropped::update(const SDL_FRect& rectPlayer)
{
	ItemDropped::update();
	move(rectPlayer);
}
void BulletDropped::render(SDL_Renderer* renderer, int curFrame, float scrollX, float scrollY)
{
	srcRect.x = curFrame * 64;
	srcRect.y = 0;
	srcRect.w = 64;
	srcRect.h = 64;
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyF(renderer, texture, &srcRect, &tmp);
}
void BulletDropped::move(const SDL_FRect& rectPlayer)
{
	ItemDropped::moveToPlayer(rectPlayer);
}
