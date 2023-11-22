#include "GameState.h"

const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 2020;

void GameState::bubbleSort(vector<vector<int>>& data) {
	int n = data.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (data[j][2] > data[j + 1][2]) { 
				std::swap(data[j], data[j + 1]);
			}
		}
	}
}

//Đọc ghi file ở đây nè
void GameState::Write_File(int totalEnemiesDestroyed, int totalTimeInSeconds, string& playerName)
{
	ofstream outfile;
	outfile.open("rank.txt", ios::app);
	outfile << playerName << "; " << totalEnemiesDestroyed << " " << totalTimeInSeconds << endl;
	outfile.close();
}

void GameState::Read_File()
{
	vector<vector<int>> playerList;

	ifstream infile("rank.txt");

	if (!infile.is_open())
	{
		std::cout << "Unable to open file." << std::endl;
		return;
	}

	while (!infile.eof()) {
		string playerName;
		int enemiesDestroyed, totalTime;

		infile >> playerName >> enemiesDestroyed >> totalTime;

		vector<int> playerInfo = { enemiesDestroyed, totalTime };
		playerList.push_back(playerInfo);
	}

	infile.close();

	bubbleSort(playerList);

	ofstream outfile("rank.txt", std::ios::trunc);
	outfile.close();

	outfile.open("rank.txt", std::ios::app);

	for (const auto& player : playerList) {
		outfile << "Player Name: " << player[0] << ", Number enemy destroyed: "
			<< player[1] << ", Total time: " << player[2] << "s" << std::endl;
	}

	outfile.close();
}

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
	countEnemy(0),
	numberEnemyDes(0),
	countdownTime(0),
	countdownShopTime(0),
	isShopRunning(0),
	currentTime(0),
	elapsedTime(0),
	remainingTime(0),
	startTime(0),
	totalTime(0),
	isEndGameRunning(0),
	frameMagazine(0),
	isType(1),
	frameLaze(0),
	isReturnMenu(0),
	isContinueGame(0),
	isPauseGame(0),
	countShop(0),
	startPause(0),
	pauseDuration(0)
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
	isPauseGame = false;
	window = SDL_CreateWindow("game test", 0, 0, widthWindow, heightWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();	
	initInfomation();
	initShop();
	initAudio();

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

	}

}

void GameState::resetTime()
{
	startTime = SDL_GetTicks();
	remainingTime = 0;
	elapsedTime = 0;
}

void GameState::folowMouse()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	centerMass.f_rect = { (float)mouseX - 32/2 ,(float)mouseY - 32/2,32,32 };
}

void GameState::renderMouse()
{
	centerMass.render(renderer);
}

void GameState::initInfomation()
{
	SDL_Surface* s = IMG_Load("img/hp.png");
	t = SDL_CreateTextureFromSurface(renderer, s);
	money = 0;
	coinImg.init(renderer,"img/coin.png");
	coinImg.f_rect = { 0,113,32,32 };
	moneyText.init(renderer,to_string(money), 45, 60, 113, "font/Minecraft.ttf");
	
	hp = { 10,10,(float)player.getHP() / 100 * 180,32 };
	hp_frame = { 0,0,204,96 };
	
	bd1.init(renderer, "img/magazine3.png");
	bd2.init(renderer, "img/magazine.png");
	bd3.init(renderer, "img/magazine2.png");
	bd1.f_rect = { 0,153,32,32 };
	bd2.f_rect = { 0,193,32,32 };
	bd3.f_rect = { 0,233,32,32 };

	numberbulletTextUSP.init(renderer,to_string(weaponList[1].gun.getTotalBullets()), 30, 60, 153, "font/Minecraft.ttf");
	numberbulletTextAK.init(renderer,to_string(weaponList[2].gun.getTotalBullets()), 30, 60, 193, "font/Minecraft.ttf");
	numberbulletTextMP5.init(renderer,to_string(weaponList[3].gun.getTotalBullets()), 30, 60, 233, "font/Minecraft.ttf");
	countdownTimeText.init(renderer, to_string((int)(remainingTime / 1000.0)) + " s", 30, widthWindow / 2 - 15, 100, "font/Minecraft.ttf");
	numberEnemyText.init(renderer, "Enemy Remaining: " + to_string(enemyList.size()), 30, widthWindow - 340, 0, "font/Minecraft.ttf");

}

void GameState::updateInfomation()
{
	
	hp.w = (float)player.getHP() / 100 * 181;
	
	moneyText.init(renderer, to_string(money), 45, 60, 113, "font/Minecraft.ttf");
	moneyText.setText(to_string(money));

	numberbulletTextUSP.init(renderer, " X " + to_string(weaponList[1].gun.getTotalBullets()), 30, 60, 153, "font/Minecraft.ttf");
	numberbulletTextAK.init(renderer, " X " + to_string(weaponList[2].gun.getTotalBullets()), 30, 60, 193, "font/Minecraft.ttf");
	numberbulletTextMP5.init(renderer, " X " + to_string(weaponList[3].gun.getTotalBullets()), 30, 60, 233, "font/Minecraft.ttf");
	numberbulletTextUSP.setText(" X " + to_string(weaponList[1].gun.getTotalBullets()));
	numberbulletTextAK.setText(" X " + to_string(weaponList[2].gun.getTotalBullets()));
	numberbulletTextMP5.setText(" X " + to_string(weaponList[3].gun.getTotalBullets()));
	numberEnemyText.init(renderer, "Enemy Remaining: " + to_string(enemyList.size()), 30, widthWindow - 340, 0, "font/Minecraft.ttf");

	if ((int)(remainingTime / 1000.0) <= 15)
	{
		if ((int)(remainingTime / 1000.0) % 2 == 0)
		{
			countdownTimeText.init(renderer, to_string((int)(remainingTime / 1000.0)) + " s", 30, widthWindow / 2 - 15, 100, "font/Minecraft.ttf", { 255,0,0,0 });
		}
		else {
			countdownTimeText.init(renderer, to_string((int)(remainingTime / 1000.0)) + " s", 30, widthWindow / 2 - 15, 100, "font/Minecraft.ttf");
		}
	}
	else
	{
		countdownTimeText.init(renderer, to_string((int)(remainingTime / 1000.0)) + " s", 30, widthWindow / 2 - 15, 100, "font/Minecraft.ttf");
	}


}

void GameState::renderInfomation()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRectF(renderer, &hp);
	SDL_RenderCopy(renderer, t, NULL, &hp_frame);
	coinImg.render(renderer, frameCoin, 0, 0);
	bd1.render(renderer, frameMagazine, 0, 0);
	bd2.render(renderer, frameMagazine, 0, 0);
	bd3.render(renderer, frameMagazine, 0, 0);
	moneyText.render(renderer);
	numberbulletTextUSP.render(renderer);
	numberbulletTextAK.render(renderer);
	numberbulletTextMP5.render(renderer);
	countdownTimeText.render(renderer);
	numberEnemyText.render(renderer);
}


void GameState::initGame()
{
	if (!hadInit)
	{
		backgroundMusic();

		centerMass.init(renderer, "img/centerMass.png");
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
			numberEnemyOnTurnGame[i] += 10;
		}
		m.loadMap(renderer);
		hadInit = true;
		frameBoss.x = 0;
		frameBoss.y = 0;
		// Bắt đầu thời gian
		startTime = SDL_GetTicks();
		countdownTime = 60000;
		countdownShopTime = 15000;
	}
}
void GameState::runGameLoop()
{
	enterName();
	label:
	playAgain();
	initGame();
	SDL_Event e;
	while (isGameRunning)
	{
		processInputGameLoop(e);

		updateGameLoop();
		
		collisionGameLoop();
		
		renderGameLoop();

		// vẽ render lên màn hình
		SDL_RenderPresent(renderer);
		
		cleanRenderGameLoop();
	}
	SDL_ShowCursor(SDL_ENABLE);
	if (isReturnMenu)
	{
		isReturnMenu = false;
		return;
	}
	runEndGame();
	if (isGameRunning)
	{
		isGameRunning = false;
		goto label;
	}

}
void GameState::processInputGameLoop(SDL_Event &e)
{

	while (SDL_PollEvent(&e))
	{
		// thoát khi bấm nút phía góc phải màn hình "X"
		if (e.type == SDL_QUIT)
			isGameRunning = 0;

		// bấm esc sẽ bật pause
		if (e.key.keysym.sym == SDLK_ESCAPE)
		{	
			startPause = SDL_GetTicks();
			runPauseGame();

			pauseDuration += SDL_GetTicks() - startPause;
			if (!isGameRunning)
			{
				return;
			}
		}


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
		{
			player.setIsAttack(true);
		}
			

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

	// ============= update mouse =============
	folowMouse();
	// ============= update infomation =============
	updateInfomation();
	// ============= update turn game  =============
	updateTurnGame();
	// ============= update frame clip =============
	frameCoin += 0.259784;
	if (frameCoin >= 7.0) frameCoin = 0;
	
	frameMagazine += 0.159784;
	if (frameMagazine >= 7.0) frameMagazine = 0;

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
	
	// had init
	if (turnGame == 7)
	{
		frameBoss.x += 0.259784;
		if (frameBoss.x >= 13)
		{
			frameBoss.x = 0;
		}
		for (auto enemy : enemyList)
		{
			if (enemy.getType() == 4)
			{
				if (enemy.getActiveBoss() == MOVE)
				{
					frameBoss.y = 0;
				}
				else if (enemy.getActiveBoss() == ATTACK)
				{
					frameBoss.y = 1;
				}
				else if (enemy.getActiveBoss() == DIE)
				{
					frameBoss.y = 2;
				}
			}
		}
		
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
	/*int valueToFind = 0;
	auto it = std::find_if(enemyList.begin(), enemyList.end(),
		[valueToFind](const Enemy& obj) {
			return Enemy::findType(obj, valueToFind);
		});

	int index;
	if (it != enemyList.end())
	{
		index = std::distance(enemyList.begin(), it);
	}
	else {
		index = 0;
	}*/
	if (enemyList.size() > 0)
	{
		for (int i = 0; i < bulletEnemyList.size(); i++)
		{
			bulletEnemyList[i].update(player);
		}
	}
	// ============== update danh sách đạn ==============
	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].update(player.f_rect.x,player.f_rect.w);


	// Lấy thời gian hiện tại
	currentTime = SDL_GetTicks();
	// Tính thời gian trôi qua từ lúc bắt đầu, trừ đi thời gian đã tạm dừng
	elapsedTime = currentTime - startTime - pauseDuration;
	// Tính thời gian còn lại
	remainingTime = countdownTime > elapsedTime ? countdownTime - elapsedTime : 0;




}

void GameState::renderGameLoop()
{
	FolowCam();
	// xóa render cũ đi
	//SDL_RenderClear(renderer);
	m.render(renderer, scrollX, scrollY);

	// tạo render danh sách đạn
	for (int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i].render(renderer, scrollX, scrollY);
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
		else if (enemyList[i].getType() == 2)
		{
			enemyList[i].render0(renderer, scrollX, scrollY, frameSlime);
		}
		else if (enemyList[i].getType() == 3)
		{
			enemyList[i].render1(renderer, scrollX, scrollY, frameSke);
		}
		else if (enemyList[i].getType() == 4)
		{
			enemyList[i].renderBoss(renderer, scrollX, scrollY, frameBoss);
		}
	}
	if (enemyList.size() > 0)
	{
		for (int i = 0; i < bulletEnemyList.size(); i++)
		{
			bulletEnemyList[i].render(renderer, scrollX, scrollY);
		}
	}
	
	// render item dropped
	
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].render(renderer, frameCoin, scrollX, scrollY);
	}
	


	for (int i = 0; i < bulletsDropped.size(); i++)
	{
		bulletsDropped[i].render(renderer,frameMagazine,scrollX, scrollY);
	}

	renderInfomation();
	renderMouse();

	// vẽ render lên màn hình
	//SDL_RenderPresent(renderer);
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
	{
		enemyList[i].freeRender(renderer,coins,bulletsDropped, enemyList,i,frameBoss);
	}


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
			{
				enemydead();
				numberEnemyDes++;
				enemyList[j].setActive(0);
			}
			
			// kiểm tra va chạm giữa đạn và quái
			if (PolygonCollisionDetect(bulletList[i].vertices, bulletList[i].f_rect, enemyList[j].vertices, enemyList[j].f_rect))
			{
				//enemyhurt();
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
			{
				enemyList[j].setActive(0);
				numberEnemyDes++;
			}
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
			pickup();
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
			pickup();
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
				dameSound();
			}
			if (player.getHP() <= 0)
			{
				isGameRunning = false;
				totalTime += countdownTime - remainingTime;
				totalTime += countdownTime * countShop;
				dameSound();
				return;
			}
		}
	}
	// va chạm giữa đạn quái và người chơi
	for (int i = 0; i < bulletEnemyList.size(); i++)
	{
		if (PolygonCollisionDetectTwoSatic(player.vertices, bulletEnemyList[i].vertices))
		{
			if (bulletEnemyList[i].getType() == 0 && bulletEnemyList[i].getFrameLaze() >= 9)
			{
				if (player.getTouchable())
				{
					dameSound();
					player.setTouchable(false);
					int newHp = player.getHP() - bulletEnemyList[i].getDamage();
					player.setHP(newHp);
					if (newHp <= 0)
					{
						isGameRunning = false;
						totalTime += countdownTime - remainingTime;
						totalTime += countdownTime * countShop;
						dameSound();
						return;
					}
				}
			}
			else if(bulletEnemyList[i].getType() == 1 || bulletEnemyList[i].getType() == 3){
				if (player.getTouchable())
				{
					dameSound();
					player.setTouchable(false);
					int newHp = player.getHP() - bulletEnemyList[i].getDamage();
					player.setHP(newHp);
					if (newHp <= 0)
					{
						isGameRunning = false;
						totalTime += countdownTime - remainingTime;
						totalTime += countdownTime * countShop;
						dameSound();
						return;
					}
				}
				bulletEnemyList[i].setActive(0);
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

		m.clear();

		player.reset();
		weaponList[0].melle.reset();
		weaponList[1].gun.reset();
		weaponList[2].gun.reset();
		weaponList[3].gun.reset();
		money = 0;
		resetTime();
		totalTime = 0;

		isGameRunning = true;
		hadInit = false;
		isShopRunning = false;
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
	if (enemyList.size() <= 0 || remainingTime <= 0)
	{
		if (money > 0 && remainingTime > 0)
		{
			totalTime += countdownTime - remainingTime;
		}
		turnGame = rand()%10 ;
		resetTime();
		runShop();

		resetTime();
		isShopRunning = true;
		int numberEnemy = numberEnemyOnTurnGame[turnGame];
		short spawnAt;
		for (int i = 0; i < numberEnemy; i++)
		{
			short type = rand()%100;
			spawnAt = rand() % 8;
			if (type % 2 == 0)
				type = 0;
			else type = 1;
			Enemy e;
			e.init(renderer, type);
			if (spawnAt == 0)
				e.spawnAt0();
			else if (spawnAt == 1)
				e.spawnAt1();
			else if (spawnAt == 2)
				e.spawnAt2();
			else if (spawnAt == 3)
				e.spawnAt3();
			else if (spawnAt == 4)
				e.spawnAt4();
			else if (spawnAt == 5)
				e.spawnAt5();
			else if (spawnAt == 6)
				e.spawnAt6();
			else if (spawnAt == 7)
				e.spawnAt7();
			enemyList.push_back(e);
		}
		// khởi tạo boss
		if (turnGame == 5)
		{
			Enemy boss;
			boss.init(renderer, 2);
			spawnAt = rand() % 8;
			if (spawnAt == 0)
				boss.spawnAt0();
			else if (spawnAt == 1)
				boss.spawnAt1();
			else if (spawnAt == 2)
				boss.spawnAt2();
			else if (spawnAt == 3)
				boss.spawnAt3();
			else if (spawnAt == 4)
				boss.spawnAt4();
			else if (spawnAt == 5)
				boss.spawnAt0();
			else if (spawnAt == 6)
				boss.spawnAt1();
			else if (spawnAt == 7)
				boss.spawnAt7();
			enemyList.push_back(boss);
		}	
		else if (turnGame == 1)
		{
			Enemy boss;
			boss.init(renderer, 3);
			spawnAt = rand() % 8;
			if (spawnAt == 0)
				boss.spawnAt0();
			else if (spawnAt == 1)
				boss.spawnAt1();
			else if (spawnAt == 2)
				boss.spawnAt2();
			else if (spawnAt == 3)
				boss.spawnAt3();
			else if (spawnAt == 4)
				boss.spawnAt4();
			else if (spawnAt == 5)
				boss.spawnAt5();
			else if (spawnAt == 6)
				boss.spawnAt6();
			else if (spawnAt == 7)
				boss.spawnAt7();
			enemyList.push_back(boss);
		}
		else if (turnGame == 3)
		{
			
			for (int i = 0; i < 2; i++)
			{
				Enemy e;
				spawnAt = rand() % 8;
				short type = rand() % 10;
				
				if (type % 2 == 0) type = 2;
				else type = 3;

				e.init(renderer, type);
				if (spawnAt == 0)
					e.spawnAt0();
				else if (spawnAt == 1)
					e.spawnAt1();
				else if (spawnAt == 2)
					e.spawnAt2();
				else if (spawnAt == 3)
					e.spawnAt3();
				else if (spawnAt == 4)
					e.spawnAt4();
				else if (spawnAt == 5)
					e.spawnAt5();
				else if (spawnAt == 6)
					e.spawnAt6();
				else if (spawnAt == 7)
					e.spawnAt7();
				enemyList.push_back(e);
			}
		}
		else if (turnGame == 7)
		{
			bossMusic();
			Enemy bossFinal;
			bossFinal.init(renderer, 4);
			spawnAt = rand() % 4;
			if (spawnAt == 0)
				bossFinal.spawnBoss1();
			else if (spawnAt == 1)
				bossFinal.spawnBoss2();
			else if (spawnAt == 2)
				bossFinal.spawnBoss3();
			else if (spawnAt == 3)
				bossFinal.spawnBoss4();

			enemyList.push_back(bossFinal);
		
		}

	}
}

void GameState::enterName()
{
	SDL_Event e;
	Text nameText;
	SDL_StartTextInput();
	while (isType)
	{
		nameText.init(renderer, "Name: " + player.name, 50, 1920 / 2 - 300, 1080 / 2, "font/Minecraft.ttf");
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_TEXTINPUT)
			{
				player.name.append(e.text.text);
			}
			if (e.key.keysym.sym == SDLK_BACKSPACE && !player.name.empty())
			{
				player.name.pop_back();
			}
			if (e.key.keysym.sym == SDLK_RETURN)
			{
				isType = false;
			}
			SDL_RenderClear(renderer);

			background.render(renderer);
			nameText.render(renderer);

			SDL_RenderPresent(renderer);
		}
	}
	SDL_StopTextInput();
	//cout << player.name;
}



