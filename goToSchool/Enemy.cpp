#include "Enemy.h"

Enemy::Enemy()
{
	r = { 0,0,0,0 };
	t = NULL;
	s = NULL;
	hp = 0;
	type = 0;
	dx = 0, dy = 0;
	speed = 0;
	angle = 0;
	active = 0;
}

void Enemy::init(SDL_Renderer* renderer)
{
	r = { -10,-10,30,30 };
	s = IMG_Load("img/ball.png");
	t = SDL_CreateTextureFromSurface(renderer, s);
	SDL_FreeSurface(s);
	hp = 30;
	type = 0;
	speed = 2;
	active = 1;
}

void Enemy::move()
{
	if (active)
	{
		r.x += cos(angle) * speed;
		r.y += sin(angle) * speed;
	}
}

void Enemy::spam(int heightWindow, int widthWindow)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(-heightWindow, 2 * heightWindow);
	std::uniform_real_distribution<float> disY(-widthWindow, 2 * widthWindow);

	float x = disX(gen);
	float y = disY(gen);

	r = { x, y, 30, 30 };
}

void Enemy::setTargetToPlayer(Player &player)
{
	dx = player.r.x - r.x;
	dy = player.r.y - r.y;
	angle = atan2(dy,dx);
}

void Enemy::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, t, NULL, &r, angle, NULL, SDL_FLIP_NONE);
}
