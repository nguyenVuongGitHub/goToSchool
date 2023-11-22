#include "GameState.h"

void GameState::showRank()
{
	vector<InfoPlayer> p = Read_File();
	vector<Text> pRank(p.size());
	vector<Text> pName(p.size());
	vector<Text> pKills(p.size());
	vector<Text> pTime(p.size());
	for (int i = 0; i < p.size(); i++)
	{
		pRank[i].init(renderer, to_string(i+1), 50, 220, 280 + 80 * i, "font/Minecraft.ttf");
		pName[i].init(renderer, p[i].name, 50, 600, 280 + 80 * i);
		pKills[i].init(renderer, to_string(p[i].numberEnemiesDestroyed), 50, 1060, 280 + 80 * i, "font/Minecraft.ttf");
		pTime[i].init(renderer, to_string(p[i].totalTime), 50, 1500, 280 + 80 * i, "font/Minecraft.ttf");
	}
	bool showing = true;
	SDL_Event e; 
	Text rank, name, numberEnemies, time, goBack;
	rank.init(renderer, "Rank", 50, 180, 200);
	name.init(renderer, "Name", 50, 600, 200);
	numberEnemies.init(renderer, "Kills", 50, 1060, 200);
	time.init(renderer, "Time", 50, 1500, 200);
	goBack.init(renderer, "Go Back", 50, 1600, 900);
	while (showing)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
			{
				if (goBack.checkCollisonWithMouse(mouseX, mouseY))
				{
					showing = false;
				}
			}
		}
		SDL_GetMouseState(&mouseX, &mouseY);
		if (goBack.checkCollisonWithMouse(mouseX, mouseY))
		{
			goBack.setCollision(true);
		}
		else
		{
			goBack.setCollision(false);
		}

		SDL_RenderClear(renderer);
		background.render(renderer);
		for (int i = 0; i < p.size(); i++)
		{
			pRank[i].render(renderer);
			pName[i].render(renderer);
			pKills[i].render(renderer);
			pTime[i].render(renderer);
		}
		goBack.updateText(renderer, goBack.getColor(RED));
		rank.render(renderer);
		name.render(renderer);
		numberEnemies.render(renderer);
		time.render(renderer);
		goBack.render(renderer);
		SDL_RenderPresent(renderer);
	}
}