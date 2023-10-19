#pragma once
#include "Character.h"
#include "bullet.h"
#include "weapon.h"

#ifndef PLAYER_H
#define PLAYER_H

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SLOW 4
#define FAST 5
class Player : public Character
{
	bool moveKey[6];
	void move() override;

public:
	Player();
	~Player();
	friend class Weapon;

	void attack(Weapon& weapon);
	void init(SDL_Renderer* renderer, string pathImg);
	void update(Weapon& weapon);
	void setMoveKey(int x); // set move là true
	void desetMoveKey(int x); // set move là false
	void render(SDL_Renderer* renderer) override;

};

#endif // !PLAYER_H



