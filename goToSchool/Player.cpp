﻿#include "Player.h"

Player::Player()
{
	memset(moveKey, 0, sizeof(moveKey));
	hp = 0;
}


Player::~Player()
{
	//Character::~Character();
	//SDL_DestroyTexture(texture);
	//SDL_FreeSurface(surface);
}
void Player::init(SDL_Renderer* renderer, string pathImg)
{
	Character::init(renderer, pathImg);
	f_rect = { 200,200,32,64 };
	speed = { 0,0 };
	hp = 100;
	active = true;
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });

}

//void Player::init(SDL_Renderer *renderer)
//{
//	// Các tài nguyên cần thiết
//	s = IMG_Load("img/tamGiac.png");
//	t = SDL_CreateTextureFromSurface(renderer, s);
//	/*weapon[0].type = USP;
//	weapon[1].type = AK_47;
//	weapon[2].type = MP5;*/
//
//	t = SDL_CreateTextureFromSurface(renderer, s);
//	r = { 250,440,60,60 };
//	speed = 5;
//	crossSpeed = (speed * sqrt(2)) / 2;
//	// Thông số cơ bản
//	angle = 0;
//	memset(moveKey, 0, sizeof(moveKey));
//	
//	//Các tọa độ
//	center = { (r.x + r.w) / 2, (r.y + r.h) / 2 };
//	vertices.push_back({ r.x, r.y });
//	vertices.push_back({ r.x + r.w, r.y });
//	vertices.push_back({ r.x + r.w, r.y + r.h });
//	vertices.push_back({ r.x, r.y + r.h });
//
//	transformVertices.push_back({ r.x, r.y });
//	transformVertices.push_back({ r.x + r.w, r.y });
//	transformVertices.push_back({ r.x + r.w, r.y + r.h });
//	transformVertices.push_back({ r.x, r.y + r.h });
//}
void Player::setMoveKey(int x)
{
	moveKey[x] = true;
}
void Player::desetMoveKey(int x)
{
	moveKey[x] = false;
}
void Player::update(Gun& weapon)
{
	attack(weapon);
	move();
}
void Player::update(Melle& weapon)
{
	attack(weapon);
	move();
}
void Player::move()
{
	speed = { 0,0 };
	//slow moving
	if (moveKey[SLOW])
	{
		speed.x = 2.1;
		speed.y = 2.1;
	}
	else if (moveKey[FAST]) //fast moving
	{
		speed.x = 10;
		speed.y = 10;
	}
	// base case move
	if (moveKey[UP] && moveKey[RIGHT])
	{
		speed.x = 5 * sqrt(2) / 2;
		speed.y = -5 * sqrt(2) / 2;
	}
	else if (moveKey[UP] && moveKey[LEFT])
	{
		speed.x = -5 * sqrt(2) / 2;
		speed.y = -5 * sqrt(2) / 2;
	}
	else if (moveKey[DOWN] && moveKey[RIGHT])
	{
		speed.x = 5 * sqrt(2) / 2;
		speed.y = 5 * sqrt(2) / 2;
	}
	else if (moveKey[DOWN] && moveKey[LEFT])
	{
		speed.x = -5 * sqrt(2) / 2;
		speed.y = 5 * sqrt(2) / 2;
	}
	else if (moveKey[UP])
	{
		speed.y = -5;
	}
	else if (moveKey[DOWN])
	{
		speed.y = 5;
	}
	else if (moveKey[LEFT])
	{
		speed.x = -5;
	}
	else if (moveKey[RIGHT])
	{
		speed.x = 5;
	}
	// Update center point
	//center = { (r.x + r.w) / 2, (r.y + r.h) / 2 };

	 //Update vertices
	vertices[0] = { f_rect.x, f_rect.y };
	vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
	vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
	vertices[3] = { f_rect.x, f_rect.y + f_rect.h };

	//for (int i = 0; i < vertices.size(); i++)
	//{
	//	cout << vertices[i].x << "\t" << vertices[i].y << endl;
	//}
	//cout << endl;
}

void Player::MoveTo()
{
	f_rect.x += speed.x;
	f_rect.y += speed.y;
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

void Player::attack(Melle& weapon)
{
	//if (isAttack)
	//{
	//	weapon.setIsAttack(true);
	//}
	//else if (!isAttack && ((int)weapon.getAngle() % 90 == 0)) {
	//	weapon.setIsAttack(false);
	//}
}

void Player::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_NONE);
	
}