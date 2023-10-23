#pragma once
#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "weapon.h"
#include "bullet.h"
#include "Gun.h"
#include "Melle.h"
#include "EveryObject.h"
using namespace std;
enum typeWeapon
{
	GUN,MELLE
};
struct WeaponList
{
	typeWeapon type;
	Gun gun;
	Melle melle;
};

class GameState
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int heightWindow, widthWindow;
	int mouseX;
	int mouseY;
	bool isGameRunning;
	Uint32 lastShotTime;

	//EveryObject background;



	Player player;

	short numberWeaponHad;
	short curWeapon;
	//Weapon weaponList[9];
	//Gun weaponList[9];
	WeaponList weaponList[9];
	vector<Enemy> enemyList;
	vector<Bullet> bulletList;


	void init();
	void processInput(SDL_Event &e);
	void update();
	void render();
	void cleanRender();
	void collision();
	bool collisionEnemyWithEnemy(Enemy &p, Enemy& obj);
	bool collisionBulletWithEnemy(SDL_FRect &r1, SDL_FRect& r2);


	bool PolygonCollisionDetect(vector<FlatVector> vertices1, SDL_FRect& r1, vector<FlatVector> vertices2, SDL_FRect& r2);

	bool CircleCollisionDetect(FlatVector center1, float radius1, SDL_FRect& r1, FlatVector center2, float radius2, SDL_FRect& r2);

	bool CirclePolygonCollisionDetect(vector<FlatVector> vertices, SDL_FRect& r1, FlatVector centerCircle, float radius, SDL_FRect& r2);

	FlatVector FindArithmeticMean(vector<FlatVector> vertices);
	void freeAll();

public:
	GameState();
	//bool playerCollisionDetect(Enemy &p, Enemy &obj);
	//bool getHoldMouse();
	void run();
	
	//void collesion();
	//bool checkCollesion(SDL_FRect &r1, SDL_FRect &r2);
	
};

