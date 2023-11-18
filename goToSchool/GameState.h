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
	int countLoop;
	float scrollX;
	float scrollY;

	/*
		infomation player
	*/
	long long money;
	Text moneyText;
	SDL_FRect hp;
	SDL_Rect hp_frame;
	SDL_Texture* t;
	coin coinImg;
	Text numberbulletTextUSP;
	Text numberbulletTextAK;
	Text numberbulletTextMP5;
	void initInfomation();
	void updateInfomation();
	void renderInfomation();
	
	//Text 

	/**
	* numberframe
	*/
	float frameCoin;
	float frameSlime;
	float frameSke;
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
	vector<Enemy> enemyList;

	vector<coin> coins;
	vector<BulletDropped> bulletsDropped;
	vector<BulletEnemy> bulletEnemyList;
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

	EveryObject backgroundShop;

	void initShop();
	void processShop();
	void updateShop();
	void renderShop();
	void collisionShop();

	void FolowCam();

	int numberEnemyOnTurnGame[10];
	int turnGame;
	int countEnemy; // đếm số quái đã bị tiêu diệt để check numberEnemyOnTurnGame
	void updateTurnGame();
	/**
	* Xử lý va chạm sử dụng định lý SAT và AABB
	*/

	bool collisionEnemyWithEnemy(Enemy &p, Enemy& obj);
	bool collisionTwoRect(SDL_FRect &r1, SDL_FRect& r2);
	bool PolygonCollisionDetect(vector<FlatVector> vertices1, SDL_FRect& r1, vector<FlatVector> vertices2, SDL_FRect& r2);
	bool PolygonCollisionDetectOneSatic(vector<FlatVector> vertices1, vector<FlatVector> vertices2, SDL_FRect& r2);
	bool CircleCollisionDetect(FlatVector center1, float radius1, SDL_FRect& r1, FlatVector center2, float radius2, SDL_FRect& r2);
	bool CirclePolygonCollisionDetect(vector<FlatVector> vertices, SDL_FRect& r1, FlatVector centerCircle, float radius, SDL_FRect& r2);
	bool CirclePolygonCollisionDetectPolygonStatic(vector<FlatVector> vertices, FlatVector centerCircle, float radius, SDL_FRect& r2);
	FlatVector FindArithmeticMean(vector<FlatVector> vertices);

	void playAgain();
public:
	GameState();
	void initData();
	//bool playerCollisionDetect(Enemy &p, Enemy &obj);
	//bool getHoldMouse();
	void menuMain();
	void freeAll();
	
	//void collesion();
	//bool checkCollesion(SDL_FRect &r1, SDL_FRect &r2);
	
};

