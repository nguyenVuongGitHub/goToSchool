#pragma once
#ifndef MELLE_H
#define MELLE_H

#include "weapon.h"
class Melle : public Weapon
{
	SDL_FPoint point;
	void attack(int curXMouse, float rectPlayer);
	
public:
	Melle()
	{
		damage = 2;
		speed = 15;
		angle = -90;
		isAttack = false;
		point = { 0,0 };
		
	}
	
	void init(SDL_Renderer* renderer, string pathImg) override;
	void render(SDL_Renderer* renderer, const SDL_FRect& rectPlayer);
	void update(SDL_Renderer* renderer,const SDL_FRect &rectPlayer);
};
#endif // !MELLE_H


