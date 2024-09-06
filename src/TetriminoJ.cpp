#include "TetriminoJ.h"


TetriminoJ::TetriminoJ() : Tetrimino()
{
    Position block1(1, -1);
	Position block2(0, 0);
	Position block3(-1, 1);
	Position block4(-2, 0);

	vector<Position> oneBlock;
	oneBlock.push_back(block1);
	oneBlock.push_back(block2);
	oneBlock.push_back(block3);
	oneBlock.push_back(block4);

	rotateMap[ONE] = oneBlock;

	Position twoBlock1(1, 1);
	Position twoBlock2(0, 0);
	Position twoBlock3(-1, -1);
	Position twoBlock4(0, -2);

	vector<Position> twoBlock;
	twoBlock.push_back(twoBlock1);
	twoBlock.push_back(twoBlock2);
	twoBlock.push_back(twoBlock3);
	twoBlock.push_back(twoBlock4);

	rotateMap[TWO] = twoBlock;

	Position threeBlock1(-1, 1);
	Position threeBlock2(0, 0);
	Position threeBlock3(1, -1);
	Position threeBlock4(2, 0);

	vector<Position> threeBlock;
	threeBlock.push_back(threeBlock1);
	threeBlock.push_back(threeBlock2);
	threeBlock.push_back(threeBlock3);
	threeBlock.push_back(threeBlock4);

	rotateMap[THREE] = threeBlock;

	Position fourBlock1(-1, -1);
	Position fourBlock2(0, 0);
	Position fourBlock3(1, 1);
	Position fourBlock4(0, 2);

	vector<Position> fourBlock;
	fourBlock.push_back(fourBlock1);
	fourBlock.push_back(fourBlock2);
	fourBlock.push_back(fourBlock3);
	fourBlock.push_back(fourBlock4);

	rotateMap[FOUR] = fourBlock;
}

TetriminoJ::TetriminoJ(GameLevel* gameLevel) : TetriminoJ()
{
    this->gameLevel = gameLevel;
}


TetriminoJ::~TetriminoJ()
{
	for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		Block* b = static_cast<Block*>((GameObject*)*it);
		
		delete b;
		b = nullptr;
	}

	blocks.clear();
}

bool TetriminoJ::create(unsigned int shader)
{
	bool ret = true;
	GameObject* block = nullptr;

	float renderPosY = 0.f - (BLOCK_HEIGHT * 5);
	float renderPosX = initRenX;
	int mapIdy = -2;
	int mapIdx = 4;
	
	Position testPos(mapIdx, mapIdy);
	
	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);

		p.x = mapIdx;
		p.y = mapIdy;
		p.renX = renderPosX;
		p.renY = renderPosY;
		
		if( idx == 2 ) {
			mapIdx -= 1;
			mapIdy -= 1;

			renderPosX -= BLOCK_WIDTH;
			renderPosY -= BLOCK_HEIGHT;
		}

		// increase render position
		renderPosY += BLOCK_HEIGHT;
		mapIdy++;
		
		block = new Block({ p.renX, p.renY }, b2Vec2((float)p.x, (float)p.y));
		block->create(shader);
		blocks.push_back(block);

		static_cast<Block*>(block)->setMapId({(float)p.x, (float)p.y});

		if (gameLevel->validatePosition(p) == true) {
			return false;
		}
	}

	return ret;
}
