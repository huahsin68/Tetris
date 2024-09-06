#ifndef __TETRIMINO_H__
#define __TETRIMINO_H__

#include "HeaderSymbol.h"
#include "Block.h"
#include "GameLevel.h"

struct isDispose
{
	bool operator() (GameObject* obj)
	{
		return obj->getDispose();
	}
};

class GameLevel;

class Tetrimino
{
public:
    Tetrimino();
    Tetrimino(ObjectType);
    Tetrimino(GameLevel*);
    virtual ~Tetrimino();

    bool checkCollision(Direction);
    virtual bool create(unsigned int) = 0;
    void deleteBlocks();
    void draw();
    void signalDirection(b2Vec2);
    void rotate();
    bool rotateCollision();


public:
    list<GameObject*> getBlocks() {
		return blocks;
	}

    bool getDispose() {
        return dispose;
    }


protected:
    Face faceIndex = ONE;

    unordered_map<Face, vector<Position>> rotateMap;

    list<GameObject*> blocks;

    GameLevel *gameLevel = nullptr;

    int mapIdx = 4;

    float initRenX = -0.65f;
    

private:
    unordered_map<Face, vector<Position>>::iterator rotateIt;

    ObjectType type;

    Position delPos;

    bool dispose = false;

    // boundary of tetrimino
    int right=mapIdx, left=mapIdx, down=0;
};

#endif // __TETRIMINO_H__