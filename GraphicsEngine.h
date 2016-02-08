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
//#include "GraphicObject.h"
#include "Texture.h"
#include "Font.h"
#include "Renderer.h"
//#include "GraphicObject.h"

/* TODO: Fix font caching (different sizes) */

using namespace std;

class Resource;
class Texture;
class GraphicObject;
struct LayerComparison;

typedef vector<shared_ptr<GraphicObject>> GfxObjectVector;
typedef priority_queue<shared_ptr<GraphicObject>, vector<shared_ptr<GraphicObject> >, LayerComparison> ObjectQueue;
typedef vector<shared_ptr<Resource>> ResourceVector;

struct LayerComparison
{
    bool operator()(const shared_ptr<GraphicObject> &lhs, const shared_ptr<GraphicObject> &rhs);
};

enum RenderLayer
{
    BACKGROUND,
    DEFAULT,
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,
    LAST
};

class GraphicsEngine
{
public:
    struct SDL2Systems
    {
        SDL2Systems();
        ~SDL2Systems();
    };

    GraphicsEngine(string title, int width, int height, double fps = 60);
    GraphicsEngine(int width, int height, double fps = 60);
    ~GraphicsEngine();

    void openWindow();
    void delay(int msecs);

    void setRenderColor(Color color);

    template <typename T, typename... A>
    T *addObject(A... args);

    void windowTitle(string wTitle);
    string windowTitle() const;

    int width() const;
    int height() const;
    void size(int &w, int &h) const;

    Texture *loadTexture(string path);
    Font *loadFont(string path, int size);
    Texture *makeText(Font *font, string text, Color color, FontQuality quality = FQ_LOW, bool unique = true);

    void disposeResource(Resource *resource);

    void triggerUpdateCallbacks();
    void triggerContinuousUpdate();

    double deltaTime() const;
    void deltaTime(double delta);

    /* Updated every second */
    int getFps() const;

    void mainloop();
    void stop();

    void cacheObjects();
    void addToInitQueue(const shared_ptr<GraphicObject> &object);

private:
    Resource *checkResource(string path);
    void cacheResource(shared_ptr<Resource> resource);
    shared_ptr<Texture> makeTexture(string path, SDL_Texture *raw);

    /* Iterates over tree in level order and applies each node with callback if node is
     * enabled */
    void doLevel(function<void(shared_ptr<GraphicObject>&)> callback, bool load, bool ignoreInitRestriction = false);

    void swapQueues();
    bool shouldLoad();

    bool loadObjects;

    ObjectQueue objectQueue1;
    ObjectQueue objectQueue2;
    ObjectQueue *currentQueue;
    ObjectQueue *auxQueue;

    ObjectQueue initQueue;

    unique_ptr<SDL_Window, function<void(SDL_Window*)>> sdlWindow;
    Renderer renderer;
    string wTitle;
    int windowWidth;
    int windowHeight;

    GfxObjectVector gfxObjects;
    ResourceVector resources;
    vector<size_t> availableResIds;

    bool running;
    int loopDelay;

    double delta;
    int fps;
};

#include "GraphicsEngine.tcc"

#endif //PROJECT_STRAT_GRAPHICSENGINE_H
