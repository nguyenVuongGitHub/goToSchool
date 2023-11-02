#include "Gun.h"

void Gun::attack(SDL_Renderer* renderer, vector<Bullet>& bulletList, Uint32 &lastShotTime, const SDL_FRect& rectPlayer)
{
	Uint32 curentTime = SDL_GetTicks();
	Uint32 timeShot = curentTime - lastShotTime;
	// điều kiện giới hạn tốc độ bắn sau mỗi 200ms và tổng số lượng đạn còn lại phải lớn hơn 0, và trong danh sách đạn phải bé hơn số đạn mỗi băng
	if (timeShot >= 200 && totalBullets > 0 && bulletList.size() <= numberBullets)
	{

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		totalBullets--;

		Bullet newBullet;
		newBullet.setRect({ rectPlayer.x + rectPlayer.w / 2,rectPlayer.y + rectPlayer.h / 2,15,15 });
		newBullet.setDxDy(mouseX - f_rect.x - 30, mouseY - f_rect.y - 30);
		newBullet.setAngle(atan2(newBullet.getDy(), newBullet.getDx()));
		newBullet.setSpeed(speed);
		//cout << speed << endl;
		newBullet.setDamage(damage);
		newBullet.setDistance(distance);
		
		newBullet.setActive(true);

		newBullet.init(renderer, type);
		
		bulletList.push_back(newBullet);
		//cout << bulletList.size() << endl;
		lastShotTime = curentTime;
	}
}

Gun::Gun(short type, short numbetBullets, long long totalBullets, short distance, short damage)
{
	Weapon::Weapon();
	this->type = type;
	this->numberBullets = numberBullets;
	this->totalBullets = totalBullets;
	this->distance = distance;
	this->damage = damage;
	if (type == USP)	speed = SPEED_USP;
	else if (type == AK)	speed = SPEED_AK;
	else speed = SPEED_MP5;

}

void Gun::init(SDL_Renderer* renderer, string pathImg)
{
	if (type == USP)
		totalBullets = 999999999;
	else if (type == AK)
		totalBullets = 300;
	else totalBullets = 200;

	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	f_rect = { 0,0,64,64 };
}

void Gun::render(SDL_Renderer* renderer, const SDL_FRect &rectPlayer)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
		
	if (curXMouse < rectPlayer.x)
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_VERTICAL);
	else 
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_NONE);
}

void Gun::update(SDL_Renderer* renderer, vector<Bullet>& bulletList, Uint32& lastShotTime,const SDL_FRect& rectPlayer)
{
	f_rect = rectPlayer;
		
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
	
	
	float deltaX = curXMouse - (rectPlayer.x + rectPlayer.w / 2);
	float deltaY = curYMouse - (rectPlayer.y + rectPlayer.h / 2);
	// tính góc giữa người chơi và chuột
	angle = atan2(deltaY, deltaX) * 180 / M_PI;
	
	if (isAttack)
		attack(renderer,bulletList,lastShotTime,rectPlayer);
}
