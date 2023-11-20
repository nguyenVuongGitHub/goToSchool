#ifndef BulletDroped_H
#define BulletDroped_H


#include "ItemDropped.h"
class BulletDropped :
    public ItemDropped
{
	int type;
public:
	int getType() { return type; }
	void setType(int type) { this->type = type; }
	BulletDropped() { type = 0; }
	void init(SDL_Renderer* renderer, string pathImg) override;
	void update(const SDL_FRect& rectPlayer);
	void move(const SDL_FRect& rectPlayer);
	void render(SDL_Renderer* renderer, int curFrame, float scrollX, float scrollY);
};

#endif // !BulletDroped_H

