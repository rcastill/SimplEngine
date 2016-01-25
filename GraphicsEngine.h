#ifndef PROJECT_STRAT_GRAPHICSENGINE_H
#define PROJECT_STRAT_GRAPHICSENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>
#include <queue>
#include <vector>
#include <memory>
#include <functional>
#include "Color.h"
#include "GraphicObject.h"
#include "Texture.h"
#include "Font.h"

/* TODO: Fix font caching (different sizes) */

using namespace std;

class Resource;
class Texture;

typedef vector<shared_ptr<GraphicObject>> GfxObjectVector;
typedef queue<shared_ptr<GraphicObject>> ObjectQueue;
typedef vector<shared_ptr<Resource>> ResourceVector;

enum FontQuality
{
    FQ_HIGH,
    FQ_MID,
    FQ_LOW
};

class GraphicsEngine
{
public:
    struct SDL2Systems
    {
        SDL2Systems();
        ~SDL2Systems();
    };

    GraphicsEngine(string title, int width, int height);
    ~GraphicsEngine();

    void openWindow();
    void delay(int msecs);

    void setRenderColor(Color color);

    template <typename T, typename... A>
    T *addObject(A... args);

    int width() const;
    int height() const;
    void size(int &w, int &h) const;

    Texture *loadTexture(string path);
    Font *loadFont(string path, int size);
    Texture *makeText(Font *font, string text, Color color, FontQuality quality = FQ_LOW, bool unique = true);

    void renderTexture(Texture *texture, SDL_Rect dstrect);
    void renderTexture(Texture *texture, int x, int y, int w, int h);
    void renderTexture(Texture *texture, int x, int y);
    void disposeResource(Resource *resource);

    void setLoopDelay(int loopDelay);
    void mainloop();
    void stop();

private:
    Resource *checkResource(string path);
    void cacheResource(shared_ptr<Resource> resource);
    shared_ptr<Texture> makeTexture(string path, SDL_Texture *raw);

    unique_ptr<SDL_Window, function<void(SDL_Window*)>> sdlWindow;
    unique_ptr<SDL_Renderer, function<void(SDL_Renderer*)>> sdlRenderer;
    string windowTitle;
    int windowWidth;
    int windowHeight;

    GfxObjectVector gfxObjects;
    ResourceVector resources;
    vector<ResourceVector::size_type> availableResIds;

    bool running;
    int loopDelay;
};

#include "GraphicsEngine.tcc"

#endif //PROJECT_STRAT_GRAPHICSENGINE_H
