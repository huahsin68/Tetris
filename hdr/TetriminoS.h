#ifndef __TETRIMINOS_L__
#define __TETRIMINOS_L__

#include "Tetrimino.h"


class TetriminoS : public Tetrimino
{
public:
    TetriminoS();
    TetriminoS(GameLevel*);
    virtual ~TetriminoS();

    virtual bool create(unsigned int);
};


#endif //__TETRIMINOS_L__