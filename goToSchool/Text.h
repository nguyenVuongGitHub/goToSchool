
#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Common.h"

enum colors
{
	WHITE,BLACK,RED,GREEN,BLUE
};


using namespace std;

class Text
{
private:
	TTF_Font* font;
	SDL_Color color;
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
	string text;
	string pathFontMain = "font/Anothershabby_trial.ttf";
	bool isCollision;
	int fontSize;
public:
	Text();
	Text(string text, TTF_Font* font);
	~Text();
	void init(SDL_Renderer* renderer, string text, int fontSize, int x, int y, string fontstr = "font/Anothershabby_trial.ttf", SDL_Color color = { 255,255,255,255 });
	void setText(string text);
	void setFont(TTF_Font* font);
	void setColor(SDL_Color color);
	SDL_Color getColor(colors c);
	void setCollision(bool x);
	bool getCollision();
	void render(SDL_Renderer* renderer);
	void setPosition(int x, int y);
	bool checkCollisonWithMouse(int mouseX, int mouseY);
	SDL_Rect getRect();
	void updateText(SDL_Renderer* renderer, SDL_Color color);
	void freeData();
};
#endif // !TEXT_H

