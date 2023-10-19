#pragma once
#include "Obj.h"
#include "bullet.h"
#include "Player.h"

#ifndef WEAPON_H
#define WEAPON_H

#define SPEED_USP 25
#define SPEED_AK 30
#define SPEED_MP5 40

#define DISTANCE_AK 25
#define DISTANCE_USP 20
#define DISTANCE_MP5 22

#define NUMBER_BULLET_AK 5
#define NUMBER_BULLET_USP 2
#define NUMBER_BULLET_MP5 9

using namespace std;
class Player;
class Weapon : public Object
{
	string name;
	short type;                                                   
	short numberBullets; // so luong vien dan moi bang dan
	long long totalBullets; // tổng số lượng đạn 
	int distance;
	int damage;
	double speed;
	double angle;

	bool isAttack;

	void shoot(SDL_Renderer* renderer, vector<Bullet>& listBullet, Player &player, Uint32& lastShotTime);
public:

	Weapon();
	friend class Player;
	long long getTotalBullet();
	void setTotalBullet(int x);
	bool getIsAttack();
	void setIsAttack(bool x);
	short getType() { return type; };
	int getDamage() { return damage; };
	void setDamage(int d) { damage = d; };
	void init(SDL_Renderer* renderer, string pathImg, short type);
	void render(SDL_Renderer* renderer, Player& p);
	void update(SDL_Renderer* renderer, vector<Bullet>& bulletList, Player& player, Uint32& lastShotTime);
	//void update(SDL_Renderer* renderer, vector<Bullet>& listBullet, float playerX, float playerY);
};

#endif // !WEAPON_H

