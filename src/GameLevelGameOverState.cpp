#include <GameLevelGameOverState.h>

GameLevelGameOverState::GameLevelGameOverState()
{
	setState(GameOver);
}

GameLevelGameOverState::GameLevelGameOverState(GameLevel* gameLevel, GameState gameState) : GameLevelState(gameLevel, gameState)
{
}

GameLevelGameOverState::GameLevelGameOverState(GameLevel* gameLevel) : GameLevelState(gameLevel)
{
}

GameLevelGameOverState::~GameLevelGameOverState()
{
}

void GameLevelGameOverState::invokeKey(int key, bool release)
{
	switch(key)
	{
	case 8:
		StateController::stateController->switchState(Play);
		break;
	}
}

void GameLevelGameOverState::render()
{
	gameLevel->renderGameOverScreen();
}

void GameLevelGameOverState::entryState()
{
}

void GameLevelGameOverState::exitState()
{
}
