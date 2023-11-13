#include "Gun.h"
Gun::Gun()
{
	type = 0;
	numberBullets = 0;
	totalBullets = 0;
	distance = 0;
}
void Gun::attack(SDL_Renderer* renderer, vector<Bullet>& bulletList, Uint32 &lastShotTime, const SDL_FRect& rectPlayer, float scrollX, float scrollY)
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
		newBullet.f_rect = { rectPlayer.x + rectPlayer.w / 2,rectPlayer.y + rectPlayer.h / 2,15,15 };
		newBullet.setDxDy(mouseX - f_rect.x - 30 + scrollX, mouseY - f_rect.y - 30 + scrollY);
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
	f_rect = { 0,0,64,24 };

	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h});
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h});
}

void Gun::render(SDL_Renderer* renderer, const SDL_FRect &rectPlayer ,const float& scrollX)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
	point = { 0,0 };
	if (curXMouse + scrollX < rectPlayer.x)
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, &point, SDL_FLIP_VERTICAL);
	else 
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, &point, SDL_FLIP_NONE);
}

void Gun::update(SDL_Renderer* renderer, vector<Bullet>& bulletList, Uint32& lastShotTime,const SDL_FRect& rectPlayer, const FlatVector& centerPlayer, float scrollX, float scrollY)
{
	f_rect = rectPlayer;
		
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
	
	//Updating rect as default
	f_rect = { centerPlayer.x,centerPlayer.y,64,24 };
	//Updating vertices
	vertices[0] = { f_rect.x, f_rect.y };
	vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
	vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h};
	vertices[3] = { f_rect.x, f_rect.y + f_rect.h};
	float deltaX = curXMouse - centerPlayer.x + scrollX;
	float deltaY = curYMouse - centerPlayer.y + scrollY;
	// tính góc giữa người chơi và chuột, and also convert radians to degrees
	angle = atan2(deltaY, deltaX) * 180 / M_PI;
	//Tranforming position from rotation
	vertices[0] = vertices[0].ClockwiseTransform(centerPlayer, angle);
	vertices[1] = vertices[1].ClockwiseTransform(centerPlayer, angle);
	vertices[2] = vertices[2].ClockwiseTransform(centerPlayer, angle);
	vertices[3] = vertices[3].ClockwiseTransform(centerPlayer, angle);
	
	if (isAttack)
		attack(renderer,bulletList,lastShotTime,rectPlayer, scrollX, scrollY);
}
