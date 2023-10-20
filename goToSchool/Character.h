#pragma once
#include "Obj.h"

#ifndef CHARACTER_H
#define CHARACTER_H


class Character : public Object
{
protected:
	double speed;
	double crossSpeed; // tốc độ khi đi chéo
	short hp; // máu
	double angle;
	bool isAttack;
	double dx, dy;
	bool active;
public:
	Character();
	~Character();
	void init(SDL_Renderer* renderer, string pathImg) override;
	void render(SDL_Renderer* renderer) override;
	virtual void move() {

	}
	virtual void attack() {

	}
	bool getIsAttack() { return isAttack; };
	void setIsAttack(bool x) { this->isAttack = x; };
	short getHP() { return hp; };
	void setHP(short h) { hp = h; };
	bool getActive() { return active; };
	void setActive(bool x) { active = x; };
};


#endif // !CHARACTER_H


