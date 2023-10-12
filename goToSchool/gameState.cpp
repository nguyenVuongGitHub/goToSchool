#include "GameState.h"

GameState::GameState() :

	heightWindow(0),
	widthWindow(0),
	mouseX(0),
	mouseY(0),
	window(NULL),
	renderer(NULL),
	isGameRunning(0),
	holdMouse(0)
{}

void GameState::init()
{
	heightWindow = 1080;
	widthWindow = 1920;
	mouseX = 0;
	mouseY = 0;
	isGameRunning = 1;
	window = SDL_CreateWindow("game test", 0, 0, widthWindow, heightWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	holdMouse = 0;
	IMG_Init(IMG_INIT_PNG);
}
void GameState::gameLoop()
{
	// object
	Player player;
	player.init(renderer);

	vector<Enemy> ListEnemy;
	
	// declare list weapon
	vector<Bullet> ListBullet;
	player.weapon[USP].type = USP;
	player.weapon[AK_47].type = AK_47;
	player.weapon[MP5].type = MP5;
	player.weapon[USP].init();
	player.weapon[AK_47].init();
	player.weapon[MP5].init();


	int curWeapon = 0;
	int countDistance = 0;

	if (ListEnemy.size() <= 10)
	{
		//newEnemy.spawn(heightWindow, widthWindow);
	}


	Uint32 last_shot_time = 0;
	SDL_Event e;
	while (isGameRunning)
	{
		// tắt con trỏ chuột
		//SDL_ShowCursor(SDL_DISABLE);

		//frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				isGameRunning = 0;

			if (e.key.keysym.sym == SDLK_ESCAPE)
				isGameRunning = 0;

			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_a)
					player.moveKey[LEFT] = true;

				else if (e.key.keysym.sym == SDLK_d)
					player.moveKey[RIGHT] = true;

				else if (e.key.keysym.sym == SDLK_w)
					player.moveKey[UP] = true;

				else if (e.key.keysym.sym == SDLK_s)
					player.moveKey[DOWN] = true;

				else if (e.key.keysym.sym == SDLK_LSHIFT)
					player.moveKey[SLOW] = true;

				else if (e.key.keysym.sym == SDLK_SPACE)
					player.moveKey[FAST] = true;
			}
			if (e.type == SDL_KEYUP)
			{
				if (e.key.keysym.sym == SDLK_a)
					player.moveKey[LEFT] = false;

				else if (e.key.keysym.sym == SDLK_d)
					player.moveKey[RIGHT] = false;

				else if (e.key.keysym.sym == SDLK_w)
					player.moveKey[UP] = false;

				else if (e.key.keysym.sym == SDLK_s)
					player.moveKey[DOWN] = false;

				else if (e.key.keysym.sym == SDLK_LSHIFT)
					player.moveKey[SLOW] = false;

				else if (e.key.keysym.sym == SDLK_SPACE)
					player.moveKey[FAST] = false;
			}
			//bắt sự kiện giữ chuột
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
				holdMouse = true;

			if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LMASK)
				holdMouse = false;

			// kiểm tra sự kiện lăn chuột
			if (e.type == SDL_MOUSEWHEEL) {
				int scrollDirection = e.wheel.y;
				if (scrollDirection > 0) {
						curWeapon++;
					if (curWeapon > 2)
						curWeapon = 0;
				}
				else if (scrollDirection < 0) {
						curWeapon--;
					if (curWeapon < 0)
						curWeapon = 2;

				}
			}
			
		}

		if(ListEnemy.size() <= 10)
		{
			Enemy newEnemy;
			newEnemy.init(renderer);
			newEnemy.spawn(heightWindow, widthWindow);
			ListEnemy.push_back(newEnemy);
		}

		// process
			for (int i = 0; i < ListEnemy.size()-1; i++)
			{
				for (int j = i + 1; j < ListEnemy.size(); j++)
				{
					playerCollisionDetect(ListEnemy[i], ListEnemy[j]);
				}
			}

		for (int i = 0; i < ListBullet.size(); i++)
		{
			for (int j = 0; j < ListEnemy.size(); j++)
			{
				if (ListEnemy[j].hp <= 0)
					ListEnemy[j].active = 0;

				
				if (checkCollesion(ListBullet[i].r, ListEnemy[j].r))
				{
					ListBullet[i].active = 0;
					ListEnemy[j].hp -= player.weapon[curWeapon].damage;
				}

			}
		}
			//UpdateGmae
			//if (transformUpdateRequired)
			//{
			//	//update vertices
			//	for (int i = 0; i < player.vertices.size(); i++)
			//	{
			//		player.transformVertices[i] = player.vertices[i].Transform(player.center, player.angle);
			//	}
			//	transformUpdateRequired = false;
			//	player.angle = (int)player.angle % 90;
			//}

			//move
			player.move();

		//acttack
	// Kiểm tra nếu chuột đang được giữ
		if (holdMouse)
		{
			// Lấy thời gian hiện tại tính bằng mili giây
			Uint32 current_time = SDL_GetTicks();

			// Tính thời gian đã trôi qua kể từ lần bắn trước đó
			Uint32 time_since_last_shot = current_time - last_shot_time;

			// Kiểm tra nếu đã đủ thời gian trôi qua từ lần bắn trước đó (200 mili giây)
			if (time_since_last_shot >= 200) {
				// Giảm số lượng đạn còn lại của vũ khí hiện tại
				player.weapon[curWeapon].totalBullets--;

				// Bắn vũ khí bằng cách gọi hàm shoot với các tham số cần thiết
				player.weapon[curWeapon].shoot(renderer, ListBullet, player.r.x, player.r.y, heightWindow, widthWindow);

				// Cập nhật thời gian bắn cuối cùng thành thời gian hiện tại
				last_shot_time = current_time;
			}
		}


		SDL_RenderClear(renderer);
		player.draw(renderer);

		//vẽ viên đạn và di chuyển đạn trong danh sách đạn
		for (int i = 0; i < ListBullet.size(); i++)
		{
			ListBullet[i].draw(renderer);
			ListBullet[i].move();
		}
		for (int i = 0; i < ListEnemy.size(); i++)
		{
			ListEnemy[i].setTargetToPlayer(player);
			ListEnemy[i].draw(renderer);
			ListEnemy[i].move();
		}
		SDL_RenderPresent(renderer);

		// xóa viên đạn ra khỏi danh sách nếu như viên đạn không còn hoạt động (active = 0)
		for (int i = 0; i < ListBullet.size(); i++)
			if (!ListBullet[i].active)
				ListBullet.erase(ListBullet.begin() + i);


		 //xóa quái ra khỏi danh sách nếu viên đạn chạm quái 
		for (int i = 0; i < ListEnemy.size(); i++)
			if (!ListEnemy[i].active)
				ListEnemy.erase(ListEnemy.begin() + i);
		
	}
}
bool GameState::checkCollesion(SDL_FRect &r1, SDL_FRect &r2)
{
	return (r1.x + r1.w >= r2.x && r2.x + r2.w >= r1.x
		&& r1.y + r1.h >= r2.y && r2.y + r2.h >= r1.y);
}
void GameState::collesion()
{
}

FlatVector FindArithmeticMean(std::vector<FlatVector> vertices)
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

bool GameState::playerCollisionDetect(Enemy &p, Enemy& obj)
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
	
	p.r.x -= normal.x * depth/2;
	p.r.y -= normal.y * depth/2;
	obj.r.x += normal.x * depth/2;
	obj.r.y += normal.y * depth/2;
	
	return true;
}

void GameState::freeAll()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}