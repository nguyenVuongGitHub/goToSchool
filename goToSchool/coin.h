
#ifndef COIN_H
#define COIN_H

#include "ItemDropped.h"
class coin :
    public ItemDropped
{
public:
	coin() {};
	void init(SDL_Renderer* renderer, string pathImg) override;
	void update(const SDL_FRect& rectPlayer);
	void move(const SDL_FRect& rectPlayer);
	void render(SDL_Renderer* renderer, int curFrame);
};

#endif // !COIN_H



