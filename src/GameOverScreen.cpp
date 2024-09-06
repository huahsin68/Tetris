#include "GameOverScreen.h"

GameOverScreen::GameOverScreen() : Screen()
{
	res = new Resource(RES_PATH + "gameover.png", true);
}

GameOverScreen::~GameOverScreen()
{
}

