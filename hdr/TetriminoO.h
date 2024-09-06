#ifndef __TETRIMINOT_O__
#define __TETRIMINOT_O__

#include "Tetrimino.h"


class TetriminoO : public Tetrimino
{
public:
    TetriminoO();
    TetriminoO(GameLevel*);
    virtual ~TetriminoO();

    virtual bool create(unsigned int);
};


#endif //__TETRIMINOT_O__