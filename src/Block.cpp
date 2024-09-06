#include "Block.h"

Block::Block()
{
    res = new Resource(RES_PATH + "sprites_block.png");
	this->boxCount = 1;
	
    physicProp->name = "BLOCK";
	physicProp->width = 0.045f;
	physicProp->height = 0.045f;

	float xOffset = 0.8f;
	float yOffset = 0.f;

	// top right position
	vertices[0] = -0.92f + xOffset;
	vertices[1] = 1.f - yOffset;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = -0.92f + xOffset;
	vertices[9] = 0.9f - yOffset;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = -1.f + xOffset;
	vertices[17] = 0.9f - yOffset;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = -1.f + xOffset;
	vertices[25] = 1.f - yOffset;
	vertices[26] = 0.f;

	// top right color
	vertices[3] = 1.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	// bottom right color
	vertices[11] = 0.0f;
	vertices[12] = 1.0f;
	vertices[13] = 0.0f;

	// bottom left color
	vertices[19] = 0.0f;
	vertices[20] = 0.0f;
	vertices[21] = 1.0f;

	// top left color
	vertices[27] = 1.0f;
	vertices[28] = 1.0f;
	vertices[29] = 0.0f;
}

Block::Block(b2Vec2 position, b2Vec2 mapId) : Block()
{
	this->mapId = mapId;
	this->scale = glm::vec2(0.6f, 0.7f);

	setPosition(position);
}

Block::Block(b2Vec2 position, glm::vec2 scale) : Block()
{
	this->scale = scale;

	setPosition(position);
}

Block::Block(b2World *physicWorld) : Block()
{
	this->physicWorld = physicWorld;
}

Block::~Block()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Block::create(unsigned int shader)
{
    setupBlock();
	createBuffer();
	CreateTexture(res);

	offsetLocation = glGetUniformLocation(shader, "offset");
	transformLoc = glGetUniformLocation(shader, "transform");    
	transformGameObject = glm::scale(transformGameObject, glm::vec3(scale, 0.0f));
}

void Block::draw()
{
	if (getDispose()) {
		return;
	}
	
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformGameObject));

	if( isTriggerAnimation() == true ) {
		if( animFramePosX >= 0.84f ) {
			setDispose(true);

			blockWatcher->triggerReposition({mapId.x, mapId.y});
		}
		else
			animFramePosX += 0.125f;
	}

	glUniform2f(offsetLocation, animFramePosX, 0.f);

    glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, tex);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Block::fall()
{
	this->setPosition({ this->getPosition().x, this->getPosition().y - 0.05f });

	float yPos = position.y;
	for (int i = 0; i < this->boxCount; i++) {
		translation[i].y = yPos;

		yPos -= yOffset;
	}

	updateObjectPosition(false);
}

void Block::moveDown()
{
	b2Vec2 pos = getPosition();
	pos = {pos.x, pos.y + yOffset};
	setPosition(pos);

	b2Vec2 mapId = getMapId();
	mapId = {mapId.x, mapId.y + 1};
	setMapId(mapId);
}

void Block::setupBlock()
{
	// use the red block
	float x = 0.f;
	float y = 0.3f;
    
	// top right texture coords
	vertices[6] = x + 0.01f;
	vertices[7] = y - 0.04f;

	// bottom right texture coords
	vertices[14] = x + 0.01f;
	vertices[15] = y + 0.17f;

	// bottom left texture coords
	vertices[22] = x + 0.12f;
	vertices[23] = y + 0.17f;

	// top left texture coords
	vertices[30] = x + 0.12f;
	vertices[31] = y - 0.04f;

	// top right position
	vertices[0] = 0.26f + position.x;
	vertices[1] = 1.f - position.y;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = 0.26f + position.x;
	vertices[9] = 0.9f - position.y;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = 0.f + position.x;
	vertices[17] = 0.9f - position.y;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = 0.f + position.x;
	vertices[25] = 1.f - position.y;
	vertices[26] = 0.f;
}

void Block::setPosition(b2Vec2 position)
{
	// top right position
	vertices[0] = 0.26f + position.x;
	vertices[1] = 1.f - position.y;
	vertices[2] = 0.f;

	// bottom right position
	vertices[8] = 0.26f + position.x;
	vertices[9] = 0.9f - position.y;
	vertices[10] = 0.f;

	// bottom left position
	vertices[16] = 0.f + position.x;
	vertices[17] = 0.9f - position.y;
	vertices[18] = 0.f;

	// top left position
	vertices[24] = 0.f + position.x;
	vertices[25] = 1.f - position.y;
	vertices[26] = 0.f;

	this->position = position;
}
