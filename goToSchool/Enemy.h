#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include <time.h>
#include <random>
using namespace std;

class Enemy
{
public:
	SDL_FRect r;
	SDL_Texture* t;
	SDL_Surface* s;
	short hp;
	short type;
	float dx, dy;
	short speed;
	float angle;
	bool active;
	float radius;
	vector<FlatVector> vertices;
	FlatVector center;
	Enemy();
	void init(SDL_Renderer* renderer);
	void move();
	void spawn(int heightWindow, int widthWindow);
	void setTargetToPlayer(Player& player);
	void draw(SDL_Renderer* renderer);
};

