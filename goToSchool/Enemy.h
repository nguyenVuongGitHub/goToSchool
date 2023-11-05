//#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
#include "Player.h"
#include "coin.h"
#include "BulletDropped.h"
#include <random>
#include <time.h>

class Enemy : public Character
{
	short type;
	float radius;
	void move() override;
	void spawn(int heightWindow, int widthWindow);
	void setTargetToPlayer(Player& player);
	void itemDroped(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped);
	int dropChance();
public:
	Enemy();
	~Enemy();
	float getRadius() const { return radius; }
	void init(SDL_Renderer* renderer, string path);
	void render(SDL_Renderer* renderer) override;
	void freeRender(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped, vector<Enemy>& enemyList, int i);
	void update(Player& player);
};

#endif // !ENEMY_H



