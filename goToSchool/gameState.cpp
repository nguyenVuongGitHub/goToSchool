#include "GameState.h"

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
	experience(0),
	lever(0),
	frameCoin(0),
	hadInit(0)
{
}

void GameState::initData()
{
	heightWindow = 1920;
	widthWindow = 1080;
	mouseX = 0;
	mouseY = 0;
	isGameRunning = 1;
	isMenuRunning = 1;
	window = SDL_CreateWindow("game test", 0, 0, widthWindow, heightWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	capacity = 4;
	boundary = { 540,960,1080,1920};
	qtree = new QuadTree(capacity, boundary);
	
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	IMG_Init(IMG_INIT_PNG);
	IMG_Init(IMG_INIT_JPG);
	TTF_Init();	
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

		player.init(renderer, "img/tamGiac.png");
		
		/*qtree->insert(&m1);
		qtree->insert(&x1);
		qtree->insert(&x2);
		qtree->insert(&x3);
		qtree->insert(&player);
		objects.push_back(&m1);
		objects.push_back(&x1);
		objects.push_back(&x2);
		objects.push_back(&x3);
		objects.push_back(&player);*/

		m.loadMap(renderer,qtree);
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
	// ============= update frame clip =============
	frameCoin += 0.259784;
	if (frameCoin >= 7.0) frameCoin = 0;
	
	//  ============= update player ==============
	if (weaponList[curWeapon].type == GUN)
	{
		player.update(weaponList[curWeapon].gun);
	}
	else {
		player.update(weaponList[curWeapon].melle);
	}
	
	// ============== spawn enemy ===============
	
	if (enemyList.size() < 10)
	{
		Enemy e;
		e.init(renderer,"img/ball.png");
		qtree->insert(&e);
		newObjects.push_back(&e);
		//cout << qtree->getObj()[0]->f_rect.x << endl; // đúng vị trí
		//cout << e.f_rect.x << endl;
		//cout << "inserted \n";

		enemyList.push_back(e);
	}
	cout << newObjects[0]->f_rect.x << endl; // số rác
	// 
	// ============== update enemy ==============
	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].update(player);

	/*for (int i = 0; i < newObjects.size(); i++)
	{
		cout << "object i = " << i << "\t" << newObjects[i]->f_rect.x << endl;
		cout << "enemy i = " << i << "\t" << enemyList[i].f_rect.x << endl;

	}*/
	//cout << endl;
	// ============== update weaponList ==============
	for (int i = 0; i < numberWeaponHad; i++)
	{
		if (weaponList[i].type == MELLE)
		{
			weaponList[i].melle.update(renderer,player.f_rect, player.center());
		}
		else {

			weaponList[i].gun.update(renderer,bulletList,lastShotTime, player.f_rect, player.center());
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

	// ============== update danh sách đạn ==============
	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].update();

	// ============= update quadtree =============
	//cout << objects.size() << endl; 
	
	qtree->update(newObjects);
}

void GameState::renderGameLoop()
{

	// xóa render cũ đi
	SDL_RenderClear(renderer);
	m.render(renderer,player);

	// tạo render danh sách đạn
	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].render(renderer);

	// tạo render người chơi
	player.render(renderer);
	
	// tạo render vũ khí
	if(weaponList[curWeapon].type == GUN)
		weaponList[curWeapon].gun.render(renderer, player.f_rect);
	else weaponList[curWeapon].melle.render(renderer, player.f_rect, player.center());
	
	// tạo render quái
	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].render(renderer);


	// render item dropped
	
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].render(renderer, frameCoin);
	}
	


	for (int i = 0; i < bulletsDropped.size(); i++)
		bulletsDropped[i].render(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRectF(renderer, &r[0]);
	SDL_RenderDrawRectF(renderer, &r[1]);
	SDL_RenderDrawRectF(renderer, &r[2]);
	SDL_RenderDrawRectF(renderer, &r[3]);
	SDL_RenderDrawRectF(renderer, &r[4]);
	SDL_RenderDrawRectF(renderer, &r[5]);
	SDL_RenderDrawRectF(renderer, &r[6]);
	SDL_RenderDrawRectF(renderer, &r[7]);
	SDL_RenderDrawRectF(renderer, &r[8]);
	SDL_RenderDrawRectF(renderer, &r[9]);
	SDL_RenderDrawRectF(renderer, &r[10]);

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
	/*while (isGameRunning)
	{*/

		
		int x = enemyList.size();
		
		// collision enemy with enemy
		for (int i = 0; i < x; i++)
		{
			Rectangle range;
			range.x = enemyList[i].getRect().x - enemyList[i].getRect().w/2;
			range.y = enemyList[i].getRect().y - enemyList[i].getRect().h/2;
			range.w = enemyList[i].getRect().w*2;
			range.h = enemyList[i].getRect().h*2;
			//cout << "i = " << i << " range : " << range.x << " " << range.y << " " << range.w << " " << range.h << endl;
			r[i].x = enemyList[i].getRect().x - enemyList[i].getRect().w / 2;
			r[i].y = enemyList[i].getRect().y - enemyList[i].getRect().h / 2;
			r[i].w = enemyList[i].getRect().w * 2;
			r[i].h = enemyList[i].getRect().h * 2;
				
			//cout << "size : " << foundObjects.size() << endl;
			qtree->query(range,foundObjects);
			//cout << objects[0]->f_rect.x << endl;
			//cout << "bug";
			//cout << "new size : " << foundObjects.size() << endl;
			//cout << foundObjects.size() << endl;
			for (int j = 0; j < foundObjects.size(); j++)
			{
				
				//cout << "Object type: " << typeid(*foundObjects[j]).name() << endl;
			//	if (dynamic_cast<Enemy*>(foundObjects[j]) != NULL )
			//	{
			////cout << "bug\n";
			//		// check collision and return result before collision
			//		CircleCollisionDetect(enemyList[i].center(), enemyList[i].getRadius(), enemyList[i].f_rect, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect);
			//	}
			}
			//foundObjects.clear();
		}
		//collisionEnemyWithEnemy(enemyList[i],enemyList[j]);
		
		// va chạm giữa đạn và quái
		//for (int i = 0; i < bulletList.size(); i++)
		//{
		//	for (int j = 0; j < enemyList.size(); j++)
		//	{
		//		// nếu máu quái <= 0 thì xét active về lại false
		//		if (enemyList[j].getHP() <= 0)
		//			enemyList[j].setActive(0);

		//		// kiểm tra va chạm giữa đạn và quái
		//		if (PolygonCollisionDetect(bulletList[i].vertices, bulletList[i].f_rect, enemyList[j].vertices, enemyList[j].f_rect))
		//		{
		//			bulletList[i].setActive(0);
		//			enemyList[j].setHP(enemyList[j].getHP() - weaponList[curWeapon].gun.getDamage());
		//		}
		//	}
		//}
		// va chạm giữa vũ khí và quái
		//if (weaponList[curWeapon].type == MELLE)
		//{
		//	for (int j = 0; j < enemyList.size(); j++)
		//	{
		//		//SDL_FRect x, y;
		//		//x = weaponList[curWeapon].melle.getRect();

		//		//y = enemyList[j].f_rect;

		//		if (enemyList[j].getHP() <= 0)
		//			enemyList[j].setActive(0);

		//		//if (collisionTwoRect(x, y))
		//		//{
		//		//	enemyList[j].setHP(enemyList[j].getHP() - weaponList[curWeapon].melle.getDamage());
		//		//}
		//		if (CirclePolygonCollisionDetectPolygonStatic(weaponList[curWeapon].melle.vertices, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect))
		//		{
		//			enemyList[j].setHP(enemyList[j].getHP() - weaponList[curWeapon].melle.getDamage());
		//		}
		//	}
		//}
		//if (weaponList[curWeapon].type == GUN)
		//{
		//	for (int j = 0; j < enemyList.size(); j++)
		//	{
		//		CirclePolygonCollisionDetectPolygonStatic(weaponList[curWeapon].gun.vertices, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect);
		//	}
		//}
		// Va chạm của người chơi
		// Va chạm giữa người và tiền
		//for (int i = 0; i < coins.size(); i++)
		//{
		//	SDL_FRect x, y;
		//	x = coins[i].f_rect;
		//	y = player.f_rect;
		//	if (collisionTwoRect(x, y))
		//	{
		//		money++;
		//		coins.erase(coins.begin() + i);
		//	}
		//}
		//// Va chạm người chơi và item
		//for (int i = 0; i < bulletsDropped.size(); i++)
		//{
		//	SDL_FRect x, y;
		//	x = bulletsDropped[i].f_rect;
		//	y = player.f_rect;
		//	if (collisionTwoRect(x, y))
		//	{
		//		long long x = weaponList[bulletsDropped[i].getType()].gun.getTotalBullets();
		//		x += 50;
		//		weaponList[bulletsDropped[i].getType()].gun.setTotalBullets(x);
		//		bulletsDropped.erase(bulletsDropped.begin() + i);
		//	}
		//}
		// Va chạm người chơi và quái
		/*for (int i = 0; i < enemyList.size(); i++)
		{
			CirclePolygonCollisionDetectPolygonStatic(player.vertices, enemyList[i].center(), enemyList[i].getRadius(), enemyList[i].f_rect);
		}*/
		// Va chạm người chơi và tường
		
		/*for (int i = 0; i < m.getWall().size(); i++)
		{
			PolygonCollisionDetectOneSatic(m.getWall()[i].vertices, player.vertices, player.f_rect);
			for (int j = 0; j < enemyList.size(); j++)
			{
				CirclePolygonCollisionDetectPolygonStatic(m.getWall()[i].vertices, enemyList[j].center(), enemyList[j].getRadius(), enemyList[j].f_rect);
			}
		}*/

		//cout << m.getWall()[0].vertices[0].x << "\t" << m.getWall()[0].vertices[0].y << endl << endl;
		/*for (int i = 0; i < m.getWall().size(); i++)
		{
		}*/

		//std::unordered_map<FlatVector, std::unordered_set<FlatVector> > collisionMap;

		//for (int i = 0; i < m.getWall().size(); i++)
		//{
		//	FlatVector wallPolygon = m.getWall()[i].vertices;
		//	collisionMap[wallPolygon].insert(player.center());

		//	for (int j = 0; j < enemyList.size(); j++)
		//	{
		//		FlatVector enemyCircle = enemyList[j].center(), enemyCircleRadius = enemyList[j].getRadius();
		//		if (collisionMap.find(wallPolygon) != collisionMap.end() && collisionMap[wallPolygon].find(enemyCircle) != collisionMap[wallPolygon].end())
		//		{
		//			// Có va chạm
		//		}
		//	}
		//}

	//}
}


/**
* Xử lý menu
*/
void GameState::initMenu()
{
	background.init(renderer, "img/background.jpg");
	background.f_rect = { 0,0,1920,1080};

	t_title.init(renderer, "GO TO SCHOOL",92, widthWindow/2 + 100, 179);
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


void GameState::freeAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}