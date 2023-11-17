#include "GameState.h"


void GameState::initMenu()
{
	background.init(renderer, "img/background.jpg");
	background.f_rect = { 0,0,1920,1080 };
	t_title.init(renderer, "GO TO SCHOOL", 92, widthWindow / 2 - (674 / 2), 179);
	t_play.init(renderer, "PLAY", 52, 881, 369);
	t_shop.init(renderer, "SHOP", 52, 881, 559);
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
			else if (t_shop.getCollision())
			{
				// do something
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
	t_shop.updateText(renderer, t_play.getColor(RED));
	t_exit.updateText(renderer, t_play.getColor(RED));

}
void GameState::renderMenu()
{
	SDL_RenderClear(renderer);

	background.render(renderer);
	t_title.render(renderer);
	t_play.render(renderer);
	t_shop.render(renderer);
	t_exit.render(renderer);

	SDL_RenderPresent(renderer);
}
void GameState::cleanRenderMenu()
{

}
void GameState::collisionMenu()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (t_play.checkCollisonWithMouse(mouseX, mouseY))
		t_play.setCollision(true);
	else if (t_shop.checkCollisonWithMouse(mouseX, mouseY))
		t_shop.setCollision(true);
	else if (t_exit.checkCollisonWithMouse(mouseX, mouseY))
		t_exit.setCollision(true);
	else
	{
		t_play.setCollision(false);
		t_shop.setCollision(false);
		t_exit.setCollision(false);
	}
}