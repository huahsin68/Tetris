#ifndef __TETRIMINOT_J__
#define __TETRIMINOT_J__

#include "Tetrimino.h"


class TetriminoJ : public Tetrimino
{
public:
    TetriminoJ();
    TetriminoJ(GameLevel*);
    virtual ~TetriminoJ();

    virtual bool create(unsigned int);
};


#endif //__TETRIMINOT_J__