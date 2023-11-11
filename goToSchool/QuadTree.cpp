#include "QuadTree.h"

void QuadTree::subdivide()
{
	float x = boundary.x;
	float y = boundary.y;
	float w = boundary.w;
	float h = boundary.h;


	Rectangle ne = { x + w / 2, y - h / 2, w / 2,h / 2 };
	northEast = new QuadTree(capacity, ne);

	Rectangle nw = { x - w / 2, y - h / 2, w / 2,h / 2 };
	northWest = new QuadTree(capacity, nw);

	Rectangle se = { x + w / 2, y + h / 2, w / 2, h / 2 };
	southEast = new QuadTree(capacity, se);

	Rectangle sw = { x - w / 2, y + h / 2, w / 2, h / 2 };
	southWest = new QuadTree(capacity, sw);
	divided = true;
	
	
}

QuadTree::QuadTree()
{
	capacity = 0;
	divided = false;
	northEast = NULL;
	southEast = NULL;
	northWest = NULL;
	southWest = NULL;
}

QuadTree::QuadTree(int capacity, Rectangle boundary)
{
	this->capacity = capacity;
	this->boundary = boundary;
	divided = false;
	northEast = NULL;
	southEast = NULL;
	northWest = NULL;
	southWest = NULL;
}

QuadTree::~QuadTree()
{

}

void QuadTree::update(vector<Object*>& newObjects) {

	// Xóa các đối tượng cũ khỏi QuadTree
	//clear();

	// Cập nhật lại vector objects với các đối tượng mới
	//for (Object* object : newObjects) {
		//insert(object);
	//}
}


void QuadTree::clear() {
	//if (divided) {
	//	// Đảm bảo giải phóng bộ nhớ trong các nút con trước khi xóa chúng
	//	if (northWest != nullptr) {
	//		northWest->clear();
	//		delete northWest;
	//	}
	//	if (northEast != nullptr) {
	//		northEast->clear();
	//		delete northEast;
	//	}
	//	if (southWest != nullptr) {
	//		southWest->clear();
	//		delete southWest;
	//	}
	//	if (southEast != nullptr) {
	//		southEast->clear();
	//		delete southEast;
	//	}

	//	divided = false;
	//}

	//// Giải phóng bộ nhớ của đối tượng trong nút hiện tại
	//for (Object* obj : objects) {
	//	delete obj;
	//}

	//// Xóa tất cả các đối tượng khỏi vector
	//objects.clear();
}

/*
* object ( x,y, object )
*/
bool QuadTree::insert(Object* object)
{
	if (!boundary.contains(object))
	{
		return false;
	}

	if (objects.size() < capacity)
	{
		objects.push_back(object);
		/*cout << objects[0]->f_rect.x << endl;
		cout << objects.size() << endl;*/
		return true;
	}
	if (!divided)
	{
		subdivide();
		
	}
	return (northEast->insert(object) ||
		northWest->insert(object) ||
		southEast->insert(object) ||
		southWest->insert(object));
}

void QuadTree::query(Rectangle& range, vector<Object*>& found)
{
	/*if (northWest == NULL) cout << "nw bug\n";
	if (northEast == NULL) cout << "ne bug\n";
	if (southEast == NULL) cout << "se bug\n";
	if (southWest == NULL) cout << "sw bug\n";*/
	//vector <Object*> found;
	if (!boundary.intersects(range))
	{
		//cout << "not found!\n";
		return;
	}
	else {
		for (int i = 0; i < objects.size(); i++)
		{
			if (range.contains(objects[i]))
			{
				found.push_back(objects[i]);
				cout << "found: " << found.size() << endl;
			}
		}
		if (divided)
		{
			northEast->query(range, found);
			northWest->query(range, found);
			southWest->query(range, found);
			southEast->query(range, found);
		
		}

		
	}
}
