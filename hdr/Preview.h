#ifndef __PREVIEW_H__
#define __PREVIEW_H__

#include "HeaderSymbol.h"
#include "Block.h"

class Preview
{
public:
    Preview();
    Preview(ObjectType);
    virtual ~Preview();
    
    void create(unsigned int);
    void draw();
    

private:
    void createI(unsigned int);
    void createJ(unsigned int);
    void createL(unsigned int);
    void createO(unsigned int);
    void createS(unsigned int);
    void createT(unsigned int);
    void createZ(unsigned int);    


private:
    list<GameObject*> blocks;

    ObjectType objectType;
};

#endif //__PREVIEW_H__