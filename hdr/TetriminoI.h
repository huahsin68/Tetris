#ifndef __TETRIMINOI_H__
#define __TETRIMINOI_H__

#include "Tetrimino.h"


class TetriminoI : public Tetrimino
{
public:
    TetriminoI();
    TetriminoI(GameLevel*);
    virtual ~TetriminoI();

    virtual bool create(unsigned int);
};

#endif //__TETRIMINOI_H__