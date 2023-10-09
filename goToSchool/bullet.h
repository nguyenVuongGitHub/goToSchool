#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
#define T_556mm 1
#define T_762mm 2
#define T_900mm 3

class Bullet
{
public:
	string name;
	short type;
	int damage;
	int speed;
	SDL_Texture* t;
	SDL_Surface* s;
	SDL_FRect r;
	double angle;
	double dx, dy;
	bool active;
	Bullet();
	void init(SDL_Renderer* renderer, float playerX, float playerY, int mouseX, int mouseY);
	void draw(SDL_Renderer* renderer);
	void move(short HeightWindow, short WidthWindow);
};

