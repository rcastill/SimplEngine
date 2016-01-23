//
// Created by rcastill on 12/27/15.
//

#ifndef PROJECT_STRAT_GAME_H
#define PROJECT_STRAT_GAME_H

#include "GraphicObject.h"
#include "TestObject.h"

class Game : public GraphicObject
{
public:
    void init();
    void update(SDL_Event &event);

private:
    TestObject *stick;
};


#endif //PROJECT_STRAT_GAME_H
