#include "bullet.h"
#include <iostream>
Bullet::Bullet()
{
	type = 0;
	damage = 0;
	speed = 0;
	active = 0;
	angle = 0;
	dx = 0;
	dy = 0;
	distance = 0;
}

void Bullet::init(SDL_Renderer* renderer, short typeWeapon)
{
	// cài đặt thông số sẽ hiển thị trong game
	string pathImg;
	if (typeWeapon == USP)
	{
		pathImg = "img/T_556mm.png";
		type = T_556mm;
	}
	if (typeWeapon == AK_47)
	{
		pathImg = "img/T_762mm.png";
		type = T_762mm;
	}
	if (typeWeapon == MP5)
	{
		pathImg = "img/T_900mm.png";
		type = T_900mm;
	}
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	//set trạng thái hoạt động lÀ TRUE
	active = 1;
}

void Bullet::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_NONE);

}
void Bullet::move()
{
	if (distance <= 0)
	{
		active = 0;
	}
	if (active)
	{
		
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
		distance--;
	}

}
void Bullet::update()
{
	move();
}