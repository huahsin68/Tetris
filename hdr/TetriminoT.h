#ifndef __TETRIMINOT_H__
#define __TETRIMINOT_H__

#include "Tetrimino.h"


class TetriminoT : public Tetrimino
{
public:
    TetriminoT();
    TetriminoT(GameLevel*);
    virtual ~TetriminoT();

    virtual bool create(unsigned int);
};


#endif //__TETRIMINOT_H__