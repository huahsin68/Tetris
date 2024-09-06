#ifndef __GAMELEVEL_H__
#define __GAMELEVEL_H__

#include "HeaderSymbol.h"
#include "Tetrimino.h"
#include "Resource.h"
#include "GameMapHash.h"
#include "BlockWatcher.h"
#include "Preview.h"
#include "Score.h"
#include "Background.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"



class BlockWatcher;
class Tetrimino;
class Preview;

class GameLevel
{
public:
	GameLevel();
	virtual ~GameLevel();

	bool checkBorder(Position);
	void clearGLBuffer();
	virtual void invokeKey(int, bool);
	void destroy(Position);
	void launchGame();
	void matchHorizontal();
	void repositionBlock(Position);
	void repositionMatchCount(int);
	void render();
	void renderGameOverScreen();
	void renderGamePlay();
	void renderMenuScreen();
	void resetPlayer();
	void restartGame();
	inline void resetIdleCnt() {
		idleCnt = 0;
	}
	void transferBlocks();
	bool validatePosition(Position&);
	

private:
	void updateScore();

	
public:
	void setAnimationShader(unsigned int shader) {
		shaderAnimation = shader;
	}
	unordered_map<Position, GameObject*, GameMapHash> getBlocks() {
		return blocks;
	}
	Tetrimino* getPlayer() {
		return player;
	}
	bool getGameOver() {
		return gameOver;
	}
	void setGameOver(bool gameOver) {
		this->gameOver = gameOver;
	}
	void setMultiInstanceShader(unsigned int shader) {
		shaderMultiInstance = shader;
	}
	void setSingleInstanceShader(unsigned int shader) {
		shaderSingleInstance = shader;
	}
	void setScan(bool scan) {
		this->scan = scan;
	}
	void triggerPause() {
		pause = !pause;
	}
	void setDestroyBlock(bool destroyBlock) {
		this->destroyBlock = destroyBlock;
	}


private:
    unsigned int shaderMultiInstance = 0;
	unsigned int shaderSingleInstance = 0;
	unsigned int shaderAnimation = 0;

	Resource* spriteRes = nullptr;

	b2Vec2 gravity;
	b2World *physicWorld = nullptr;

	int timeFrame = 0;

	int desiredFallFPS = 600;  // smaller the number will be faster
	int fallFps = 1000 / desiredFallFPS;

	Score *score = nullptr;
	Preview *next = nullptr;
	Tetrimino *player = nullptr;
	BlockWatcher *blockWatcher = nullptr;
	Background *background = nullptr;
	MenuScreen *menuScreen = nullptr;
	GameOverScreen *gameOverScreen = nullptr;

	unordered_map<Position, GameObject*, GameMapHash> blocks;
	unordered_map<Position, GameObject*, GameMapHash>::iterator gameMapIt;

	list<int> scanPosY;
	map<int, int> matchCount;
	vector<Position> purgeContainer;
	
	int gameOverCnt = 0;
	bool gameOver = false;
	bool scan = false;
	bool destroyBlock = false;
	int idleCnt = 0; // block the move if not moving for 1 sec

	bool pause = false;
	int increaseScore = 0;
	bool matchOnce = false;

	ObjectType objectType;
};

#endif /* __GAMELEVEL_H_ */