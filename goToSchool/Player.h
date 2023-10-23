#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include "Character.h"
#include "bullet.h"
#include "weapon.h"
#include "Gun.h"
#include "Melle.h"
class Player : public Character
{
	bool moveKey[6];
	void move() override;

	void attack(Gun& weapon);
	void attack(Melle& weapon);

public:
	Player();
	~Player();
	friend class Weapon;


	void init(SDL_Renderer* renderer, string pathImg);
	void update(Gun& weapon);
	void update(Melle& weapon);

	void setMoveKey(int x); // set move là true
	void desetMoveKey(int x); // set move là false
	void render(SDL_Renderer* renderer) override;

};

#endif // !PLAYER_H



