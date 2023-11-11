#ifndef QUADTREE_H
#define QUADTREE_H
#include <SDL.h>
#include <vector>
#include "Obj.h"
using namespace std;
class Rectangle {
public:
	float x, y, w, h;
	Rectangle()
	{
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
	Rectangle(float x, float y, float w, float h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	bool contains(Object* object)
	{
		return (object->f_rect.x >= this->x - this->w &&
			object->f_rect.x <= this->x + this->w &&
			object->f_rect.y >= this->y - this->h &&
			object->f_rect.y <= this->y + this->h

			);
	}
	bool intersects(Rectangle &range)
	{
		//cout << range.x << " " << range.w << " " << x  << " " << w << endl;
		return !(range.x - range.w >= x + w ||
			range.x + range.w <= x - w ||
			range.y - range.h >= y + h ||
			range.y + range.h <= y - h
			);
	}
};
class QuadTree
{
private:
	bool divided;
	int capacity;
	Rectangle boundary;
	vector<Object*> objects;
	void subdivide();
	QuadTree* northWest;
	QuadTree* northEast;
	QuadTree* southWest;
	QuadTree* southEast;
public:
	vector<Object*> getObj() { return objects; }
	QuadTree();
	QuadTree(int capacity, Rectangle boundary);
	~QuadTree();
	void update(vector<Object*>& newObjects);
	void clear();
	bool insert(Object* object);
	void query(Rectangle& range,vector<Object*>& found);
	
};

#endif // !QUADTREE_H



