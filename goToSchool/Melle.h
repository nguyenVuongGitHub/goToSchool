//#pragma once
#ifndef MELLE_H
#define MELLE_H

#include "weapon.h"
class Melle : public Weapon
{
	void attack(int curXMouse, float rectPlayer);
	
public:
	Melle()
	{
		damage = 1;
		speed = 15;
		angle = 0;
	}
	
	void init(SDL_Renderer* renderer, string pathImg) override;
	void render(SDL_Renderer* renderer, const SDL_FRect& rectPlayer, const FlatVector& centerPlayer);
	void update(SDL_Renderer* renderer,const SDL_FRect &rectPlayer, const FlatVector& centerPlayer, float scrollX, float scrollY);
};
#endif // !MELLE_H


