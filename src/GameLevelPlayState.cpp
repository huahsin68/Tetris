#include <GameLevelPlayState.h>


GameLevelPlayState::GameLevelPlayState()
{
	setState(Play);
}

GameLevelPlayState::GameLevelPlayState(GameLevel* gameLevel, GameState gameState) : GameLevelState(gameLevel, gameState)
{
}

GameLevelPlayState::GameLevelPlayState(GameLevel* gameLevel) : GameLevelState(gameLevel)
{
}

GameLevelPlayState::~GameLevelPlayState()
{
}

void GameLevelPlayState::invokeKey(int key, bool release)
{
	int ret = 0;

	switch(key)
	{
	// left
	case 1:
		if( !gameLevel->getPlayer()->checkCollision(Left) )
			gameLevel->getPlayer()->signalDirection({-0.25f, 0.f});
		break;

	// right
	case 2:
		if( !gameLevel->getPlayer()->checkCollision(Right) )
			gameLevel->getPlayer()->signalDirection({0.25f, 0.f});
		break;

	// down
	case 3:
		if( !gameLevel->getPlayer()->checkCollision(Down) )
			gameLevel->getPlayer()->signalDirection({0.f, 0.095f});		
		break;

	// spacebar
	case 4:
		if( !gameLevel->getPlayer()->rotateCollision() )
			gameLevel->getPlayer()->rotate();
		break;

	// pause
	case 5:
		gameLevel->triggerPause();
		break;
	}
}

void GameLevelPlayState::render()
{
	gameLevel->renderGamePlay();
}

void GameLevelPlayState::entryState()
{
	gameLevel->resetPlayer();
}

void GameLevelPlayState::exitState()
{
	// freeze paddle when play state is exit
	ready = true;
	gameLevel->restartGame();
}
