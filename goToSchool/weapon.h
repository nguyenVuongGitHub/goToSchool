//#pragma once

#ifndef WEAPON_H
#define WEAPON_H

#include "Obj.h"
//#include "bullet.h"
//#include "Player.h"

//class Player;
class Weapon : public Object
{
protected:
	//short type;                                                   
	int damage;
	double speed;
	double angle;
	bool isAttack;
	//short numberBullets; // so luong vien dan moi bang dan
	//long long totalBullets; // tổng số lượng đạn 
	//int distance;
	//void shoot(SDL_Renderer* renderer, vector<Bullet>& listBullet, Player &player, Uint32& lastShotTime);
public:

	Weapon() : damage(0), speed(0), angle(0), isAttack(false)
	{}

	bool getIsAttack() { return isAttack; }
	void setIsAttack(bool x) { isAttack = x; }
	int getDamage() { return damage; }
	void setDamage(int d) { damage = d; }
	double getSpeed() { return speed; }
	void setSpeed(double s) { speed = s; }
	double getAngle() { return angle; }
	void setAngle(double a) { angle = a; }

	virtual void init(SDL_Renderer* renderer, string pathImg) 
	{}
	//void render(SDL_Renderer* renderer, Player& p);
	//friend class Player;
	//long long getTotalBullet();
	//void setTotalBullet(int x);
	//void update(SDL_Renderer* renderer, vector<Bullet>& bulletList, Player& player, Uint32& lastShotTime);
	//void update(SDL_Renderer* renderer, vector<Bullet>& listBullet, float playerX, float playerY);
};

#endif // !WEAPON_H

