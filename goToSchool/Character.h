//#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include "Obj.h"

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
	FlatVector center() const
	{
		float x = 0, y = 0;
		for (int i = 0; i < vertices.size(); i++)
		{
			x += vertices[i].x;
			y += vertices[i].y;
		}
		x /= (float)vertices.size();
		y /= (float)vertices.size();
		return FlatVector(x, y);
	}
};


#endif // !CHARACTER_H


