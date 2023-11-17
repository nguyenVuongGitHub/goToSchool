#include "Text.h"

Text::Text()
{
	font = NULL;
	surface = NULL;
	texture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	text = "";
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	isCollision = false;
	fontSize = 0;
}

Text::Text(string text, TTF_Font* font)
{
	this->text = text;
	this->font = font;
}

Text::~Text()
{
	/*SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);*/
}

void Text::init(SDL_Renderer* renderer, string text, int fontSize, int x, int y, string fontstr, SDL_Color color)
{
	this->text = text;
	this->font = font;
	rect.x = x;
	rect.y = y;
	this->color = color;
	this->fontSize = fontSize;

	font = TTF_OpenFont(fontstr.c_str(), fontSize);
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	rect.w = surface->w;
	rect.h = surface->h;
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_FreeSurface(surface);

}

void Text::setText(string text)
{
	this->text = text;
}

void Text::setFont(TTF_Font* font)
{
	this->font = font;
}

void Text::setColor(SDL_Color color)
{
	this->color = color;
}

void Text::setCollision(bool x)
{
	isCollision = x;
}

bool Text::getCollision()
{
	return isCollision;
}

void Text::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Text::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

bool Text::checkCollisonWithMouse(int mouseX, int mouseY)
{
	if (mouseX >= rect.x && mouseX <= rect.x + rect.w
		&& mouseY >= rect.y && mouseY <= rect.y + rect.h) {
		return true;
	}
	return false;
}

SDL_Rect Text::getRect()
{
	return rect;
}

void Text::updateText(SDL_Renderer* renderer, SDL_Color color)
{
	if (isCollision)
	{
		setColor(color);
		/*cout << color.r << " " << color.g << " " << color.b << endl;*/
		font = TTF_OpenFont(pathFontMain.c_str(), fontSize);
		surface = TTF_RenderText_Solid(font, text.c_str(), this->color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
	}
	else {

		setColor({255,255,255,255});
		font = TTF_OpenFont(pathFontMain.c_str(), fontSize);
		surface = TTF_RenderText_Solid(font, text.c_str(), this->color);
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
	}
}

void Text::freeData()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
}

SDL_Color Text::getColor(colors c)
{
	switch (c)
	{
	case WHITE:
		return { 255,255,255,255 };
	case BLACK:
		return { 0,0,0,0 };
	case RED:
		return { 255,0,0,0 };
	case GREEN:
		return { 0,255,0,0 };
	case BLUE:
		return { 0,0,255,0 };
	default:
		return { 0,0,0,0 };
	}
}
