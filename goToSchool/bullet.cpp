#include "bullet.h"
#include <iostream>
Bullet::Bullet()
{
	name = "";
	type = 0;
	int damage = 0;
	int speed = 0;
	s = NULL;
	t = NULL;
	r = { 0,0,0,0 };
	active = 0;
	angle = 0;
	dx, dy = 0;
	distance = 0;
}

void Bullet::init(SDL_Renderer* renderer, string pathImg, short typeWeapon)
{
	// cài đặt thông số sẽ hiển thị trong game
	if (typeWeapon == USP)
	{
		name = "Dan sung luc";
		type = T_556mm;
	}
	if (typeWeapon == AK_47)
	{
		name = "Dan sung truong";
		type = T_762mm;
	}
	if (typeWeapon == MP5)
	{
		name = "Dan tieu lien";
		type = T_900mm;
	}

	s = IMG_Load(pathImg.c_str());
	t = SDL_CreateTextureFromSurface(renderer, s);
	SDL_FreeSurface(s);
	//set trạng thái hoạt động lÀ TRUE
	active = 1;

}

void Bullet::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, t, NULL, &r, angle, NULL, SDL_FLIP_NONE);
}
void Bullet::move()
{
	if (distance <= 0)
	{
		active = 0;
	}
	if (active)
	{
		r.x += cos(angle) * speed;
		r.y += sin(angle) * speed;
		distance--;
	}

}
