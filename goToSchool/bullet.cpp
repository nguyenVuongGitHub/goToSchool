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
	angle = 0;
	active = 0;
	dx = 0;
	dy = 0;
}

void Bullet::init(SDL_Renderer* renderer,float playerX, float playerY, int mouseX, int mouseY)
{
	name = "Dan sung truong";
	type = T_762mm;
	damage = 5;
	speed = 30;
	//set vị trí tại trung tâm của hình
	r = { playerX+30, playerY+30, 20, 20 };
	s = IMG_Load("img/T_762mm.png");
	t = SDL_CreateTextureFromSurface(renderer, s);

	
	dx = mouseX - playerX-30;
	dy = mouseY - playerY-30;
	angle = atan2(dy, dx);

	active = 1;

}

void Bullet::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, t, NULL, &r, angle, NULL, SDL_FLIP_NONE);
}
void Bullet::move(short HeightWindow, short WidthWindow)
{
	if (r.x <= 0 || r.y >= HeightWindow || r.x >= WidthWindow || r.y <= 0)
	{
		active = 0;
	}
	if (active)
	{
		r.x += cos(angle) * speed;
		r.y += sin(angle) * speed;
	}

}
