
#include "coin.h"


void coin::init(SDL_Renderer* renderer, string pathImg)
{
	ItemDropped::init(renderer, pathImg);
	f_rect = { 0, 0, 15, 15 };
}

void coin::update(const SDL_FRect& rectPlayer)
{
	ItemDropped::update();
	move(rectPlayer);
}
void coin::move(const SDL_FRect & rectPlayer)
{
	// di chuyển khi mà quái chết ( distance vẫn còn giá trị )
	if (distance >= 0 )
	{
		f_rect.x += sin(angle)*speed;
		f_rect.y += cos(angle)*speed;
		speed++;
		if (speed >= 4) speed = 4;
		distance--;
	}
	// di chuyển lại gần người chơi
	ItemDropped::moveToPlayer(rectPlayer);

}
void coin::render(SDL_Renderer* renderer, int curFrame, float scrollX, float scrollY)
{
	
	srcRect.x = curFrame*64;
	srcRect.y = 0;
	srcRect.w = 64;
	srcRect.h = 64;
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyF(renderer, texture, &srcRect, &tmp);
}
