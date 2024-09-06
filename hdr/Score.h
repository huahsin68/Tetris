#ifndef __SCORE_H__
#define __SCORE_H__

#include "HeaderSymbol.h"
#include "Resource.h"
#include "GameObject.h"
#include "Text.h"


class Score
{
public:
    Score();
    virtual ~Score();

    void create(unsigned int);
    void draw();
    void increamentScore();


private:
    void updateScore();


public:
	inline void setScore(int score) {
		this->score += score;
	}

	inline int getScore() {
		return score;
	}


private:
    Text *digit1 = nullptr;
    Text *digit2 = nullptr;

    Resource *res = nullptr;

    int score = 0;
};

#endif // __SCORE_H__