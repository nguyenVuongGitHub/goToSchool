#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include "bullet.h"
#include <vector>

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
class Weapon
{
public:
	string name;
	short type;
	short numberBullets; // so luong vien dan moi bang dan
	long long totalBullets; // tổng số lượng đạn 
	int distance;
	int damage;
	int speed;
	Weapon();
	void init();
	void draw();
	void shoot(SDL_Renderer* renderer, vector<Bullet>& listBullet, float playerX, float playerY, int heightWindow, int WidthWindow);
};

