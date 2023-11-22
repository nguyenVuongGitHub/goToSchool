#include "GameState.h"

void GameState::runEndGame()
{
	initEndGame();
	SDL_Event e;
	while (isEndGameRunning)
	{
		processInputEndGame(e);

		updateEndGame();

		collisionEndGame();

		renderEndGame();

	}
}

void GameState::initEndGame()
{
	isEndGameRunning = true;
	endMusic();
	backgroundEndGame.init(renderer, "img/background.jpg");
	backgroundEndGame.f_rect = { 0,0,2910,1080 };
	titleEndGame.init(renderer, "GAME OVER", 92, widthWindow / 2 - (674 / 2), 179,"font/Minecraft.ttf");
	numberEnemyDestroyed.init(renderer, "Number enemy detroyed: " + to_string(numberEnemyDes), 52, 500, 369, "font/Minecraft.ttf");
	totalTimeText.init(renderer, "Total time : " + to_string( (int) ( (totalTime - countdownTime) / 1000.0) ) + " s", 52, 500, 559, "font/Minecraft.ttf");
	playAgainText.init(renderer, "PLAY AGAIN", 52, 350, 700, "font/Minecraft.ttf");
	returnMenu.init(renderer, "EXIT TO MENU", 52, 750, 700, "font/Minecraft.ttf");
	// Gọi hàm Write_File để ghi thông tin vào tệp tin
	Write_File(numberEnemyDes, (int)((totalTime - countdownTime) / 1000.0), player.name);

}

void GameState::processInputEndGame(SDL_Event& e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
		{
			if (playAgainText.getCollision())
			{
				isGameRunning = true;
				isEndGameRunning = false;
			}
			else if (returnMenu.getCollision())
			{
				opMusic();
				isEndGameRunning = false;
				return;
			}
		}
	}
}

void GameState::updateEndGame()
{
	playAgainText.updateText(renderer, playAgainText.getColor(RED));
	returnMenu.updateText(renderer, returnMenu.getColor(RED));
}

void GameState::renderEndGame()
{
	SDL_RenderClear(renderer);

	backgroundEndGame.render(renderer);
	titleEndGame.render(renderer);
	numberEnemyDestroyed.render(renderer);
	totalTimeText.render(renderer);
	playAgainText.render(renderer);
	returnMenu.render(renderer);
	
	SDL_RenderPresent(renderer);
}

void GameState::collisionEndGame()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (returnMenu.checkCollisonWithMouse(mouseX, mouseY))
	{
		returnMenu.setCollision(true);
	}
	else if (playAgainText.checkCollisonWithMouse(mouseX, mouseY))
		playAgainText.setCollision(true);
	else
	{
		returnMenu.setCollision(false);
		playAgainText.setCollision(false);
	}
}

void GameState::initMenu()
{
	opMusic();
	background.init(renderer, "img/background.jpg");
	background.f_rect = { 0,0,1920,1080 };
	t_title.init(renderer, "GO TO SCHOOL", 92, widthWindow / 2 - (674 / 2), 179);
	t_play.init(renderer, "PLAY", 52, 881, 369);
	t_ranking.init(renderer, "RANK", 52, 881, 559);
	t_exit.init(renderer, "EXIT", 52, 881, 749);

}
void GameState::processInputMenu(SDL_Event& e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
		{
			if (t_play.getCollision())
			{
				runGameLoop();
			}
			else if (t_ranking.getCollision())
			{
				showRank();
			}
			else if (t_exit.getCollision())
			{
				isMenuRunning = false;
			}

		}
	}
}
void GameState::updateMenu()
{
	t_play.updateText(renderer, t_play.getColor(RED));
	t_ranking.updateText(renderer, t_play.getColor(RED));
	t_exit.updateText(renderer, t_play.getColor(RED));

}
void GameState::renderMenu()
{
	SDL_RenderClear(renderer);

	background.render(renderer);
	t_title.render(renderer);
	t_play.render(renderer);
	t_ranking.render(renderer);
	t_exit.render(renderer);

	SDL_RenderPresent(renderer);
}
void GameState::collisionMenu()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (t_play.checkCollisonWithMouse(mouseX, mouseY))
		t_play.setCollision(true);
	else if (t_ranking.checkCollisonWithMouse(mouseX, mouseY))
		t_ranking.setCollision(true);
	else if (t_exit.checkCollisonWithMouse(mouseX, mouseY))
		t_exit.setCollision(true);
	else
	{
		t_play.setCollision(false);
		t_ranking.setCollision(false);
		t_exit.setCollision(false);
	}
}