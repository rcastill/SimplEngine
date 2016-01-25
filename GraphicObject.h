//
// Created by rcastill on 12/18/15.
//

#ifndef PROJECT_STRAT_GRAPHICOBJECT_H
#define PROJECT_STRAT_GRAPHICOBJECT_H

#include <SDL2/SDL_events.h>
#include <vector>
#include <memory>
#include "Texture.h"

class GraphicsEngine;
class GraphicObject;

using namespace std;


typedef vector<shared_ptr<GraphicObject>> GfxObjectVector;
typedef vector<Resource*> RawResourceVector;

class GraphicObject
{
public:
    GraphicObject();
    virtual ~GraphicObject();

    bool enabled() const;
    void enabled(bool objectEnabled);

    virtual void init();
    virtual void update(SDL_Event &event);
    virtual void render();

    template <typename T, typename... A>
    T *addChild(A... args);

    Texture *loadTexture(string path);

protected:
    GfxObjectVector children;
    GraphicsEngine *gfx;
    bool objectEnabled;

private:
    friend class GraphicsEngine;
    RawResourceVector resources;

    void unsetGraphicsEngine();
    bool checkEngine() const;
};

#include "GraphicObject.tcc"

#endif //PROJECT_STRAT_GRAPHICOBJECT_H
