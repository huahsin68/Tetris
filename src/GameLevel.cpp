#include "GameLevel.h"
#include "StateController.h"
#include "Background.h"
#include "TetriminoI.h"
#include "TetriminoT.h"
#include "TetriminoJ.h"
#include "TetriminoL.h"
#include "TetriminoO.h"
#include "TetriminoS.h"
#include "TetriminoZ.h"


StateController* StateController::stateController = StateController::getInstance();

GameLevel::GameLevel()
{
	gravity.x = 0;
	gravity.y = 0;

	physicWorld = new b2World(gravity);
	blockWatcher = new BlockWatcher(this);

	StateController::stateController->initState(this);
	
	int random = rand()/(RAND_MAX/(6-0));
	objectType = static_cast<ObjectType>(static_cast<int>(random));
}

GameLevel::~GameLevel()
{
}

bool GameLevel::checkBorder(Position search)
{
	gameMapIt = blocks.find(search);	
	if( gameMapIt != blocks.end() || (search.x < 0 || search.x > 8) ) {
		return true;
	}

	return false;
}

void GameLevel::clearGLBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	glutPostRedisplay();
}

void GameLevel::destroy(Position search)
{
	gameMapIt = blocks.find(search);
	if( gameMapIt != blocks.end() ) {
		Block* found = static_cast<Block*>(blocks[search]);

		found->setTriggerAnimation(true);
		found->registerWatcher(blockWatcher);
	}
}

void GameLevel::invokeKey(int key, bool release)
{
	StateController::stateController->getCurrentState()->invokeKey(key, release);
}

void GameLevel::launchGame()
{
	background = new Background();
	background->create(shaderSingleInstance);

	score = new Score();
	score->create(shaderSingleInstance);

	menuScreen = new MenuScreen();
	menuScreen->create(shaderSingleInstance);

	gameOverScreen = new GameOverScreen();	
	gameOverScreen->create(shaderSingleInstance);

	StateController::stateController->switchState(Start);
}

void GameLevel::matchHorizontal()
{
	if( scan == true ) {
		// scan weather the rows are fill?
		for( auto const& x : matchCount ) {
			// destroy the row when row are filled
			if( x.second == 9 ) {
				destroyBlock = true;

				matchCount[x.first] = 0;

				for( int i=0; i<9; i++ )
					destroy({i, x.first});

				repositionMatchCount(x.first);

				blockWatcher->queueRow(x.first);
				
				increaseScore++;
			}
		}

		scanPosY.clear();

		scan = false;
	}
}

void GameLevel::render()
{
	StateController::stateController->getCurrentState()->render();

	glutPostRedisplay();
}

void GameLevel::renderGameOverScreen()
{
	glUseProgram(shaderSingleInstance);

	gameOverScreen->draw();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameLevel::renderGamePlay()
{
	static int lastTime = 0;

	int actTime = glutGet(GLUT_ELAPSED_TIME);
	int interval = actTime - lastTime;
	lastTime = actTime;

	timeFrame += interval;

	if( !gameOver ) {
		if (timeFrame > (1000 / fallFps) && !pause) {
			if( !player->checkCollision(Down) )
				player->signalDirection({0.f, 0.095f});

			if( idleCnt > 0 ) {
				transferBlocks();
				idleCnt = 0;
			}

			idleCnt++;
			timeFrame = 0;
		}
	}

	glUseProgram(shaderAnimation);

	if( player != nullptr && !gameOver && !destroyBlock) {
		player->draw();

		if( player->getDispose() == true )
			resetPlayer();
	}

	for (auto i : blocks) {
		Block* b = static_cast<Block*>(i.second);
		b->draw();
		b->updateObjectPosition(false);
	}

	next->draw();

	glUseProgram(shaderSingleInstance);

	score->draw();
	background->draw();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	blockWatcher->purgeBlock();

	// if there is a match, stop the player
	matchHorizontal();

	// update score after OpenGL reset command
	updateScore();
}

void GameLevel::renderMenuScreen()
{
	glUseProgram(shaderSingleInstance);

	menuScreen->draw();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void GameLevel::restartGame()
{
	clearGLBuffer();

	idleCnt = -1;
	gameOver = false;

	if( player != nullptr ) {
		list<GameObject*> tmpList = player->getBlocks();

		for (list<GameObject*>::iterator it = tmpList.begin(); it != tmpList.end(); it++) {
			Block *tmp = static_cast<Block*>((GameObject*)*it);
			tmp->setDispose(true);
		}

		player->deleteBlocks();
		delete player;
	}

	for (auto i : blocks) {
		Block* b = static_cast<Block*>(i.second);
		b->setDispose(true);
	}

	blocks.clear();
}

void GameLevel::repositionBlock(Position position)
{
	unordered_map<Position,GameObject*,GameMapHash>::iterator prevBlockKey;
	Position preKey(position.x, position.y);
	prevBlockKey = blocks.find(preKey);
	
	// lookup for the upper block
	int x = (int)position.x;
	int y = (int)position.y - 1;

	// bail if reach at top edge
	if( y < -1 )
		return;

	Position search(x,y);
	gameMapIt = blocks.find(search);
	if( gameMapIt != blocks.end() ) {
		Block* found = static_cast<Block*>(gameMapIt->second);

		found->moveDown();
		
		// take current block assign into prev key
		blocks[preKey] = gameMapIt->second;
	}
	// delete the last block from the map
	else {
		// return to original position (self block) for deletion
		Position delPosition(x, y+1);
		
		gameMapIt = blocks.find(delPosition);
		if( gameMapIt != blocks.end() ) {
			blocks.erase(delPosition);
		}

		if( delPosition.y == 0 ) {
			gameOverCnt++;

			if( gameOverCnt == 9 ) {
				gameOver = false;
				gameOverCnt = 0;
			}
		}
	}

	repositionBlock({x, y});
}

void GameLevel::repositionMatchCount(int rowId)
{
	int index = 0;

	// reposition score count for each row
	int size = matchCount.size();
	auto matchCountIt = matchCount.rbegin();

	// adjust to the starting index
	for( ; matchCountIt != matchCount.rend(); matchCountIt++ ) {

		if( matchCountIt->first == rowId ) {
			break;
		}

		// increament the index to tally with the iterator
		index++;
	}

	while( index < size ) {
		
		// current key
		int currentKey = matchCountIt->first;

		if( (index+1) < size ) {
			// forward the cursor
			std::advance(matchCountIt, 1);
			
			matchCount[currentKey] = matchCountIt->second;
		}
		else if( (size-1) == index ) {
			matchCount.erase(currentKey);

			size = matchCount.size();
		}

		index++;
	}
}

void GameLevel::resetPlayer()
{
	switch( objectType ) {
		case L:
			player = new TetriminoL(this);
			break;
		case J:
			player = new TetriminoJ(this);
			break;
		case O:
			player = new TetriminoO(this);
			break;
		case I:
			player = new TetriminoI(this);
			break;
		case S:
			player = new TetriminoS(this);
			break;
		case Z:
			player = new TetriminoZ(this);
			break;
		case T:
			player = new TetriminoT(this);
			break;
	}

	player->create(shaderAnimation);

	int random = rand()/(RAND_MAX/(6-0));
	objectType = static_cast<ObjectType>(static_cast<int>(random));

	if( next != nullptr ) {
		delete next;
		next = nullptr;
	}

	next = new Preview(objectType);
	next->create(shaderAnimation);
}

void GameLevel::transferBlocks()
{
	if( player == nullptr )
		return;

	list<GameObject*> tmpList = player->getBlocks();

	for (list<GameObject*>::iterator it = tmpList.begin(); it != tmpList.end(); it++) {
		Block *tmp = static_cast<Block*>((GameObject*)*it);
		b2Vec2 mapId = tmp->getMapId();

		// bail if the block has reach the top of edge
		if( mapId.y <= 0 ) {
			setGameOver(true);
		}
		
		scanPosY.push_back(mapId.y);
		Position p(mapId.x, mapId.y);

		// map horizontal count
		matchCount[mapId.y] += 1;
		
		blocks[p] = new Block(*tmp);

		tmp->setDispose(true);
	}

	scanPosY.sort();
	scanPosY.unique();
	
	setScan(true);

	// make sure switch state only execute once
	if( gameOver ) {
		StateController::stateController->switchState(GameOver);
	}
}

void GameLevel::updateScore()
{
	while( increaseScore > 0 ) {
		score->increamentScore();

		increaseScore--;
	}
}

bool GameLevel::validatePosition(Position &position)
{
	gameMapIt = blocks.find({position.x, position.y});
	if (gameMapIt != blocks.end()) {
		return true;
	}

	return false;
}
