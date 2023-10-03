#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
class Player
{
public:
	Player();
	~Player();
	SDL_Surface* s;
	SDL_Texture* t;
	SDL_FRect r;
	float speed;
	float crossSpeed;
	bool moveKey[4];

	void init(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer);
	void move();
	//
};

