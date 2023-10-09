﻿#include "Player.h"
Player::Player() :

	s(NULL),
	t(NULL),
	r({ 0,0,0,0 }), 
	speed(0),
	moveKey{0,0,0,0,0,0},
	crossSpeed(0)

{}

Player::~Player()
{
	SDL_FreeSurface(s);
	SDL_DestroyTexture(t);
}
void Player::init(SDL_Renderer *renderer)
{
	s = IMG_Load("img/tamGiac.png");

	t = SDL_CreateTextureFromSurface(renderer, s);
	r = { 250,440,60,60 };
	speed = 5;
	crossSpeed = (speed * sqrt(2)) / 2;
	memset(moveKey, 0, sizeof(moveKey));
}
void Player::move()
{
	
	//slow move
	if (moveKey[SLOW])
	{
		speed = 4.8;
		crossSpeed = 3.5;
	}
	else if (moveKey[FAST])
	{
		speed = 15;
		crossSpeed = 9.5;
	}
	else {
		// default speed
		speed = 10;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	//fast move

	// base case move
	if (moveKey[UP] && moveKey[RIGHT])
	{
		
		if (r.y >= 0 + 10) {
			r.y -= crossSpeed;
		}
		if (r.x <= 1920 - 70) {
			r.x += crossSpeed;
		}
	}
	else if (moveKey[UP] && moveKey[LEFT])
	{
		
		if (r.y >= 0 + 10) {
			r.y -= crossSpeed;
		}
		if (r.x >= 0 + 10) {
			r.x -= crossSpeed;
		}
	}
	else if (moveKey[DOWN] && moveKey[RIGHT])
	{
		
		
		if (r.y <= 1080 - 60) {
			r.y += crossSpeed;
		}

		if (r.x <= 1920 - 70) {
			r.x += crossSpeed;
		}
	}
	else if (moveKey[DOWN] && moveKey[LEFT])
	{
		if (r.y <= 1080 - 60) {
			r.y += crossSpeed;
		}
		if (r.x >= 0 + 10) {
			r.x -= crossSpeed;
		}
	}
	else if (moveKey[UP])
	{
		if (r.y >= 0 + 10) {
			r.y -= speed;
		}
	}
	else if (moveKey[DOWN])
	{
		if (r.y <= 1080 - 60) {
			r.y += speed;
		}
	}
	else if (moveKey[LEFT])
	{
		if (r.x >= 0 + 10) {
			r.x -= speed;
		}
	}
	else if (moveKey[RIGHT])
	{
		if (r.x <= 1920 - 70) {
			r.x += speed;
		}
	}
}

void Player::draw(SDL_Renderer* renderer)
{
	int curXMouse;
	int curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);

	// Tính toán góc giữa chuột và tâm tam giác
	float deltaX = curXMouse - r.x - (r.w / 2);
	float deltaY = curYMouse - r.y - (r.h / 2);
	float angle = atan2(deltaY, deltaX) * 180 / M_PI;

	// Đảo ngược góc quay để đỉnh tam giác hướng về phía chuột
	angle += 90;
	SDL_RenderCopyExF(renderer, t, NULL, &r, angle, NULL, SDL_FLIP_NONE);
}