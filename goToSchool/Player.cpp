#include "Player.h"

Player::Player()
{
	memset(moveKey, 0, sizeof(moveKey));
	hp = 0;
}
Player::~Player()
{
}
void Player::init(SDL_Renderer* renderer, string pathImg)
{
	isMove = false;
	Character::init(renderer, pathImg);
	framAni = { 0,0 };
	f_rect = { 1000,1000,32,64 };
	speed = 5;
	crossSpeed = (speed * sqrt(2)) / 2;
	hp = 100;
	active = true;
	touchable = true;
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });

}

void Player::setMoveKey(int x)
{
	moveKey[x] = true;
	isMove = true;
}
void Player::desetMoveKey(int x)
{
	moveKey[x] = false;
	isMove = false;
}
void Player::update(Gun& weapon)
{
	attack(weapon);
	move();
}
void Player::update(Melle& weapon)
{
	move();
}
void Player::move()
{

	//slow moving
	if (moveKey[SLOW])
	{
		speed = 2.1;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	else if (moveKey[FAST]) //fast moving
	{
		speed = 10;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	else {
		// default moving
		speed = 5;
		crossSpeed = (speed * sqrt(2)) / 2;
	}

	// base case move
	if (moveKey[UP] && moveKey[RIGHT])
	{
		f_rect.y -= crossSpeed;
		f_rect.x += crossSpeed;
	}
	else if (moveKey[UP] && moveKey[LEFT])
	{
		f_rect.y -= crossSpeed;
		f_rect.x -= crossSpeed;

	}
	else if (moveKey[DOWN] && moveKey[RIGHT])
	{
		f_rect.y += crossSpeed;
		f_rect.x += crossSpeed;
	}
	else if (moveKey[DOWN] && moveKey[LEFT])
	{
		f_rect.y += crossSpeed;
		f_rect.x -= crossSpeed;
	}
	else if (moveKey[UP])
	{
		f_rect.y -= speed;
	}
	else if (moveKey[DOWN])
	{
		f_rect.y += speed;
	}
	else if (moveKey[LEFT])
	{
		f_rect.x -= speed;
	}
	else if (moveKey[RIGHT])
	{
		f_rect.x += speed;
	}
	 //Update vertices
	vertices[0] = { f_rect.x, f_rect.y };
	vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
	vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
	vertices[3] = { f_rect.x, f_rect.y + f_rect.h };

}

void Player::attack(Gun &weapon)
{
	// check isAttack at processInput (gameState.cpp)
	if (isAttack)
	{
		weapon.setIsAttack(true);
	}
	else {
		weapon.setIsAttack(false);
	}
}

void Player::render(SDL_Renderer* renderer, float scrollX, float scrollY)
{
	srcRect.x = (int)framAni.x * 32;
	srcRect.y = (int)framAni.y * 64;
	srcRect.w = 32;
	srcRect.h = 64;
	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	cursorX += scrollX;
	cursorY += scrollY;
	if (cursorX < f_rect.x + f_rect.w / 2)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, angle, NULL, flip);
	
}

void Player::reset2()
{
	desetMoveKey(LEFT);
	desetMoveKey(UP);
	desetMoveKey(DOWN);
	desetMoveKey(RIGHT);
	desetMoveKey(FAST);
	desetMoveKey(SLOW);
	isMove = false;
	isAttack = false;
}

void Player::reset()
{
	desetMoveKey(LEFT);
	desetMoveKey(UP);
	desetMoveKey(DOWN);
	desetMoveKey(RIGHT);
	desetMoveKey(FAST);
	desetMoveKey(SLOW);
	isMove = true;
	vertices.clear();
}
