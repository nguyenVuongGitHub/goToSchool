#include "EveryObject.h"

void EveryObject::init(SDL_Renderer* renderer, string pathImg)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	
}

void EveryObject::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyF(renderer, texture, NULL, &f_rect);
}
