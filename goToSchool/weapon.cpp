#include "weapon.h"
Weapon::Weapon()
{
	name = "";
	type = 0;
	numberBullets = 0;
	distance = 0;
	damage = 0;
	speed = 0;
	totalBullets = 0;
}

void Weapon::init()
{
	if (type == AK_47)
	{
		name = "AK 47";
		numberBullets = NUMBER_BULLET_AK;
		distance = DISTANCE_AK;
		damage = 10;
		speed = SPEED_AK;
		totalBullets = 100;
	}
	if (type == USP)
	{
		name = "USP";
		numberBullets = NUMBER_BULLET_USP;
		distance = DISTANCE_USP;
		damage = 3;
		speed = SPEED_USP;
		totalBullets = 99999999;
	}
	if (type == MP5)
	{
		name = "MP5";
		numberBullets = NUMBER_BULLET_MP5;
		distance = DISTANCE_MP5;
		damage = 7;
		speed = SPEED_MP5;
		totalBullets = 100;
	}
}

void Weapon::shoot(SDL_Renderer* renderer,vector<Bullet> &listBullet,float playerX, float playerY, int heightWindow, int WidthWindow)
{
	
	if (totalBullets > 0 && listBullet.size() <= numberBullets)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		//khởi tạo viên đạn mới
		Bullet newBullet;


		// set vị trí đạn bắn ra từ đâu
		newBullet.r = {playerX + 30, playerY + 30, 20, 20};
		newBullet.dx = mouseX - playerX - 30;
		newBullet.dy = mouseY - playerY - 30;
		newBullet.angle = atan2(newBullet.dy, newBullet.dx);
		newBullet.speed = speed;
		newBullet.distance = distance;

		string pathBullet;
		// tùy theo loại súng mà sẽ lấy đạn của loại đó
		if (type == AK_47)
			pathBullet = "img/T_762mm.png";
		else if (type == USP)
			pathBullet = "img/T_556mm.png";
		else if(type == MP5)
			pathBullet = "img/T_900mm.png";

		newBullet.init(renderer, pathBullet.c_str(), type);
		listBullet.push_back(newBullet);
	}
}
