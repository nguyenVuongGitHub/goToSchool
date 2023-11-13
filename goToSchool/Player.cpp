#include "Player.h"

Player::Player()
{
	memset(moveKey, 0, sizeof(moveKey));
	hp = 0;
}


Player::~Player()
{
	//Character::~Character();
	//SDL_DestroyTexture(texture);
	//SDL_FreeSurface(surface);
}
void Player::init(SDL_Renderer* renderer, string pathImg)
{
	isMove = false;
	Character::init(renderer, pathImg);
	framAni = { 0,0 };
	f_rect = { 1000,1000,32,64 };
	speed = 5;
	crossSpeed = (speed * sqrt(2)) / 2;
	hp = 100;
	active = true;
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });

}

//void Player::init(SDL_Renderer *renderer)
//{
//	// Các tài nguyên cần thiết
//	s = IMG_Load("img/tamGiac.png");
//	t = SDL_CreateTextureFromSurface(renderer, s);
//	/*weapon[0].type = USP;
//	weapon[1].type = AK_47;
//	weapon[2].type = MP5;*/
//
//	t = SDL_CreateTextureFromSurface(renderer, s);
//	r = { 250,440,60,60 };
//	speed = 5;
//	crossSpeed = (speed * sqrt(2)) / 2;
//	// Thông số cơ bản
//	angle = 0;
//	memset(moveKey, 0, sizeof(moveKey));
//	
//	//Các tọa độ
//	center = { (r.x + r.w) / 2, (r.y + r.h) / 2 };
//	vertices.push_back({ r.x, r.y });
//	vertices.push_back({ r.x + r.w, r.y });
//	vertices.push_back({ r.x + r.w, r.y + r.h });
//	vertices.push_back({ r.x, r.y + r.h });
//
//	transformVertices.push_back({ r.x, r.y });
//	transformVertices.push_back({ r.x + r.w, r.y });
//	transformVertices.push_back({ r.x + r.w, r.y + r.h });
//	transformVertices.push_back({ r.x, r.y + r.h });
//}
void Player::setMoveKey(int x)
{
	moveKey[x] = true;
	isMove = true;
}
void Player::desetMoveKey(int x)
{
	moveKey[x] = false;
	isMove = false;
}
void Player::update(Gun& weapon)
{
	attack(weapon);
	move();
}
void Player::update(Melle& weapon)
{
	attack(weapon);
	move();
}
void Player::move()
{

	//slow moving
	if (moveKey[SLOW])
	{
		speed = 2.1;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	else if (moveKey[FAST]) //fast moving
	{
		speed = 10;
		crossSpeed = (speed * sqrt(2)) / 2;
	}
	else {
		// default moving
		speed = 5;
		crossSpeed = (speed * sqrt(2)) / 2;
	}

	// base case move
	if (moveKey[UP] && moveKey[RIGHT])
	{
		f_rect.y -= crossSpeed;
		f_rect.x += crossSpeed;
	}
	else if (moveKey[UP] && moveKey[LEFT])
	{
		f_rect.y -= crossSpeed;
		f_rect.x -= crossSpeed;

	}
	else if (moveKey[DOWN] && moveKey[RIGHT])
	{
		f_rect.y += crossSpeed;
		f_rect.x += crossSpeed;
	}
	else if (moveKey[DOWN] && moveKey[LEFT])
	{
		f_rect.y += crossSpeed;
		f_rect.x -= crossSpeed;
	}
	else if (moveKey[UP])
	{
		f_rect.y -= speed;
	}
	else if (moveKey[DOWN])
	{
		f_rect.y += speed;
	}
	else if (moveKey[LEFT])
	{
		f_rect.x -= speed;
	}
	else if (moveKey[RIGHT])
	{
		f_rect.x += speed;
	}
	// Update center point
	//center = { (r.x + r.w) / 2, (r.y + r.h) / 2 };

	 //Update vertices
	vertices[0] = { f_rect.x, f_rect.y };
	vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
	vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
	vertices[3] = { f_rect.x, f_rect.y + f_rect.h };

	//for (int i = 0; i < vertices.size(); i++)
	//{
	//	cout << vertices[i].x << "\t" << vertices[i].y << endl;
	//}
	//cout << endl;
}

void Player::attack(Gun &weapon)
{
	// check isAttack at processInput (gameState.cpp)
	if (isAttack)
	{
		weapon.setIsAttack(true);
	}
	else {
		weapon.setIsAttack(false);
	}
}

void Player::attack(Melle& weapon)
{
	//if (isAttack)
	//{
	//	weapon.setIsAttack(true);
	//}
	//else if (!isAttack && ((int)weapon.getAngle() % 90 == 0)) {
	//	weapon.setIsAttack(false);
	//}
}

void Player::render(SDL_Renderer* renderer, float scrollX, float scrollY)
{
	srcRect.x = (int)framAni.x * 32;
	srcRect.y = (int)framAni.y * 64;
	srcRect.w = 32;
	srcRect.h = 64;
	int cursorX, cursorY;
	SDL_GetMouseState(&cursorX, &cursorY);
	cursorX += scrollX;
	cursorY += scrollY;
	if (cursorX < f_rect.x + f_rect.w / 2)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}
	SDL_FRect tmp = { f_rect.x - scrollX, f_rect.y - scrollY, f_rect.w, f_rect.h };
	SDL_RenderCopyExF(renderer, texture, &srcRect, &tmp, angle, NULL, flip);
	
}