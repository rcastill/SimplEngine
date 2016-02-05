//
// Created by rcastill on 12/18/15.
//

#ifndef PROJECT_STRAT_GRAPHICOBJECT_H
#define PROJECT_STRAT_GRAPHICOBJECT_H

#include <SDL2/SDL_events.h>
#include <vector>
#include <cassert>
#include <memory>
#include "Texture.h"
#include "Font.h"
#include "Color.h"
#include "Renderer.h"

class GraphicsEngine;
class GraphicObject;

using namespace std;

typedef vector<shared_ptr<GraphicObject>> GfxObjectVector;
typedef vector<Resource*> RawResourceVector;

struct MouseState
{
    struct
    {
        int x;
        int y;

    } pos;

    bool leftPressed;
    bool middlePressed;
    bool rightPressed;
};

class GraphicObject
{
public:
    GraphicObject();
    virtual ~GraphicObject();

    bool enabled() const;
    void enabled(bool objectEnabled);

    virtual void init();

    virtual void onMouseLeftPressed(int x, int y);
    virtual void onMouseMiddlePressed(int x, int y);
    virtual void onMouseRightPressed(int x, int y);
    virtual void onMouseLeftReleased(int x, int y);
    virtual void onMouseMiddleReleased(int x, int y);
    virtual void onMouseRightReleased(int x, int y);
    virtual void onMouseMotion(int x, int y);
    virtual void onKeyPressed(SDL_Keycode key);
    virtual void onKeyReleased(SDL_Keycode key);
    virtual void onQuit();
    virtual void continuousUpdate(const Uint8 *keyboardPressed, MouseState mouseState);
    virtual void update(SDL_Event &event);

    virtual void render(Renderer &renderer);

    template <typename T, typename... A>
    T *addChild(A... args);

protected:
    Texture *loadTexture(string path);
    void stop();
    Font* loadFont(string path, int size);
    Texture* makeText(Font *font, string text, Color color, FontQuality quality = FQ_LOW, bool unique = true);

    void windowTitle(string wTitle);
    string windowTitle() const;
    int getFps() const;

    double deltaTime() const;
    void deltaTime(double delta);
    int screenWidth();
    int screenHeight();
    void screenSize(int& w, int& h);

    GfxObjectVector children;
    bool objectEnabled;

private:
    friend class GraphicsEngine;
    RawResourceVector resources;
    GraphicsEngine *gfx;

    void unsetGraphicsEngine();
};

#include "GraphicObject.tcc"

#endif //PROJECT_STRAT_GRAPHICOBJECT_H
