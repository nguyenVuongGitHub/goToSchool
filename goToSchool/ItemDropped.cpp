#include "ItemDropped.h"

ItemDropped::ItemDropped()
{
	distance = 0;
	angle = 0;
	speed = 0;
	timeExis = 0;
	isActive = false;
}

float ItemDropped::distanceFromPlayer(SDL_FRect rectPlayer)
{
	return sqrt(pow(rectPlayer.x - f_rect.x, 2) + pow(rectPlayer.y - f_rect.y, 2));
}

void ItemDropped::setTargetToPlayer(SDL_FRect rectPlayer)
{
	angle = atan2(rectPlayer.y - f_rect.y, rectPlayer.x - f_rect.x);
}

void ItemDropped::init(SDL_Renderer* renderer, string pathImg)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	isActive = true;
	distance = 25;
	speed = 2;
	timeExis = 250;
}

void ItemDropped::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture, NULL, &f_rect);
}

void ItemDropped::update()
{
	timeExis--;
	if (timeExis <= 0)
	{
		isActive = false;
	}
}

void ItemDropped::moveToPlayer(const SDL_FRect& rectPlayer)
{
	// di chuyển lại gần người chơi nếu khoảng cách nhỏ hơn 200
	if (distanceFromPlayer(rectPlayer) <= 200)
	{
		setTargetToPlayer(rectPlayer);
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
		speed += 1;
	}
}
