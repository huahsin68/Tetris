#include "MenuScreen.h"

MenuScreen::MenuScreen() : Screen()
{
	res = new Resource(RES_PATH + "menu.png", true);
}

MenuScreen::~MenuScreen()
{
}
