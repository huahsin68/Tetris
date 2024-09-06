/*
 * GameLevelMenuState.cpp
 *
 *  Created on: Mar 31, 2023
 *      Author: kokhoe
 */

#include "GameLevelMenuState.h"
#include "GameLevel.h"

GameLevelMenuState::GameLevelMenuState()
{
	setState(Pause);
}

GameLevelMenuState::GameLevelMenuState(GameLevel* gameLevel, GameState gameState) : GameLevelState(gameLevel, gameState)
{
}

GameLevelMenuState::GameLevelMenuState(GameLevel* gameLevel) : GameLevelState(gameLevel)
{
}

GameLevelMenuState::~GameLevelMenuState()
{
}

void GameLevelMenuState::invokeKey(int key, bool release)
{
	switch(key)
	{
	case 6:
		StateController::stateController->switchState(Play);
		break;
	}
}

void GameLevelMenuState::render()
{
	gameLevel->renderMenuScreen();
}

void GameLevelMenuState::entryState()
{
}

void GameLevelMenuState::exitState()
{
}
