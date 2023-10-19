#include "Character.h"

Character::Character()
{
	speed = 0;
	crossSpeed = 0; // tốc độ khi đi chéo
	hp = 0;
	angle = 0;
	isAttack = false;
	active = false;
	dx = 0;
	dy = 0;
	
}
Character::~Character()
{
	/*SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);*/
	//cout << "Doi tuong da bi Huy\n";
}
void Character::init(SDL_Renderer* renderer, string pathImg)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	f_rect = { 0,0,0,0 };
}


void Character::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture, NULL, &f_rect);
}

