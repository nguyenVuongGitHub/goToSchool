//#pragma once


#ifndef OBJ_H
#define OBJ_H

#include "Common.h"
#include "FlatVector.h"

using namespace std;
enum Shape {
	nav = 0,
	circle = 1,
	box = 2,
	triangle = 3
};
// abstract class
class Object
{
private:
	Shape shape;
protected:
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect srcRect;
	SDL_FPoint point;
public:
	SDL_FRect f_rect;
	vector<FlatVector> vertices;

	Object()
	{
		shape = nav;
		texture = NULL;
		surface = NULL;
		f_rect = { 0,0,0,0 };
	}
	 ~Object() = default;
	virtual void init(SDL_Renderer* renderer, string pathImg) {

	}
	virtual void render(SDL_Renderer* renderer) {

	}
	SDL_FRect getRect() {
		return f_rect;
	}
	//void setRect(SDL_FRect f_rect) {
	//	this->f_rect = f_rect;
	//}
	/*SDL_Texture* getTexture() {
		return texture;
	}
	vector<FlatVector> getVertives()
	{
		return vertices;
	}*/
};

#endif // !OBJ_H

