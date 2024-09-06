#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__


#include "HeaderSymbol.h"
#include "Resource.h"
#include "GameObject.h"


class Background : public GameObject
{
public:
    Background();
    virtual ~Background();

    void create(unsigned int);
    void draw();

private:
	Resource* res = nullptr;

};

#endif // __BACKGROUND_H__