//#pragma once

#ifndef ENEMY_H
#define ENEMY_H
#include "Character.h"
#include "Player.h"
#include "coin.h"
#include "BulletDropped.h"
#include <random>
#include <time.h>
#include "BulletEnemy.h"
class Enemy : public Character
{
	short type; // 0 - slime  1 - skeleton 2 - boss
	float radius;
	int damage;
	int distanceAI; // số bước đi khi là AI
	int countAI; // đếm để dừng lại khi là AI
	Uint32 lastShotTime;
	float distanceToPlayer(float xPlayer, float yPlayer);
	void move(Player& player);
	void setTargetToPlayer(Player& player);
	bool seePlayer(float x, float y);
	void setAI();
	void itemDroped(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped);
	int dropChance();
	void attack(SDL_Renderer* renderer, Player& player, vector<BulletEnemy>& bulletEnemyList);
public:
	Enemy();
	~Enemy();
	void setType(short type) {
		this->type = type;
	}
	short getType() {
		return type;
	}
	void spawnAtLake();
	void spawnAtGround();
	void spawnAtGround2();
	void spawnAtGround3();
	void spawnAtGround4();
	void setDamage(int damage) { this->damage = damage; }
	int getDamage() { return damage; }
	float getRadius() const { return radius; }
	void init(SDL_Renderer* renderer, short type);
	void setPos(float x, float y);
	//render slime
	void render0(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame);
	//render skeleton
	void render1(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame);
	void freeRender(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped, vector<Enemy>& enemyList, int i);
	void update(SDL_Renderer* renderer, Player& player,vector<BulletEnemy>& bulletEnemyList);
};

#endif // !ENEMY_H



