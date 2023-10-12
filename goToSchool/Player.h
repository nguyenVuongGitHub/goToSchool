#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "FlatVector.h"
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
	std::vector<FlatVector> vertices; // Các đỉnh tạo độ
	std::vector<FlatVector> transformVertices; // Các đỉnh được chuyển đổi
	FlatVector center; // Vị trí trung tâm của vật thể, người chơi

	SDL_RendererFlip isFlip; // Theo dõi khả năng lật hình

	float angle; // Góc xoay
	float speed;
	float crossSpeed;
	bool moveKey[4];

	void init(SDL_Renderer* renderer, SDL_FRect r);
	void draw(SDL_Renderer* renderer);
	void move();
	//
};

