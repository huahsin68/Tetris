#include <GameLevelState.h>

GameLevelState::GameLevelState()
{
	// default to play state
	gameState = Start;
}

GameLevelState::GameLevelState(GameState gameState)
{
	this->gameState = gameState;
}

GameLevelState::GameLevelState(GameLevel *gameLevel, GameState gameState) : GameLevelState(gameState)
{
	this->gameLevel = gameLevel;
}

GameLevelState::GameLevelState(GameLevel *gameLevel)
{
	this->gameLevel = gameLevel;
}

GameLevelState::~GameLevelState()
{
}

