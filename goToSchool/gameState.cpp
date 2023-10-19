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
	lastShotTime(0)
{}

void GameState::init()
{
	widthWindow = 1080;
	heightWindow = 1920;
	mouseX = 0;
	mouseY = 0;
	isGameRunning = 1;
	window = SDL_CreateWindow("game test", 0, 0, widthWindow, heightWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	IMG_Init(IMG_INIT_PNG);

	numberWeaponHad = 3;
	curWeapon = 0;

	player.init(renderer, "img/tamGiac.png");
	weaponList[0].init(renderer,"img/USP.png" , USP);
	weaponList[1].init(renderer,"img/AK.png" , AK_47 );
	weaponList[2].init(renderer, "img/MP5.png", MP5);

}

void GameState::run()
{
	init();

	SDL_Event e;
	while (isGameRunning)
	{
		processInput(e);

		collision();
		
		update();
		
		render();
		
		cleanRender();
	}
	freeAll();
}
void GameState::processInput(SDL_Event &e)
{

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			isGameRunning = 0;

		if (e.key.keysym.sym == SDLK_ESCAPE)
			isGameRunning = 0;

		if (e.type == SDL_KEYDOWN)
		{
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
		if (e.type == SDL_KEYUP)
		{
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
		//bắt sự kiện giữ chuột
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
			player.setIsAttack(true);

		if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LMASK)
			player.setIsAttack(false);

		 //kiểm tra sự kiện lăn chuột
		if (!player.getIsAttack() && e.type == SDL_MOUSEWHEEL) {
			int scrollDirection = e.wheel.y;
			if (scrollDirection > 0) {
				curWeapon--;	
				if (curWeapon < 0)
					curWeapon = numberWeaponHad;
			}
			else if (scrollDirection < 0) {
				curWeapon++;
				if (curWeapon > numberWeaponHad)
					curWeapon = 0;

			}
		}
	}
}
void GameState::update()
{
	player.update(weaponList[curWeapon]);
	
	if (enemyList.size() < 10)
	{
		Enemy e;
		e.init(renderer,"img/ball.png");
		enemyList.push_back(e);
	}

	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].update(player);


	for (int i = 0; i < numberWeaponHad; i++)
		weaponList[i].update(renderer,bulletList,player,lastShotTime);
	

	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].update();
}
void GameState::render()
{
	SDL_RenderClear(renderer);

	for (int i = 0; i < bulletList.size(); i++)
		bulletList[i].render(renderer);

	player.render(renderer);
	
	weaponList[curWeapon].render(renderer, player);

	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].render(renderer);


	SDL_RenderPresent(renderer);
}
void GameState::cleanRender()
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		if (!bulletList[i].getActive()) {
			bulletList[i].setActive(false);
			bulletList.erase(bulletList.begin() + i);
		}
	}
	for (int i = 0; i < enemyList.size(); i++)
		enemyList[i].freeRender(enemyList,i);
}
void GameState::collision()
{
	int x = enemyList.size();

	// va chạm giữa quái và quái 
	for (int i = 0; i < x-1; i++)
		for (int j = i + 1; j < enemyList.size(); j++)
			collisionEnemyWithEnemy(enemyList[i],enemyList[j]);
		
	// va chạm giữa đạn và quái
	for (int i = 0; i < bulletList.size(); i++)
	{
		for (int j = 0; j < enemyList.size(); j++)
		{
			SDL_FRect x,y;
			x = bulletList[i].getRect();
			y = enemyList[j].getRect();

			if (enemyList[j].getHP() <= 0)
				enemyList[j].setActive(0);

			if (collisionBulletWithEnemy(x, y))
			{
				bulletList[i].setActive(0);
				enemyList[j].setHP(enemyList[j].getHP() - weaponList[curWeapon].getDamage());
				
			}
		}
	}

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
	x1 = p.getRect().x;
	x2 = obj.getRect().x;
	y1 = p.getRect().y;
	y2 = obj.getRect().y;
	x1 -= normal.x * depth / 2;
	y1 -= normal.y * depth / 2;
	x2 += normal.x * depth / 2;
	y2 += normal.y * depth / 2;
	p.setRect({ x1,y1,p.getRect().w,p.getRect().h });
	obj.setRect({ x2,y2,obj.getRect().w,obj.getRect().h });
	/*p.getRect().x -= 
	p.getRect().y -= 
	obj.getRect().x += 
	obj.getRect().y += */

	return true;
}
bool GameState::collisionBulletWithEnemy(SDL_FRect& r1, SDL_FRect& r2)
{
	return (r1.x + r1.w >= r2.x && r2.x + r2.w >= r1.x
		&& r1.y + r1.h >= r2.y && r2.y + r2.h >= r1.y);
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
void GameState::freeAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}