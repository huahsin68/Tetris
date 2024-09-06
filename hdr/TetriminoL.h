#ifndef __TETRIMINOT_L__
#define __TETRIMINOT_L__

#include "Tetrimino.h"


class TetriminoL : public Tetrimino
{
public:
    TetriminoL();
    TetriminoL(GameLevel*);
    virtual ~TetriminoL();

    virtual bool create(unsigned int);
};


#endif //__TETRIMINOT_L__