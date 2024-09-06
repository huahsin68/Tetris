#include "Preview.h"

Preview::Preview()
{

}

Preview::Preview(ObjectType objectType)
{
	this->objectType = objectType;
}

Preview::~Preview()
{
    for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		Block* b = static_cast<Block*>((GameObject*)*it);
		delete b;
	}
}

void Preview::create(unsigned int shader)
{
    switch(objectType) {
	case L:
		createL(shader);
		break;
	case J:
		createJ(shader);
		break;
	case O:
		createO(shader);
		break;
	case I:
		createI(shader);
		break;
	case S:
		createS(shader);
		break;
	case Z:
		createZ(shader);
		break;
	case T:
		createT(shader);
		break;
	}
}

void Preview::createI(unsigned int shader)
{
	float renderPosY = -0.365f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = 1.3f;
		p.renY = renderPosY;

        Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

        renderPosY += BLOCK_HEIGHT;
    }
}

void Preview::createJ(unsigned int shader)
{
	float renderPosY = -0.32f;
	float renderPosX = 1.42f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = renderPosX;
		p.renY = renderPosY;

		if( idx == 2 ) {
			renderPosX -= BLOCK_WIDTH;
			renderPosY -= BLOCK_HEIGHT;
		}

        Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

        renderPosY += BLOCK_HEIGHT;
    }
}

void Preview::createL(unsigned int shader)
{
	float renderPosY = -0.32f;
	float renderPosX = 1.17f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = renderPosX;
		p.renY = renderPosY;

        if( idx == 2 ) {
			renderPosX += BLOCK_WIDTH;
			renderPosY -= BLOCK_HEIGHT;
		}

		Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

		renderPosY += BLOCK_HEIGHT;
    }
}

void Preview::createO(unsigned int shader)
{
	float renderPosY = -0.27f;
	float renderPosX = 1.17f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = renderPosX;
		p.renY = renderPosY;

        if( idx == 1 ) {
			renderPosX += BLOCK_WIDTH;
			renderPosY -= (BLOCK_HEIGHT*2);
		}

		Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

		renderPosY += BLOCK_HEIGHT;
    }
}

void Preview::createS(unsigned int shader)
{
	float renderPosY = -0.32f;
	float renderPosX = 1.17f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = renderPosX;
		p.renY = renderPosY;

        if( idx == 1 ) {
			renderPosX += BLOCK_WIDTH;
			renderPosY -= BLOCK_HEIGHT;
		}

		Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

		renderPosY += BLOCK_HEIGHT;
    }
}

void Preview::createT(unsigned int shader)
{
	float renderPosY = -0.32f;
	float renderPosX = 1.18f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = renderPosX;
		p.renY = renderPosY;

        if( idx == 2 ) {
			renderPosX += BLOCK_WIDTH;
			renderPosY -= (BLOCK_HEIGHT*2);
		}

		Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

		renderPosY += BLOCK_HEIGHT;

		cout << "debug Preview: " << p.renX << ", " << p.renY << endl;
    }
}

void Preview::createZ(unsigned int shader)
{
	float renderPosY = -0.32f;
	float renderPosX = 1.42f;

	for( int idx=0; idx<4; idx++ ) {
		Position p(0, 0);
		
		p.renX = renderPosX;
		p.renY = renderPosY;

        if( idx == 1 ) {
			renderPosX -= BLOCK_WIDTH;
			renderPosY -= BLOCK_HEIGHT;
		}

		Block *block = new Block({ p.renX, p.renY }, glm::vec2(0.5f, 0.6f));
		block->create(shader);
		blocks.push_back(block);

		renderPosY += BLOCK_HEIGHT;
    }
}

void Preview::draw()
{
    for (list<GameObject*>::iterator it = blocks.begin(); it != blocks.end(); it++) {
		((GameObject*)*it)->draw();
    }
}