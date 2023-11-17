#include "Enemy.h"

Enemy::Enemy()
{
	type = 0;
	radius = 0;
	lastShotTime = 0;
}

Enemy::~Enemy()
{
	//Character::~Character();
	/*SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);*/
}

void Enemy::init(SDL_Renderer* renderer, short type)
{
	string path;
	if (type == 0)
	{
		path = "img/slime.png";
		f_rect = {64,64,32,32 };
		hp = 30;
		speed = 2;
		active = 1;
		radius = 15;
		damage = 2;
		this->type = type;
	}
	else if (type == 1)
	{
		path = "img/ske.png";
		f_rect = { 64,64,32,32 };
		hp = 30;
		speed = 3;
		active = 1;
		radius = 15;
		damage = 5;
		this->type = type;
	}
	Character::init(renderer, path);

	// 1080 and 1920 is width and height of window
	//spawn();

	//center = { f_rect.x + f_rect.w / 2, f_rect.y + f_rect.h / 2 };
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
	
	setTargetToPlayer(player);
	move(player);
	attack(renderer,player,bulletEnemyList);
}

float Enemy::distanceToPlayer(float xPlayer, float yPlayer)
{
	return sqrt(pow(f_rect.x - xPlayer, 2) + pow(f_rect.y - yPlayer, 2));
}

void Enemy::move(Player& player)
{
	if (active && type == 0)
	{
		f_rect.x += cos(angle) * speed;
		f_rect.y += sin(angle) * speed;
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
		vertices[0] = { f_rect.x, f_rect.y };
		vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
		vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
		vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	}
}

void Enemy::spawnAtLake()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(1164,1559);
	std::uniform_real_distribution<float> disY(1230,1658);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAtGround()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0, 1025);
	std::uniform_real_distribution<float> disY(0, 5);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAtGround2()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(0, 5);
	std::uniform_real_distribution<float> disY(824, 1544);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAtGround3()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(1950, 1952);
	std::uniform_real_distribution<float> disY(682, 1977);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnAtGround4()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(595, 1952);
	std::uniform_real_distribution<float> disY(1983, 1984);

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
	if (timeShot >= 1500 && distanceToPlayer(player.f_rect.x, player.f_rect.y) <= 400 && type == 1)
	{
		BulletEnemy b;
		b.init(renderer,player);
		b.f_rect.x = f_rect.x;
		b.f_rect.y = f_rect.y;
		b.setDamage(damage);
		bulletEnemyList.push_back(b);
		lastShotTime = curentTime;
	}
}

void Enemy::render1(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame)
{
	srcRect = { curFrame * 32, 0, 32, 32 };
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, angle, NULL, SDL_FLIP_NONE);
}

void Enemy::render0(SDL_Renderer* renderer, float scrollX, float scrollY, int curFrame)
{
	srcRect = { curFrame * 32, 0, 32, 32 };
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, angle, NULL, SDL_FLIP_NONE);
}

void Enemy::freeRender(SDL_Renderer* renderer, vector<coin>& coins,vector<BulletDropped> &bulletsDropped, vector<Enemy>& enemyList, int i)
{
	if (!enemyList[i].active)
	{
		itemDroped(renderer, coins,bulletsDropped);
		enemyList.erase(enemyList.begin() + i);
	}
}
