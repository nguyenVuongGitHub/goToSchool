#include "Melle.h"

void Melle::attack(int curXMouse , float rectPlayer)
{
	// 90 và -270 là góc phía dưới tính từ -90
	//
	//	       -90
	// -speed      +speed			
	//		 -270,90
	//
	if (angle == 90 || angle == -270) angle = -90;

	if ( isAttack && curXMouse < rectPlayer)
	{
		angle -= speed;
	}
	
	else if ( isAttack && curXMouse > rectPlayer)
	{
		angle += speed;
	}

	
}

void Melle::init(SDL_Renderer* renderer, string pathImg)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer,surface);

	f_rect = { 0,0,128,20 };
}

void Melle::render(SDL_Renderer* renderer, const SDL_FRect& rectPlayer)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);

	if (curXMouse <= rectPlayer.x + rectPlayer.w/2)
	{
		f_rect.x = rectPlayer.x-20;
		f_rect.y = rectPlayer.y + rectPlayer.h / 2;
		point = { 0,0};
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, &point, SDL_FLIP_VERTICAL);

	}else
	{
		f_rect.x = rectPlayer.x + rectPlayer.w;
		f_rect.y = rectPlayer.y + rectPlayer.h / 2;
		point = { 0,0 };
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, &point, SDL_FLIP_NONE);
	}

}

void Melle::update(SDL_Renderer* renderer, const SDL_FRect &rectPlayer)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);


	//float deltaX = curXMouse - (rectPlayer.x + rectPlayer.w / 2);
	//float deltaY = curYMouse - (rectPlayer.y + rectPlayer.h / 2);
	//// tính góc giữa người chơi và chuột
	//angle = atan2(deltaY, deltaX) * 180 / M_PI;

	attack(curXMouse,rectPlayer.x + rectPlayer.w/2);
}
