//#pragma once
#ifndef GUN_H
#define GUN_H

#include "weapon.h"
#include "bullet.h"
class Gun : public Weapon
{
	short type;
	short numberBullets;
	long long totalBullets;
	short distance;
	void attack(SDL_Renderer* renderer, vector<Bullet>& bulletList, Uint32& lastShotTime, const SDL_FRect& rectPlayer, float scrollX, float scrollY);
public:
	Gun();
	Gun(short type, short numbetBullets, long long totalBullets,short distance, short damage);
	
	long long getTotalBullets() { return totalBullets; }
	void setTotalBullets(long long totalBullets) { this->totalBullets = totalBullets; }

	void init(SDL_Renderer* renderer, string pathImg) override;
	void render(SDL_Renderer* renderer, const SDL_FRect& rectPlayer, const float&scrollX);
	void update(SDL_Renderer* renderer, vector<Bullet>& bulletList, Uint32& lastShotTime, const SDL_FRect& rectPlayer, const FlatVector& centerPlayer, float scrollX, float scrollY);
	void reset();
};

#endif // !GUN_H


