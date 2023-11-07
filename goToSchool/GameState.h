#pragma once
#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "weapon.h"
#include "bullet.h"
#include "Gun.h"
#include "Melle.h"
#include "EveryObject.h"
#include "Text.h"
#include "map.h"
#include "coin.h"
#include "BulletDropped.h"
#include "Collision.h"
#include <thread>

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

	/**
	* các thông số của window
	*/
	SDL_Window* window;
	SDL_Renderer* renderer;
	int heightWindow, widthWindow;
	int mouseX;
	int mouseY;
	bool isGameRunning;
	bool isMenuRunning;

	/**
	* numberframe
	*/
	float frameCoin;
	/**
	* Thông tin người chơi và vũ khí
	* 
	*/
	Player player;
	short numberWeaponHad;
	short curWeapon;
	WeaponList weaponList[9];
	vector<Bullet> bulletList;
	Uint32 lastShotTime;

	long long money;
	long long experience;
	int lever;

	vector<coin> coins;
	vector<BulletDropped> bulletsDropped;
	/**
	* xử lý của game loop
	*/
	bool hadInit;
	void initGame();
	void runGameLoop();
	void processInputGameLoop(SDL_Event &e);
	void updateGameLoop();
	void renderGameLoop();
	void cleanRenderGameLoop();
	void collisionGameLoop();


	/*chèn map*/
	Map m;
	/* xử lý của menu
	* 
	*/

	// danh sách các biến trong menu
	EveryObject background;
	Text t_title;
	Text t_play;
	Text t_shop;
	Text t_exit;

	void initMenu();
	void processInputMenu(SDL_Event& e);
	void updateMenu();
	void renderMenu();
	void cleanRenderMenu();
	void collisionMenu();


	/**
	* Xử lý va chạm sử dụng định lý SAT và AABB
	*/


public:
	GameState();
	void initData();
	//bool playerCollisionDetect(Enemy &p, Enemy &obj);
	//bool getHoldMouse();
	void menuMain();
	void freeAll();
	
	//void collesion();
	//bool checkCollesion(SDL_FRect &r1, SDL_FRect &r2);
	

	friend void collisionWall(GameState* gameState);
};

void collisionWall(GameState *gameState)
{
	while (gameState->isGameRunning)
	{
		//for (int i = 0; i < gameState->m.getWall().size(); i++)
		//{
		//	PolygonCollisionDetectOneSatic(gameState->m.getWall()[i].vertices, gameState->player.vertices, gameState->player.f_rect);
		//	for (int j = 0; j < gameState->m.enemyList.size(); j++)
		//	{
		//		CirclePolygonCollisionDetectPolygonStatic(gameState->m.getWall()[i].vertices, gameState->m.enemyList[j].center(), gameState->m.enemyList[j].getRadius(), gameState->m.enemyList[j].f_rect);
		//	}
		//}
		gameState->collisionGameLoop();
	}
}

