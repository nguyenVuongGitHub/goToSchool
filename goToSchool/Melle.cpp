#include "Melle.h"

void Melle::attack(int curXMouse , float centerPlayer)
{

}
void Melle::reset()
{
	vertices.clear();
}
void Melle::init(SDL_Renderer* renderer, string pathImg)
{
	surface = IMG_Load(pathImg.c_str());
	texture = SDL_CreateTextureFromSurface(renderer,surface);

	f_rect = { 0,0,64,10 };
	vertices.push_back({ f_rect.x, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y });
	vertices.push_back({ f_rect.x + f_rect.w, f_rect.y + f_rect.h });
	vertices.push_back({ f_rect.x, f_rect.y + f_rect.h });

}

void Melle::render(SDL_Renderer* renderer, const SDL_FRect& rectPlayer, const FlatVector &centerPlayer)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
	point = { 0, 0};
	if (curXMouse <= centerPlayer.x)
	{
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, &point, SDL_FLIP_VERTICAL);
	}
	else
	{
		SDL_RenderCopyExF(renderer, texture, NULL, &f_rect, angle, &point, SDL_FLIP_NONE);
	}

}

void Melle::update(SDL_Renderer* renderer, const SDL_FRect &rectPlayer , const FlatVector &centerPlayer, float scrollX, float scrollY)
{
	int curXMouse, curYMouse;
	SDL_GetMouseState(&curXMouse, &curYMouse);
	//Updating rect as default
	f_rect = { centerPlayer.x,centerPlayer.y,64,10 };
	//Updating vertices
	vertices[0] = { f_rect.x, f_rect.y };
	vertices[1] = { f_rect.x + f_rect.w, f_rect.y };
	vertices[2] = { f_rect.x + f_rect.w, f_rect.y + f_rect.h };
	vertices[3] = { f_rect.x, f_rect.y + f_rect.h };
	if (!isAttack)
	{
		float deltaX = curXMouse - centerPlayer.x + scrollX;
		float deltaY = curYMouse - centerPlayer.y + scrollY;
		// tính góc giữa người chơi và chuột, and also convert radians to degrees
		angle = atan2(deltaY, deltaX) * 180 / M_PI;
	}
	//Tranforming position from rotation
	vertices[0] = vertices[0].ClockwiseTransform(centerPlayer, angle);
	vertices[1] = vertices[1].ClockwiseTransform(centerPlayer, angle);
	vertices[2] = vertices[2].ClockwiseTransform(centerPlayer, angle);
	vertices[3] = vertices[3].ClockwiseTransform(centerPlayer, angle);
	//cout << centerPlayer.x << "\t" << centerPlayer.y << endl;
	//cout << vertices[0].x << "\t" << vertices[0].y << endl;

	//attack(curXMouse,centerPlayer.x);
}
