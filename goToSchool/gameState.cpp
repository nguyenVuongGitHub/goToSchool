#include "GameState.h"

const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 2020;

GameState::GameState() :

	mouseX(0),
	mouseY(0),
	window(NULL),
	renderer(NULL),
	isGameRunning(0),
	widthWindow(0),
	heightWindow(0),
	numberWeaponHad(0),
	curWeapon(0),
	lastShotTime(0),
	isMenuRunning(0),
	money(0),
	frameCoin(0),
	frameSlime(0),
	hadInit(0), 
	countLoop(0),
	turnGame(0),
	frameSke(0),
	scrollX(0),
	scrollY(0),
	countEnemy(0)
{
	hp = { 0,0,0,0 };
	hp_frame = { 0,0,0,0 };
	for (int i = 0; i < 10; i++)
	{
		numberEnemyOnTurnGame[i] = 0;
	}
	t = NULL;
}

void GameState::initData()
{
	widthWindow = 1920;
	heightWindow = 1080;
	mouseX = 0;
	mouseY = 0;
	scrollX = 0;
	scrollY = 0;
	isGameRunning = 1;
	isMenuRunning = 1;
	window = SDL_CreateWindow("game test", 0, 0, widthWindow, heightWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();	
	initInfomation();
}

void GameState::menuMain()
{
	
	initMenu();
	
	SDL_Event e;
	while(isMenuRunning)
	{
		processInputMenu(e);

		updateMenu();

		collisionMenu();

		renderMenu();

		cleanRenderMenu();
	}
}

void GameState::initInfomation()
{
	SDL_Surface* s = IMG_Load("img/hp.png");
	t = SDL_CreateTextureFromSurface(renderer, s);
	money = 0;
	coinImg.init(renderer,"img/coin.png");
	coinImg.f_rect = { 0,100,60,60 };
	moneyText.init(renderer,to_string(money), 45, 60, 113, "font/Minecraft.ttf");
	hp = { 10,10,(float)player.getHP() / 100 * 180,32 };
	hp_frame = { 0,0,204,96 };

	numberbulletTextUSP.init(renderer, " X " + to_string(weaponList[1].gun.getTotalBullets()), 30, 60, 153, "font/Minecraft.ttf");
	numberbulletTextAK.init(renderer, " X " + to_string(weaponList[2].gun.getTotalBullets()), 30, 60, 183, "font/Minecraft.ttf");
	numberbulletTextMP5.init(renderer, " X " + to_string(weaponList[3].gun.getTotalBullets()), 30, 60, 213, "font/Minecraft.ttf");
	
}

void GameState::updateInfomation()
{
	
	hp.w = (float)player.getHP() / 100 * 180;
	
	moneyText.init(renderer, to_string(money), 45, 60, 113, "font/Minecraft.ttf");
	moneyText.setText(to_string(money));

	numberbulletTextUSP.init(renderer, " X " + to_string(weaponList[1].gun.getTotalBullets()), 30, 60, 153, "font/Minecraft.ttf");
	numberbulletTextAK.init(renderer, " X " + to_string(weaponList[2].gun.getTotalBullets()), 30, 60, 183, "font/Minecraft.ttf");
	numberbulletTextMP5.init(renderer, " X " + to_string(weaponList[3].gun.getTotalBullets()), 30, 60, 213, "font/Minecraft.ttf");
	numberbulletTextUSP.setText(" X " + to_string(weaponList[1].gun.getTotalBullets()));
	numberbulletTextAK.setText(" X " + to_string(weaponList[2].gun.getTotalBullets()));
	numberbulletTextMP5.setText(" X " + to_string(weaponList[3].gun.getTotalBullets()));
}

void GameState::renderInfomation()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRectF(renderer, &hp);
	SDL_RenderCopy(renderer, t, NULL, &hp_frame);
	coinImg.render(renderer, frameCoin, 0, 0);
	moneyText.render(renderer);
	numberbulletTextUSP.render(renderer);
	numberbulletTextAK.render(renderer);
	numberbulletTextMP5.render(renderer);
}


void GameState::initGame()
{
	if (!hadInit)
	{
		numberWeaponHad = 4;
		curWeapon = 0;
		Melle m1;

		Gun x1(USP, NUMBER_BULLET_USP, 999999999, DISTANCE_USP, DAMAGE_USP);
		Gun x2(AK, NUMBER_BULLET_AK, 200, DISTANCE_AK, DAMAGE_AK);
		Gun x3(MP5, NUMBER_BULLET_MP5, 100, DISTANCE_MP5, DAMAGE_MP5);

		m1.init(renderer, "img/knight.png");
		x1.init(renderer, "img/USP.png");
		x2.init(renderer, "img/AK.png");
		x3.init(renderer, "img/MP5.png");

		weaponList[0].type = MELLE;
		weaponList[1].type = GUN;
		weaponList[2].type = GUN;
		weaponList[3].type = GUN;

		weaponList[0].melle = m1;
		weaponList[1].gun = x1;
		weaponList[2].gun = x2;
		weaponList[3].gun = x3;

		player.init(renderer, "img/player.png");
		for (int i = 0; i < 10; i++)
		{
			numberEnemyOnTurnGame[i] = rand() % 30;
		}
		m.loadMap(renderer);
		hadInit = true;
	}
}
void GameState::runGameLoop()
{
	playAgain();
	initGame();

	SDL_Event e;
	while (isGameRunning)
	{
		processInputGameLoop(e);

		updateGameLoop();
		
		collisionGameLoop();
		
		renderGameLoop();
		
		cleanRenderGameLoop();
	}
}
void GameState::processInputGameLoop(SDL_Event &e)
{

	while (SDL_PollEvent(&e))
	{
		// thoát khi bấm nút phía góc phải màn hình "X"
		if (e.type == SDL_QUIT)
			isGameRunning = 0;

		// thoát khi bấm "esc"
		if (e.key.keysym.sym == SDLK_ESCAPE)
			isGameRunning = 0;

		if (e.type == SDL_KEYUP)
		{
			// nếu rồi thì kiểm tra nút đó là nút nào
			// sau đó sẽ đặt hướng di chuyển của người chơi

			if (e.key.keysym.sym == SDLK_a)
				player.desetMoveKey(LEFT);

			else if (e.key.keysym.sym == SDLK_d)
				player.desetMoveKey(RIGHT);

			else if (e.key.keysym.sym == SDLK_w)
				player.desetMoveKey(UP);

			else if (e.key.keysym.sym == SDLK_s)
				player.desetMoveKey(DOWN);

			else if (e.key.keysym.sym == SDLK_LSHIFT)
				player.desetMoveKey(SLOW);

			else if (e.key.keysym.sym == SDLK_SPACE)
				player.desetMoveKey(FAST);
		}
		// kiểm tra nút đã được bấm xuống chưa 
		if (e.type == SDL_KEYDOWN)
		{
			// nếu rồi thì kiểm tra nút đó là nút nào
			// sau đó sẽ đặt hướng di chuyển của người chơi

			if (e.key.keysym.sym == SDLK_a)
				player.setMoveKey(LEFT);
			
			else if (e.key.keysym.sym == SDLK_d)
				player.setMoveKey(RIGHT);

			else if (e.key.keysym.sym == SDLK_w)
				player.setMoveKey(UP);

			else if (e.key.keysym.sym == SDLK_s)
				player.setMoveKey(DOWN);

			else if (e.key.keysym.sym == SDLK_LSHIFT)
				player.setMoveKey(SLOW);

			else if (e.key.keysym.sym == SDLK_SPACE)
				player.setMoveKey(FAST);
		}
		// kiểm tra nút đã được thả ra chưa
		//bắt sự kiện giữ chuột và sẽ đặt người chơi vào trạng thái tấn công
		// SDL_BUTTON_LMASK là chuột trái
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
			player.setIsAttack(true);

		if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LMASK)
			player.setIsAttack(false);

		 //kiểm tra sự kiện lăn chuột
		if (!player.getIsAttack() && e.type == SDL_MOUSEWHEEL) {
			int scrollDirection = e.wheel.y;
			// nếu scrollDirection lớn hơn 0 thì là lăn chuột lên trên
			if (scrollDirection > 0) {
				curWeapon--;	
				if (curWeapon < 0)
					curWeapon = numberWeaponHad-1;
			}
			// nếu scrollDirection bế hơn 0 thì là lăn chuột xuống dưới

			else if (scrollDirection < 0) {
				curWeapon++;
				if (curWeapon > numberWeaponHad-1)
					curWeapon = 0;

			}
		}
	}
}

void GameState::updateGameLoop()
{
	// ============= update count loop ============= 
	countLoop++;
	if (countLoop % 10 == 0)
	{
		player.setTouchable(true);
	}
	if (countLoop == 1000000) countLoop = 0;
	// ============= update infomation =============
	updateInfomation();
	// ============= update turn game  =============
	updateTurnGame();
	// ============= update frame clip =============
	frameCoin += 0.259784;
	if (frameCoin >= 7.0) frameCoin = 0;

	frameSlime += 0.259784;
	if (frameSlime >= 6.0) frameSlime = 0;
	
	player.framAni.x += 0.259784;
	if (player.framAni.x >= 6.0)
	{
		player.framAni.x = 0;
	}

	if (player.isMove)
	{
		player.framAni.y = 1;
	}
	else
	{
		player.framAni.y = 0;
	}

	frameSke += 0.059784;
	if (frameSke >= 4.0) frameSke = 0;
	//  ============= update player ==============
	if (weaponList[curWeapon].type == GUN)
	{
		player.update(weaponList[curWeapon].gun);
	}
	else {
		player.update(weaponList[curWeapon].melle);
	}
	
	// ============== spawn enemy ===============
	
	/*if (enemyList.size() < 10)
	{
		Enemy e;
		e.init(renderer,"img/slime.png",0);
		enemyList.push_back(e);
	}*/
	//cout << "X: " << player.f_rect.x << " Y: " << player.f_rect.y << endl;
	// ============== update enemy ==============
	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].update(renderer,player,bulletEnemyList);
	// ============== update weaponList ==============
	for (int i = 0; i < numberWeaponHad; i++)
	{
		if (weaponList[i].type == MELLE)
		{
			weaponList[i].melle.update(renderer,player.f_rect, player.center(), scrollX, scrollY);
		}
		else {

			weaponList[i].gun.update(renderer,bulletList,lastShotTime, player.f_rect, player.center(), scrollX, scrollY);
		}

	}
	// ============== update itemDropped ==============
	for (int i = 0; i < coins.size(); i++)
	{
		
		coins[i].update(player.f_rect);
	}
	for (int i = 0; i < bulletsDropped.size(); i++)
	{
		bulletsDropped[i].update(player.f_rect);
	}
	// ============== update bulletEnemyList ==============
	for (int i = 0; i < bulletEnemyList.size(); i++)
	{
		bulletEnemyList[i].update(player);
	}
	// ============== update danh sách đạn ==============
	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].update();
}

void GameState::renderGameLoop()
{
	FolowCam();
	// xóa render cũ đi
	SDL_RenderClear(renderer);
	m.render(renderer, scrollX, scrollY);

	// tạo render danh sách đạn
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i].render(renderer, scrollX, scrollY);
	}

	for (int i = 0; i < bulletEnemyList.size(); i++)
	{
		bulletEnemyList[i].render(renderer, scrollX, scrollY);
	}
	// tạo render người chơi

	player.render(renderer, scrollX, scrollY);
	
	// tạo render vũ khí
	if (weaponList[curWeapon].type == GUN)
	{
		weaponList[curWeapon].gun.f_rect.x -= scrollX;
		weaponList[curWeapon].gun.f_rect.y -= scrollY;
		weaponList[curWeapon].gun.render(renderer, player.f_rect, scrollX);
	}
	else
	{
		weaponList[curWeapon].melle.f_rect.x -= scrollX;
		weaponList[curWeapon].melle.f_rect.y -= scrollY;
		weaponList[curWeapon].melle.render(renderer, player.f_rect, player.center());
	}
	
	// tạo render quái
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (enemyList[i].getType() == 0)
		{
			enemyList[i].render0(renderer, scrollX, scrollY, frameSlime);
		}
		else if (enemyList[i].getType() == 1)
		{
			enemyList[i].render1(renderer, scrollX, scrollY, frameSke);

		}
		
	}

	// render item dropped
	
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].render(renderer, frameCoin, scrollX, scrollY);
	}
	


	for (int i = 0; i < bulletsDropped.size(); i++)
	{
		bulletsDropped[i].render(renderer, scrollX, scrollY);
	}

	renderInfomation();
	// vẽ render lên màn hình
	SDL_RenderPresent(renderer);
}

void GameState::cleanRenderGameLoop()
{
	// xóa đạn nếu đạn trong danh sách nếu đạn không còn hoạt động nữa
	for (int i = 0; i < bulletList.size(); i++)
	{
		if (!bulletList[i].getActive()) {
			bulletList[i].setActive(false);
			bulletList.erase(bulletList.begin() + i);
		}
	}
	for (int i = 0; i < bulletEnemyList.size(); i++)
	{
		if (!bulletEnemyList[i].getActive()) {
			bulletEnemyList[i].setActive(false);
			bulletEnemyList.erase(bulletEnemyList.begin() + i);
		}
	}
	// xóa quái vật nếu như quái không còn hoạt động nữa
	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].freeRender(renderer,coins,bulletsDropped, enemyList,i);


	// xóa item nếu item không còn hoạt động nữa
	for (int i = 0; i < coins.size(); i++)
		if (!coins[i].getActive())
			coins.erase(coins.begin() + i);

	for (int i = 0; i < bulletsDropped.size(); i++)
		if (!bulletsDropped[i].getActive())
			bulletsDropped.erase(bulletsDropped.begin() + i);
}

void GameState::collisionGameLoop()
{
	int x = enemyList.size();

	// va chạm giữa quái và quái 
	for (int i = 0; i < x - 1; i++)
	{

		for (int j = i + 1; j < enemyList.size(); j++)
			CircleCollisionDetect(enemyList[i].center(), enemyList[i].getRadius(), enemyList[i].f_rect, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect);
	}
	
	// va chạm giữa đạn và quái
	for (int i = 0; i < bulletList.size(); i++)
	{
		for (int j = 0; j < enemyList.size(); j++)
		{
			// nếu máu quái <= 0 thì xét active về lại false
			if (enemyList[j].getHP() <= 0)
				enemyList[j].setActive(0);
			
			// kiểm tra va chạm giữa đạn và quái
			if (PolygonCollisionDetect(bulletList[i].vertices, bulletList[i].f_rect, enemyList[j].vertices, enemyList[j].f_rect))
			{
				bulletList[i].setActive(0);
				enemyList[j].setHP(enemyList[j].getHP() - weaponList[curWeapon].gun.getDamage());
			}
		}
	}
	// va chạm giữa vũ khí và quái
	if (weaponList[curWeapon].type == MELLE)
	{
		for (int j = 0; j < enemyList.size(); j++)
		{
			if (enemyList[j].getHP() <= 0)
				enemyList[j].setActive(0);
			if (CirclePolygonCollisionDetectPolygonStatic(weaponList[curWeapon].melle.vertices, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect))
			{
				enemyList[j].setHP(enemyList[j].getHP() - weaponList[curWeapon].melle.getDamage());
			}
		}
	}
	// Va chạm của người chơi
	// Va chạm giữa người và tiền
	for (int i = 0; i < coins.size(); i++)
	{
		SDL_FRect x,y;
		x = coins[i].f_rect;
		y = player.f_rect;
		if (collisionTwoRect(x, y))
		{
			money++;
			coins.erase(coins.begin() + i);
		}
	}
	// Va chạm người chơi và item
	for (int i = 0; i < bulletsDropped.size(); i++)
	{
		SDL_FRect x, y;
		x = bulletsDropped[i].f_rect;
		y = player.f_rect;
		if (collisionTwoRect(x, y))
		{
			long long x = weaponList[bulletsDropped[i].getType()].gun.getTotalBullets();
			x += 50;
			weaponList[ bulletsDropped[i].getType() ].gun.setTotalBullets(x);
			bulletsDropped.erase(bulletsDropped.begin() + i);
		}
	}
	// Va chạm người chơi và quái
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (CirclePolygonCollisionDetectPolygonStatic(player.vertices, enemyList[i].center(), enemyList[i].getRadius(), enemyList[i].f_rect))
		{
			if (player.getTouchable())
			{
				player.setTouchable(false);
				int newHp = player.getHP() - enemyList[i].getDamage();
				player.setHP(newHp);
			}
			if (player.getHP() <= 0)
			{
				isGameRunning = false;
			}
		}
	}
	for (int i = 0; i < bulletEnemyList.size(); i++)
	{
		if (collisionTwoRect(player.f_rect, bulletEnemyList[i].f_rect))
		{
			bulletEnemyList[i].setActive(0);
			if (player.getTouchable())
			{
				player.setTouchable(false);
				int newHp = player.getHP() - bulletEnemyList[i].getDamage();
				player.setHP(newHp);
			}
			if (player.getHP() <= 0)
			{
				isGameRunning = false;
			}
		}
	}
	// Va chạm người chơi và tường
	for (int i = 0; i < m.getWall().size(); i++)
	{
		PolygonCollisionDetectOneSatic(m.getWall()[i].vertices, player.vertices, player.f_rect);
	}
	for (int i = 0; i < m.getWall().size(); i++)
	{
		for (int j = 0; j < enemyList.size(); j++)
		{
			CirclePolygonCollisionDetectPolygonStatic(m.getWall()[i].vertices, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect);
		}
	}
}


void GameState::playAgain()
{
	if (!isGameRunning)
	{
		bulletList.clear();
		bulletEnemyList.clear();
		enemyList.clear();
		coins.clear();
		bulletsDropped.clear();

		player.reset();
		weaponList[0].melle.reset();
		weaponList[1].gun.reset();
		weaponList[2].gun.reset();
		weaponList[3].gun.reset();

		isGameRunning = true;
		hadInit = false;
	}
}


void GameState::freeAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameState::FolowCam()
{
	scrollX = player.f_rect.x - 1920/2;
	scrollY = player.f_rect.y - 1080/2;

	if (scrollX < 0)
	{
		scrollX = 0;
	}
	if (scrollX > LEVEL_WIDTH - 1920/2)
	{
		scrollX = LEVEL_WIDTH - 1920/2;
	}
	if (scrollY < 0)
	{
		scrollY = 0;
	}
	if (scrollY > LEVEL_HEIGHT - 1080 / 2)
	{
		scrollY = LEVEL_HEIGHT - 1080 / 2;
	}
}

void GameState::updateTurnGame()
{
	cout << enemyList.size() << endl;
	if (enemyList.size() <= 0)
	{
		turnGame = rand() % 10;
		int x = numberEnemyOnTurnGame[turnGame];
		for (int i = 0; i < x; i++)
		{
			short type = rand()%100;
			if (type % 2 == 0)
				type = 0;
			else type = 1;
			short spawnAt = rand() % 4;
			Enemy e;
			e.init(renderer, type);
			if (spawnAt == 0)
			{
				e.spawnAtLake();
			}
			else if (spawnAt == 1)
			{
				e.spawnAtGround();
			}
			else if (spawnAt == 2)
			{
				e.spawnAtGround2();
			}
			else if (spawnAt == 3)
			{
				e.spawnAtGround3();
			}
			else if (spawnAt == 4)
			{
				e.spawnAtGround4();
			}
			enemyList.push_back(e);
		}
	}
}
