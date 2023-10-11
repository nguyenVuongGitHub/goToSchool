#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;

#define USP 1
#define AK_47 2
#define MP5 3

// type bullet
#define T_556mm 1
#define T_762mm 2
#define T_900mm 3


/*
	sung luc: speed  60, time_since_last_shot = 500
	sung ak: speed 100, time_since_last_shot = 300
	sung tieuLien: speed 120, time_since_last_shot 300
*/

class Bullet
{
public:
	string name;
	short type;
	SDL_Texture* t;
	SDL_Surface* s;
	SDL_FRect r;
	bool active;
	double angle;
	double dx, dy;
	int speed;
	int distance;
	Bullet();
	void init(SDL_Renderer* renderer, string pathImg, short typeWeapon);
	void draw(SDL_Renderer* renderer);
	void move();
};

