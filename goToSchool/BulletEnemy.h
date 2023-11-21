#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include "bullet.h"
#include "Player.h"
class BulletEnemy :
    public Bullet
{
    void setTargetToPlayer(Player& player);
public:
    BulletEnemy() {}
    void init(SDL_Renderer* renderer, Player& player, string path);
    void update(Player& player);
    void render(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame);
};

#endif // !BULLETENEMY_H
