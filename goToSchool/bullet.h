//#pragma once


#ifndef BULLET_H
#define BULLET_H

#include "Obj.h"



class Bullet : public Object
{
	short type;
	bool active;
	double angle;
	double dx, dy;
	int speed;
	int distance;
	int damage;
	void move();

public:

	Bullet();

	void setType(short t) { type = t; }
	void setActive(bool a) { active = a; }
	void setAngle(double d) { angle = d; }
	void setDxDy(double dx, double dy) { this->dx = dx; this->dy = dy; }
	void setDistance(int d) { distance = d; }
	void setSpeed(int s) { speed = s; }
	void setDamage(int d) { damage = d; }

	short getType() { return type; }
	bool getActive() { return active; }
	double getAngle() { return angle; }
	double getDx() { return dx; }
	double getDy() { return dy; }
	int getSpeed() { return speed; }
	int getDamage() { return damage; }
	int getDistance() { return distance; }

	//Bullet(string name, short type, bool active, double angle, double dx, double dy, int speed, int distance, int damage);
	void init(SDL_Renderer* renderer, short typeWeapon);
	void render(SDL_Renderer* renderer);

	void update();
};



#endif // !BULLET_H


