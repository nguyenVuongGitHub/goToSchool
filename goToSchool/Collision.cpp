#include "GameState.h"


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
	r2.x += normal.x * depth;
	r2.y += normal.y * depth;

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