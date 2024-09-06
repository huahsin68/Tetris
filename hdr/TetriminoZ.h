#ifndef __TETRIMINOZ_L__
#define __TETRIMINOZ_L__

#include "Tetrimino.h"


class TetriminoZ : public Tetrimino
{
public:
    TetriminoZ();
    TetriminoZ(GameLevel*);
    virtual ~TetriminoZ();

    virtual bool create(unsigned int);
};


#endif //__TETRIMINOZ_L__