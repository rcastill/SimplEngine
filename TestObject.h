//
// Created by rcastill on 12/26/15.
//

#ifndef PROJECT_STRAT_TESTOBJECT_H
#define PROJECT_STRAT_TESTOBJECT_H

#include "GfxSDL2Engine.h"
//#include "GraphicObject.h"
//#include "Texture.h"

class TestObject : public GraphicObject
{
public:
    TestObject();
    ~TestObject();

    void init();
    void render();

private:
    Texture *texture;
};


#endif //PROJECT_STRAT_TESTOBJECT_H
