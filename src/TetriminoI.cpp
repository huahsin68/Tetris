#include "TetriminoI.h"


TetriminoI::TetriminoI() : Tetrimino()
{
    Position block1(1, 2);
	Position block2(0, 1);
	Position block3(-1, 0);
	Position block4(-2, -1);

	vector<Position> oneBlock;
	oneBlock.push_back(block1);
	oneBlock.push_back(block2);
	oneBlock.push_back(block3);
	oneBlock.push_back(block4);

	rotateMap[ONE] = oneBlock;

	Position twoBlock1(-2, 1);
	Position twoBlock2(-1, 0);
	Position twoBlock3(0, -1);
	Position twoBlock4(1, -2);

	vector<Position> twoBlock;
	twoBlock.push_back(twoBlock1);
	twoBlock.push_back(twoBlock2);
	twoBlock.push_back(twoBlock3);
	twoBlock.push_back(twoBlock4);

	rotateMap[TWO] = twoBlock;

	Position threeBlock1(-1, -2);
	Position threeBlock2(0, -1);
	Position threeBlock3(1, 0);
	Position threeBlock4(2, 1);

	vector<Position> threeBlock;
	threeBlock.push_back(threeBlock1);
	threeBlock.push_back(threeBlock2);
	threeBlock.push_back(threeBlock3);
	threeBlock.push_back(threeBlock4);

	rotateMap[THREE] = threeBlock;

	Position fourBlock1(2, -1);
	Position fourBlock2(1, 0);
	Position fourBlock3(0, 1);
	Position fourBlock4(-1, 2);

	vector<Position> fourBlock;
	fourBlock.push_back(fourBlock1);
	fourBlock.push_back(fourBlock2);
	fourBlock.push_back(fourBlock3);
	fourBlock.push_back(fourBlock4);

	rotateMap[FOUR] = fourBlock;
	
	faceIndex = FOUR;
}

TetriminoI::TetriminoI(GameLevel* gameLevel) : TetriminoI()
{
    this->gameLevel = gameLevel;
}


TetriminoI::~TetriminoI()
{
	for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		Block* b = static_cast<Block*>((GameObject*)*it);

		delete b;
		b = nullptr;
	}

	blocks.clear();
}

bool TetriminoI::create(unsigned int shader)
{
	bool ret = true;
	GameObject* block = nullptr;

	float renderPosY = 0.f - (BLOCK_HEIGHT * 5);
	int mapIdy = -2;
	
	// row zero is reserve
	// start the tetrimino at position 1
	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);

		p.x = 4;
		p.y = mapIdy;
		p.renX = initRenX;
		p.renY = renderPosY;

		block = new Block({ p.renX, p.renY }, b2Vec2((float)p.x, (float)p.y));
		block->create(shader);
		blocks.push_back(block);

		static_cast<Block*>(block)->setMapId({(float)p.x, (float)p.y});

		// increase render position
		renderPosY += BLOCK_HEIGHT;
		mapIdy++;
	}

	if( !ret )
		gameLevel->transferBlocks();

	return ret;
}
