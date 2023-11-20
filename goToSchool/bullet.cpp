#include "bullet.h"

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
	if (typeWeapon == AK)
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
	flip = SDL_FLIP_NONE;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	//set trạng thái hoạt động lÀ TRUE
	active = 1;
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
}

void Bullet::render(SDL_Renderer* renderer, float scrollX, float scrollY)
{
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, NULL, &tmp, angleFlip, NULL, flip);
}
void Bullet::move(float x, float w)
{
	if (distance <= 0)
	{
		active = 0;
	}
	if (active)
	{
		
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
		if (f_rect.x > x + w / 2)
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		distance-=speed;
		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
}
void Bullet::update(float x, float w)
{
	move(x,w);
}