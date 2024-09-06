#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "HeaderSymbol.h"
#include "GameObject.h"
#include "Resource.h"
#include "BlockWatcher.h"

class BlockWatcher;

class Block: public GameObject
{
public:
    Block();
    Block(b2Vec2, b2Vec2);
    Block(b2Vec2, glm::vec2);
    Block(b2World*);
	virtual ~Block();

    void create(unsigned int);
    void draw();
    void fall();
    void moveDown();
    void setPosition(b2Vec2);
    void registerWatcher(BlockWatcher *blockWatcher) {
        this->blockWatcher = blockWatcher;
    }


public:
    b2Vec2 getMapId() {
        return mapId;
    }
    void setMapId(b2Vec2 mapId) {
        this->mapId = mapId;
    }


private:
    void setupBlock();


private:
    Resource* res = nullptr;

    float yOffset = 0.095f;
    float animFramePosX = 0.f;

    b2Vec2 mapId = { 0.f, 0.f };
    
    BlockWatcher *blockWatcher = nullptr;

    glm::vec2 scale = glm::vec2{1.f, 1.f};
};

#endif /* __BLOCK_H__ */