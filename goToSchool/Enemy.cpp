#include "Enemy.h"

Enemy::Enemy()
{
	type = 0;
	radius = 0;
	distance = 0;
	countState = 0;
}

Enemy::~Enemy()
{
	//Character::~Character();
	/*SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);*/
}

void Enemy::init(SDL_Renderer* renderer,string path)
{
	Character::init(renderer, path);
	f_rect = {  10, 10,30,30 };
	hp = 30;
	speed = 2;
	active = 1;
	radius = 15;
	distance = 2;
	countState = 0;
	angle = 10;
	// 1080 and 1920 is width and height of window
	spawn(1080,1920);

	//center = { f_rect.x + f_rect.w / 2, f_rect.y + f_rect.h / 2 };
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
}
void Enemy::update(Player& player)
{
	
	//setAImove(player);
	//setTargetToPlayer(player);
	//move();
}

void Enemy::move()
{
	if (active)
	{
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;

		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
}

void Enemy::spawn(int widthWindow, int heightWindow )
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(300, 700);
	std::uniform_real_distribution<float> disY(300, 700);

	float x = disX(gen);
	float y = disY(gen);

	f_rect = { x, y, 30, 30 };
}

void Enemy::setTargetToPlayer(Player &player)
{
	dx = player.f_rect.x - f_rect.x;
	dy = player.f_rect.y - f_rect.y;
	angle = atan2(dy,dx);
	
}

void Enemy::setAImove(Player &player)
{
	if (sqrt(pow(player.getRect().x, 2) - pow(f_rect.x, 2)) >= 500)
	{
		setTargetToPlayer(player);
	}
	if (active && distance > 0)
	{
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
		distance--;
	}
	if (distance <= 0)
	{
		countState++;
	}
	if (countState >= 100)
	{
		angle = rand() % 360;
		distance = 2;
		countState = 0;
	}
}

void Enemy::itemDroped(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped)
{
	/**
	* why 17 and 11 ??
	* because this is my birthday
	*/
	int x = dropChance();
	//cout << "X : " << x << endl;
	//if (x == 17 || x == 11)
	//{
		coin coin;
		for (int i = 0; i <= 5; i++)
		{
			coin.init(renderer, "img//coin.png");
			coin.f_rect = { f_rect.x+f_rect.w/2 , f_rect.y + f_rect.h/2 ,64, 64}; // lấy vị trí là trung tâm của quái để phát ra
			coin.setAngle(i*17 + (f_rect.y + f_rect.x)*11 + 2004); // góc đặt đại
			//qtree->insert(&coin);
			coins.push_back(coin);
		}
	//}
	if (x <= 10)
	{
		BulletDropped bd;
		bd.init(renderer, "img//T_556mm.png");
		bd.f_rect = { f_rect.x + f_rect.w / 2 , f_rect.y + f_rect.h / 2 ,15 , 15 }; // lấy vị trí là trung tâm của quái để phát ra
		bd.setType(AK);
		//qtree->insert(&bd);
		bulletsDropped.push_back(bd);
	}
		
}

int Enemy::dropChance()
{
	return rand() % 31;
}

void Enemy::render(SDL_Renderer* renderer)
{
	SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, NULL, SDL_FLIP_NONE);
}

void Enemy::freeRender(SDL_Renderer* renderer, vector<coin>& coins,vector<BulletDropped> &bulletsDropped, vector<Enemy>& enemyList, int i)
{
	if (!enemyList[i].active)
	{
		itemDroped(renderer, coins,bulletsDropped);
		enemyList.erase(enemyList.begin() + i);
	}
}
