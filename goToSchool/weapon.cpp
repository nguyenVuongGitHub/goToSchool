#include "weapon.h"

Weapon::Weapon()
{
	type = 0;
	numberBullets = 0;
	distance = 0;
	damage = 0;
	speed = 0;
	totalBullets = 0;
	angle = 0;
}

long long Weapon::getTotalBullet()
{
	return totalBullets;
}

void Weapon::setTotalBullet(int x)
{
	totalBullets = x;
}
bool Weapon::getIsAttack()
{
	return isAttack;
}
void Weapon::setIsAttack(bool x)
{
	isAttack = x;
}
void Weapon::shoot(SDL_Renderer* renderer, vector<Bullet>& bulletList,Player &player, Uint32& lastShotTime)
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
		newBullet.setRect({player.getRect().x + player.getRect().w/2,player.getRect().y + player.getRect().h / 2,15,15});
		newBullet.setDxDy(mouseX - f_rect.x - 30, mouseY - f_rect.y - 30);
		newBullet.setAngle(atan2(newBullet.getDy(), newBullet.getDx()));
		newBullet.setSpeed((int)speed);
		newBullet.setDamage(damage);
		newBullet.setDistance(distance);
		newBullet.setActive(true);
		
		newBullet.init(renderer, type);
		bulletList.push_back(newBullet);
		
		lastShotTime = curentTime;
	}
}
void Weapon::init(SDL_Renderer* renderer, string pathImg,short type)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	f_rect = { 0,0,64,64 };
	this->type = type;

	if (type == AK_47)
	{
		numberBullets = NUMBER_BULLET_AK;
		distance = DISTANCE_AK;
		damage = 10;
		speed = SPEED_AK;
		totalBullets = 100;
	}
	if (type == USP)
	{
		numberBullets = NUMBER_BULLET_USP;
		distance = DISTANCE_USP;
		damage = 3;
		speed = SPEED_USP;
		totalBullets = 99999999;
	}
	if (type == MP5)
	{
		numberBullets = NUMBER_BULLET_MP5;
		distance = DISTANCE_MP5;
		damage = 7;
		speed = SPEED_MP5;
		totalBullets = 100;
	}

}

void Weapon::render(SDL_Renderer* renderer, Player &p)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
	
	if (curXMouse < p.getRect().x)
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_VERTICAL);
	else 
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_NONE);
}

void Weapon::update(SDL_Renderer* renderer, vector<Bullet>& bulletList, Player& p, Uint32& lastShotTime)
{
	f_rect = p.getRect();
	
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);


	float deltaX = curXMouse - (p.getRect().x + p.getRect().w / 2);
	float deltaY = curYMouse - (p.getRect().y + p.getRect().h / 2);
	// tính góc giữa người chơi và chuột
	angle = atan2(deltaY, deltaX) * 180 / M_PI;

	if (isAttack)
		shoot(renderer, bulletList,p,lastShotTime);

}

//void Weapon::init()
//{
//
//	/*if (type == AK_47)
//	{
//		name = "AK 47";
//		numberBullets = NUMBER_BULLET_AK;
//		distance = DISTANCE_AK;
//		damage = 10;
//		speed = SPEED_AK;
//		totalBullets = 100;
//	}
//	if (type == USP)
//	{
//		name = "USP";
//		numberBullets = NUMBER_BULLET_USP;
//		distance = DISTANCE_USP;
//		damage = 3;
//		speed = SPEED_USP;
//		totalBullets = 99999999;
//	}
//	if (type == MP5)
//	{
//		name = "MP5";
//		numberBullets = NUMBER_BULLET_MP5;
//		distance = DISTANCE_MP5;
//		damage = 7;
//		speed = SPEED_MP5;
//		totalBullets = 100;
//	}*/
//}

//void Weapon::update(SDL_Renderer* renderer, vector<Bullet>& ListBullet, float playerX, float playerY)
//{
//	//if (holdMouse)
//	//{
//	//	// Lấy thời gian hiện tại tính bằng mili giây
//	//	Uint32 current_time = SDL_GetTicks();
//
//	//	// Tính thời gian đã trôi qua kể từ lần bắn trước đó
//	//	Uint32 time_since_last_shot = current_time - last_shot_time;
//
//	//	// Kiểm tra nếu đã đủ thời gian trôi qua từ lần bắn trước đó (200 mili giây)
//	//	if (time_since_last_shot >= 200) {
//	//		// Giảm số lượng đạn còn lại của vũ khí hiện tại
//	//		setTotalBullet(getTotalBullet() - 1);
//
//	//		// Bắn vũ khí bằng cách gọi hàm shoot với các tham số cần thiết
//	//		shoot(renderer, ListBullet, playerX, playerY);
//
//	//		// Cập nhật thời gian bắn cuối cùng thành thời gian hiện tại
//	//		last_shot_time = current_time;
//	//	}
//	//}
//}

//void Weapon::shoot(SDL_Renderer* renderer,vector<Bullet> &listBullet,float playerX, float playerY)
//{
//	
//	if (totalBullets > 0 && listBullet.size() <= numberBullets)
//	{
//		int mouseX, mouseY;
//		SDL_GetMouseState(&mouseX, &mouseY);
//		//khởi tạo viên đạn mới
//		Bullet newBullet;
//
//
//		// set vị trí đạn bắn ra từ đâu
//		newBullet.r = {playerX + 30, playerY + 30, 20, 20};
//		newBullet.dx = mouseX - playerX - 30;
//		newBullet.dy = mouseY - playerY - 30;
//		newBullet.angle = atan2(newBullet.dy, newBullet.dx);
//		newBullet.speed = speed;
//		newBullet.distance = distance;
//
//		string pathBullet;
//		// tùy theo loại súng mà sẽ lấy đạn của loại đó
//		if (type == AK_47)
//			pathBullet = "img/T_762mm.png";
//		else if (type == USP)
//			pathBullet = "img/T_556mm.png";
//		else if(type == MP5)
//			pathBullet = "img/T_900mm.png";
//
//		newBullet.init(renderer, pathBullet.c_str(), type);
//		listBullet.push_back(newBullet);
//	}
//}
