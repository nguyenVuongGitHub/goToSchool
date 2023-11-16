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
    void init(SDL_Renderer* renderer, Player& player);
    void update(Player& player);
    //void move();
};

#endif // !BULLETENEMY_H
