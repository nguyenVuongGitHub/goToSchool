﻿#include "Player.h"
Player::Player()
{
	// Các tài nguyên cần thiết
	s = NULL;
	t = NULL;
	r = { 0,0,0,0 };

	// Thông số cơ bản
	angle = 0;
	speed = 0;
	isFlip = SDL_FLIP_NONE;
	memset(moveKey, 0, sizeof(moveKey));
	crossSpeed = 0;

	//Các tọa độ
	center = { 0,0 };
	//vertices.push_back({ 0,0 });
	//vertices.push_back({ 0,0 });
	//vertices.push_back({ 0,0 });
	//vertices.push_back({ 0,0 });
}


Player::~Player()
{
	SDL_FreeSurface(s);
	SDL_DestroyTexture(t);
}
void Player::init(SDL_Renderer *renderer, SDL_FRect r)
{
	// Các tài nguyên cần thiết
	s = IMG_Load("img/grass_block.png");
	s = IMG_Load("img/tamGiac.png");
	weapon[0].type = USP;
	weapon[1].type = AK_47;
	weapon[2].type = MP5;

	t = SDL_CreateTextureFromSurface(renderer, s);
	this->r = r;

	// Thông số cơ bản
	angle = 0;
	speed = 10;
	isFlip = SDL_FLIP_NONE;
	crossSpeed = 5;
	memset(moveKey, 0, sizeof(moveKey));
	
	//Các tọa độ
	center = { (r.x + r.w) / 2, (r.y + r.h) / 2 };
	vertices.push_back({ r.x, r.y });
	vertices.push_back({ r.x + r.w, r.y });
	vertices.push_back({ r.x + r.w, r.y + r.h });
	vertices.push_back({ r.x, r.y + r.h });

	transformVertices.push_back({ r.x, r.y });
	transformVertices.push_back({ r.x + r.w, r.y });
	transformVertices.push_back({ r.x + r.w, r.y + r.h });
	transformVertices.push_back({ r.x, r.y + r.h });
}
void Player::move()
{
	
	//slow move
	if (moveKey[SLOW])
	{
		speed = 2.1;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	else if (moveKey[FAST])
	{
		speed = 10;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	else {
		// default speed
		speed = 5;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	//fast move

	// base case move
	if (moveKey[UP] && moveKey[RIGHT])
	{
		r.y -= crossSpeed;
		r.x += crossSpeed;
		isFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (moveKey[UP] && moveKey[LEFT])
	{
		isFlip = SDL_FLIP_NONE;
		r.y -= crossSpeed;
		r.x -= crossSpeed;

	}
	else if (moveKey[DOWN] && moveKey[RIGHT])
	{
		r.y += crossSpeed;
		r.x += crossSpeed;
		isFlip = SDL_FLIP_HORIZONTAL;
	}
	else if (moveKey[DOWN] && moveKey[LEFT])
	{
		isFlip = SDL_FLIP_NONE;
		r.y += crossSpeed;
		r.x -= crossSpeed;
	}
	else if (moveKey[UP])
	{
		r.y -= speed;
	}
	else if (moveKey[DOWN])
	{
		r.y += speed;
	}
	else if (moveKey[LEFT])
	{
		isFlip = SDL_FLIP_NONE;
		r.x -= speed;
	}
	else if (moveKey[RIGHT])
	{
		isFlip = SDL_FLIP_HORIZONTAL;
		r.x += speed;
	}
	// Update center point
	center = { (r.x + r.w) / 2, (r.y + r.h) / 2 };

	// Update vertices
	vertices[0] = { r.x, r.y };
	vertices[1] = { r.x + r.w, r.y };
	vertices[2] = { r.x + r.w, r.y + r.h };
	vertices[3] = { r.x, r.y + r.h };
}

void Player::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, t, NULL, &r, angle, NULL, isFlip);
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