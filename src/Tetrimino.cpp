#include "Tetrimino.h"


Tetrimino::Tetrimino() : delPos(0,0)
{
}

Tetrimino::Tetrimino(ObjectType type) : Tetrimino()
{
	this->type = type;
}

Tetrimino::Tetrimino(GameLevel* gameLevel) : Tetrimino()
{
	this->gameLevel = gameLevel;
}

Tetrimino::~Tetrimino()
{
	// for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
	// 	Block* b = static_cast<Block*>((GameObject*)*it);

	// 	delete b;
	// 	b = nullptr;
	// }

	// blocks.clear();
}

bool Tetrimino::checkCollision(Direction direction)
{
	int forwdX=0, forwdY=0;

	switch( direction ) {
	case Down:
		forwdY = 1;
		break;

	case Left:
		forwdX = -1;
		break;

	case Right:
		forwdX = 1;
		break;
	}

	if( blocks.size() == 0 )
		cout << "debug blocks is empty" << endl;
	
	// check for all block
	for( list<GameObject*>::iterator it=blocks.begin(); it != blocks.end(); it++ ) {
		Block* b = static_cast<Block*>(*it);

		Position search(b->getMapId().x + forwdX, b->getMapId().y + forwdY);
		if( gameLevel->checkBorder(search) ) {
			return true;
		}
	}

	return false;
}

void Tetrimino::deleteBlocks()
{
	blocks.remove_if(isDispose());
}

void Tetrimino::draw()
{
	bool removeBlockFlag = false;
	bool destroy = false;

	if( dispose == true ) {
		return;
	}

    for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		((GameObject*)*it)->draw();

		if (((GameObject*)*it)->getDispose() == true) {

			// only block that trigger by player is called destroy
			// this code must not remove to fix block accidentally deleted when
			// reach on the ground
			// if( static_cast<Block*>((GameObject*)*it)->getTriggerDestroy() == true ) {
			// 	Block *tmp = static_cast<Block*>((GameObject*)*it);
			// 	cout << "debug delete block: " << tmp->getMapId().x << ", " << tmp->getMapId().y << endl;

			// 	delPos.x = tmp->getMapId().x;
			// 	delPos.y = tmp->getMapId().y;

			// 	destroy = true;
			// }

			delete* it;
			
			removeBlockFlag = true;
		}
	}

	if (removeBlockFlag == true) {
		blocks.remove_if(isDispose());
		removeBlockFlag = false;

		// only block that trigger by player require regroup
		if( destroy == true ) {
			// pass in the currect postion of deleted block
			// move down the upper block
			gameLevel->repositionBlock({delPos.x, delPos.y});
			gameLevel->setScan(true);

			destroy = false;
		}

		if( blocks.size() == 0 ) {
			dispose = true;
		}
	}
}

void Tetrimino::rotate()
{
	b2Vec2 direction = { 0.f, 0.f };
	vector<Position> vlist;

	gameLevel->resetIdleCnt();

	if( faceIndex == FOUR )
		faceIndex = ONE;
	else
		faceIndex = static_cast<Face>(static_cast<int>(faceIndex) + 1);

	rotateIt = rotateMap.find(faceIndex);
	if( rotateIt != rotateMap.end() ) {
		vlist = rotateMap[faceIndex];
	}

	int idx = 0;
	for (GameObject *block : blocks) {
		Block *b = static_cast<Block*>((GameObject*)block);

		direction.x = vlist[idx].x * BLOCK_WIDTH; // -0.5f;
		direction.y = vlist[idx].y * BLOCK_HEIGHT; // -0.095f;
		
		b->setPosition({ b->getPosition().x + direction.x, b->getPosition().y + direction.y });
		b->updateObjectPosition(false);
		b->setMapId({ b->getMapId().x + vlist[idx].x, b->getMapId().y + vlist[idx].y });

		idx++;
	}
}

bool Tetrimino::rotateCollision()
{
	b2Vec2 forwardDirection = { 0.f, 0.f };
	int offsetx = 0;
	int offsety = 0;
	vector<Position> vlist;

	Face searchFace = faceIndex;

	if( searchFace == FOUR )
		searchFace = ONE;
	else
		searchFace = static_cast<Face>(static_cast<int>(faceIndex) + 1);

	rotateIt = rotateMap.find(searchFace);
	if( rotateIt != rotateMap.end() )
		vlist = rotateMap[searchFace];

	int idx = 0;
	for (GameObject *block : blocks) {
		Block *b = static_cast<Block*>((GameObject*)block);

		Position search(b->getMapId().x + vlist[idx].x, b->getMapId().y + vlist[idx].y);
		if( gameLevel->checkBorder(search) ) {
			return true;
		}

		idx++;
	}

	return false;
}

void Tetrimino::signalDirection(b2Vec2 direction)
{
	if( blocks.size() == 0 ) 
		return;

	// stop moving down if reach the end of the map
	for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		Block *b = static_cast<Block*>((GameObject*)*it);
		if( b->getMapId().y == MAP_DEPTH_Y ) {
			return;
		}
	}

	gameLevel->resetIdleCnt();
	
	int offsetx = 0;
	int offsety = 0;

	if( direction.x > 0 )
		offsetx = 1;
	else if( direction.x < 0)
		offsetx = -1;
	else if( direction.y > 0 )
		offsety = 1;

	for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		Block *b = static_cast<Block*>((GameObject*)*it);
		b->setPosition({b->getPosition().x + direction.x, b->getPosition().y + direction.y});
		b->updateObjectPosition(false);
		b->setMapId({b->getMapId().x + offsetx, b->getMapId().y + offsety});
	}

	return;
}
