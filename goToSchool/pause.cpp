#include "GameState.h"

void GameState::initPauseGame()
{
	SDL_ShowCursor(SDL_ENABLE);
	isPauseGameRunning = true;
	isReturnMenu = false;
	isContinueGame = false;
	backgroundPauseGame.init(renderer, "img/backgroundPause.png");
	backgroundPauseGame.f_rect = { (float)widthWindow / 2 - 700 / 2, (float)heightWindow / 2 - 700 / 2,700, 700 };
	titlePause.init(renderer, "PAUSE", 50, (float)widthWindow / 2 - 700 + 640, (float)heightWindow / 2 - 700 / 2 + 35, "font/Minecraft.ttf");
	continuePause.init(renderer, "CONTINUE", 45, (float)widthWindow / 2 - 700 + 605, (float)heightWindow / 2 - 700 / 2 + 235, "font/Minecraft.ttf");
	returnPause.init(renderer, "RETURN MENU", 45, (float)widthWindow / 2 - 700 + 560, (float)heightWindow / 2 - 700 / 2 + 435, "font/Minecraft.ttf");

}

void GameState::processInputPauseGame(SDL_Event &e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
		{
			if (returnPause.getCollision())
			{
				isGameRunning = false;
				isPauseGameRunning = false;
				isReturnMenu = true;
			}
			else if (continuePause.getCollision())
			{
				isPauseGameRunning = false;
				isContinueGame = true;
			}
		}
	}
}

void GameState::renderPauseGame()
{
	//renderGameLoop();
	backgroundPauseGame.render(renderer);
	titlePause.render(renderer);
	continuePause.render(renderer);
	returnPause.render(renderer);
	SDL_RenderPresent(renderer);
}

void GameState::updatePauseGame()
{
	continuePause.updateText(renderer, continuePause.getColor(RED),"font/Minecraft.ttf");
	returnPause.updateText(renderer, returnPause.getColor(RED), "font/Minecraft.ttf");
}

void GameState::collisionPauseGame()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (returnPause.checkCollisonWithMouse(mouseX, mouseY))
		returnPause.setCollision(true);
	else if (continuePause.checkCollisonWithMouse(mouseX, mouseY))
		continuePause.setCollision(true);
	else
	{
		returnPause.setCollision(false);
		continuePause.setCollision(false);
	}
}

void GameState::runPauseGame()
{
	initPauseGame();
	SDL_Event e;
	while (isPauseGameRunning)
	{
		processInputPauseGame(e);

		updatePauseGame();

		collisionPauseGame();

		renderPauseGame();

	}
}