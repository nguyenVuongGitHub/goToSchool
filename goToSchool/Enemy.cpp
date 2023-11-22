#include "Enemy.h"

Enemy::Enemy()
{
	type = 0;
	radius = 0;
	lastShotTime = 0;
	distanceAI = 0;
	countAI = 0;
	damage = 0;
	activeBoss = 0;
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
	else if (type == 4)
	{
		path = "img/boss.png";
		f_rect = { 64,64,500,500};
		hp = 300;
		speed = 4;
		radius = 90;
		damage = 15;
	}
	Character::init(renderer, path);
	flip = SDL_FLIP_NONE;
	distanceAI = 50;
	countAI = 0;
	angle = rand() % 360;
	active = 1;
	this->type = type;
	activeBoss = MOVE;
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
	if (type == 4)
	{
		if (hp <= 0)
		{
			activeBoss = DIE;
		}
		else if (isAttack)
		{
			activeBoss = ATTACK;
		}
		else {
			activeBoss = MOVE;
		}
		setTargetToPlayer(player);
		move(player);
	}
	else
	{
		// nếu nhìn thấy người chơi
		if (seePlayer(player.f_rect.x, player.f_rect.y))
		{
			// cài đặt hướng di chuyển vào người chơi
			setTargetToPlayer(player);
			move(player);
		}
		else { // ngược lại

			// cài đặt hướng di chuyển tự do cho quái vật
			setAI();

			// distanceAT là khoảng cách di chuyển khi đang trong trạng thái AI
			// nếu khoảng cách này lớn hơn 0 thì tiếp tục di chuyển
			// ngược lại sẽ được tính góc di chuyển khác trong hàm setAI()
			if (distanceAI > 0)
			{
				move(player);
				distanceAI--;
			}

		}
	}

	// khả năng tấn công của quái vật tùy theo loại quái vật có khả năng tấn công ( tấn công từ xa )
	if (type == 1 || type == 3)
	{
		attack(renderer, player, bulletEnemyList);
	}
	else if (type == 4)
		attack2(renderer, player, bulletEnemyList);
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
	if (active && type == 4)
	{
		if (distanceToPlayer(player.f_rect.x, player.f_rect.y) >= 1000)
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

void Enemy::spawnBoss1()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(354, 784);
	std::uniform_real_distribution<float> disY(946, 1521);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}
void Enemy::spawnBoss2()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(1014, 1529);
	std::uniform_real_distribution<float> disY(184, 534);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}
void Enemy::spawnBoss3()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(1061, 1826);
	std::uniform_real_distribution<float> disY(2094, 2304);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}

void Enemy::spawnBoss4()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> disX(2017, 2242);
	std::uniform_real_distribution<float> disY(895, 1860);

	float x = disX(gen);
	float y = disY(gen);

	f_rect.x = x;
	f_rect.y = y;
}


void Enemy::setTargetToPlayer(Player &player)
{
	// tính toán góc cần di chuyển đến giữa người chơi và quái vật
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
	// countAI: biến đếm thời gian nghỉ của quái vật
	// distanceAI : biến đếm khoảng cách di chuyển của quái vật


	// ban đầu distanceAI lớn hơn 0 ==> countAI vẫn bằng 0 nên sẽ trực tiếp bỏ qua dòng if số 321

	// kiểm tra ban đầu nếu countAI > một số random trong khoảng [0 - 50] 
	// thì sẽ bắt đầu thay đổi góc di chuyển và cài đặt lại các thông số mặc định ban đầu
	if (countAI >= (rand() % 50))
	{
		angle = rand() % 360;
		countAI = 0;
		distanceAI = 50;
	}

	// nếu discanceAI <= 0 tức là quái vật đã đi hết quảng đường cần thiết thì nó sẽ bắt đầu đếm thời gian nghỉ của AI
	if (distanceAI <= 0)
	{
		countAI++;
	}
	else {
		// nếu như chưa đi hết quảng đường cần thiết ( lúc này countAI vẫn bằng 0 ) thì sẽ không làm gì hết và kết thúc hàm
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
		bd.init(renderer, "img//magazine.png");
		bd.f_rect.x = f_rect.x + f_rect.w / 2;
		bd.f_rect.y = f_rect.y + f_rect.h / 2; // lấy vị trí là trung tâm của quái để phát ra
		bd.setType(AK);
		bulletsDropped.push_back(bd);
	}
	if (x == 11)
	{
		BulletDropped bd;
		bd.init(renderer, "img//magazine2.png");
		bd.f_rect.x = f_rect.x + f_rect.w / 2;
		bd.f_rect.y = f_rect.y + f_rect.h / 2; // lấy vị trí là trung tâm của quái để phát ra
		bd.setType(MP5);
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
		b.setType(1);
		b.init(renderer, player,"img/bulletThreat.png",f_rect.x,f_rect.y,type);
		b.setDamage(damage);
		bulletEnemyList.push_back(b);
		lastShotTime = curentTime;
	}
}

void Enemy::attack2(SDL_Renderer* renderer, Player& player, vector<BulletEnemy>& bulletEnemyList)
{
	Uint32 curentTime = SDL_GetTicks();
	Uint32 timeShot = curentTime - lastShotTime;
	if (timeShot >= 2000 && distanceToPlayer(player.f_rect.x, player.f_rect.y) <= 1000)
	{
		bossShoot();
		isAttack = true;
		BulletEnemy b;
		b.setType(0);
		b.setDamage(damage);
		b.setFrameLaze(0);
		b.init(renderer, player, "img/laze.png",f_rect.x, f_rect.y,type);
		bulletEnemyList.push_back(b);
		lastShotTime = curentTime;
	}
	else isAttack = false;
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

void Enemy::renderBoss(SDL_Renderer* renderer, float scrollX, float scrollY, FlatVector frameBoss)
{
	srcRect.x = (int)frameBoss.x * 100;
	srcRect.y = (int)frameBoss.y * 100;
	srcRect.w = 100;
	srcRect.h = 100;
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, 0, NULL, flip);
}

void Enemy::freeRender(SDL_Renderer* renderer, vector<coin>& coins,vector<BulletDropped> &bulletsDropped, vector<Enemy>& enemyList, int i, FlatVector frameBoss)
{
	if (!enemyList[i].active)
	{
		if (type == 4)
		{
			if (frameBoss.x > 12)
			{
				backgroundMusic();
				itemDroped(renderer, coins,bulletsDropped);
				enemyList.erase(enemyList.begin() + i);
				
			}
		}
		else {
			itemDroped(renderer, coins, bulletsDropped);
			enemyList.erase(enemyList.begin() + i);
		}
	}
}
