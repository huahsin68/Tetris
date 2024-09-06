#ifndef __BLOCKWATCHER_H__
#define __BLOCKWATCHER_H__


#include "HeaderSymbol.h"
#include "GameLevel.h"

class GameLevel;

class BlockWatcher
{
public:
    BlockWatcher();
    BlockWatcher(GameLevel*);
    virtual ~BlockWatcher();

    void purgeBlock();
    void queueRow(int);
    // void removeRow(int);
    void triggerReposition(Position);


private:
    vector<Position> purgeContainer;

    GameLevel *gameLevel = nullptr;

    deque<int> destroyRow;

    int clearingRow = -1; // indicate no row is being process now
};

#endif // __BLOCKWATCHER_H__