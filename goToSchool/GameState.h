#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "Enemy.h"
#include "weapon.h"
#include "bullet.h"
using namespace std;
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
	Player player;

	short numberWeaponHad;
	short curWeapon;
	Weapon weaponList[9];
	
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

