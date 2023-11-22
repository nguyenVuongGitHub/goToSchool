#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include "bullet.h"
#include "Player.h"
class BulletEnemy :
    public Bullet
{
    void setTargetToPlayer(Player& player);
    float frameLaze;
    float angleFlip;
public:
    BulletEnemy() { frameLaze = 0; angleFlip = 0; }
    void setFrameLaze(float x) { frameLaze = x; }
    float getFrameLaze() { return frameLaze; }
    void setAngleflip(float x)
    {
        angleFlip = x;
    }
    float getAngleflip() { return angleFlip; }
    void init(SDL_Renderer* renderer, Player& player, string path, float xEnemy, float yEnemy, int typeEnemy);
    void update(Player& player, float xenemy, float yenemy);
    void render(SDL_Renderer* renderer, float scrollX, float scrollY);
};

#endif // !BULLETENEMY_H
