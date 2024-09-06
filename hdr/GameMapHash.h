#ifndef __GAMEMAPHASH_H__
#define __GAMEMAPHASH_H__

#include "HeaderSymbol.h"


class GameMapHash
{
public:
	size_t operator()(const Position& p) const
	{
		return p.x ^ p.y;
	}
};

#endif // __GAMEMAPHASH_H__