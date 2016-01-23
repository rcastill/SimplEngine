//
// Created by rcastill on 12/18/15.
//

#ifndef PROJECT_STRAT_GRAPHICOBJECT_H
#define PROJECT_STRAT_GRAPHICOBJECT_H

#include <SDL2/SDL_events.h>

class GraphicsEngine;

class GraphicObject
{
public:
    virtual ~GraphicObject();

    void setGraphicsEngine(GraphicsEngine *gfx);

    virtual void init();
    virtual void update(SDL_Event &event);
    virtual void render();

protected:
    GraphicsEngine *gfx;
};

#endif //PROJECT_STRAT_GRAPHICOBJECT_H
