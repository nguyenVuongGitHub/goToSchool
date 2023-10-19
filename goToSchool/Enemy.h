#pragma once
#include "Character.h"
#include "Player.h"
#include <random>
using namespace std;

class Enemy : public Character
{
	short type;
	float radius;
	void move() override;
	void spawn(int heightWindow, int widthWindow);
	void setTargetToPlayer(Player& player);
public:
	Enemy();
	~Enemy();
	void init(SDL_Renderer* renderer, string path);
	void render(SDL_Renderer* renderer) override;
	void freeRender(vector<Enemy>& enemyList, int i);
	void update(Player& player);
};

