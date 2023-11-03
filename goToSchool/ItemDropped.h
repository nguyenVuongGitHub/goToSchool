#ifndef ITEM_DROPPED_H
#define ITEM_DROPPED_H



#include "Obj.h"
class ItemDropped :
    public Object
{
protected:
	int distance;
	double angle;
	int speed;
	int timeExis; // thời gian tồn tại
	bool isActive;
public:
	ItemDropped();
	float distanceFromPlayer(SDL_FRect rectPlayer);
	void setTargetToPlayer(SDL_FRect rectPlayer);
	void setAngle(double angle) { this->angle = angle; }
	void setDistance(int distance) { this->distance = distance; }
	void setActive(bool active) { isActive = active; }
	void setSpeed(double speed) { this->speed = speed;}
	void setTimeExis(int timeExis) { this->timeExis = timeExis; }

	double getAngle() { return angle; }
	int getDistance() { return distance; }
	bool getActive() { return isActive; }
	int getSpeed() { return speed; }
	int getTimeExis() { return timeExis; }

	void init(SDL_Renderer* renderer, string pathImg) override;
	void render(SDL_Renderer* renderer) override;
	void update();
	void moveToPlayer(const SDL_FRect& rectPlayer);
};


#endif // !ITEM_DROPED_H

