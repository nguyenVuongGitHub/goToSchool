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

#define DIE 0
#define ATTACK 1
#define MOVE 2

class Enemy : public Character
{
	short type; // 0 - slime  1 - skeleton 2 - boss
	float radius;
	int damage;
	int distanceAI; // số bước đi khi là AI
	int countAI; // đếm để dừng lại khi là AI
	Uint32 lastShotTime;
	int activeBoss;
	float frameLaze;
	float distanceToPlayer(float xPlayer, float yPlayer);
	void move(Player& player);
	void setTargetToPlayer(Player& player);
	bool seePlayer(float x, float y);
	void setAI();
	void itemDroped(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped);
	int dropChance();
	void attack(SDL_Renderer* renderer, Player& player, vector<BulletEnemy>& bulletEnemyList);
	void attack2(SDL_Renderer* renderer, Player& player, vector<BulletEnemy>& bulletEnemyList); // for boss
	SDL_RendererFlip flip;
public:
	Enemy();
	~Enemy();
	void setType(short type) {
		this->type = type;
	}
	short getType() {
		return type;
	}
	void spawnAt0();
	void spawnAt1();
	void spawnAt2();
	void spawnAt3();
	void spawnAt4();
	void spawnAt5();
	void spawnAt6();
	void spawnAt7();
	void spawnBoss1();
	void spawnBoss2();
	void spawnBoss3();
	void spawnBoss4();
	void setDamage(int damage) { this->damage = damage; }
	int getDamage() { return damage; }
	float getRadius() const { return radius; }
	void init(SDL_Renderer* renderer, short type);
	void setPos(float x, float y);
	//render slime
	void render0(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame);
	//render skeleton
	void render1(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame);
	//render boss
	void renderBoss(SDL_Renderer* renderer, float scrollX, float scrollY,FlatVector frameBoss);

	int getActiveBoss() { return activeBoss; }
	void setActiveBoss(int ac) { activeBoss = ac; }
	void freeRender(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped, vector<Enemy>& enemyList, int i, FlatVector frameBoss);
	void update(SDL_Renderer* renderer, Player& player,vector<BulletEnemy>& bulletEnemyList);

	// Hàm điều kiện để tìm kiếm dựa trên thuộc tính value
	static bool findType(const Enemy& obj, int type) {
		return obj.type == type;
	}
};

#endif // !ENEMY_H



