#include "GameState.h"

void GameState::initShop()
{
	backgroundShop.init(renderer, "img/backgroundShop.png");
	backgroundShop.f_rect = { (float)widthWindow/2 - 700/2, (float)heightWindow/2 - 700/2,700, 700 };
	shopItem1.init(renderer, "img/ShopItem1.png");
	shopItem1.f_rect = { (float)widthWindow / 2 - 700 / 2 + 100, (float)heightWindow / 2 - 700 / 2 + 150, 220, 220 };
	shopItem2.init(renderer, "img/ShopItem2.png");
	shopItem2.f_rect = { (float)widthWindow / 2 - 700 / 2 + 380, (float)heightWindow / 2 - 700 / 2 + 150, 220, 220 };
	shopItem3.init(renderer, "img/ShopItem3.png");
	shopItem3.f_rect = { (float)widthWindow / 2 - 700 / 2 + 160, (float)heightWindow / 2 - 700 / 2 + 490, 220, 220 };
	shopItem4.init(renderer, "img/ShopItem4.png");
	shopItem4.f_rect = { (float)widthWindow / 2 - 700 / 2 + 380, (float)heightWindow / 2 - 700 / 2 + 430, 220, 220 };
	//skipShop.init(renderer,"skip",32, (float)widthWindow / 2 - 700 / 2 + 380 + 200, (float)heightWindow / 2 - 700 / 2 + 490+220,"font/Minecraft.ttf");

}

void GameState::processShop(SDL_Event& e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LMASK)
		{
			if (isOnShopItem1)
			{
				if (money >= 10)
				{
					weaponList[1].gun.setTotalBullets(weaponList[1].gun.getTotalBullets() + 50);
					money -= 10;
				}
			}
			else if (isOnShopItem2)
			{
				if (money >= 50)
				{
					weaponList[2].gun.setTotalBullets(weaponList[2].gun.getTotalBullets()+50);
					money -= 50;
				}
			}
			else if (isOnShopItem3)
			{
				if (money >= 100)
				{
					weaponList[3].gun.setTotalBullets(weaponList[3].gun.getTotalBullets() + 50);
					money -= 100;
				}
			}
			else if (isOnShopItem4)
			{
				if (player.getHP() < 100 && money >= 200)
				{
					money -= 200;
					player.setHP(player.getHP() + 50);
				}
				if (player.getHP() > 100)
				{
					player.setHP(100);
				}
			}
			//else if (skipShop.getCollision())
			//{
			//	remainingTime = 0;
			//	return;
			//}
		}
	}
}

void GameState::updateShop()
{

	//skipShop.updateText(renderer, skipShop.getColor(RED));
	// Effect item 1
	if (isOnShopItem1)
	{
		shopItem1.f_rect = { (float)widthWindow / 2 - 700 / 2 + 100, (float)heightWindow / 2 - 700 / 2 + 150 - 15, 220, 220 };
	}
	else
	{
		shopItem1.f_rect = { (float)widthWindow / 2 - 700 / 2 + 100, (float)heightWindow / 2 - 700 / 2 + 150, 220, 220 };
	}
	// Effect item 2
	if (isOnShopItem2)
	{
		shopItem2.f_rect = { (float)widthWindow / 2 - 700 / 2 + 380, (float)heightWindow / 2 - 700 / 2 + 150 - 15, 220, 220 };
	}
	else
	{
		shopItem2.f_rect = { (float)widthWindow / 2 - 700 / 2 + 380, (float)heightWindow / 2 - 700 / 2 + 150, 220, 220 };
	}
	// Effect item 3
	if (isOnShopItem3)
	{
		shopItem3.f_rect = { (float)widthWindow / 2 - 700 / 2 + 100, (float)heightWindow / 2 - 700 / 2 + 430 - 15, 220, 220 };
	}
	else
	{
		shopItem3.f_rect = { (float)widthWindow / 2 - 700 / 2 + 100, (float)heightWindow / 2 - 700 / 2 + 430, 220, 220 };
	}
	// Effect item 4
	if (isOnShopItem4)
	{
		shopItem4.f_rect = { (float)widthWindow / 2 - 700 / 2 + 380, (float)heightWindow / 2 - 700 / 2 + 430 - 15, 220, 220 };
	}
	else
	{
		shopItem4.f_rect = { (float)widthWindow / 2 - 700 / 2 + 380, (float)heightWindow / 2 - 700 / 2 + 430, 220, 220 };
	}

	//Update info
	hp.w = (float)player.getHP() / 100 * 181;

	moneyText.init(renderer, to_string(money), 45, 60, 113, "font/Minecraft.ttf");
	moneyText.setText(to_string(money));

	numberbulletTextUSP.init(renderer, " X " + to_string(weaponList[1].gun.getTotalBullets()), 30, 60, 153, "font/Minecraft.ttf");
	numberbulletTextAK.init(renderer, " X " + to_string(weaponList[2].gun.getTotalBullets()), 30, 60, 193, "font/Minecraft.ttf");
	numberbulletTextMP5.init(renderer, " X " + to_string(weaponList[3].gun.getTotalBullets()), 30, 60, 233, "font/Minecraft.ttf");
	numberbulletTextUSP.setText(" X " + to_string(weaponList[1].gun.getTotalBullets()));
	numberbulletTextAK.setText(" X " + to_string(weaponList[2].gun.getTotalBullets()));
	numberbulletTextMP5.setText(" X " + to_string(weaponList[3].gun.getTotalBullets()));

	countdownTimeText.init(renderer, to_string((int)(remainingTime / 1000.0)) + " s", 30, widthWindow / 2 - 15, 100, "font/Minecraft.ttf");
}

void GameState::renderShop()
{
	renderGameLoop();
	backgroundShop.render(renderer);
	shopItem1.render(renderer);
	shopItem2.render(renderer);
	shopItem3.render(renderer);
	shopItem4.render(renderer);
	//skipShop.render(renderer);
	SDL_RenderPresent(renderer);
}

void GameState::collisionShop()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	//if (skipShop.checkCollisonWithMouse(mouseX, mouseY))
	//{
	//	skipShop.setCollision(true);
	//}
	//else {
	//	skipShop.setCollision(false);
	//}
	if (mouseX >= shopItem1.f_rect.x && mouseX <= shopItem1.f_rect.x + shopItem1.f_rect.w
		&& mouseY >= shopItem1.f_rect.y && mouseY <= shopItem1.f_rect.y + shopItem1.f_rect.h)
	{
		isOnShopItem1 = true;
	}
	else
	{
		isOnShopItem1 = false;
	}
	if (mouseX >= shopItem2.f_rect.x && mouseX <= shopItem2.f_rect.x + shopItem2.f_rect.w
		&& mouseY >= shopItem2.f_rect.y && mouseY <= shopItem2.f_rect.y + shopItem2.f_rect.h)
	{
		isOnShopItem2 = true;
	}
	else
	{
		isOnShopItem2 = false;
	}
	if (mouseX >= shopItem3.f_rect.x && mouseX <= shopItem3.f_rect.x + shopItem3.f_rect.w
		&& mouseY >= shopItem3.f_rect.y && mouseY <= shopItem3.f_rect.y + shopItem3.f_rect.h)
	{
		isOnShopItem3 = true;
	}
	else
	{
		isOnShopItem3 = false;
	}
	if (mouseX >= shopItem4.f_rect.x && mouseX <= shopItem4.f_rect.x + shopItem4.f_rect.w
		&& mouseY >= shopItem4.f_rect.y && mouseY <= shopItem4.f_rect.y + shopItem4.f_rect.h)
	{
		isOnShopItem4 = true;
	}
	else
	{
		isOnShopItem4 = false;
	}
}
void GameState::runShop()
{
	SDL_ShowCursor(SDL_ENABLE);
	if (isShopRunning)
	{
		SDL_Event e;
		do 
		{
			currentTime = SDL_GetTicks();
			elapsedTime = currentTime - startTime;
			remainingTime = countdownShopTime > elapsedTime ? countdownShopTime - elapsedTime : 0;
			processShop(e);
			updateShop();
			collisionShop();
			renderShop();
		} while (remainingTime > 0);
		if (enemyList.size() > 0)
		{
			countShop++;
		}
	}
	SDL_ShowCursor(SDL_DISABLE);

}