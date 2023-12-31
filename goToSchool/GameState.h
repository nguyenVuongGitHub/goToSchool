﻿#pragma once
#include <algorithm>
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
#include "audio.h"
using namespace std;

struct InfoPlayer
{
	string name;
	int numberEnemiesDestroyed;
	int totalTime;
};

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
	EveryObject centerMass;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int heightWindow, widthWindow;
	int mouseX;
	int mouseY;
	bool isGameRunning;
	bool isMenuRunning;
	bool isShopRunning;
	int countLoop;
	float scrollX;
	float scrollY;
	bool isPauseGame;
	int countShop; // đếm số lần shop được chạy ( 1 - hết 60s, 2 - hết quái)
	Uint32 startTime;
	Uint32 countdownTime;
	Uint32 countdownShopTime;
	Uint32 remainingTime;
	Uint32 currentTime;
	Uint32 elapsedTime;
	Uint32 curTime;
	Text countdownTimeText;
	Text numberEnemyText;
	void resetTime();
	void folowMouse();
	void renderMouse();
	/*
		infomation player
	*/
	long long money;
	Text moneyText;
	SDL_FRect hp;
	SDL_Rect hp_frame;
	SDL_Texture* t;
	coin coinImg;
	BulletDropped bd1; // usp
	BulletDropped bd2; // ak
	BulletDropped bd3; // mp5
	Text numberbulletTextUSP;
	Text numberbulletTextAK;
	Text numberbulletTextMP5;
	void initInfomation();
	void updateInfomation();
	void renderInfomation();
	
	

	/**
	* numberframe
	*/
	FlatVector frameBoss;
	float frameCoin;
	float frameMagazine;
	float frameSlime;
	float frameSke;
	float frameLaze;
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


	bool isType;
	void enterName();

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

	/**
	*	Xử lý pause game
	*/
	bool isReturnMenu;
	bool isContinueGame;
	EveryObject backgroundPauseGame;
	bool isPauseGameRunning;
	Text continuePause;
	Text returnPause;
	Text titlePause;
	Uint32 startPause;
	Uint32 pauseDuration;
	void initPauseGame();
	void processInputPauseGame(SDL_Event &e);
	void renderPauseGame();
	void updatePauseGame();
	void collisionPauseGame();
	void runPauseGame();
	

	/*chèn map*/
	Map m;
	/* xử lý của menu
	* 
	*/
	// end game
	bool isEndGameRunning;
	EveryObject backgroundEndGame;
	Text titleEndGame;
	Text numberEnemyDestroyed;
	int numberEnemyDes;
	Uint32 totalTime;
	Text totalTimeText;
	Text playAgainText;
	Text returnMenu;
	void runEndGame();
	void initEndGame();
	void processInputEndGame(SDL_Event& e);
	void updateEndGame();
	void renderEndGame();
	void collisionEndGame();

	// danh sách các biến trong menu
	EveryObject background;
	Text t_title;
	Text t_play;
	Text t_ranking;
	Text t_exit;


	void initMenu();
	void processInputMenu(SDL_Event& e);
	void updateMenu();
	void renderMenu();
	void collisionMenu();


	EveryObject backgroundShop;
	EveryObject shopItem1;
	EveryObject shopItem2;
	EveryObject shopItem3;
	EveryObject shopItem4;
	Text skipShop;
	bool isOnShopItem1;
	bool isOnShopItem2;
	bool isOnShopItem3;
	bool isOnShopItem4;

	void initShop();
	void runShop();
	void processShop(SDL_Event& e);
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
	bool PolygonCollisionDetectTwoSatic(vector<FlatVector> vertices1, vector<FlatVector> vertices2);
	FlatVector FindArithmeticMean(vector<FlatVector> vertices);

	void playAgain();
	/*
	*Đọc xuất File
	*/

	void insertSort(vector<InfoPlayer>& data);
	void Write_File(int totalEnemiesDestroyed, int totalTimeInSeconds, string& playerName);
	vector<InfoPlayer> Read_File();

	void showRank();

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

