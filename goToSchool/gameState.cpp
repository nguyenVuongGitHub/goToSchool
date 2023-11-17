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
	frameSke(0)
{
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

/**
* xử lý game loop
*/

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

		m.loadMap(renderer);
		hadInit = true;
	}
}
void GameState::runGameLoop()
{
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

	frameSke += 0.159784;
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


/**
* Xử lý menu
*/
void GameState::initMenu()
{
	background.init(renderer, "img/background.jpg");
	background.f_rect = { 0,0,1920,1080};
	//cout << t_title.getRect().w << endl ;
	t_title.init(renderer, "GO TO SCHOOL", 92, widthWindow / 2 - (674 / 2), 179);
	t_play.init(renderer, "PLAY", 52,881, 369);
	t_shop.init(renderer, "SHOP", 52,881, 559);
	t_exit.init(renderer, "EXIT", 52,881, 749);

}
void GameState::processInputMenu(SDL_Event& e)
{
	while (SDL_PollEvent(&e))
	{

		isGameRunning = true;
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
		{
			if (t_play.getCollision())
			{
				runGameLoop();
			}
			else if (t_shop.getCollision())
			{
				// do something
			}
			else if (t_exit.getCollision())
			{
				isMenuRunning = false;
			}
			
		}
	}
}
void GameState::updateMenu()
{
	t_play.updateText(renderer,t_play.getColor(RED));
	t_shop.updateText(renderer, t_play.getColor(RED));
	t_exit.updateText(renderer, t_play.getColor(RED));

}
void GameState::renderMenu()
{
	SDL_RenderClear(renderer);

	background.render(renderer);
	t_title.render(renderer);
	t_play.render(renderer);
	t_shop.render(renderer);
	t_exit.render(renderer);
	
	SDL_RenderPresent(renderer);
}
void GameState::cleanRenderMenu()
{

}
void GameState::collisionMenu()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (t_play.checkCollisonWithMouse(mouseX, mouseY))
		t_play.setCollision(true);
	else if (t_shop.checkCollisonWithMouse(mouseX, mouseY))
		t_shop.setCollision(true);
	else if (t_exit.checkCollisonWithMouse(mouseX, mouseY))
		t_exit.setCollision(true);
	else
	{
		t_play.setCollision(false);
		t_shop.setCollision(false);
		t_exit.setCollision(false);
	}
}


FlatVector GameState::FindArithmeticMean(vector<FlatVector> vertices)
{
	float sumX = 0;
	float sumY = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		FlatVector v = vertices[i];
		sumX += v.x;
		sumY += v.y;
	}
	FlatVector tmp(sumX / vertices.size(), sumY / vertices.size());
	return tmp;

}

bool GameState::collisionEnemyWithEnemy(Enemy& p, Enemy& obj)
{

	float depth = INFINITY; // Khởi tạo độ sâu mà vật thể bị trùng
	FlatVector normal; // Khởi tạo vector đơn vị
	for (int i = 0; i < p.vertices.size(); i++) // Duyệt tất cả các đỉnh của vật thể
	{
		// Tìm đường x để xét
		FlatVector va = p.vertices[i];
		FlatVector vb = p.vertices[(i + 1) % p.vertices.size()];
		FlatVector edge = vb - va;
		FlatVector axis(edge.x, edge.y);

		float min1 = INFINITY; // Khởi tạo điểm có tọa độ thấp nhất cùa vật thể 1 trên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo điểm có tọa độ cao nhất của vật thể 1 trên đường axis vừa tạo

		for (int i = 0; i < p.vertices.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			FlatVector v = p.vertices[i];
			float proj = axis.Dot(v);
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2 = INFINITY; // Khởi tạo điểm có tọa độ thấp nhất cùa vật thể 2 trên đường axis vừa tạo
		float max2 = -INFINITY; // Khởi tạo điểm có tọa độ thấp nhất cùa vật thể 2 trên đường axis vừa tạo

		for (int i = 0; i < obj.vertices.size(); i++) // Duyệt qua các đỉnh của vật thể 2 để tìm điểm cao, thấp nhất
		{
			FlatVector v = obj.vertices[i];
			float proj = axis.Dot(v);
			if (proj < min2) min2 = proj;
			if (proj > max2) max2 = proj;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}

		float axisDepth = std::min(max2 - min1, max1 - min2); // Khởi tạo cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis; // Lưu lại vị trí đường x
		}

	}

	// Y hệt như trên chỉ khác là so vật 2 với vật 1
	for (int i = 0; i < obj.vertices.size(); i++)
	{
		FlatVector va = obj.vertices[i];
		FlatVector vb = obj.vertices[(i + 1) % obj.vertices.size()];

		FlatVector edge = vb - va;
		FlatVector axis(edge.x, edge.y);

		float min1 = INFINITY;
		float max1 = -INFINITY;

		for (int i = 0; i < p.vertices.size(); i++)
		{
			FlatVector v = p.vertices[i];
			float proj = axis.Dot(v);
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2 = INFINITY;
		float max2 = -INFINITY;

		for (int i = 0; i < obj.vertices.size(); i++)
		{
			FlatVector v = obj.vertices[i];
			float proj = axis.Dot(v);
			if (proj < min2) min2 = proj;
			if (proj > max2) max2 = proj;
		}

		if (min1 >= max2 || min2 >= max1)
		{
			return false;
		}
		float axisDepth = std::min(max2 - min1, max1 - min2);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	depth /= normal.Length(); // Chia độ dài của vector để lấy được tỉ số với vector đơn vị
	normal = normal.Normalize(); // Chuyển đổi thành vector đơn vị
	FlatVector centerA = FindArithmeticMean(p.vertices); // Tính trung bình cộng
	FlatVector centerB = FindArithmeticMean(obj.vertices);

	FlatVector direction = centerB - centerA; // Khởi tạo một vector có hướng từ điểm A trong vật thể 1 tới điểm B trong vật thể 2

	if (normal.Dot(direction) < 0) // Nếu hướng của normal và direction không trùng
	{
		normal = normal * -1; // Đổi hướng vector normal để xác định đúng hướng mà vật thể cần được đặt ra
	}
	float x1, x2, y1, y2;
	x1 = p.f_rect.x;
	x2 = obj.f_rect.x;
	y1 = p.f_rect.y;
	y2 = obj.f_rect.y;
	x1 -= normal.x * depth / 2;
	y1 -= normal.y * depth / 2;
	x2 += normal.x * depth / 2;
	y2 += normal.y * depth / 2;
	p.f_rect = { x1,y1,p.f_rect.w,p.f_rect.h };
	obj.f_rect = { x2,y2,obj.f_rect.w,obj.f_rect.h };
	/*p.getRect().x -= 
	p.getRect().y -= 
	obj.getRect().x += 
	obj.getRect().y += */

	return true;
}
bool GameState::collisionTwoRect(SDL_FRect& r1, SDL_FRect& r2)
{
	return (r1.x + r1.w >= r2.x && r2.x + r2.w >= r1.x
		&& r1.y + r1.h >= r2.y && r2.y + r2.h >= r1.y);
}


/**
*
* Va chạm giữa các hình tròn và thay đổi tọa độ của các hình tròn có va chạm
*
* \param center1 : Tâm của đường tròn thứ nhất
* \param radius1 : Bán kình của đường tròn thứ nhất
* \param r1 : tọa độ của đường tròn thứ nhất
* \param center2 : Tâm của đường tròn thứ hai
* \param radius2 : Bán kình của đường tròn thứ hai
* \param r2 : tọa độ của đường tròn thứ hai
*
* \returns Hàm này trả về true khi va chạm, false khi không va chạm
*/
bool GameState::CircleCollisionDetect(FlatVector center1, float radius1, SDL_FRect& r1, FlatVector center2, float radius2, SDL_FRect& r2)
{
	FlatVector normal;
	float depth = 0;

	float distance = center1.Distance(center2); // Khoảng cách từ 2 tâm của đường tròn
	float sumRadius = radius1 + radius2;

	if (distance >= sumRadius)
	{
		return false;
	}

	normal = (center1 - center2).Normalize();
	depth = sumRadius - distance;

	r1.x += normal.x * depth / 2;
	r1.y += normal.y * depth / 2;
	r2.x -= normal.x * depth / 2;
	r2.y -= normal.y * depth / 2;

	return true;

}


/**
*
* Va chạm giữa các hình polygon (đa giác) và thay đổi tọa độ của các polygon có va chạm
*
* \used Định lý sparating axis theorem (SAT) và định lý aixs aligned bounding box (AABB)
*
* \param vertices1 : Các đỉnh của polygon thứ nhất
* \param r1 : tọa độ của polypon thứ nhất
* \param vertices2 : Các đỉnh của polygon thứ hai
* \param r2 : tọa độ của polypon thứ hai
*
* \returns Hàm này trả về true khi va chạm, false khi không va chạm
*/
bool GameState::PolygonCollisionDetect(vector<FlatVector> vertices1, SDL_FRect& r1, vector<FlatVector> vertices2, SDL_FRect& r2)
{
	float depth = INFINITY; // Khởi tạo độ sâu mà vật thể bị trùng
	FlatVector normal; // Khởi tạo vector đơn vị, thứ sẽ cho vật thể biết phải chạy ra hướng nào
	for (int i = 0; i < vertices1.size(); i++) // Duyệt tất cả các đỉnh của vật thể
	{
		// Tìm trục (axis) để xét
		FlatVector va = vertices1[i];
		FlatVector vb = vertices1[(i + 1) % vertices1.size()];
		FlatVector edge = vb - va;
		FlatVector axis(-edge.y, edge.x);

		float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices1.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices1[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo
		float max2 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices2.size(); i++) // Duyệt qua các đỉnh của vật thể 2 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices2[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min2) min2 = proj;
			if (proj > max2) max2 = proj;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}

		float axisDepth = std::min(max2 - min1, max1 - min2); // Khởi tạo cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis; // Lưu lại trục (axis) đang xét
		}
	}

	// Y hệt như trên chỉ khác là so vật 2 với vật 1
	for (int i = 0; i < vertices2.size(); i++)
	{
		// Tìm trục (axis) theo polygon thứ 2 để xét
		FlatVector va = vertices2[i];
		FlatVector vb = vertices2[(i + 1) % vertices2.size()];

		FlatVector edge = vb - va;
		FlatVector axis(edge.x, edge.y);
		axis = axis.Normalize();

		float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices1.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices1[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo
		float max2 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices2.size(); i++) // Duyệt qua các đỉnh của vật thể 2 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices2[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min2) min2 = proj;
			if (proj > max2) max2 = proj;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}
		float axisDepth = std::min(max2 - min1, max1 - min2); // Khởi tạo cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis;  // Lưu lại trục (axis) đang xét
		}
	}

	depth /= normal.Length(); // Chia độ dài của vector để lấy được tỉ số với vector đơn vị
	normal = normal.Normalize(); // Chuyển đổi thành vector đơn vị
	FlatVector centerA = FindArithmeticMean(vertices1); // Tính trung bình cộng để tìm vị trí trung tâm
	FlatVector centerB = FindArithmeticMean(vertices2); // Tính trung bình cộng để tìm vị trí trung tâm

	FlatVector direction = centerB - centerA; // Khởi tạo một vector có hướng từ điểm A trong vật thể 1 tới điểm B trong vật thể 2

	if (normal.Dot(direction) < 0) // Nếu hướng của normal và direction không trùng
	{
		normal = normal * -1; // Đổi hướng vector normal để xác định đúng hướng mà vật thể cần được đặt ra
	}


	// Sửa lại tọa độ
	r1.x -= normal.x * depth / 2;
	r1.y -= normal.y * depth / 2;
	r2.x += normal.x * depth / 2;
	r2.y += normal.y * depth / 2;

	return true;
}

/**
*
* Va chạm giữa các hình polygon (đa giác) và thay đổi tọa độ của các polygon có va chạm riêng polygon 1 không thay đổi
*
* \used Định lý sparating axis theorem (SAT) và định lý aixs aligned bounding box (AABB)
*
* \param vertices1 : Các đỉnh của polygon thứ nhất
* \param vertices2 : Các đỉnh của polygon thứ hai
* \param r2 : tọa độ của polypon thứ hai
*
* \returns Hàm này trả về true khi va chạm, false khi không va chạm
*/
bool GameState::PolygonCollisionDetectOneSatic(vector<FlatVector> vertices1, vector<FlatVector> vertices2, SDL_FRect& r2)
{
	float depth = INFINITY; // Khởi tạo độ sâu mà vật thể bị trùng
	FlatVector normal; // Khởi tạo vector đơn vị, thứ sẽ cho vật thể biết phải chạy ra hướng nào
	for (int i = 0; i < vertices1.size(); i++) // Duyệt tất cả các đỉnh của vật thể
	{
		// Tìm trục (axis) để xét
		FlatVector va = vertices1[i];
		FlatVector vb = vertices1[(i + 1) % vertices1.size()];
		FlatVector edge = vb - va;
		FlatVector axis(-edge.y, edge.x);

		float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices1.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices1[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo
		float max2 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices2.size(); i++) // Duyệt qua các đỉnh của vật thể 2 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices2[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min2) min2 = proj;
			if (proj > max2) max2 = proj;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}

		float axisDepth = std::min(max2 - min1, max1 - min2); // Khởi tạo cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis; // Lưu lại trục (axis) đang xét
		}
	}

	// Y hệt như trên chỉ khác là so vật 2 với vật 1
	for (int i = 0; i < vertices2.size(); i++)
	{
		// Tìm trục (axis) theo polygon thứ 2 để xét
		FlatVector va = vertices2[i];
		FlatVector vb = vertices2[(i + 1) % vertices2.size()];

		FlatVector edge = vb - va;
		FlatVector axis(edge.x, edge.y);
		axis = axis.Normalize();

		float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices1.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices1[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo
		float max2 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 1 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices2.size(); i++) // Duyệt qua các đỉnh của vật thể 2 để tìm điểm cao, thấp nhất
		{
			float proj = axis.Dot(vertices2[i]); // Lấy giá trị của tích vô hướng = độ lớn bé của vector khi được chiếu lên trục (axis)
			if (proj < min2) min2 = proj;
			if (proj > max2) max2 = proj;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}
		float axisDepth = std::min(max2 - min1, max1 - min2); // Khởi tạo cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis;  // Lưu lại trục (axis) đang xét
		}
	}

	depth /= normal.Length(); // Chia độ dài của vector để lấy được tỉ số với vector đơn vị
	normal = normal.Normalize(); // Chuyển đổi thành vector đơn vị
	FlatVector centerA = FindArithmeticMean(vertices1); // Tính trung bình cộng để tìm vị trí trung tâm
	FlatVector centerB = FindArithmeticMean(vertices2); // Tính trung bình cộng để tìm vị trí trung tâm

	FlatVector direction = centerB - centerA; // Khởi tạo một vector có hướng từ điểm A trong vật thể 1 tới điểm B trong vật thể 2

	if (normal.Dot(direction) < 0) // Nếu hướng của normal và direction không trùng
	{
		normal = normal * -1; // Đổi hướng vector normal để xác định đúng hướng mà vật thể cần được đặt ra
	}


	// Sửa lại tọa độ
	r2.x += normal.x * depth ;
	r2.y += normal.y * depth ;

	return true;
}

/**
* Tìm đỉnh gần tâm đường tròn nhất và trả về index của đỉnh đó
*
* \param centerCircle : Tâm của đường tròn
* \param vertices : các đỉnh của polygon (đa giác)
*
* \returns Hàm này sẽ trả về index của đỉnh gần tâm đường tròn nhất
*/
int FindClosestPointFromPolygonToCircle(FlatVector centerCircle, vector<FlatVector> vertices)
{
	int result = -1;
	float minDistance = INFINITY;
	float distance;
	FlatVector v;
	for (int i = 0; i < vertices.size(); i++)
	{
		v = vertices[i];
		distance = v.Distance(centerCircle);

		if (distance < minDistance)
		{
			minDistance = distance;
			result = i;
		}
	}
	return result;
}

/**
*
* Va chạm giữa hình polygon (đa giác) và hình tròn, đồng thời thay đổi tọa độ của polygon và hình tròn có va chạm
*
* \Used Định lý sparating axis theorem (SAT) và định lý aixs aligned bounding box (AABB)
*
* \param vertices : Các đỉnh của polygon
* \param r1 : tọa độ của polypon
* \param centerCircle : Tâm của đường tròn
* \param radius : Bán kình của đường tròn
* \param r2 : tọa độ của đường tròn
*
* \returns Hàm này trả về true khi va chạm, false khi không va chạm
*/
bool GameState::CirclePolygonCollisionDetect(vector<FlatVector> vertices, SDL_FRect& r1, FlatVector centerCircle, float radius, SDL_FRect& r2)
{
	float depth = INFINITY; // Khởi tạo độ sâu mà vật thể bị trùng
	FlatVector normal;  // Khởi tạo vector đơn vị, thứ sẽ cho vật thể biết phải chạy ra hướng nào
	float axisDepth;
	for (int i = 0; i < vertices.size(); i++) // Duyệt tất cả các đỉnh của vật thể
	{
		// Tìm đường x để xét
		FlatVector va = vertices[i];
		FlatVector vb = vertices[(i + 1) % vertices.size()];
		FlatVector edge = vb - va;
		FlatVector axis(-edge.y, edge.x);

		float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			FlatVector v = vertices[i];
			float proj = axis.Dot(v);
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
		float max2; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

		FlatVector direction = axis.Normalize(); // Lấy vector dơn vị chỉ phương hướng của trục đang xét(axis)
		FlatVector directionRadius = direction * radius; // Vector tượng trưng cho vector từ tâm đường tròn tới đường tròn (vector bán kính)

		FlatVector vectorRadius1 = centerCircle + directionRadius; // Vector bán kính thứ nhất
		FlatVector vectorRadius2 = centerCircle - directionRadius; // Vector bán kính thứ hai có chiều ngược lại so với vector bán kính thứ nhất

		min2 = axis.Dot(vectorRadius1); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét
		max2 = axis.Dot(vectorRadius2); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét

		if (min2 > max2) // Chính sửa lại giá trị. Vì khi lấy giá trị từ vector bán kính không thề biết trước cái nào sẽ lơn hơn hay bé hơn
		{
			// Đổi giá trị
			float t = min2;
			min2 = max2;
			max2 = t;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}

		axisDepth = std::min(max2 - min1, max1 - min2); // Cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis; // Lưu lại trục (axis) đang xét
		}
	}

	int cpIndex = FindClosestPointFromPolygonToCircle(centerCircle, vertices); // Lấy thứ tự định gần tâm đường tròn nhất
	FlatVector cp = vertices[cpIndex]; // Đỉnh gần tâm đường tròn nhất

	FlatVector axis = cp - centerCircle; // Trục axit cần xét

	float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
	float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

	for (int i = 0; i < vertices.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
	{
		FlatVector v = vertices[i];
		float proj = axis.Dot(v);
		if (proj < min1) min1 = proj;
		if (proj > max1) max1 = proj;
	}

	float min2; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
	float max2; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

	FlatVector directionRadius = axis.Normalize() * radius; // Vector tượng trưng cho vector từ tâm đường tròn tới đường tròn (vector bán kính)

	FlatVector vectorRadius1 = centerCircle + directionRadius; // Vector bán kính thứ nhất
	FlatVector vectorRadius2 = centerCircle - directionRadius; // Vector bán kính thứ hai có chiều ngược lại so với vector bán kính thứ nhất

	min2 = axis.Dot(vectorRadius1); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét
	max2 = axis.Dot(vectorRadius2); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét

	if (min2 > max2) // Chính sửa lại giá trị. Vì khi lấy giá trị từ vector bán kính không thề biết trước cái nào sẽ lơn hơn hay bé hơn
	{
		// Đổi giá trị
		float t = min2;
		min2 = max2;
		max2 = t;
	}

	if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
	{
		return false; //Nếu không có va chạm thì trả về false;
	}

	axisDepth = std::min(max2 - min1, max1 - min2); // Cập nhật giá trị độ sâu mà 2 vật thể bị trùng

	if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
	{
		depth = axisDepth; // Lưu lại giá trị bị trùng
		normal = axis; // Lưu lại trục (axis) đang xét
	}

	depth /= normal.Length(); // Chia độ dài của vector để lấy được tỉ số với vector đơn vị
	normal = normal.Normalize(); // Chuyển đổi thành vector đơn vị
	FlatVector centerPolygon = FindArithmeticMean(vertices); // Tính trung bình cộng để tìm vị trí trung tâm

	FlatVector direction = centerCircle - centerPolygon; // Khởi tạo một vector có hướng từ tâm trong polygon tới tâm đường tròn

	if (normal.Dot(direction) < 0) // Nếu hướng của normal và direction không trùng
	{
		normal = normal * -1; // Đổi hướng vector normal để xác định đúng hướng mà vật thể cần được đặt ra
	}


	// Sửa lại tọa độ
	r1.x -= normal.x * depth / 2;
	r1.y -= normal.y * depth / 2;
	r2.x += normal.x * depth / 2;
	r2.y += normal.y * depth / 2;

	return true;
}

/**
*
* Va chạm giữa hình polygon (đa giác) và hình tròn, đồng thời thay đổi tọa độ của polygon và hình tròn có va chạm
*
* \Used Định lý sparating axis theorem (SAT) và định lý aixs aligned bounding box (AABB)
*
* \param vertices : Các đỉnh của polygon
* \param centerCircle : Tâm của đường tròn
* \param radius : Bán kình của đường tròn
* \param r2 : tọa độ của đường tròn
*
* \returns Hàm này trả về true khi va chạm, false khi không va chạm
*/
bool GameState::CirclePolygonCollisionDetectPolygonStatic(vector<FlatVector> vertices, FlatVector centerCircle, float radius, SDL_FRect& r2)
{
	float depth = INFINITY; // Khởi tạo độ sâu mà vật thể bị trùng
	FlatVector normal;  // Khởi tạo vector đơn vị, thứ sẽ cho vật thể biết phải chạy ra hướng nào
	float axisDepth;
	for (int i = 0; i < vertices.size(); i++) // Duyệt tất cả các đỉnh của vật thể
	{
		// Tìm đường x để xét
		FlatVector va = vertices[i];
		FlatVector vb = vertices[(i + 1) % vertices.size()];
		FlatVector edge = vb - va;
		FlatVector axis(-edge.y, edge.x);

		float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
		float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

		for (int i = 0; i < vertices.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
		{
			FlatVector v = vertices[i];
			float proj = axis.Dot(v);
			if (proj < min1) min1 = proj;
			if (proj > max1) max1 = proj;
		}

		float min2; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
		float max2; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

		FlatVector direction = axis.Normalize(); // Lấy vector dơn vị chỉ phương hướng của trục đang xét(axis)
		FlatVector directionRadius = direction * radius; // Vector tượng trưng cho vector từ tâm đường tròn tới đường tròn (vector bán kính)

		FlatVector vectorRadius1 = centerCircle + directionRadius; // Vector bán kính thứ nhất
		FlatVector vectorRadius2 = centerCircle - directionRadius; // Vector bán kính thứ hai có chiều ngược lại so với vector bán kính thứ nhất

		min2 = axis.Dot(vectorRadius1); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét
		max2 = axis.Dot(vectorRadius2); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét

		if (min2 > max2) // Chính sửa lại giá trị. Vì khi lấy giá trị từ vector bán kính không thề biết trước cái nào sẽ lơn hơn hay bé hơn
		{
			// Đổi giá trị
			float t = min2;
			min2 = max2;
			max2 = t;
		}

		if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
		{
			return false; //Nếu không có va chạm thì trả về false;
		}

		axisDepth = std::min(max2 - min1, max1 - min2); // Cập nhật giá trị độ sâu mà 2 vật thể bị trùng

		if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
		{
			depth = axisDepth; // Lưu lại giá trị bị trùng
			normal = axis; // Lưu lại trục (axis) đang xét
		}
	}

	int cpIndex = FindClosestPointFromPolygonToCircle(centerCircle, vertices); // Lấy thứ tự định gần tâm đường tròn nhất
	FlatVector cp = vertices[cpIndex]; // Đỉnh gần tâm đường tròn nhất

	FlatVector axis = cp - centerCircle; // Trục axit cần xét

	float min1 = INFINITY; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
	float max1 = -INFINITY; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

	for (int i = 0; i < vertices.size(); i++) // Duyệt qua các đỉnh của vật thể 1 để tìm điểm cao, thấp nhất
	{
		FlatVector v = vertices[i];
		float proj = axis.Dot(v);
		if (proj < min1) min1 = proj;
		if (proj > max1) max1 = proj;
	}

	float min2; // Khởi tạo biến lưu điểm thấp nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo
	float max2; // Khởi tạo biến lưu điểm lớn nhất cùa vật thể 2 khi chiếu lên đường axis vừa tạo

	FlatVector directionRadius = axis.Normalize() * radius; // Vector tượng trưng cho vector từ tâm đường tròn tới đường tròn (vector bán kính)

	FlatVector vectorRadius1 = centerCircle + directionRadius; // Vector bán kính thứ nhất
	FlatVector vectorRadius2 = centerCircle - directionRadius; // Vector bán kính thứ hai có chiều ngược lại so với vector bán kính thứ nhất

	min2 = axis.Dot(vectorRadius1); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét
	max2 = axis.Dot(vectorRadius2); // Lấy giá trị độ lớn của vector bán kính khi chiếu lên trục axis đang xét

	if (min2 > max2) // Chính sửa lại giá trị. Vì khi lấy giá trị từ vector bán kính không thề biết trước cái nào sẽ lơn hơn hay bé hơn
	{
		// Đổi giá trị
		float t = min2;
		min2 = max2;
		max2 = t;
	}

	if (min1 >= max2 || min2 >= max1) // Sử dụng định lý xác định va chạm AABB để kiểm tra va chạm 
	{
		return false; //Nếu không có va chạm thì trả về false;
	}

	axisDepth = std::min(max2 - min1, max1 - min2); // Cập nhật giá trị độ sâu mà 2 vật thể bị trùng

	if (axisDepth < depth) // Nếu độ sâu của 2 vật thể nhỏ hơn độ sâu 2 vật thể lúc trước
	{
		depth = axisDepth; // Lưu lại giá trị bị trùng
		normal = axis; // Lưu lại trục (axis) đang xét
	}

	depth /= normal.Length(); // Chia độ dài của vector để lấy được tỉ số với vector đơn vị
	normal = normal.Normalize(); // Chuyển đổi thành vector đơn vị
	FlatVector centerPolygon = FindArithmeticMean(vertices); // Tính trung bình cộng để tìm vị trí trung tâm

	FlatVector direction = centerCircle - centerPolygon; // Khởi tạo một vector có hướng từ tâm trong polygon tới tâm đường tròn

	if (normal.Dot(direction) < 0) // Nếu hướng của normal và direction không trùng
	{
		normal = normal * -1; // Đổi hướng vector normal để xác định đúng hướng mà vật thể cần được đặt ra
	}


	// Sửa lại tọa độ của r2(vật thể hình tròn)
	r2.x += normal.x * depth * 2 / 3;
	r2.y += normal.y * depth * 2 / 3;

	return true;
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
	if (enemyList.size() <= 0)
	{
		turnGame = rand() % 5;
		//turnGame = 0;
		if (turnGame == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				Enemy e;
				e.init(renderer, 0);
				e.spawnAtLake();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 4; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround2();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 4; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround4();
				enemyList.push_back(e);
			}
		}
		else if (turnGame == 1)
		{
			for (int i = 0; i < 9; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround3();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 2; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround4();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 4; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround();
				enemyList.push_back(e);
			}
		}
		else if (turnGame == 2)
		{
			for (int i = 0; i < 5; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround2();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 5; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround3();
				enemyList.push_back(e);
			}
		}
		else if (turnGame == 3)
		{
			for (int i = 0; i < 5; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 5; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround4();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 5; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround2();
				enemyList.push_back(e);
			}
			for (int i = 0; i < 5; i++)
			{
				Enemy e;
				e.init(renderer, 1);
				e.spawnAtGround3();
				enemyList.push_back(e);
			}
		}
		else if (turnGame == 4)
		{

		}
		else if (turnGame == 5)
		{
			// boss

		}
	}
}
