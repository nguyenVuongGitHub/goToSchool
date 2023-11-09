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

	bool collisionEnemyWithEnemy(Enemy &p, Enemy& obj);
	bool collisionTwoRect(SDL_FRect &r1, SDL_FRect& r2);
	bool PolygonCollisionDetect(vector<FlatVector> vertices1, SDL_FRect& r1, vector<FlatVector> vertices2, SDL_FRect& r2);
	bool PolygonCollisionDetectOneSatic(vector<FlatVector> vertices1, vector<FlatVector> vertices2, SDL_FRect& r2);
	bool CircleCollisionDetect(FlatVector center1, float radius1, SDL_FRect& r1, FlatVector center2, float radius2, SDL_FRect& r2);
	bool CirclePolygonCollisionDetect(vector<FlatVector> vertices, SDL_FRect& r1, FlatVector centerCircle, float radius, SDL_FRect& r2);
	bool CirclePolygonCollisionDetectPolygonStatic(vector<FlatVector> vertices, FlatVector centerCircle, float radius, SDL_FRect& r2);
	FlatVector FindArithmeticMean(vector<FlatVector> vertices);

	float sweptAABB(const SDL_FRect& object, const FlatVector objectSpeed, const SDL_FRect& other, FlatVector& result);

	bool isColliding(const SDL_FRect& object, const SDL_FRect& other);

	bool RayVsRect(const FlatVector& ray_origin, const FlatVector& ray_dir, const SDL_FRect* target, FlatVector& contact_normal, float& t_hit_near);
	bool DynamicRectVsRect(const SDL_FRect* r_dynamic, const FlatVector& speedDynamic, const SDL_FRect r_static, FlatVector& contact_normal, float& contact_time);
	bool ResolveDynamicRectVsRect(SDL_FRect* r_dynamic, const float fTimeStep, SDL_FRect* r_static);

	SDL_FRect GetSweptBroadphaseBox(SDL_FRect b, FlatVector speed);

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

