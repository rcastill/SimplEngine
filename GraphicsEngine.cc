#include "GraphicsEngine.h"

#include <iostream>

GraphicsEngine::GraphicsEngine(string title, int width, int height) :
    windowTitle(title),
    windowWidth(width),
    windowHeight(height),
    running(true)
{
    SDL_Window *tmpWindow = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width, height,
            SDL_WINDOW_HIDDEN
    );

    if (tmpWindow == 0)
        throw runtime_error(SDL_GetError());

    sdlWindow.get_deleter() = [](SDL_Window *w) {
        SDL_DestroyWindow(w);
    };
    sdlWindow.reset(tmpWindow);

    SDL_Renderer *tmpRenderer = SDL_CreateRenderer(sdlWindow.get(), -1, SDL_RENDERER_ACCELERATED);

    if (tmpRenderer == 0)
        throw runtime_error(SDL_GetError());

    sdlRenderer.get_deleter() = [](SDL_Renderer *r) {
        SDL_DestroyRenderer(r);
    };
    sdlRenderer.reset(tmpRenderer);
}

GraphicsEngine::~GraphicsEngine()
{
    for (auto &object : gfxObjects)
        object->unsetGraphicsEngine();

    cout << "~GraphicsEngine" << endl;
}

void GraphicsEngine::openWindow()
{
    SDL_ShowWindow(sdlWindow.get());
}


void GraphicsEngine::delay(int msecs)
{
    SDL_Delay((Uint32) msecs);
}

void GraphicsEngine::setRenderColor(Color color)
{
    SDL_SetRenderDrawColor(
            sdlRenderer.get(),
            color.r(),
            color.g(),
            color.b(),
            color.a()
    );
}

int GraphicsEngine::width() const
{
    return windowWidth;
}

int GraphicsEngine::height() const
{
    return windowHeight;
}

void GraphicsEngine::setLoopDelay(int loopDelay)
{
    this->loopDelay = loopDelay;
}

void GraphicsEngine::mainloop()
{

    SDL_Event event;
    ObjectQueue objectQueue;

    /* Loads queue with initial objects (Root children) */
    auto loadQueue = [&objectQueue, this] () {
        for (auto obj : gfxObjects)
            objectQueue.push(obj);
    };


    /* Iterates over tree in level order and applies each node with callback if node is
     * enabled */
    auto doLevel = [&objectQueue] (function<void(shared_ptr<GraphicObject>&)> callback) {
        while (!objectQueue.empty()) {
            auto object = objectQueue.front();
            objectQueue.pop();

            if (!object->enabled())
                continue;

            callback(object);

            for (auto &child : object->children)
                objectQueue.push(child);
        }

    };

    /* Init objects */
    loadQueue();
    doLevel([this](shared_ptr<GraphicObject> &obj) {
        obj->gfx = this;
        obj->init();
    });

    while (running) {
        SDL_RenderClear(sdlRenderer.get());

        while (SDL_PollEvent(&event) != 0) {
            /* Update objects */
            loadQueue();
            doLevel([&event](shared_ptr<GraphicObject> &obj) {
                obj->update(event);
            });
        }

        /* Render objects */
        loadQueue();
        doLevel([](shared_ptr<GraphicObject> &obj) {
            obj->render();
        });

        SDL_RenderPresent(sdlRenderer.get());
        SDL_Delay((Uint32) loopDelay);
    }
}

void GraphicsEngine::disposeResource(Resource *resource)
{
    if (--(resource->refCount) == 0) {
        availableResIds.push_back(resource->id());
        cout << 1 << endl;
        resources[resource->id()] = 0;
    }
}

Texture *GraphicsEngine::loadTexture(string path)
{
    Resource *rawResource = checkResource(path);
    Texture *foundTexture = dynamic_cast<Texture*>(rawResource);

    if (foundTexture != NULL) {
        foundTexture->retain();
        return foundTexture;
    }

    SDL_Texture *sdlTexture = 0;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL)
        return 0;

    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer.get(), loadedSurface);

    if (sdlTexture == NULL)
        return 0;

    SDL_FreeSurface(loadedSurface);

    auto texture = makeTexture(path, sdlTexture);
    cacheResource(texture);

    return texture.get();
}

Font *GraphicsEngine::loadFont(string path, int size)
{
    Resource *rawResource = checkResource(path);
    Font *foundFont = dynamic_cast<Font*>(rawResource);

    if (foundFont != NULL)
        return foundFont;

    auto font = shared_ptr<Font>(new Font(path, size));

    if (!(font->ttfFont))
        return 0;

    cacheResource(font);

    return font.get();
}

Texture *GraphicsEngine::makeText(Font *font, string text, Color color, FontQuality quality, bool unique)
{
    string path = "text://" + text;

    Resource *rawResource = checkResource(path);
    Texture *foundTexture = dynamic_cast<Texture*>(rawResource);

    if (foundTexture)
        return foundTexture;

    SDL_Surface *surface = NULL;

    if (quality == FQ_LOW)
        surface = TTF_RenderText_Solid(font->ttfFont.get(), text.c_str(), color.getSdlColor());
    else if (quality == FQ_MID)
        surface = TTF_RenderText_Shaded(font->ttfFont.get(), text.c_str(), color.getSdlColor(),
                                        color.negative().getSdlColor());
    else if (quality == FQ_HIGH)
        surface = TTF_RenderText_Blended(font->ttfFont.get(), text.c_str(), color.getSdlColor());
    else
        throw runtime_error("Invalid font quality");

    if (surface == NULL)
        return 0;

    SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer.get(), surface);

    if (sdlTexture == NULL)
        return 0;

    SDL_FreeSurface(surface);

    auto texture = makeTexture(path, sdlTexture);
    texture->unique(unique);
    cacheResource(texture);

    return texture.get();
}

void GraphicsEngine::renderTexture(Texture *texture, SDL_Rect dstrect)
{
    if (!texture)
        throw runtime_error("Could not render texture.");

    SDL_RenderCopy(sdlRenderer.get(),
                   texture->sdlTexture.get(),
                   (texture->fullSource) ? 0 : &(texture->srcrect),
                   &dstrect);
}

void GraphicsEngine::renderTexture(Texture *texture, int x, int y, int w, int h)
{
    SDL_Rect dstrect = {x, y, w, h};
    renderTexture(texture, dstrect);
}

void GraphicsEngine::renderTexture(Texture *texture, int x, int y)
{
    if (!texture)
        throw runtime_error("Could not render texture.");

    int w, h;
    texture->getSize(w, h);
    renderTexture(texture, x, y, w, h);
}

void GraphicsEngine::size(int &w, int &h) const
{
    w = windowWidth;
    h = windowHeight;
}

Resource *GraphicsEngine::checkResource(string path)
{
    for (auto &resource : resources) {
        if (resource && resource->getPath() == path) {
            if (resource->unique())
                return NULL;

            return resource.get();
        }
    }

    return NULL;
}

void GraphicsEngine::cacheResource(shared_ptr<Resource> resource)
{
    if (!availableResIds.empty()) {
        resource->id(availableResIds.back());
        resources[availableResIds.back()] = resource;
        availableResIds.pop_back();

    } else {
        resource->id(resources.size());
        resources.push_back(resource);
    }
}

shared_ptr<Texture> GraphicsEngine::makeTexture(string path, SDL_Texture *raw)
{
    auto texture = make_shared<Texture>(path);
    texture->sdlTexture.reset(raw);
    texture->updateInfo();
    return texture;
}

void GraphicsEngine::stop()
{
    running = false;
}

GraphicsEngine::SDL2Systems::SDL2Systems()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw runtime_error(IMG_GetError());

    if (TTF_Init() < 0)
        throw runtime_error(TTF_GetError());
}

GraphicsEngine::SDL2Systems::~SDL2Systems()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
