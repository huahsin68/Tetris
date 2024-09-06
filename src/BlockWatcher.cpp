#include "BlockWatcher.h"

BlockWatcher::BlockWatcher()
{
}

BlockWatcher::BlockWatcher(GameLevel* gameLevel)
{
	this->gameLevel = gameLevel;
}

BlockWatcher::~BlockWatcher()
{
}

void BlockWatcher::purgeBlock()
{
	if( purgeContainer.size() == 0 ) {
		return;
	}

	clearingRow = destroyRow.front();

	Position pos(0, 0);
	pos.y = clearingRow;

	for(int x=0; x<MAP_DEPTH_X; x++ ) {
		pos.x = x;

		auto it = find_if(purgeContainer.begin(), purgeContainer.end(), [&pos](const Position &p) {
			return p == pos;
		});

		if( it != purgeContainer.end() ) {
			gameLevel->repositionBlock((Position)*it);

			purgeContainer.erase(it);
		}
	}

	destroyRow.pop_front();

	if( purgeContainer.size() == 0 ) {
		gameLevel->setDestroyBlock(false);
	}
}

void BlockWatcher::queueRow(int row)
{
	deque<int>::iterator it = find(destroyRow.begin(), destroyRow.end(), row);

	// the row was not found
	if( it == destroyRow.end() ) {
		destroyRow.push_back(row);
	}
}

void BlockWatcher::triggerReposition(Position pos)
{
	purgeContainer.push_back(pos);
}
