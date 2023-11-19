﻿#include "Character.h"

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
}
void Character::init(SDL_Renderer* renderer, string pathImg)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}


void Character::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture, NULL, &f_rect);
}

