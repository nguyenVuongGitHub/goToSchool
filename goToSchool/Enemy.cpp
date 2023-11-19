#include "Enemy.h"

Enemy::Enemy()
{
	type = 0;
	radius = 0;
	lastShotTime = 0;
	distanceAI = 0;
	countAI = 0;
	damage = 0;
}

Enemy::~Enemy()
{
}

void Enemy::init(SDL_Renderer* renderer, short type)
{
	string path;
	if (type == 0)
	{
		path = "img/slime.png";
		f_rect = {64,64,32,32 };
		hp = 30;
		speed = 3;
		radius = 15;
		damage = 2;
	}
	else if (type == 1)
	{
		path = "img/ske.png";
		f_rect = { 64,64,32,32 };
		hp = 30;
		speed = 3;
		radius = 15;
		damage = 4;
	}
	else if (type == 2)
	{
		path = "img/slime.png";
		f_rect = { 64,64,96,96};
		hp = 50;
		speed = 2;
		radius = 45;
		damage = 7;
	}
	else if (type == 3)
	{
		path = "img/ske.png";
		f_rect = { 64,64,96,96 };
		hp = 90;
		speed = 3;
		radius = 45;
		damage = 12;
	}
	Character::init(renderer, path);
	flip = SDL_FLIP_NONE;
	distanceAI = 50;
	countAI = 0;
	angle = rand() % 360;
	active = 1;
	this->type = type;

	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });
}
void Enemy::setPos(float x, float y)
{
	f_rect.x = x;
	f_rect.y = y;
}
void Enemy::update(SDL_Renderer* renderer, Player& player, vector<BulletEnemy> &bulletEnemyList)
{
	if (seePlayer(player.f_rect.x,player.f_rect.y))
	{
		setTargetToPlayer(player);
		move(player);
	}
	else {
		setAI();
		if (distanceAI > 0)
		{
			move(player);
			distanceAI--;
		}

	}
	if(type == 1 || type == 3)
		attack(renderer,player,bulletEnemyList);
}

float Enemy::distanceToPlayer(float xPlayer, float yPlayer)
{
	return sqrt(pow(f_rect.x - xPlayer, 2) + pow(f_rect.y - yPlayer, 2));
}

void Enemy::move(Player& player)
{
	if (active && type == 0 )
	{
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
		if (f_rect.x > player.f_rect.x + player.f_rect.w / 2)
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
	if (active && type == 1)
	{
		if (distanceToPlayer(player.f_rect.x,player.f_rect.y) >= 400)
		{
			f_rect.x += cos(angle) * speed;
			f_rect.y += sin(angle) * speed;
		}
		if (f_rect.x > player.f_rect.x + player.f_rect.w / 2)
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}

	if (active &&  type == 2)
	{
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
		if (f_rect.x > player.f_rect.x + player.f_rect.w / 2)
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
	if (active && type == 3)
	{
		if (distanceToPlayer(player.f_rect.x, player.f_rect.y) >= 400)
		{
			f_rect.x += cos(angle) * speed;
			f_rect.y += sin(angle) * speed;
		}
		if (f_rect.x > player.f_rect.x + player.f_rect.w / 2)
		{
			flip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			flip = SDL_FLIP_NONE;
		}
		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
}

void Enemy::spawnAt0()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(640,1888);
	std::uniform_real_distribution<float> disY(5,10);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAt1()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(2333, 2510);
	std::uniform_real_distribution<float> disY(645, 2000);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAt2()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(690, 2040);
	std::uniform_real_distribution<float> disY(2424, 2426);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAt3()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(5, 10);
	std::uniform_real_distribution<float> disY(640, 1856);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAt4()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(800, 1400);
	std::uniform_real_distribution<float> disY(700, 1400);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAt5()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(1919,2314);
	std::uniform_real_distribution<float> disY(720, 1185);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}
void Enemy::spawnAt6()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(681, 2108);
	std::uniform_real_distribution<float> disY(1914, 2369);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAt7()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(281, 906);
	std::uniform_real_distribution<float> disY(1140, 1725);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::setTargetToPlayer(Player &player)
{
	dx = player.f_rect.x - f_rect.x;
	dy = player.f_rect.y - f_rect.y;
	angle = atan2(dy,dx);
}

bool Enemy::seePlayer(float x,float y)
{
	return distanceToPlayer(x, y) <= 650;
}

void Enemy::setAI()
{
	if (countAI >= (rand() % 50))
	{
		angle = rand() % 360;
		countAI = 0;
		distanceAI = 50;
	}

	if (distanceAI <= 0)
	{
		countAI++;
	}
	else {
		return;
	}
	
}

void Enemy::itemDroped(SDL_Renderer* renderer, vector<coin>& coins, vector<BulletDropped>& bulletsDropped)
{

	int x = dropChance();
	coin coin;
	for (int i = 0; i <= 5; i++)
	{
		coin.init(renderer, "img//coin.png");
		coin.f_rect.x = f_rect.x + f_rect.w / 2 ;
		coin.f_rect.y = f_rect.y + f_rect.h / 2 ; // lấy vị trí là trung tâm của quái để phát ra
		coin.setAngle(i*17 + (f_rect.y + f_rect.x)*11 + 2004); // góc đặt đại
		coins.push_back(coin);
	}

	if (x == 10)
	{
		BulletDropped bd;
		bd.init(renderer, "img//T_556mm.png");
		bd.f_rect = { f_rect.x + f_rect.w / 2 , f_rect.y + f_rect.h / 2 ,15 , 15 }; // lấy vị trí là trung tâm của quái để phát ra
		bd.setType(AK);
		bulletsDropped.push_back(bd);
	}
		
}

int Enemy::dropChance()
{
	return rand() % 31;
}

void Enemy::attack(SDL_Renderer* renderer, Player& player, vector<BulletEnemy> &bulletEnemyList)
{
	Uint32 curentTime = SDL_GetTicks();
	Uint32 timeShot = curentTime - lastShotTime;
	if (timeShot >= 1500 && distanceToPlayer(player.f_rect.x, player.f_rect.y) <= 400)
	{
		BulletEnemy b;
		b.init(renderer,player);
		b.f_rect.x = f_rect.x + f_rect.w / 2;
		b.f_rect.y = f_rect.y + f_rect.h / 2;
		if (type == 3)
		{
			b.f_rect.w = 45;
			b.f_rect.h = 45;
		}
		b.setDamage(damage);
		bulletEnemyList.push_back(b);
		lastShotTime = curentTime;
	}
}

void Enemy::render1(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame)
{
	srcRect = { curFrame * 32, 0, 32, 32 };
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, 0, NULL, flip);
}

void Enemy::render0(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame)
{
	srcRect = { curFrame * 32, 0, 32, 32 };
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, 0, NULL, flip);
}

void Enemy::freeRender(SDL_Renderer* renderer, vector<coin>& coins,vector<BulletDropped> &bulletsDropped, vector<Enemy>& enemyList, int i)
{
	if (!enemyList[i].active)
	{
		itemDroped(renderer, coins,bulletsDropped);
		enemyList.erase(enemyList.begin() + i);
	}
}
